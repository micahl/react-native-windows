#pragma once

#include <ReactUWP\IReactInstance.h>
#include <winrt\microsoft.reactnative.h>
#include "LifecycleState.h"
#include "ReactInstanceManager.h"

namespace winrt::Microsoft::ReactNative::implementation {
class ReactInstanceManagerBuilder {
 public:
  void JavaScriptBundleFile(winrt::hstring jsBundleFile) {
    m_jsBundleFile = jsBundleFile;
  };
  void JavaScriptMainModuleName(winrt::hstring jsMainModuleName) {
    m_jsMainModuleName = jsMainModuleName;
  };
  void UseDeveloperSupport(bool useDevSupport) {
    m_useDeveloperSupport = useDevSupport;
  };
  void InitialLifecycleState(LifecycleState state) {
    m_initialLifecycleState = state;
    m_isLifecycleStateSet = TRUE;
  };

  void Packages(Windows::Foundation::Collections::IVectorView<
                winrt::Microsoft::ReactNative::IReactPackage> packages) {
    m_packages = packages;
  }

  winrt::Microsoft::ReactNative::ReactInstanceManager Build();

 private:
  Windows::Foundation::Collections::IVectorView<
      winrt::Microsoft::ReactNative::IReactPackage>
      m_packages;
  std::wstring m_jsBundleFile{};
  std::wstring m_jsMainModuleName{};
  bool m_useDeveloperSupport{false};
  bool m_isLifecycleStateSet{false};
  LifecycleState m_initialLifecycleState{LifecycleState::BeforeCreate};
};
} // namespace winrt::Microsoft::ReactNative::implementation
