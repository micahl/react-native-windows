using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.ApplicationModel;
using Windows.ApplicationModel.Activation;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;
using Microsoft.React;

namespace Playground
{
  /// <summary>
  /// Provides application-specific behavior to supplement the default Application class.
  /// </summary>
  sealed partial class App : ReactApplication
  {
    private MainReactNativeHost _host = new MainReactNativeHost();

    /// <summary>
    /// Initializes the singleton application object.  This is the first line of authored code
    /// executed, and as such is the logical equivalent of main() or WinMain().
    /// </summary>
    public App()
    {
      this.InitializeComponent();
    }

    protected override ReactNativeHost HostCore => _host;
  }

  sealed class MainReactNativeHost : ReactNativeHost
  {
    protected override string MainComponentName => "Playground";
    protected override string JavaScriptMainModuleName => "Playground/index.uwp";
    protected override IReadOnlyList<IReactPackage> Packages
    {
      get
      {
        return new[] { new AppModulePackage() };
      }
    }
  }

  sealed class AppModulePackage : IReactPackage
  {
    public IReadOnlyList<INativeModule> CreateNativeModules(ReactContext reactContext)
    {
      return new List<INativeModule>() { new SampleModule() };
    }
  }

  public class SampleModule : Microsoft.React.INativeModule
  {
    Dictionary<string, string> _constants;
    Dictionary<string, MethodDelegate> m_delegates = new Dictionary<string, MethodDelegate>();
    Dictionary<String, MethodWithCallbackDelegate> m_delegateWithCallback = new Dictionary<string, MethodWithCallbackDelegate>();

    public SampleModule()
    {
      _constants = new Dictionary<string, string>();
      _constants.Add("a", "\"b\"");

      m_delegates.Add("method1", new MethodDelegate(
       (string para) =>
       {

       }));

      m_delegateWithCallback.Add("method2", new MethodWithCallbackDelegate(
       (string para, MethodCallback callback) =>
       {
         string[] results = new string[] { "{ \"result\":true }" };
         callback(results);
       }));
    }

    public IReadOnlyDictionary<string, string> Constants
    {
      get
      {
        return _constants;
      }
    }

    public IReadOnlyDictionary<string, MethodDelegate> Methods
    {
      get
      {
        return m_delegates;
      }
    }

    public IReadOnlyDictionary<string, MethodWithCallbackDelegate> MethodsWithCallback
    {
      get
      {
        return m_delegateWithCallback;
      }
    }

    public string Name
    {
      get
      {
        return "SampleModule";
      }
    }
  }
}
