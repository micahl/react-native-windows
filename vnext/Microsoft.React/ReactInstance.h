#pragma once

#include "Bridge.ReactInstance.g.h"
#include "winrt/microsoft.react.h"

namespace winrt::Microsoft::React::Bridge::implementation
{
    struct ReactInstance : ReactInstanceT<ReactInstance>
    {
        ReactInstance() = default;
		winrt::Windows::Foundation::Collections::IIterable<winrt::Microsoft::React::INativeModule> NativeModules() { return nullptr; };
		void InvokeFunction(hstring moduleName, hstring method, Windows::Data::Json::JsonArray arguments, hstring tracingName);
		void InvokeCallback(int callbackId, Windows::Data::Json::JsonArray arguments);
    };
}

//namespace winrt::Microsoft::React::Bridge::factory_implementation
//{
//    struct ReactInstance : ReactInstanceT<ReactInstance, implementation::ReactInstance>
//    {
//    };
//}
