#pragma once

#include "ReactNativeHost.g.h"
#include "ReactInstanceManager.h"
#include "ReactRootView.h"

#include <ReactUWP/IReactInstance.h>
#include <ReactUWP/IXamlRootView.h>
#include <ReactUWP/ReactUwp.h>

namespace winrt::Microsoft::ReactNative::implementation {
struct ReactNativeHost : ReactNativeHostT<ReactNativeHost> {
  ReactNativeHost();

  UIElement OnCreate();

  winrt::Microsoft::ReactNative::ReactInstanceManager ReactInstanceManager();

  void OnSuspend();
  void OnEnteredBackground();
  void OnLeavingBackground();
  void OnResume(OnResumeAction const &action);

  virtual hstring MainComponentName();
  virtual hstring JavaScriptMainModuleName();
  virtual hstring JavaScriptBundleFile();
  virtual bool UseDeveloperSupport();
  virtual Windows::Foundation::Collections::IVectorView<
      Microsoft::ReactNative::IReactPackage>
  Packages();

  bool HasInstance() {
    return m_reactInstanceManager != nullptr;
  }

  hstring get_MainComponentName() {
    return overridable().MainComponentName();
  }
  hstring get_JavaScriptMainModuleName() {
    return overridable().JavaScriptMainModuleName();
  }
  hstring get_JavaScriptBundleFile() {
    return overridable().JavaScriptBundleFile();
  }
  bool get_UseDeveloperSupport() {
    return overridable().UseDeveloperSupport();
  }

  winrt::Windows::Foundation::Collections::IVectorView<
      winrt::Microsoft::ReactNative::IReactPackage>
  get_Packages() {
    return overridable().Packages();
  }

 private:
  winrt::Microsoft::ReactNative::ReactInstanceManager m_reactInstanceManager{
      nullptr};
  winrt::hstring m_mainComponentName{};
  winrt::hstring m_javascriptMainModuleName{};

  std::shared_ptr<ReactRootView> m_reactRootView{nullptr};

  void Init();
  winrt::Microsoft::ReactNative::ReactInstanceManager
  CreateReactInstanceManager();
  std::shared_ptr<ReactRootView> CreateRootView();
};
} // namespace winrt::Microsoft::ReactNative::implementation

namespace winrt::Microsoft::ReactNative::factory_implementation {
struct ReactNativeHost
    : ReactNativeHostT<ReactNativeHost, implementation::ReactNativeHost> {};
} // namespace winrt::Microsoft::ReactNative::factory_implementation
