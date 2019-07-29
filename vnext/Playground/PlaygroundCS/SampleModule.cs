// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

using Microsoft.ReactNative;
using Microsoft.ReactNative.Bridge;
using System;
using System.Linq;
using System.Collections.Generic;
using System.Diagnostics;

namespace Playground
{
  public class SampleModule : INativeModule
  {
    public string Name => nameof(SampleModule);

    public IReadOnlyDictionary<string, object> Constants { get; }
      = new Dictionary<string, object>()
    {
      { "a", "\"b\"" },
    };

    public IReadOnlyDictionary<string, MethodDelegate> Methods { get; }
      = new Dictionary<string, MethodDelegate>()
      {
        { "method1", (args) => { /* fire and forget */ }}
      };

    public IReadOnlyDictionary<string, MethodWithCallbackDelegate> MethodsWithCallback { get; }
      = new Dictionary<string, MethodWithCallbackDelegate>()
      {
        { "method2", (args, callback) => {
          Debug.WriteLine($"SampleModule.method2(${args})");

            // Build up a complex object to pass back as arguments when invoking
            // the callback.  They'll automatically be converted to an equivalent
            // type in JavaScript when the JS function is called.
            var parameters = new List<object> {
              new[] { 0, 1, 2, 3, 4 },
              new[] { 0.02f, 1.0f, 0.42f },
              new[] { "a", "bb" },
              new object[] { new object[] { "First", 0x48 }, "Last" }
            };
            callback(parameters.AsReadOnly());
          }
        },
        {
          // I can refer to the Method3 like this as part of the field initializer because its static.
          // If it wasn't then I'd have to add it later (e.g. as part of the constructor at the earliest).
          "method3", Method3 
        }
      };

    public static void Method3(IReadOnlyList<object> args, MethodDelegate callback)
    {
      // At the moment the input args are packed into a single JSON-formatted string.
      Debug.WriteLine($"SampleModule.method3({args})");

      // Invoke the callback with some arguments. Using JSON isn't required.  We
      // could have used other basic types instead (e.g. int, double, float, bool,
      // etc.)
      string text = @"{ ""result"" : true }";
      // This uses the built-in Windows.Data.Json.JsonObject, but any
      // object whose ToString() returns a json-formatted text could be used
      // (e.g. the Newtonsoft.Json.Linq.JObject). No automatic conversion
      // is done on a string passed directly as arguments. It comes out as a string
      // on the other side and would need to be parsed (e.g. JSON.parse()).
      // Simple... what goes in is what comes out.
      var json = Windows.Data.Json.JsonObject.Parse(text);
      callback(new[] { json });

    }

    public IReadOnlyDictionary<string, MethodWithPromise> MethodsWithPromise { get; }
      = new Dictionary<string, MethodWithPromise>() {
        { "method4", (args, promise) => {
            try
            {
              promise.Resolve(true);
            }
            catch (Exception e)
            {
              promise.Reject("0x80000000", e.Message, e.StackTrace, e);
            }
          }
        }
      };
  }
}
