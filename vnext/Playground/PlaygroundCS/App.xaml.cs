using Microsoft.ReactNative;

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
}
