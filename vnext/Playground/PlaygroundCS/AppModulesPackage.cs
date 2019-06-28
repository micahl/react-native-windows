using Microsoft.ReactNative;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Playground
{
  sealed class AppModulesPackage : IReactPackage
  {
    public IReadOnlyList<INativeModule> CreateNativeModules(ReactContext reactContext)
    {
      return new List<INativeModule>() { new SampleModule() };
    }
  }
}
