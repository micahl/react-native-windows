// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include "pch.h"
#include "ABIModule.h"
#include "NativeModulesProvider.h"
#include "Promise.h"

namespace winrt::Microsoft::ReactNative::Bridge {

auto ABIModule::getName() -> std::string {
  auto name = m_module.Name();
  return to_string(name);
}

auto ABIModule::getConstants() -> std::map<std::string, folly::dynamic> {
  std::map<std::string, folly::dynamic> constants;
  auto constantsMapView = m_module.Constants();

  for (auto const &pair : constantsMapView) {
    std::string key = to_string(pair.Key());
    folly::dynamic value = ConvertToDynamic(pair.Value());

    constants.emplace(key, value);
  }

  return constants;
}

auto ABIModule::getMethods()
    -> std::vector<facebook::xplat::module::CxxModule::Method> {
  std::vector<facebook::xplat::module::CxxModule::Method> methods;

  // Add methods without callback
  auto methodsMapView = m_module.Methods();

  for (auto pair : methodsMapView) {
    hstring key = pair.Key();
    MethodDelegate method = pair.Value();

    methods.push_back(facebook::xplat::module::CxxModule::Method(
        to_string(key), [this, method](folly::dynamic args) {
          hstring str = to_hstring(folly::toJson(args));
          auto methodArgs =
              single_threaded_vector<IInspectable>({box_value(str)});

          method(methodArgs.GetView());
        }));
  }

  // Add methods with callback
  auto methodsWithCallBackMapView = m_module.MethodsWithCallback();

  for (auto const &pair : methodsWithCallBackMapView) {
    std::string nativeMethodName = to_string(pair.Key());
    MethodWithCallbackDelegate nativeMethod = pair.Value();

    auto methodWithCallback =
        WrapMethodWithCallback(nativeMethodName, nativeMethod);

    methods.push_back(methodWithCallback);
  }

  // Add methods with promise
  auto methodsWithPromiseMapView = m_module.MethodsWithPromise();
  for (auto const &pair : methodsWithPromiseMapView) {
    std::string nativeMethodWithPromiseName = to_string(pair.Key());
    MethodWithPromise nativeMethodWithPromise = pair.Value();

    auto methodWithPromise = WrapMethodWithPromise(
        nativeMethodWithPromiseName, nativeMethodWithPromise);

    methods.push_back(methodWithPromise);
  }

  return methods;
}

auto ABIModule::WrapMethodWithCallback(
    std::string methodName,
    MethodWithCallbackDelegate const& method)
    -> facebook::xplat::module::CxxModule::Method {
  return facebook::xplat::module::CxxModule::Method(
      methodName,
      [this, nativeMethod = std::move(method)](
          folly::dynamic args, Callback jsMethod) {
        std::string strArgs = folly::toJson(args);
        auto strValue = to_hstring(strArgs);
        auto abiParameter =
            single_threaded_vector<IInspectable>({box_value(strValue)});

        auto jsCallbackABI =
            MethodDelegate([jsMethod = std::move(jsMethod)](
                               IVectorView<IInspectable> argValues) {
              // when invoked convert the args and callback to the javascript
              // method
              std::vector<folly::dynamic> args;
              if (argValues != nullptr) {
                for (auto arg : argValues) {
                  auto dynamicObject = ConvertToDynamic(arg);
                  args.push_back(dynamicObject);
                }
              }

              jsMethod(args);
            });

        nativeMethod(abiParameter.GetView(), jsCallbackABI);
      });
}

auto ABIModule::WrapMethodWithPromise(
    std::string methodName,
    MethodWithPromise const& method) -> facebook::xplat::module::CxxModule::Method {
  return facebook::xplat::module::CxxModule::Method(
      methodName,
      [this, method = std::move(method)](
          folly::dynamic args, Callback cbResolve, Callback cbReject) {
        hstring strArgs = to_hstring(folly::toJson(args));
        auto abiParameter =
            single_threaded_vector<IInspectable>({box_value(strArgs)});

        // Create a wrapper for the callback into JS that the native
        // code can invoke.
        auto jsResolveCallback =
            MethodDelegate([cbResolve = std::move(cbResolve)](
                               IVectorView<IInspectable> methodArgs) {
              if (cbResolve == nullptr)
                return;

              if (methodArgs == nullptr || methodArgs.Size() < 1)
                throw hresult_invalid_argument();

              auto object = ConvertToDynamic(methodArgs.GetAt(0));
              cbResolve(std::vector<folly::dynamic>{object});
            });

        auto jsRejectCallback =
            MethodDelegate([cbReject = std::move(cbReject)](
                               IVectorView<IInspectable> methodArgs) {
              if (cbReject == nullptr)
                return;

              std::vector<folly::dynamic> args;
              for (auto arg : methodArgs) {
                auto dynamicObject = ConvertToDynamic(arg);
                args.push_back(dynamicObject);
              }

              cbReject(args);
            });

        auto promise = Promise(jsResolveCallback, jsRejectCallback);

        method(abiParameter.GetView(), promise);
      });
}

} // namespace winrt::Microsoft::ReactNative::Bridge
