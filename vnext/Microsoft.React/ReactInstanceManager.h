#pragma once
#include "ReactInstanceManager.g.h"
#include "ReactInit.h"
#include "LifecycleState.h"
#include <ReactUWP/ReactUwp.h>
#include <ReactUWP/IReactInstance.h>
#include <winrt\microsoft.react.h>

namespace winrt::Microsoft::React::implementation
{
	struct ReactInstanceManager : ReactInstanceManagerT<ReactInstanceManager>
	{
		ReactInstanceManager() = default;
		ReactInstanceManager(
			std::string jsBundleFile,
			std::string jsMainModuleName,
			Windows::Foundation::Collections::IVectorView<winrt::Microsoft::React::IReactPackage> &packages,
			bool useDeveloperSupport,
			LifecycleState initialLifecycleState);

		std::shared_ptr<react::uwp::IReactInstanceCreator> InstanceCreator();
		std::shared_ptr<react::uwp::IReactInstance> Instance() { return InstanceCreator()->getInstance(); }

		void OnSuspend();
		void OnEnteredBackground();
		void OnLeavingBackground();
		void OnResume(Microsoft::React::OnResumeAction const& action);

		void OnBackPressed();

	private:
		std::string m_jsBundleFile{};
		std::string m_jsMainModuleName{};
		Windows::Foundation::Collections::IVectorView<winrt::Microsoft::React::IReactPackage> m_packages;
		bool m_useDeveloperSupport;
		std::shared_ptr<NativeModulesProvider> m_modulesProvider{ nullptr };
		std::shared_ptr<ViewManagersProvider> m_viewManagersProvider{ nullptr };


		//	There should be one react instance creator per instance, as it
		//	both holds the current instance and is responsible for creating new
		//	instances on live reload.
		std::shared_ptr<react::uwp::IReactInstanceCreator> m_reactInstanceCreator{ nullptr };
	};
}

namespace winrt::Microsoft::React::factory_implementation
{
	struct ReactInstanceManager : ReactInstanceManagerT<ReactInstanceManager, implementation::ReactInstanceManager>
	{
	};
}
