#pragma once

#include "ReactApplication.g.h"
#include "ReactNativeHost.h"

#include <winrt\Windows.UI.Core.h>
#include <winrt\Windows.ApplicationModel.Activation.h>

namespace winrt::Microsoft::React::implementation
{
    struct ReactApplication : ReactApplicationT<ReactApplication>
    {
		ReactApplication();

		winrt::Microsoft::React::ReactNativeHost Host();

		virtual winrt::Microsoft::React::ReactNativeHost HostCore();

        virtual void OnLaunched(Windows::ApplicationModel::Activation::LaunchActivatedEventArgs const&);
		virtual void OnSuspending(IInspectable const&, Windows::ApplicationModel::SuspendingEventArgs const&);
		virtual void OnNavigationFailed(IInspectable const&, Windows::UI::Xaml::Navigation::NavigationFailedEventArgs const&);

	protected:
		virtual winrt::Microsoft::React::ReactApplicationDelegate __stdcall CreateReactApplicationDelegate()
		{
			return winrt::Microsoft::React::ReactApplicationDelegate(*this);
		}

	private:
		winrt::Microsoft::React::ReactNativeHost m_host{ nullptr };
		winrt::Microsoft::React::ReactApplicationDelegate m_delegate{ nullptr };

		void OnCreate(Windows::ApplicationModel::Activation::LaunchActivatedEventArgs const& e);
    };
}

namespace winrt::Microsoft::React::factory_implementation
{
    struct ReactApplication : ReactApplicationT<ReactApplication, implementation::ReactApplication>
    {
    };
}
