#pragma once

#include "ReactRootView.g.h"

#include <ViewManagerProvider.h>

#include <ReactUWP/IXamlRootView.h>
#include <ReactUWP/ReactUwp.h>
#include <ReactUWP/IReactInstance.h>
//#include <winrt/microsoft.react.h>

#include "ReactInstanceManager.h"
#include "ReactNativeHost.h"
#include "ReactApplication.h"

namespace winrt::Microsoft::React::implementation
{
	//std::shared_ptr<react::uwp::IXamlRootView>
	//StartReactApplication(
	//	Windows::UI::Xaml::Controls::Grid const& grid,
	//	ReactNativeHost host,
	//	const std::shared_ptr<react::uwp::IReactInstanceCreator>& instanceCreator,
	//	folly::dynamic initialProps);


    struct ReactRootView : ReactRootViewT<ReactRootView>
    {
        ReactRootView() = default;

		void OnCreate(winrt::Microsoft::React::ReactNativeHost const& host);
		void StartReactApplication(
			winrt::Microsoft::React::ReactInstanceManager const& instanceManager,
			winrt::hstring componentName,
			folly::dynamic initialProps);

	private:
		std::shared_ptr<react::uwp::IXamlRootView> m_xamlView;
		winrt::hstring m_moduleName{};
		folly::dynamic m_initialProps{};
		winrt::Microsoft::React::ReactInstanceManager m_reactInstanceManager{};

		static void OnBackRequested(
			winrt::Microsoft::React::ReactNativeHost const& host,
			IInspectable sender,
			winrt::Windows::UI::Core::BackRequestedEventArgs e);

		//IAsyncAction StartReactApplicationAsync(
		//	ReactInstanceManager const& instanceManager,
		//	winrt::hstring componentName,
		//	folly::dynamic initialProps);
    };
}

namespace winrt::Microsoft::React::factory_implementation
{
    struct ReactRootView : ReactRootViewT<ReactRootView, implementation::ReactRootView>
    {
    };
}
