#pragma once
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include "ReactRootView.g.h"

#include <ViewManagerProvider.h>

#include <ReactUWP/IReactInstance.h>
#include <ReactUWP/IXamlRootView.h>
#include <ReactUWP/ReactUwp.h>
//#include <winrt/microsoft.reactnative.h>

#include "ReactApplication.h"
#include "ReactInstanceManager.h"
#include "ReactNativeHost.h"

namespace winrt::Microsoft::ReactNative::implementation {
// std::shared_ptr<react::uwp::IXamlRootView>
// StartReactApplication(
//	Windows::UI::Xaml::Controls::Grid const& grid,
//	ReactNativeHost host,
//	const std::shared_ptr<react::uwp::IReactInstanceCreator>&
//instanceCreator, 	folly::dynamic initialProps);

struct ReactRootView : ReactRootViewT<ReactRootView> {
  ReactRootView() = default;

  void OnCreate(winrt::Microsoft::ReactNative::ReactNativeHost const &host);
  void StartReactApplication(
      winrt::Microsoft::ReactNative::ReactInstanceManager const
          &instanceManager,
      winrt::hstring componentName,
      folly::dynamic initialProps);

 private:
  std::shared_ptr<react::uwp::IXamlRootView> m_xamlView;
  winrt::hstring m_moduleName{};
  folly::dynamic m_initialProps{};
  winrt::Microsoft::ReactNative::ReactInstanceManager m_reactInstanceManager{};

  static void OnBackRequested(
      winrt::Microsoft::ReactNative::ReactNativeHost const &host,
      IInspectable sender,
      winrt::Windows::UI::Core::BackRequestedEventArgs e);

  // IAsyncAction StartReactApplicationAsync(
  //	ReactInstanceManager const& instanceManager,
  //	winrt::hstring componentName,
  //	folly::dynamic initialProps);
};
} // namespace winrt::Microsoft::ReactNative::implementation

namespace winrt::Microsoft::ReactNative::factory_implementation {
struct ReactRootView
    : ReactRootViewT<ReactRootView, implementation::ReactRootView> {};
} // namespace winrt::Microsoft::ReactNative::factory_implementation
