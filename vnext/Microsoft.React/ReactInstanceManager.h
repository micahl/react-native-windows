#pragma once
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include "ReactInstanceManager.g.h"

#include "LifecycleState.h"
#include "NativeModulesProvider.h"
#include "ReactInit.h"
#include "ViewManagersProvider.h"

#include <ReactUWP/IReactInstance.h>
#include <ReactUWP/ReactUwp.h>

namespace winrt::Microsoft::ReactNative::implementation {
using namespace winrt;
using namespace Microsoft::ReactNative::Bridge;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;

struct ReactInstanceManager : ReactInstanceManagerT<ReactInstanceManager> {
  ReactInstanceManager() = default;
  ReactInstanceManager(
      std::string jsBundleFile,
      std::string jsMainModuleName,
      IVectorView<IReactPackage> &packages,
      bool useDeveloperSupport,
      LifecycleState initialLifecycleState);

  std::shared_ptr<react::uwp::IReactInstanceCreator> InstanceCreator();
  std::shared_ptr<react::uwp::IReactInstance> Instance() {
    return InstanceCreator()->getInstance();
  }

  void OnSuspend();
  void OnEnteredBackground();
  void OnLeavingBackground();
  void OnResume(OnResumeAction const &action);

  void OnBackPressed();

 private:
  std::string m_jsBundleFile{};
  std::string m_jsMainModuleName{};
  IVectorView<IReactPackage> m_packages;
  bool m_useDeveloperSupport;
  std::shared_ptr<NativeModulesProvider> m_modulesProvider{nullptr};
  std::shared_ptr<ViewManagersProvider> m_viewManagersProvider{nullptr};

  //	There should be one react instance creator per instance, as it
  //	both holds the current instance and is responsible for creating new
  //	instances on live reload.
  std::shared_ptr<react::uwp::IReactInstanceCreator> m_reactInstanceCreator{
      nullptr};
};
} // namespace winrt::Microsoft::ReactNative::implementation

namespace winrt::Microsoft::ReactNative::factory_implementation {
struct ReactInstanceManager : ReactInstanceManagerT<
                                  ReactInstanceManager,
                                  implementation::ReactInstanceManager> {};
} // namespace winrt::Microsoft::ReactNative::factory_implementation
