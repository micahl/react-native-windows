#pragma once

#include "ReactContext.g.h"
#include <winrt/Windows.Data.Json.h>

namespace winrt::Microsoft::React::implementation
{
    struct ReactContext : ReactContextT<ReactContext>
    {
        ReactContext() = default;

        Microsoft::React::IReactInstance ReactInstance();
    };
}

//namespace winrt::Microsoft::React::factory_implementation
//{
//    struct ReactContext : ReactContextT<ReactContext, implementation::ReactContext>
//    {
//    };
//}
