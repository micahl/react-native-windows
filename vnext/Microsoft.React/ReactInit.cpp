/********************************************************************************
	ReactInit.cpp

	Copyright (c) Microsoft Corporation. All rights reserved.
 ********************************************************************************/
#include "pch.h"
#include "ReactInit.h"
#include <ReactUWP/ReactUwp.h>
#include <ReactUWP/IXamlRootView.h>

using namespace winrt;
using namespace winrt::Windows::UI::Xaml;

namespace winrt::Microsoft::React::implementation
{
	/*-------------------------------------------------------------------------------
		winrt::Microsoft::React::implementation::InitReactNative
	-------------------------------------------------------------------------------*/
	void InitReactNative()
	{
#if _DEBUG
		facebook::react::InitializeLogging([](facebook::react::RCTLogLevel /*logLevel*/, const char* message) {
			std::string str = std::string("React:") + message;
			OutputDebugStringA(str.c_str());
		});
#endif
	}

	ReactInstanceCreator::ReactInstanceCreator(
		std::string jsBundleFile,
		std::string jsMainModuleName,
		std::shared_ptr<NativeModulesProvider> modulesProvider,
		std::shared_ptr<ViewManagersProvider> viewManagersProvider)
		: m_jsBundleFile(jsBundleFile), m_jsMainModuleName(jsMainModuleName), m_modulesProvider(modulesProvider), m_viewManagersProvider(viewManagersProvider)
	{
		if (modulesProvider == nullptr)
		{
			throw winrt::hresult_null_argument(L"modulesProvider");
		}

		if (viewManagersProvider == nullptr)
		{
			throw winrt::hresult_null_argument(L"viewManagersProvider");
		}
	}

	std::shared_ptr<react::uwp::IReactInstance> ReactInstanceCreator::getInstance()
	{
		if (m_instance)
			return m_instance;

		std::shared_ptr<react::uwp::IReactInstance> reactInstance = react::uwp::CreateReactInstance(m_modulesProvider, m_viewManagersProvider);

		react::uwp::ReactInstanceSettings settings;
		settings.UseWebDebugger = true;
		settings.UseLiveReload = true;

		reactInstance->Start(reactInstance, settings);

		if (m_jsBundleFile.empty())
		{
			if (!m_jsMainModuleName.empty())
			{
				m_jsBundleFile = m_jsMainModuleName;
			}
			else
			{
				m_jsBundleFile = "App.windows";
			}
		}

		reactInstance->loadBundle(std::move(m_jsBundleFile));

		m_instance = reactInstance;
		return m_instance;
	}

	void ReactInstanceCreator::markAsNeedsReload()
	{
		m_instance->SetAsNeedsReload();
		m_instance = nullptr;
	}
}