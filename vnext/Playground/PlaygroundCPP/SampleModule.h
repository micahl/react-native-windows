#pragma once
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include "SampleModule.g.h"

using namespace winrt;
using namespace Microsoft::ReactNative;
using namespace Windows::Foundation::Collections;

namespace winrt::Playground::implementation {
struct SampleModule : SampleModuleT<SampleModule> {
  SampleModule() = default;

  hstring Name();
  IMapView<hstring, hstring> Constants();
  IMapView<hstring, MethodDelegate> Methods();
  IMapView<hstring, MethodWithCallbackDelegate> MethodsWithCallback();
};
} // namespace winrt::Playground::implementation

namespace winrt::Playground::factory_implementation {
struct SampleModule
    : SampleModuleT<SampleModule, implementation::SampleModule> {};
} // namespace winrt::Playground::factory_implementation
