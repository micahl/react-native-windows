#pragma once
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include "ReactContext.g.h"
#include <winrt/Windows.Data.Json.h>

namespace winrt::Microsoft::ReactNative::implementation {
struct ReactContext : ReactContextT<ReactContext> {
  ReactContext() = default;

  Microsoft::ReactNative::IReactInstance ReactInstance();
};
} // namespace winrt::Microsoft::ReactNative::implementation

// namespace winrt::Microsoft::ReactNative::factory_implementation
//{
//    struct ReactContext : ReactContextT<ReactContext,
//    implementation::ReactContext>
//    {
//    };
//}
