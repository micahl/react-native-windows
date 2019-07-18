#pragma once

#include "AppModulesPackage.g.h"

using namespace winrt;
using namespace Microsoft::ReactNative;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;

namespace winrt::Playground::implementation {
struct AppModulesPackage : AppModulesPackageT<AppModulesPackage> {
  AppModulesPackage() = default;

  IVectorView<INativeModule> CreateNativeModules(
      ReactContext const &reactContext);
};
} // namespace winrt::Playground::implementation

namespace winrt::Playground::factory_implementation {
struct AppModulesPackage
    : AppModulesPackageT<AppModulesPackage, implementation::AppModulesPackage> {
};
} // namespace winrt::Playground::factory_implementation
