#include "pch.h"
#include "ReactApplicationDelegate.h"
#if __has_include("ReactApplicationDelegate.g.cpp")
#include "ReactApplicationDelegate.g.cpp"
#endif
#include "ReactNativeHost.h"

using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::UI::Xaml;

namespace {

	static void ApplyArguments(winrt::Microsoft::React::ReactNativeHost host, std::wstring arguments)
	{
    //winrt::Microsoft::React::implementation::ReactNativeHost* h = winrt::get_self<winrt::Microsoft::React::implementation::ReactNativeHost>(host);
		if (!arguments.empty() && host.HasInstance())
		{
			// TODO: check for 'remoteDebugging'.  Return if not found.  Otherwise, validate a value is provided and then parse it to set
			// the ReactInstanceManager.DevSupportManager.IsRemoteDebuggingEnabled flag
		}
	}
}

namespace winrt::Microsoft::React::implementation
{
	ReactApplicationDelegate::ReactApplicationDelegate(Application const& application) :
		m_application(application)
	{
		if (application == nullptr)
		{
			throw winrt::hresult_null_argument(); // ArgumentNullException
		}

		m_reactApplication = application.as<IReactApplication>();
		if (m_reactApplication == nullptr)
		{
			throw winrt::hresult_invalid_argument(L"Expected argument to implement 'IReactApplication' interface");
		}

		m_application.Resuming({ this, &ReactApplicationDelegate::OnResuming });
		m_application.Suspending({ this, &ReactApplicationDelegate::OnSuspending });
		m_application.LeavingBackground({ this, &ReactApplicationDelegate::OnLeavingBackground });
		m_application.EnteredBackground({ this, &ReactApplicationDelegate::OnEnteredBackground });
	}

	void ReactApplicationDelegate::OnActivated(winrt::Windows::ApplicationModel::Activation::IActivatedEventArgs const& args)
	{
		switch (args.Kind())
		{
		case ActivationKind::Protocol:
			auto protocolArgs = args.as<IProtocolActivatedEventArgs>();
			//auto uri = protocolArgs.Uri;

			throw winrt::hresult_not_implemented(L"Need to integrate with the Linking module");
			if (args.PreviousExecutionState() != ApplicationExecutionState::Running)
			{
				OutputDebugStringW(L"TODO... Figure out the right activation path for PreviousExecutionState");
				throw winrt::hresult_not_implemented(L"ReactApplicationDelegate.OnActivated doesn't handle PreviousExecutionState other than Running");
			}
			else
			{
				OutputDebugStringW(L"TODO... Figure out the right activation path");
				throw winrt::hresult_not_implemented(L"ReactApplicationDelegate.OnActivated doesn't handle PreviousExecutionState when its Running");
			}
			break;
		}
	}

	// Create the root view for the React app
	UIElement ReactApplicationDelegate::OnCreate(hstring const& arguments)
	{
		auto host = m_reactApplication.Host();
		//auto instanceManager = host.InstanceCreator();
		host.OnResume([=]() {
			m_application.Exit();
			});

		ApplyArguments(host, arguments.c_str());
		return host.OnCreate();
	}

	void ReactApplicationDelegate::OnResuming(IInspectable sender, IInspectable args)
	{
		m_reactApplication.Host().OnResume([=]() {
			m_application.Exit();
		});

		OutputDebugStringW(L"ReactApplicationDelegate::OnResuming");
	}

	void ReactApplicationDelegate::OnSuspending(IInspectable sender, IInspectable args)
	{
		OutputDebugStringW(L"ReactApplicationDelegate::OnSuspending");
		m_reactApplication.Host().OnSuspend();
	}

	void ReactApplicationDelegate::OnLeavingBackground(IInspectable sender, winrt::Windows::ApplicationModel::LeavingBackgroundEventArgs args)
	{
		OutputDebugStringW(L"ReactApplicationDelegate::OnLeavingBackground");
		m_reactApplication.Host().OnLeavingBackground();
	}

	void ReactApplicationDelegate::OnEnteredBackground(IInspectable sender, winrt::Windows::ApplicationModel::EnteredBackgroundEventArgs args)
	{
		OutputDebugStringW(L"ReactApplicationDelegate::OnEnteredBackground");
		m_reactApplication.Host().OnEnteredBackground();
	}
}
