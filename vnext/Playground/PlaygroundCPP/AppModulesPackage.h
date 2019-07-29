#pragma once
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include "AppModulesPackage.g.h"

using namespace winrt;
using namespace Microsoft::ReactNative;
using namespace Microsoft::ReactNative::Bridge;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;

namespace winrt::Playground::implementation {
struct AppModulesPackage : AppModulesPackageT<AppModulesPackage> {
  AppModulesPackage() = default;

  IVectorView<INativeModule> CreateNativeModules(ReactContext const &reactContext);
};
} // namespace winrt::Playground::implementation

namespace winrt::Playground::factory_implementation {
struct AppModulesPackage
    : AppModulesPackageT<AppModulesPackage, implementation::AppModulesPackage> {
};
} // namespace winrt::Playground::factory_implementation
