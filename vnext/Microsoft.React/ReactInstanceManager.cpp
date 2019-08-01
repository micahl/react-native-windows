// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include "pch.h"
#include "ReactInstanceManager.h"
#if __has_include("ReactInstanceManager.g.cpp")
#include "ReactInstanceManager.g.cpp"
#endif

#include <cxxreact/CxxModule.h>
#include <cxxreact/Instance.h>
#include <cxxreact/ModuleRegistry.h>

using namespace winrt;
using namespace winrt::Microsoft::ReactNative;
using namespace winrt::Microsoft::ReactNative::Bridge;
using namespace winrt::Windows::Foundation::Collections;

namespace winrt::Microsoft::ReactNative::implementation {
ReactInstanceManager::ReactInstanceManager(
    Microsoft::ReactNative::ReactInstanceSettings instanceSettings,
    std::string jsBundleFile,
    std::string jsMainModuleName,
    IVectorView<IReactPackage> &packages,
    bool useDeveloperSupport,
    LifecycleState initialLifecycleState)
    : m_instanceSettings(instanceSettings),
      m_jsBundleFile(jsBundleFile),
      m_jsMainModuleName(jsMainModuleName),
      m_packages(packages),
      m_useDeveloperSupport(useDeveloperSupport) {
  if (packages == nullptr) {
    throw hresult_invalid_argument(L"packages");
  }

  // TODO: Create a LifeCycleStateMachine to raise events in response
  // to events from the application and associate it with the ReactContext.
  // Define the ILifecycleEventListener and add support to ReactContext to register
  // a lifecycle listener.
  // Define the IBackgroundEventListener and add support to ReactContext to register
  // modules as background event listeners.
}

void ReactInstanceManager::OnSuspend() {
  OutputDebugStringW(L"ReactInstanceManager::OnSuspend not implemented");
  // throw hresult_not_implemented(L"ReactInstanceManager::OnSuspend");

  // DispatcherHelpers.AssertOnDispatcher();

  //_defaultBackButtonHandler = null;
  //_suspendCancellation?.Dispose();

  // if (_useDeveloperSupport)
  //{
  //    _devSupportManager.IsEnabled = false;
  //}

  //_lifecycleStateMachine.OnSuspend();
}

// Called when the host entered background mode.
void ReactInstanceManager::OnEnteredBackground() {
  OutputDebugStringW(
      L"ReactInstanceManager::OnEnteredBackground not implemented");
  // throw
  // hresult_not_implemented(L"ReactInstanceManager::OnEnteredBackground");

  // DispatcherHelpers.AssertOnDispatcher();
  //_lifecycleStateMachine.OnEnteredBackground();
}

// Called when the host is leaving background mode.
void ReactInstanceManager::OnLeavingBackground() {
  OutputDebugStringW(
      L"ReactInstanceManager::OnLeavingBackground not implemented");
  // throw
  // hresult_not_implemented(L"ReactInstanceManager::OnLeavingBackground");

  // DispatcherHelpers.AssertOnDispatcher();
  //_lifecycleStateMachine.OnLeavingBackground();
}

// Used when the application resumes to reset the back button handling in
// JavaScript.
void ReactInstanceManager::OnResume(OnResumeAction const &action) {
  // fire_and_forget action();
  // action();

  OutputDebugStringW(L"ReactInstanceManager::OnResume not implemented");
  // throw hresult_not_implemented(L"ReactInstanceManager::OnResume");

  // see the ReactInstanceManager.cs from the C# implementation
  // DispatcherHelpers.Initialize();
  // DispatcherHelpers.AssertOnDispatcher();
  // ReactChoreographer.Initialize();

  //_defaultBackButtonHandler = onBackPressed;
  //_suspendCancellation = new CancellationDisposable();

  // if (_useDeveloperSupport)
  //{
  //	_devSupportManager.IsEnabled = true;
  //}

  //_lifecycleStateMachine.OnResume();
}

void ReactInstanceManager::OnBackPressed() {
  OutputDebugStringW(L"ReactInstanceManager::OnBackPressed not implemented");
  // throw
  // hresult_not_implemented(L"ReactInstanceManager.OnBackPressed");
  // TODO

  // DispatcherHelpers.AssertOnDispatcher();
  // var reactContext = _currentReactContext;
  // if (reactContext == null)
  //{
  //	RnLog.Warn(ReactConstants.RNW, $"ReactInstanceManager: OnBackPressed:
  // Instance detached from instance manager.");
  // InvokeDefaultOnBackPressed();
  //}
  // else
  //{
  //	reactContext.GetNativeModule<DeviceEventManagerModule>().EmitHardwareBackPressed();
  //}
}

std::shared_ptr<react::uwp::IReactInstanceCreator>
ReactInstanceManager::InstanceCreator() {
  if (m_reactInstanceCreator == nullptr) {
     m_reactInstanceCreator = std::make_shared<ReactInstanceCreator>(
        m_instanceSettings,
        m_jsBundleFile,
        m_jsMainModuleName,
        m_modulesProvider,
        m_viewManagersProvider);
  }

  return m_reactInstanceCreator;
}

auto ReactInstanceManager::GetOrCreateReactContext() -> ReactContext {
  if (m_currentReactContext != nullptr)
    return m_currentReactContext;

  m_currentReactContext = CreateReactContextCore();

  return m_currentReactContext;
}

// TODO: Should we make this method async?  On first run when getInstance
// is called it starts things up. Does this need to block?
auto ReactInstanceManager::CreateReactContextCore() -> ReactContext {
  auto reactContext = ReactContext();

  /* TODO hook up an exception handler if UseDeveloperSupport is set
  if (m_useDeveloperSupport) {
    if (m_nativeModuleCallExceptionHandler) {
      reactContext.NativeModuleCallExceptionHandler =
          m_nativeModuleCallExceptionHandler;
    } else {
      reactContext.NativeModuleCallExceptionHandler =
        m_devSupportManager.HandleException;
    }
  }
  */

  if (m_modulesProvider == nullptr) {
    // equivalent to the C# NativeModulesRegistry
    m_modulesProvider = std::make_shared<NativeModulesProvider>();

    // TODO: Define a CoreModulesPackage, load it here.
    // TODO: Wrap/re-implement our existing set of core modules and add
    // them to the CoreModulesPackage.

    for (auto package : m_packages) {
      auto modules = package.CreateNativeModules(reactContext);
      for (auto module : modules) {
        // TODO: Allow a module to override another if they conflict on name?
        m_modulesProvider->RegisterModule(module);
      }
    }
  }

  if (m_viewManagersProvider == nullptr) {
    m_viewManagersProvider = std::make_shared<ViewManagersProvider>();

    // TODO: Register default modules
    // The registration that currently happens in the moduleregistry.cpp
    // should happen here if we convert all modules to go through the ABI
    // rather than directly against facebook's types.
  }

  auto instancePtr = InstanceCreator()->getInstance();
  auto reactInstance =
  winrt::make<Bridge::implementation::ReactInstance>(instancePtr);

  Bridge::implementation::ReactContext *contextImpl{
      get_self<Bridge::implementation::ReactContext>(reactContext)};
  contextImpl->InitializeWithInstance(reactInstance);

  return reactContext;
}
} // namespace winrt::Microsoft::ReactNative::implementation
