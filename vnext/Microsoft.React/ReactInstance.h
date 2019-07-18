#pragma once

#include "Bridge.ReactInstance.g.h"
#include "winrt/microsoft.reactnative.h"

namespace winrt::Microsoft::ReactNative::Bridge::implementation {
struct ReactInstance : ReactInstanceT<ReactInstance> {
  ReactInstance() = default;
  winrt::Windows::Foundation::Collections::IIterable<
      winrt::Microsoft::ReactNative::INativeModule>
  NativeModules() {
    return nullptr;
  };
  void InvokeFunction(
      hstring moduleName,
      hstring method,
      Windows::Data::Json::JsonArray arguments,
      hstring tracingName);
  void InvokeCallback(int callbackId, Windows::Data::Json::JsonArray arguments);
};
} // namespace winrt::Microsoft::ReactNative::Bridge::implementation

// namespace winrt::Microsoft::ReactNative::Bridge::factory_implementation
//{
//    struct ReactInstance : ReactInstanceT<ReactInstance,
//    implementation::ReactInstance>
//    {
//    };
//}
