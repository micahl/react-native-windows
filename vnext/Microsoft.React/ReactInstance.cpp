// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include "pch.h"
#include "ReactInstance.h"
#if __has_include("Bridge.ReactInstance.g.cpp")
#include "Bridge.ReactInstance.g.cpp"
#endif

#include "ABIModule.h"

namespace winrt::Microsoft::ReactNative::Bridge::implementation {
void ReactInstance::InvokeFunction(
    hstring const& moduleName,
    hstring const& method,
    IVectorView<IInspectable> const& arguments) {
  folly::dynamic args =
      Microsoft::ReactNative::Bridge::ABIModule::ConvertToDynamic(arguments);

  m_instance->CallJsFunction(to_string(moduleName), to_string(method), std::move(args));
}

void ReactInstance::InvokeCallback(
    int callbackId,
    IVectorView<IInspectable> const& arguments) {
  throw hresult_not_implemented(L"ReactInstance.InvokeCallback");
}
} // namespace winrt::Microsoft::ReactNative::Bridge::implementation
