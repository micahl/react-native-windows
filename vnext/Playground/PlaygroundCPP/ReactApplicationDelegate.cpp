#include "pch.h"
#include "ReactApplicationDelegate.h"
#if __has_include("ReactUWP.ReactApplicationDelegate.g.cpp")
#include "ReactUWP.ReactApplicationDelegate.g.cpp"
#endif

#include <winrt/coroutine.h>

using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::UI::Xaml;

namespace {
    inline constexpr hresult error_null_argument{ static_cast<hresult>(0x80004003) }; // ArgumentNullException

    struct hresult_null_argument : hresult_error
    {
        hresult_null_argument() noexcept : hresult_error(error_null_argument) {}
        hresult_null_argument(param::hstring const& message) noexcept : hresult_error(error_null_argument, message) {}
        hresult_null_argument(take_ownership_from_abi_t) noexcept : hresult_error(error_null_argument, take_ownership_from_abi) {}
    };

	static void ApplyArguments(winrt::ReactUWP::ReactNativeHost host, std::wstring arguments)
	{
		winrt::ReactUWP::implementation::ReactNativeHost* h = winrt::get_self<winrt::ReactUWP::implementation::ReactNativeHost>(host);
		//if (!arguments.empty() && h->HasInstance())
		//{
		//	// TODO: check for 'remoteDebugging'.  Return if not found.  Otherwise, validate a value is provided and then parse it to set 
		//	// the ReactInstanceManager.DevSupportManager.IsRemoteDebuggingEnabled flag
		//}
	}

}

namespace winrt::ReactUWP::implementation
{
    //int32_t ReactApplicationDelegate::MyProperty()
    //{
    //    throw hresult_not_implemented();
    //}

    //void ReactApplicationDelegate::MyProperty(int32_t /*value*/)
    //{
    //    throw hresult_not_implemented();
    //}

	ReactApplicationDelegate::ReactApplicationDelegate(Application const& application) :
		m_application(application)
	{
		if (application == nullptr)
		{
			throw hresult_null_argument(); // ArgumentNullException
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

	//void ReactApplicationDelegate::OnActivated(winrt::Windows::ApplicationModel::Activation::IActivatedEventArgs const& args)
	//{
	//	switch (args.Kind())
	//	{
	//	case ActivationKind::Protocol:
	//		auto protocolArgs = args.as<IProtocolActivatedEventArgs>();
	//		//auto uri = protocolArgs.Uri;

	//		throw winrt::hresult_not_implemented(L"Need to integrate with the Linking module");
	//		if (args.PreviousExecutionState() != ApplicationExecutionState::Running)
	//		{
	//			OutputDebugStringW(L"TODO... Figure out the right activation path for PreviousExecutionState");
	//		}
	//		else
	//		{
	//			OutputDebugStringW(L"TODO... Figure out the right activation path");
	//		}
	//		break;
	//	}
	//}

	// Create the root view for the React app
	UIElement ReactApplicationDelegate::OnCreate(hstring const& arguments)
	{
		auto host = m_reactApplication.Host();
		auto instanceManager = host.InstanceManager();

		host.InstanceManager().OnResume([=]() {
			m_application.Exit();
		});

		ApplyArguments(host, arguments.c_str());

		auto rootView = instanceManager.CreateRootView(host.MainComponentName(), nullptr);
		//rootView.OnCreate(host); // or rootView.Start(?);
		//rootView.StartReactApplication(host.InstanceManager(), host.MainComponentName(), initialProps);
		throw winrt::hresult_not_implemented(L"ReactApplicationDelegate::OnCreate(..., need to pass initial props object");
		return rootView;
	}

	void ReactApplicationDelegate::OnResuming(IInspectable sender, IInspectable args)
	{
		auto reactApplication = m_reactApplication.try_as<ReactApplication>();
		if (reactApplication == nullptr) throw winrt::hresult_error();

		//winrt::ReactUWP::ReactNativeHost host = m_reactApplication.Host;
		//auto manager = host.InstanceManager;
		OutputDebugStringW(L"ReactApplicationDelegate::OnResuming");
	}

	void ReactApplicationDelegate::OnSuspending(IInspectable sender, IInspectable args)
	{
		OutputDebugStringW(L"ReactApplicationDelegate::OnSuspending");
	}

	void ReactApplicationDelegate::OnLeavingBackground(IInspectable sender, winrt::Windows::ApplicationModel::LeavingBackgroundEventArgs args)
	{
		OutputDebugStringW(L"ReactApplicationDelegate::OnLeavingBackground");
	}

	void ReactApplicationDelegate::OnEnteredBackground(IInspectable sender, winrt::Windows::ApplicationModel::EnteredBackgroundEventArgs args)
	{
		OutputDebugStringW(L"ReactApplicationDelegate::OnEnteredBackground");
	}

}

