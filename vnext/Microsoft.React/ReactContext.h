#pragma once
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include "Bridge.ReactContext.g.h"
#include <winrt/Windows.Data.Json.h>

namespace winrt::Microsoft::ReactNative::Bridge::implementation {
struct ReactContext : ReactContextT<ReactContext> {
  ReactContext() = default;

  IReactInstance ReactInstance();
};
} // namespace winrt::Microsoft::ReactNative::Bridge::implementation

// namespace winrt::Microsoft::ReactNative::Bridge::factory_implementation
//{
//    struct ReactContext : ReactContextT<ReactContext,
//    implementation::ReactContext>
//    {
//    };
//}
