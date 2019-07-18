// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include "pch.h"
#include "ABIModule.h"
#include <ReactUWP/ReactUwp.h>
#include "NativeModulesProvider.h"

#include <folly/json.h>
#include <windows.foundation.h>
#include "winrt\Windows.Foundation.Collections.h"
#include "winrt\Windows.Foundation.h"

std::string ABIModule::getName() {
  auto name = m_module.Name();

  return winrt::to_string(name);
}

std::map<std::string, folly::dynamic> ABIModule::getConstants() {
  using namespace winrt::Windows::Foundation;
  using namespace winrt::Windows::Foundation::Collections;

  auto constantsMapView = m_module.Constants();
  auto constantsIter = constantsMapView.First();

  std::map<std::string, folly::dynamic> ret;
  boolean hasCurrent;

  do {
    hasCurrent = constantsIter.HasCurrent();

    if (!hasCurrent)
      break;

    auto pair = constantsIter.Current();

    winrt::hstring key, value;
    key = pair.Key();
    value = pair.Value();

    ret.emplace(
        winrt::to_string(key), folly::parseJson(winrt::to_string(value)));
    constantsIter.MoveNext();
  } while (hasCurrent);

  return ret;
}

std::vector<facebook::xplat::module::CxxModule::Method>
ABIModule::getMethods() {
  using namespace ABI::Windows::Foundation;
  using namespace ABI::Windows::Foundation::Collections;

  std::vector<facebook::xplat::module::CxxModule::Method> ret;
  boolean hasCurrent;

  // Add methods without callback
  auto methodsMapView = m_module.Methods();
  auto methodsIter = methodsMapView.First();

  do {
    hasCurrent = methodsIter.HasCurrent();

    if (!hasCurrent)
      break;

    auto pair = methodsIter.Current();

    winrt::hstring key;
    winrt::Microsoft::ReactNative::MethodDelegate value;
    key = pair.Key();
    value = pair.Value();

    ret.push_back(facebook::xplat::module::CxxModule::Method(
        winrt::to_string(key), [this, value](folly::dynamic args) {
          std::string str = folly::toJson(args);

          winrt::hstring para = winrt::to_hstring(str);
          value(para);
        }));

    methodsIter.MoveNext();

  } while (hasCurrent);

  // Add methods with callback

  auto methodsWithCallBackMapView = m_module.MethodsWithCallback();
  auto methodsWithCallBackIter = methodsWithCallBackMapView.First();

  do {
    if (!methodsWithCallBackIter.HasCurrent())
      break;

    auto pair = methodsWithCallBackIter.Current();

    winrt::hstring key;
    winrt::Microsoft::ReactNative::MethodWithCallbackDelegate abiCallback;
    key = pair.Key();
    abiCallback = pair.Value();

    ret.push_back(facebook::xplat::module::CxxModule::Method(
        winrt::to_string(key),
        [this, abiCallback = std::move(abiCallback)](
            folly::dynamic args, Callback cbSuccess, Callback cbFail) {
          // TODO: When to call the cbFail?  It's included in the Method
          // construction above so that we use the right template and have
          // everything work correctly across the bridge.  If not included then
          // things don't appear to get set up correctly.  I've seen the result
          // be that it causes the callback ID to end up being the value of a
          // parameter.
          std::string jsonArgs = folly::toJson(args);
          winrt::hstring abiParameter = winrt::to_hstring(jsonArgs);

          auto callback = winrt::Microsoft::ReactNative::MethodCallback(
              [cbSuccess = std::move(cbSuccess)](
                  winrt::Windows::Foundation::Collections::IVectorView<
                      winrt::hstring> argVectorView) {
                std::vector<folly::dynamic> args;

                if (argVectorView != nullptr) {
                  unsigned int size = argVectorView.Size();

                  for (unsigned int i = 0; i < size; i++) {
                    winrt::hstring itemString;
                    itemString = argVectorView.GetAt(i);
                    if (itemString.empty())
                      args.push_back(nullptr);
                    else
                      args.push_back(
                          folly::parseJson(winrt::to_string(itemString)));
                  }
                }

                cbSuccess(args);
              });

          abiCallback(abiParameter, callback);
        }));

    methodsWithCallBackIter.MoveNext();
  } while (true);

  return ret;
}
