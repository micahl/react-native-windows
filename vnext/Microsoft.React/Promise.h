#pragma once
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include "Bridge.Promise.g.h"

namespace winrt::Microsoft::ReactNative::Bridge::implementation {
  using namespace winrt;
  using namespace winrt::Windows::Foundation;
  using namespace winrt::Microsoft::ReactNative;
  using namespace winrt::Microsoft::ReactNative::Bridge;

struct Promise : PromiseT<Promise> {
  const hstring DefaultError = L"EUNSPECIFIED";

  Promise(MethodDelegate resolve, MethodDelegate reject)
      : m_resolve(resolve), m_reject(reject) {
    if (resolve == nullptr)
      throw hresult_invalid_argument(L"Cannot use a null callback for Resolve");
    if (reject == nullptr)
      throw hresult_invalid_argument(L"Cannot use a null callback for Reject");
  }

  void Resolve(IInspectable const &value);
  void Reject(
      hstring const &code,
      hstring const &message,
      hstring const &stack,
      IInspectable const &value);

 private:
  MethodDelegate m_resolve;
  MethodDelegate m_reject;
};
} // namespace winrt::Microsoft::ReactNative::implementation

namespace winrt::Microsoft::ReactNative::Bridge::factory_implementation {
struct Promise : PromiseT<Promise, implementation::Promise> {};
} // namespace winrt::Microsoft::ReactNative::Bridge::factory_implementation
