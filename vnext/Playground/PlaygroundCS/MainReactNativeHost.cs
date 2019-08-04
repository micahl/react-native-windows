// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

using Microsoft.ReactNative;
using Microsoft.ReactNative.Bridge;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Playground
{
  sealed class MainReactNativeHost : ReactNativeHost
  {
    public MainReactNativeHost()
    {
#if DEBUG
      this.InstanceSettings.UseWebDebugger = true;
      this.InstanceSettings.UseLiveReload = true;
#endif
      this.InstanceSettings.UseJsi = true;
    }

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
