// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include "pch.h"
#include "ReactNativeHost.h"
#include "ReactNativeHost.g.cpp"
#include "ReactInit.h"
#include "ReactInstanceManager.h"
#include "ReactInstanceManagerBuilder.h"
#include "ReactRootView.h"

#include <NativeModuleProvider.h>
#include <ViewManager.h>
#include <ViewManagerProvider.h>

using namespace winrt;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;

namespace winrt::Microsoft::ReactNative::implementation {
ReactNativeHost::ReactNativeHost() {
  Init();
}

winrt::Microsoft::ReactNative::ReactInstanceManager
ReactNativeHost::ReactInstanceManager() {
  if (m_reactInstanceManager == nullptr) {
    m_reactInstanceManager = CreateReactInstanceManager();
  }

  return m_reactInstanceManager;
}

UIElement ReactNativeHost::OnCreate() {
  folly::dynamic initialProps = folly::dynamic::object();

  m_reactRootView = CreateRootView();

  if (m_reactRootView == nullptr)
    return nullptr;

  m_reactRootView->OnCreate(*this);
  m_reactRootView->StartReactApplication(
      ReactInstanceManager(), get_MainComponentName(), initialProps);

  return *m_reactRootView;
}

void ReactNativeHost::OnSuspend() {
  if (HasInstance()) {
    ReactInstanceManager().OnSuspend();
  }
}

void ReactNativeHost::OnEnteredBackground() {
  if (HasInstance()) {
    ReactInstanceManager().OnEnteredBackground();
  }
}

void ReactNativeHost::OnLeavingBackground() {
  if (HasInstance()) {
    ReactInstanceManager().OnLeavingBackground();
  }
}

void ReactNativeHost::OnResume(
    Microsoft::ReactNative::OnResumeAction const &action) {
  if (HasInstance()) {
    ReactInstanceManager().OnResume(action);
  }
}

hstring ReactNativeHost::MainComponentName() {
  throw winrt::hresult_not_implemented(
      L"Must implement ReactNativeHost.MainComponentName.");
}

hstring ReactNativeHost::JavaScriptMainModuleName() {
  throw winrt::hresult_not_implemented(
      L"Must implement ReactNativeHost.JavaScriptMainModuleName.");
}

hstring ReactNativeHost::JavaScriptBundleFile() {
  return {};
}

bool ReactNativeHost::UseDeveloperSupport() {
#if _DEBUG
  return true;
#else
  return false;
#endif
}


auto ReactNativeHost::Packages() -> IVectorView<IReactPackage>{
  throw winrt::hresult_not_implemented(
      L"Must implement ReactNativeHost.Packages");
}

void ReactNativeHost::Init() {
#if _DEBUG
  facebook::react::InitializeLogging(
      [](facebook::react::RCTLogLevel /*logLevel*/, const char *message) {
        std::string str = std::string("ReactNative:") + message;
        OutputDebugStringA(str.c_str());
      });
#endif
}

winrt::Microsoft::ReactNative::ReactInstanceManager
ReactNativeHost::CreateReactInstanceManager() {
  auto builder = ReactInstanceManagerBuilder();
  builder.UseDeveloperSupport(UseDeveloperSupport());
  builder.InitialLifecycleState(LifecycleState::BeforeCreate);
  builder.JavaScriptBundleFile(get_JavaScriptBundleFile());
  builder.JavaScriptMainModuleName(get_JavaScriptMainModuleName());
  builder.Packages(get_Packages());

  return builder.Build();
}

std::shared_ptr<ReactRootView> ReactNativeHost::CreateRootView() {
  auto rootView = std::make_shared<ReactRootView>();
  return rootView;
}
} // namespace winrt::Microsoft::ReactNative::implementation
