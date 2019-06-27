#pragma once

#include "ReactApplication.h"
#include "ReactUWP.ReactApplicationDelegate.g.h"

using namespace winrt::Windows::UI::Xaml;
using namespace winrt::Windows::ApplicationModel;
using namespace winrt::Windows::ApplicationModel::Activation;

namespace winrt::ReactUWP::implementation
{
    struct ReactApplicationDelegate : ReactApplicationDelegateT<ReactApplicationDelegate>
    {
		ReactApplicationDelegate() = default;
		ReactApplicationDelegate(Application const& application);

		//void OnActivated(winrt::Windows::ApplicationModel::Activation::IActivatedEventArgs const& args);
		UIElement OnCreate(hstring const& args);

	private:
		Application m_application{ nullptr };
		winrt::ReactUWP::IReactApplication m_reactApplication{ nullptr };

		void OnResuming(IInspectable sender, IInspectable args);
		void OnSuspending(IInspectable sender, IInspectable args);
		void OnLeavingBackground(IInspectable sender, winrt::Windows::ApplicationModel::LeavingBackgroundEventArgs args);
		void OnEnteredBackground(IInspectable sender, winrt::Windows::ApplicationModel::EnteredBackgroundEventArgs args);
    };
}

namespace winrt::ReactUWP::factory_implementation
{
    struct ReactApplicationDelegate : ReactApplicationDelegateT<ReactApplicationDelegate, implementation::ReactApplicationDelegate>
    {
    };
}
