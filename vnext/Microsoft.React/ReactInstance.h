#pragma once
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include "Bridge.ReactInstance.g.h"

#include <ReactUWP/IReactInstance.h>
#include <winrt/Microsoft.ReactNative.h>

namespace winrt::Microsoft::ReactNative::Bridge::implementation {
using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;

struct ReactInstance : ReactInstanceT<ReactInstance> {
  ReactInstance() = default;
  ReactInstance(std::shared_ptr<react::uwp::IReactInstance> instance)
      : m_instance(instance) {
    if (instance == nullptr) {
      throw hresult_null_argument(L"instance");
    }
  }

  IIterable<INativeModule> NativeModules() {
    return nullptr;
  };
  void InvokeFunction(
      hstring const& moduleName,
      hstring const& method,
      IVectorView<IInspectable> const& arguments);
  void InvokeCallback(int callbackId, IVectorView<IInspectable> const& arguments);

 private:
  std::shared_ptr<react::uwp::IReactInstance> m_instance{};
};
} // namespace winrt::Microsoft::ReactNative::Bridge::implementation

namespace winrt::Microsoft::ReactNative::Bridge::factory_implementation {
struct ReactInstance
    : ReactInstanceT<ReactInstance, implementation::ReactInstance> {};
} // namespace winrt::Microsoft::ReactNative::Bridge::factory_implementation
