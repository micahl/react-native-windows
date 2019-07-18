#include "pch.h"
#include "ReactInstanceManager.h"
#if __has_include("ReactInstanceManager.g.cpp")
#include "ReactInstanceManager.g.cpp"
#endif

#include "cxxreact/Instance.h"
#include "cxxreact/ModuleRegistry.h"
#include "cxxreact/CxxModule.h"

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::Microsoft::ReactNative::implementation
{
  ReactInstanceManager::ReactInstanceManager(
    std::string jsBundleFile,
    std::string jsMainModuleName,
    Windows::Foundation::Collections::IVectorView<winrt::Microsoft::ReactNative::IReactPackage>& packages,
    bool useDeveloperSupport,
    LifecycleState initialLifecycleState)
    : m_jsBundleFile(jsBundleFile), m_jsMainModuleName(jsMainModuleName), m_packages(packages), m_useDeveloperSupport(useDeveloperSupport)
  {
    if (packages == nullptr)
    {
      throw winrt::hresult_invalid_argument(L"packages");
    }
  }

  void ReactInstanceManager::OnSuspend()
  {
    OutputDebugStringW(L"ReactInstanceManager::OnSuspend not implemented");
    //throw winrt::hresult_not_implemented(L"ReactInstanceManager::OnSuspend");

    //DispatcherHelpers.AssertOnDispatcher();

    //_defaultBackButtonHandler = null;
    //_suspendCancellation?.Dispose();

    //if (_useDeveloperSupport)
    //{
    //    _devSupportManager.IsEnabled = false;
    //}

    //_lifecycleStateMachine.OnSuspend();
  }

  // Called when the host entered background mode.
  void ReactInstanceManager::OnEnteredBackground()
  {
    OutputDebugStringW(L"ReactInstanceManager::OnEnteredBackground not implemented");
    //throw winrt::hresult_not_implemented(L"ReactInstanceManager::OnEnteredBackground");

    //DispatcherHelpers.AssertOnDispatcher();
    //_lifecycleStateMachine.OnEnteredBackground();
  }

  // Called when the host is leaving background mode.
  void ReactInstanceManager::OnLeavingBackground()
  {
    OutputDebugStringW(L"ReactInstanceManager::OnLeavingBackground not implemented");
    //throw winrt::hresult_not_implemented(L"ReactInstanceManager::OnLeavingBackground");

    //DispatcherHelpers.AssertOnDispatcher();
    //_lifecycleStateMachine.OnLeavingBackground();
  }

  // Used when the application resumes to reset the back button handling in JavaScript.
  void ReactInstanceManager::OnResume(Microsoft::ReactNative::OnResumeAction const& action)
  {
    //winrt::fire_and_forget action();
    //action();

    OutputDebugStringW(L"ReactInstanceManager::OnResume not implemented");
    //throw winrt::hresult_not_implemented(L"ReactInstanceManager::OnResume");

    // see the ReactInstanceManager.cs from the C# implementation
    //DispatcherHelpers.Initialize();
    //DispatcherHelpers.AssertOnDispatcher();
    //ReactChoreographer.Initialize();

    //_defaultBackButtonHandler = onBackPressed;
    //_suspendCancellation = new CancellationDisposable();

    //if (_useDeveloperSupport)
    //{
    //	_devSupportManager.IsEnabled = true;
    //}

    //_lifecycleStateMachine.OnResume();
  }

  void ReactInstanceManager::OnBackPressed()
  {
    OutputDebugStringW(L"ReactInstanceManager::OnBackPressed not implemented");
    //throw winrt::hresult_not_implemented(L"ReactInstanceManager.OnBackPressed");
    // TODO

    //DispatcherHelpers.AssertOnDispatcher();
    //var reactContext = _currentReactContext;
    //if (reactContext == null)
    //{
    //	RnLog.Warn(ReactConstants.RNW, $"ReactInstanceManager: OnBackPressed: Instance detached from instance manager.");
    //	InvokeDefaultOnBackPressed();
    //}
    //else
    //{
    //	reactContext.GetNativeModule<DeviceEventManagerModule>().EmitHardwareBackPressed();
    //}
  }

  std::shared_ptr<react::uwp::IReactInstanceCreator> ReactInstanceManager::InstanceCreator()
  {
    if (m_reactInstanceCreator == nullptr)
    {
      if (m_modulesProvider == nullptr)
      {
        m_modulesProvider = std::make_shared<NativeModulesProvider>();

        ReactContext context = ReactContext{ nullptr };

        for (auto package : m_packages)
        {
          auto modules = package.CreateNativeModules(context);
          for (auto module : modules)
          {
            m_modulesProvider->RegisterModule(module);
          }
        }
      }

      if (m_viewManagersProvider == nullptr)
      {
        m_viewManagersProvider = std::make_shared<ViewManagersProvider>();

        // TODO: Register default modules
        // The registration that currently happens in the moduleregistry.cpp should
        // happen here if we convert all modules to go through the ABI rather than
        // directly against facebook's types.
      }

      m_reactInstanceCreator = std::make_shared<ReactInstanceCreator>(
        m_jsBundleFile,
        m_jsMainModuleName,
        m_modulesProvider,
        m_viewManagersProvider);
    }

    return m_reactInstanceCreator;
  }
}
