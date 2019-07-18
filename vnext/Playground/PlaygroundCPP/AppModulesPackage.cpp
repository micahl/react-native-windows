// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include "pch.h"
#include "AppModulesPackage.h"
#if __has_include("AppModulesPackage.g.cpp")
#include "AppModulesPackage.g.cpp"
#endif

#include "SampleModule.h"

using namespace winrt;
using namespace Microsoft::ReactNative;
using namespace Windows::UI::Xaml;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;

namespace winrt::Playground::implementation {
IVectorView<INativeModule> AppModulesPackage::CreateNativeModules(
    ReactContext const &reactContext) {
  auto modules = single_threaded_vector<INativeModule>({
      winrt::make<SampleModule>(),
  });

  return modules.GetView();
}
} // namespace winrt::Playground::implementation
