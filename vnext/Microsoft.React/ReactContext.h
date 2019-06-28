#pragma once

#include "ReactContext.g.h"
#include <winrt/Windows.Data.Json.h>

namespace winrt::Microsoft::ReactNative::implementation
{
    struct ReactContext : ReactContextT<ReactContext>
    {
        ReactContext() = default;

        Microsoft::ReactNative::IReactInstance ReactInstance();
    };
}

//namespace winrt::Microsoft::ReactNative::factory_implementation
//{
//    struct ReactContext : ReactContextT<ReactContext, implementation::ReactContext>
//    {
//    };
//}
