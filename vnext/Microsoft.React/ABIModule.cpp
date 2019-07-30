// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include "pch.h"
#include "ABIModule.h"
#include "NativeModulesProvider.h"
#include "Promise.h"

#include <folly/json.h>
#include <ReactUWP/ReactUwp.h>
#include "winrt/Windows.Foundation.h"
#include "winrt/Windows.Foundation.Collections.h"

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

// Convert a WinRT IInspectable into a folly::dynamic object
auto ABIModule::ConvertToDynamic(IInspectable const &object) -> folly::dynamic {
  if (object == nullptr)
    return nullptr;

  auto propValue = object.try_as<IPropertyValue>();
  if (!propValue) {
    auto stringable = object.try_as<IStringable>();
    if (stringable) {
      // This handles types such as the Newtonsoft.Json.Linq.JObject and
      // the Windows.Data.Json.JsonObject.
      auto stringified = to_string(stringable.ToString());
      auto json = folly::parseJson(stringified);
      return json;
    } else {
      throw hresult_invalid_argument(L"Unrecognized argument value type.");
    }
  }

  auto propType = propValue.Type();
  folly::dynamic value;

  switch (propType) {
    case PropertyType::Boolean:
      value = propValue.GetBoolean();
      break;
    case PropertyType::Char16:
      value = propValue.GetChar16();
      break;
    case PropertyType::Double:
      value = propValue.GetDouble();
      break;
    case PropertyType::Int16:
      value = propValue.GetInt16();
      break;
    case PropertyType::Int32:
      value = propValue.GetInt32();
      break;
    case PropertyType::Int64:
      value = propValue.GetInt64();
      break;
    case PropertyType::Single:
      value = propValue.GetSingle();
      break;
    case PropertyType::String: {
      hstring stringValue = propValue.GetString();
      value = to_string(stringValue);
      break;
    }
    case PropertyType::UInt8:
      value = propValue.GetUInt8();
      break;
    case PropertyType::UInt16:
      value = propValue.GetUInt16();
      break;
    case PropertyType::UInt32:
      value = propValue.GetUInt32();
      break;
    case PropertyType::UInt64:
      value = propValue.GetUInt64();
      break;

    // ARRAYS
    case PropertyType::BooleanArray: {
      com_array<bool> tmpArray;
      propValue.GetBooleanArray(tmpArray);
      folly::dynamic d(tmpArray.begin(), tmpArray.end());
      value = d;
      break;
    }
    case PropertyType::Char16Array: {
      com_array<char16_t> tmpArray;
      propValue.GetChar16Array(tmpArray);
      folly::dynamic d(tmpArray.begin(), tmpArray.end());
      value = d;
      break;
    }
    case PropertyType::DoubleArray: {
      com_array<double_t> tmpArray;
      propValue.GetDoubleArray(tmpArray);
      folly::dynamic d(tmpArray.begin(), tmpArray.end());
      value = d;
      break;
    }
    case PropertyType::InspectableArray: {
      com_array<IInspectable> tmpArray;
      propValue.GetInspectableArray(tmpArray);
      folly::dynamic d = folly::dynamic::array;
      for (auto inspectable : tmpArray) {
        d.push_back(ConvertToDynamic(inspectable));
      }
      value = d;
      break;
    }
    case PropertyType::Int16Array: {
      com_array<int16_t> tmpArray;
      propValue.GetInt16Array(tmpArray);
      folly::dynamic d(tmpArray.begin(), tmpArray.end());
      value = d;
      break;
    }
    case PropertyType::Int32Array: {
      com_array<int32_t> tmpArray;
      propValue.GetInt32Array(tmpArray);
      folly::dynamic d(tmpArray.begin(), tmpArray.end());
      value = d;
      break;
    }
    case PropertyType::Int64Array: {
      com_array<int64_t> tmpArray;
      propValue.GetInt64Array(tmpArray);
      folly::dynamic d(tmpArray.begin(), tmpArray.end());
      value = d;
      break;
    }
    case PropertyType::SingleArray: {
      com_array<float> tmpArray;
      propValue.GetSingleArray(tmpArray);
      folly::dynamic d(tmpArray.begin(), tmpArray.end());
      value = d;
      break;
    }
    case PropertyType::StringArray: {
      com_array<hstring> tmpArray;
      propValue.GetStringArray(tmpArray);
      folly::dynamic d = folly::dynamic::array;
      for (auto strItem : tmpArray) {
        d.push_back(to_string(strItem));
      }
      value = d;
      break;
    }
    case PropertyType::UInt8Array: {
      com_array<uint8_t> tmpArray;
      propValue.GetUInt8Array(tmpArray);
      folly::dynamic d(tmpArray.begin(), tmpArray.end());
      value = d;
      break;
    }
    case PropertyType::UInt16Array: {
      com_array<uint16_t> tmpArray;
      propValue.GetUInt16Array(tmpArray);
      folly::dynamic d(tmpArray.begin(), tmpArray.end());
      value = d;
      break;
    }
    case PropertyType::UInt32Array: {
      com_array<uint32_t> tmpArray;
      propValue.GetUInt32Array(tmpArray);
      folly::dynamic d(tmpArray.begin(), tmpArray.end());
      value = d;
      break;
    }
    case PropertyType::UInt64Array: {
      com_array<uint64_t> tmpArray;
      propValue.GetUInt64Array(tmpArray);
      folly::dynamic d(tmpArray.begin(), tmpArray.end());
      value = d;
      break;
    }
    default:
      wchar_t buf[512];
      swprintf(
          buf,
          sizeof(buf),
          L"Unrecognized argument value type: %d\n",
          propType);
      throw hresult_invalid_argument(buf);
  }

  return value;
}

} // namespace winrt::Microsoft::ReactNative::Bridge::implementation
