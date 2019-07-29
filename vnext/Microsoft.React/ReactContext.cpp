// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include "pch.h"
#include "ReactContext.h"
#if __has_include("Bridge.ReactContext.g.cpp")
#include "Bridge.ReactContext.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::ReactNative::Bridge;

namespace winrt::Microsoft::ReactNative::Bridge::implementation {
  IReactInstance ReactContext::ReactInstance() {
    throw winrt::hresult_not_implemented(L"ReactContext.ReactInstance.get");
  }
} // namespace winrt::Microsoft::ReactNative::Bridge::implementation
