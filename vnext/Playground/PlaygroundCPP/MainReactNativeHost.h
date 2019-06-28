#pragma once

#include "MainReactNativeHost.g.h"

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
		IVectorView<IReactPackage> Packages() { return single_threaded_vector<IReactPackage>().GetView(); };
    };
}

namespace winrt::Playground::factory_implementation
{
    struct MainReactNativeHost : MainReactNativeHostT<MainReactNativeHost, implementation::MainReactNativeHost>
    {
    };
}
