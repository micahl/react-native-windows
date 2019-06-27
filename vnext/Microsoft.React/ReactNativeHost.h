#pragma once

#include "ReactNativeHost.g.h"
#include "ReactRootView.h"
#include "ReactInstanceManager.h"

#include <ReactUWP/IXamlRootView.h>
#include <ReactUWP/ReactUwp.h>
#include <ReactUWP/IReactInstance.h>

namespace winrt::Microsoft::React::implementation
{
	struct ReactNativeHost : ReactNativeHostT<ReactNativeHost>
	{
		ReactNativeHost();

		UIElement OnCreate();

		winrt::Microsoft::React::ReactInstanceManager ReactInstanceManager();

		void OnSuspend();
		void OnEnteredBackground();
		void OnLeavingBackground();
		void OnResume(OnResumeAction const& action);

		virtual hstring MainComponentName();
		virtual hstring JavaScriptMainModuleName();
		virtual hstring JavaScriptBundleFile();
		virtual bool UseDeveloperSupport();
		virtual Windows::Foundation::Collections::IVectorView<Microsoft::React::IReactPackage> Packages();

		bool HasInstance() { return m_reactInstanceManager != nullptr; }

		hstring get_MainComponentName() { return overridable().MainComponentName(); }
		hstring get_JavaScriptMainModuleName() { return overridable().JavaScriptMainModuleName(); }
		hstring get_JavaScriptBundleFile() { return overridable().JavaScriptBundleFile(); }
		bool get_UseDeveloperSupport() { return overridable().UseDeveloperSupport(); }

		winrt::Windows::Foundation::Collections::IVectorView<winrt::Microsoft::React::IReactPackage> get_Packages() { return overridable().Packages(); }

	private:
		winrt::Microsoft::React::ReactInstanceManager m_reactInstanceManager{ nullptr };
		winrt::hstring m_mainComponentName{};
		winrt::hstring m_javascriptMainModuleName{};

		std::shared_ptr<ReactRootView> m_reactRootView{ nullptr };

		void Init();
		winrt::Microsoft::React::ReactInstanceManager CreateReactInstanceManager();
		std::shared_ptr<ReactRootView> CreateRootView();
	};
}

namespace winrt::Microsoft::React::factory_implementation
{
	struct ReactNativeHost : ReactNativeHostT<ReactNativeHost, implementation::ReactNativeHost>
	{
	};
}
