#pragma once
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include "ReactSupport.h"
#include <winrt/Microsoft.ReactNative.h>

namespace winrt::Microsoft::ReactNative::Bridge {
  using namespace winrt;
  using namespace Windows::Foundation;
  using namespace Windows::Foundation::Collections;

  // This is the module that knows how to translate across the ABI
  // boundary between the native core and the language projections
  // based on WinRT such that someone can author a native
  // module using any of the supported language projections (e.g. C#,
  // C++/CX, or C++/winrt).
  // TODO: Currently the arguments coming from the JavaScript side
  // are given to the native method as an object array of size 1 that
  // is a string containing the JSON representation.
class ABIModule : public facebook::xplat::module::CxxModule {
 public:
  ABIModule(INativeModule const &module)
      : m_module(module) {
    assert(module != nullptr);
  }

  std::string getName() override;
  std::map<std::string, folly::dynamic> getConstants() override;
  std::vector<facebook::xplat::module::CxxModule::Method> getMethods() override;

 private:
  INativeModule m_module{nullptr};

  // TODO: should implement a ConvertToIInspectable(folly::dynamic object) and use it

  facebook::xplat::module::CxxModule::Method
  WrapMethodWithCallback(std::string methodName, MethodWithCallbackDelegate const& method);

  facebook::xplat::module::CxxModule::Method
  WrapMethodWithPromise(std::string methodName, MethodWithPromise const& method);
};

} // namespace winrt::Microsoft::ReactNative::Bridge
