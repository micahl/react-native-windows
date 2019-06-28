#include "pch.h"
#include "SampleModule.h"
#if __has_include("SampleModule.g.cpp")
#include "SampleModule.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::ReactNative;
using namespace Windows::Foundation::Collections;

namespace winrt::Playground::implementation
{
  hstring SampleModule::Name()
  {
    return L"SampleModule";
  }

  IMapView<hstring, hstring> SampleModule::Constants()
  {
    auto constants = single_threaded_map<hstring, hstring>();
    constants.Insert(L"a", L"\"b\"");
    return constants.GetView();
  }

  IMapView<hstring, Microsoft::ReactNative::MethodDelegate> SampleModule::Methods()
  {
    auto delegates = single_threaded_map<hstring, Microsoft::ReactNative::MethodDelegate>();
    delegates.Insert(L"method1", [=](hstring para)
    {
      // no op
      OutputDebugString(L"SampleModule.method1()");
    });

    return delegates.GetView();
  }

  IMapView<hstring, Microsoft::ReactNative::MethodWithCallbackDelegate> SampleModule::MethodsWithCallback()
  {
    auto delegatesWithCallback = single_threaded_map<hstring, Microsoft::ReactNative::MethodWithCallbackDelegate>();
    delegatesWithCallback.Insert(L"method2",
      [=](hstring para, MethodCallback callback)
    {
      OutputDebugString(L"SampleModule.method2()");

      auto results = single_threaded_vector<hstring>();
      results.Append(L"{ \"result\":true }");
      callback(results.GetView());
    });

    return delegatesWithCallback.GetView();
  }
}
