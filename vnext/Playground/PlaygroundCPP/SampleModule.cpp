// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include "pch.h"
#include "SampleModule.h"
#include <winrt\Windows.Data.Json.h>

using namespace winrt;
using namespace Microsoft::ReactNative;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;

namespace winrt::Playground::implementation {
hstring SampleModule::Name() {
  return L"SampleModule";
}

IMapView<hstring, IInspectable> SampleModule::Constants() {
  auto constants = single_threaded_map<hstring, IInspectable>();
  std::wstring value = L"\"b\"";
  constants.Insert(L"a", box_value(L"\"b\""));
  return constants.GetView();
}

IMapView<hstring, MethodDelegate> SampleModule::Methods() {
  auto delegates = single_threaded_map<hstring, MethodDelegate>();
  delegates.Insert(L"method1", [](IVectorView<IInspectable> const &args) {
    // no op
    OutputDebugStringW(L"SampleModule.method1()\n");
  });

  return delegates.GetView();
}

void SampleModule::method3(
    IVectorView<IInspectable> const &args,
    MethodDelegate const &callback) {

  if (args.Size() < 1)
    throw hresult_invalid_argument();

  // At the moment the input args are packed into a single JSON-formatted
  // string.
  auto input = args.GetAt(0);
  auto inputValue = input.as<IPropertyValue>();
  assert(inputValue.Type() == PropertyType::String);
  auto inputString = input.as<IPropertyValue>().GetString();
  OutputDebugStringW(L"SampleModule.method3(");
  OutputDebugStringW(inputString.c_str());
  OutputDebugStringW(L")\n");

  // Invoke the callback with some arguments. Using JSON isn't required.  We
  // could have used other basic types instead (e.g. int, double, float, bool,
  // etc.)
  auto text = L"{ \"result\" : true }";
  auto json = Windows::Data::Json::JsonObject::Parse(text);
  auto callbackArgs = single_threaded_vector<IInspectable>({json}).GetView();

  callback(callbackArgs);
}

IMapView<hstring, MethodWithCallbackDelegate>
SampleModule::MethodsWithCallback() {
  auto delegatesWithCallback =
      single_threaded_map<hstring, MethodWithCallbackDelegate>();
  delegatesWithCallback.Insert(
      L"method2",
      [](IVectorView<IInspectable> const &args,
         MethodDelegate const &callback) {
        OutputDebugStringW(L"SampleModule.method2()\n");

        // Build up a complex object to pass back as arguments when invoking
        // the callback.  They'll automatically be converted to an equivalent
        // type in JavaScript when the JS function is called.
        auto integerArray = PropertyValue::CreateInt32Array(
            std::array<int32_t, 5>{0, 1, 2, 3, 4});

        auto floatArray = PropertyValue::CreateSingleArray(
            std::array<float_t, 3>{0.02f, 1.0f, 0.42f});

        auto stringArray = PropertyValue::CreateStringArray({L"a", L"bb"});

        auto mixedArray = PropertyValue::CreateInspectableArray(
            std::array<IInspectable, 2>{box_value(L"First"), box_value(0x48)});

        auto nestedArray = PropertyValue::CreateInspectableArray(
            std::array<IInspectable, 2>{mixedArray, box_value(L"Last")});

        auto callbackArgs = single_threaded_vector<IInspectable>({box_value(84),
                                                                  integerArray,
                                                                  floatArray,
                                                                  stringArray,
                                                                  nestedArray});

        callback(callbackArgs.GetView());
      });

  delegatesWithCallback.Insert(
      L"method3", MethodWithCallbackDelegate(this, &SampleModule::method3));

  return delegatesWithCallback.GetView();
}

IMapView<hstring, MethodWithPromise> SampleModule::MethodsWithPromise() {
  auto methods = single_threaded_map<hstring, MethodWithPromise>();

  methods.Insert(
      L"method4",
      [](IVectorView<IInspectable> const &args, Promise const &promise) {
        //
        try {
          promise.Resolve(box_value(true));
        } catch (std::exception e) {
          hstring what = to_hstring(e.what());
          promise.Reject(
              L"0x80000000", what, L"stack trace goes here", nullptr);
        }
      });

  return methods.GetView();
}
} // namespace winrt::Playground::implementation
