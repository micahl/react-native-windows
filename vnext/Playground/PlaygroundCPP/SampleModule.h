#pragma once
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include "winrt\Microsoft.ReactNative.Bridge.h"

namespace winrt::Playground::implementation {

using namespace winrt;
using namespace Microsoft::ReactNative;
using namespace Microsoft::ReactNative::Bridge;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;

struct SampleModule
    : implements<SampleModule, Microsoft::ReactNative::Bridge::INativeModule> {
  SampleModule() = default;

  void method3(
      IVectorView<IInspectable> const &args,
      MethodDelegate const &callback);

  hstring Name();
  IMapView<hstring, IInspectable> Constants();
  IMapView<hstring, MethodDelegate> Methods();
  IMapView<hstring, MethodWithCallbackDelegate> MethodsWithCallback();
  IMapView<hstring, MethodWithPromise> MethodsWithPromise();
};
} // namespace winrt::Playground::implementation
