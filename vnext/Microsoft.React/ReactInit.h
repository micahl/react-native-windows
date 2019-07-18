#pragma once

#include "NativeModulesProvider.h"
#include "ReactInstanceManager.h"
#include "ReactNativeHost.h"
#include "ViewManagersProvider.h"

#include <ReactUWP/ReactUwp.h>

namespace react {
namespace uwp {
struct IReactInstanceCreator;
struct IXamlRootView;
} // namespace uwp
} // namespace react

namespace winrt::Microsoft::ReactNative::implementation {
void InitReactNative();

struct ReactInstanceCreator : react::uwp::IReactInstanceCreator {
  ReactInstanceCreator(
      std::string jsBundleFile,
      std::string jsMainModuleName,
      std::shared_ptr<NativeModulesProvider> modulesProvider,
      std::shared_ptr<ViewManagersProvider> viewManagersProvider);

  std::string m_jsMainModuleName{};
  std::string m_jsBundleFile{};
  std::shared_ptr<NativeModulesProvider> m_modulesProvider{nullptr};
  std::shared_ptr<ViewManagersProvider> m_viewManagersProvider{nullptr};

  std::shared_ptr<react::uwp::IReactInstance> getInstance();
  void markAsNeedsReload();

 private:
  std::shared_ptr<react::uwp::IReactInstance> m_instance;
};
} // namespace winrt::Microsoft::ReactNative::implementation
