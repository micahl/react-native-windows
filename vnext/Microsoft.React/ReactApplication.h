#pragma once

#include "ReactApplication.g.h"
#include "ReactNativeHost.h"

#include <winrt\Windows.UI.Core.h>
#include <winrt\Windows.ApplicationModel.Activation.h>

namespace winrt::Microsoft::ReactNative::implementation
{
    struct ReactApplication : ReactApplicationT<ReactApplication>
    {
		ReactApplication();

		winrt::Microsoft::ReactNative::ReactNativeHost Host();

		virtual winrt::Microsoft::ReactNative::ReactNativeHost HostCore();

        virtual void OnLaunched(Windows::ApplicationModel::Activation::LaunchActivatedEventArgs const&);
		virtual void OnSuspending(IInspectable const&, Windows::ApplicationModel::SuspendingEventArgs const&);
		virtual void OnNavigationFailed(IInspectable const&, Windows::UI::Xaml::Navigation::NavigationFailedEventArgs const&);

	protected:
		virtual winrt::Microsoft::ReactNative::ReactApplicationDelegate __stdcall CreateReactApplicationDelegate()
		{
			return winrt::Microsoft::ReactNative::ReactApplicationDelegate(*this);
		}

	private:
		winrt::Microsoft::ReactNative::ReactNativeHost m_host{ nullptr };
		winrt::Microsoft::ReactNative::ReactApplicationDelegate m_delegate{ nullptr };

		void OnCreate(Windows::ApplicationModel::Activation::LaunchActivatedEventArgs const& e);
    };
}

namespace winrt::Microsoft::ReactNative::factory_implementation
{
    struct ReactApplication : ReactApplicationT<ReactApplication, implementation::ReactApplication>
    {
    };
}
