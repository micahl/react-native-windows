#pragma once

#include "NativeModulesProvider.h"
#include "ViewManagersProvider.h"
#include "ReactNativeHost.h"
#include "ReactInstanceManager.h"

#include <ReactUWP/ReactUwp.h>

namespace react {
	namespace uwp {
		struct IReactInstanceCreator;
		struct IXamlRootView;
	}
}

namespace winrt::Microsoft::React::implementation
{
	void InitReactNative();

	struct ReactInstanceCreator : react::uwp::IReactInstanceCreator
	{
		ReactInstanceCreator(
			std::string jsBundleFile,
			std::string jsMainModuleName,
			std::shared_ptr<NativeModulesProvider> modulesProvider,
			std::shared_ptr<ViewManagersProvider> viewManagersProvider);

		std::string m_jsMainModuleName{};
		std::string m_jsBundleFile{};
		std::shared_ptr<NativeModulesProvider> m_modulesProvider{ nullptr };
		std::shared_ptr<ViewManagersProvider> m_viewManagersProvider{ nullptr };

		std::shared_ptr<react::uwp::IReactInstance> getInstance();
		void markAsNeedsReload();

	private:
		std::shared_ptr<react::uwp::IReactInstance> m_instance;
	};
}