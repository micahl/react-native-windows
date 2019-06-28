#pragma once

#include "MainReactNativeHost.g.h"
#include "AppModulesPackage.h"

using namespace winrt;
using namespace Microsoft::ReactNative;
using namespace Windows::Foundation::Collections;

namespace winrt::Playground::implementation
{
  struct MainReactNativeHost : MainReactNativeHostT<MainReactNativeHost>
  {
    MainReactNativeHost() = default;

    hstring MainComponentName() { return L"Playground"; };
    hstring JavaScriptMainModuleName() { return L"Playground/index.uwp"; };
    bool UseDeveloperSupport() { return TRUE; };
    IVectorView<IReactPackage> Packages()
    {
      auto packages = single_threaded_vector<IReactPackage>(
        {
          winrt::make<AppModulesPackage>()
        });
      return packages.GetView();
    };
  };
}

namespace winrt::Playground::factory_implementation
{
  struct MainReactNativeHost : MainReactNativeHostT<MainReactNativeHost, implementation::MainReactNativeHost>
  {
  };
}
