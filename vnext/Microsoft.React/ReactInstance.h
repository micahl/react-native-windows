#pragma once
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include "Bridge.ReactInstance.g.h"

#include <winrt/Microsoft.ReactNative.h>

namespace winrt::Microsoft::ReactNative::Bridge::implementation {
  using namespace winrt;
  using namespace Windows::Foundation;
  using namespace Windows::Foundation::Collections;

  struct ReactInstance : ReactInstanceT<ReactInstance> {
    ReactInstance() = default;
    IIterable<INativeModule> NativeModules() {
      return nullptr;
    };
    void InvokeFunction(
        hstring moduleName,
        hstring method,
        IVectorView<IInspectable> arguments,
        hstring tracingName);
    void InvokeCallback(int callbackId, IVectorView<IInspectable> arguments);
  };
} // namespace winrt::Microsoft::ReactNative::Bridge::implementation

// namespace winrt::Microsoft::ReactNative::Bridge::factory_implementation
//{
//    struct ReactInstance : ReactInstanceT<ReactInstance,
//    implementation::ReactInstance>
//    {
//    };
//}
