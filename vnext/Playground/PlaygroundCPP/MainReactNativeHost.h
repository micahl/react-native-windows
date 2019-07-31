#pragma once
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include "MainReactNativeHost.g.h"
#include "AppModulesPackage.h"

using namespace winrt;
using namespace Microsoft::ReactNative;
using namespace Windows::Foundation::Collections;

namespace winrt::Playground::implementation {
struct MainReactNativeHost : MainReactNativeHostT<MainReactNativeHost> {
  MainReactNativeHost() = default;

  hstring MainComponentName() {
    return L"Playground";
  };
  hstring JavaScriptMainModuleName() {
    return L"Playground/index.uwp";
  };
  bool UseDeveloperSupport() {
    return TRUE;
  };
  IVectorView<IReactPackage> Packages() {
    auto packages = single_threaded_vector<IReactPackage>(
        {winrt::make<AppModulesPackage>()});
    return packages.GetView();
  };
  ReactInstanceSettings InstanceSettings() {
    auto settings = ReactInstanceSettings();
#if DEBUG
    settings.UseLiveReload(true); // true by default in debug builds already
    settings.UseWebDebugger(true); // true by default in debug builds already
#endif
    settings.UseJsi(true);
    return settings;
  };
};
} // namespace winrt::Playground::implementation

namespace winrt::Playground::factory_implementation {
struct MainReactNativeHost : MainReactNativeHostT<
                                 MainReactNativeHost,
                                 implementation::MainReactNativeHost> {};
} // namespace winrt::Playground::factory_implementation
