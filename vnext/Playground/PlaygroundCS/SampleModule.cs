// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

using Microsoft.ReactNative;
using System;
using System.Collections.Generic;

namespace Playground
{
  public class SampleModule : Microsoft.ReactNative.INativeModule
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
