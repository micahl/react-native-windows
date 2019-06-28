using Microsoft.ReactNative;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Playground
{
  sealed class MainReactNativeHost : ReactNativeHost
  {
    protected override string MainComponentName => "Playground";
    protected override string JavaScriptMainModuleName => "Playground/index.uwp";
    protected override IReadOnlyList<IReactPackage> Packages
    {
      get
      {
        return new[] { new AppModulesPackage() };
      }
    }
  }
}
