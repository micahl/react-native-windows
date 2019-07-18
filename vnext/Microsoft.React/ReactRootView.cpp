#include "pch.h"
#include "ReactRootView.h"
#if __has_include("ReactRootView.g.cpp")
#include "ReactRootView.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::Microsoft::ReactNative::implementation {
void ReactRootView::OnCreate(
    winrt::Microsoft::ReactNative::ReactNativeHost const &host) {
  auto resources = Windows::UI::Xaml::Application::Current().Resources();
  auto brush =
      resources.Lookup(winrt::box_value(L"ApplicationPageBackgroundThemeBrush"))
          .as<Windows::UI::Xaml::Media::SolidColorBrush>();
  this->Background(brush);

  // TODO:
  // if (DispatcherHelpers.IsOnDispatcher())
  //{
  //	SystemNavigationManager.GetForCurrentView().BackRequested += (sender, e)
  //= > OnBackRequested(host, sender, e);
  //	Window.Current.CoreWindow.Dispatcher.AcceleratorKeyActivated += (sender,
  //e) = > OnAcceleratorKeyActivated(host, sender, e);
  //}
}

void ReactRootView::OnBackRequested(
    winrt::Microsoft::ReactNative::ReactNativeHost const &host,
    IInspectable sender,
    winrt::Windows::UI::Core::BackRequestedEventArgs e) {
  auto hostImpl = host.as<ReactNativeHost>();
  if (hostImpl->HasInstance()) {
    hostImpl->ReactInstanceManager().OnBackPressed();
    e.Handled(TRUE);
  }
}

void ReactRootView::StartReactApplication(
    winrt::Microsoft::ReactNative::ReactInstanceManager const &instanceManager,
    winrt::hstring componentName,
    folly::dynamic initialProps) {
  auto impl = instanceManager.as<ReactInstanceManager>();
  auto instanceCreator = impl->InstanceCreator();

  m_xamlView = react::uwp::CreateReactRootView(
      *this, componentName.c_str(), instanceCreator);
  if (m_xamlView == nullptr)
    return;

  // Set initial properties since just created
  m_xamlView->SetInitialProps(std::move(initialProps));

  m_xamlView->AttachRoot();
}

// IAsyncAction ReactRootView::StartReactApplicationAsync(
//	ReactInstanceManager const& instanceManager,
//	winrt::hstring componentName,
//	folly::dynamic initialProps)
//{
//	if (Dispatcher() == nullptr)
//	{
//		throw winrt::hresult_null_argument(L"dispatcher");
//	}
//	else if (!Dispatcher().HasThreadAccess())
//	{
//		throw winrt::hresult_invalid_operation(L"Thread does not have
//dispatcher access.");
//	}

//	if (m_reactInstanceManager != nullptr)
//	{
//		throw winrt::hresult_invalid_operation(L"This root view has
//already been attached to an instance manager.");
//	}

//	m_reactInstanceManager = instanceManager;
//	m_moduleName = componentName;
//	m_initialProps = initialProps;

//}

// TODO
// private static void OnBackRequested(ReactNativeHost host, object sender,
// BackRequestedEventArgs e)
//{
//	if (host.HasInstance)
//	{
//		host.ReactInstanceManager.OnBackPressed();
//		e.Handled = true;
//	}
//}

// private static void OnAcceleratorKeyActivated(ReactNativeHost host,
// CoreDispatcher sender, AcceleratorKeyEventArgs e)
//{
//	if (host.HasInstance)
//	{
//		var reactInstanceManager = host.InstanceManager;
//		if (reactInstanceManager.DevSupportManager.IsEnabled)
//		{
//			if (e.VirtualKey == VirtualKey.Shift)
//			{
//				s_isShiftKeyDown = IsKeyDown(e.EventType);
//			}
//			else if (e.VirtualKey == VirtualKey.Control)
//			{
//				s_isControlKeyDown = IsKeyDown(e.EventType);
//			}
//			else if (IsKeyDown(e.EventType) && s_isShiftKeyDown &&
//e.VirtualKey == VirtualKey.F10)
//			{
//				reactInstanceManager.DevSupportManager.ShowDevOptionsDialog();
//			}
//			else if (e.EventType == CoreAcceleratorKeyEventType.KeyUp &&
//s_isControlKeyDown && e.VirtualKey == VirtualKey.R)
//			{
//				reactInstanceManager.DevSupportManager.HandleReloadJavaScript();
//			}
//		}
//	}
//}

// private static bool IsKeyDown(CoreAcceleratorKeyEventType t)
//{
//	return t == CoreAcceleratorKeyEventType.KeyDown || t ==
//CoreAcceleratorKeyEventType.SystemKeyDown;
//}
} // namespace winrt::Microsoft::ReactNative::implementation
