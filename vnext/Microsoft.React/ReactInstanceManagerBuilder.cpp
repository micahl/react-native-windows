#include "pch.h"
#include "ReactInstanceManagerBuilder.h"

using namespace winrt::Microsoft::ReactNative;

namespace winrt::Microsoft::ReactNative::implementation
{
	winrt::Microsoft::ReactNative::ReactInstanceManager ReactInstanceManagerBuilder::Build()
	{
		if (!m_isLifecycleStateSet)
		{
			throw winrt::hresult_invalid_operation(L"Initial lifecycle state was not set.");
		}

		if (!m_useDeveloperSupport && m_jsBundleFile.empty())
		{
			throw winrt::hresult_invalid_operation(L"JavaScriptBundleFile must be provided when UseDeveloperSupport is false.");
		}

		if (m_jsBundleFile.empty() && m_jsMainModuleName.empty())
		{
			throw new winrt::hresult_invalid_operation(L"Either MainModulePath or the JavaScriptBundleFile must be provided.");
		}

		auto instanceManager = winrt::make<ReactInstanceManager>(
			winrt::to_string(m_jsBundleFile),
			winrt::to_string(m_jsMainModuleName),
			m_packages,
			m_useDeveloperSupport,
			m_initialLifecycleState);
		return instanceManager;
	}
}
