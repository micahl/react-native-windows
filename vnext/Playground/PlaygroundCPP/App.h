#pragma once
#include "App.xaml.g.h"

#include "MainReactNativeHost.h"

namespace winrt::Playground::implementation
{
    struct App : AppT<App>
    {
        App();

		winrt::Microsoft::React::ReactNativeHost HostCore()
		{
			if (m_host == nullptr)
			{
				m_host = winrt::make<winrt::Playground::implementation::MainReactNativeHost>();
			}

			return m_host;
		}

	private:
		winrt::Playground::MainReactNativeHost m_host{};
    };
}