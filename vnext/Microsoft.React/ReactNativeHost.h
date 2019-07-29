#pragma once
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include "ReactNativeHost.g.h"
#include "ReactInstanceManager.h"
#include "ReactRootView.h"

#include <ReactUWP/IReactInstance.h>
#include <ReactUWP/IXamlRootView.h>
#include <ReactUWP/ReactUwp.h>

namespace winrt::Microsoft::ReactNative::implementation {
using namespace winrt;
using namespace Microsoft::ReactNative;
using namespace Microsoft::ReactNative::Bridge;
using namespace Windows::Foundation::Collections;

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
  virtual IVectorView<IReactPackage> Packages();

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

  IVectorView<IReactPackage> get_Packages() {
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
