// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include "pch.h"
#include "Promise.h"
#if __has_include("Bridge.Promise.g.cpp")
#include "Bridge.Promise.g.cpp"
#endif

namespace winrt::Microsoft::ReactNative::Bridge::implementation {

void Promise::Resolve(IInspectable const &value) {
  auto args = single_threaded_vector<IInspectable>({value});
  m_resolve(args.GetView());
}

void Promise::Reject(
    hstring const &code,
    hstring const &message,
    hstring const &stack,
    IInspectable const &value) {
  auto args = single_threaded_vector<IInspectable>({
      code.empty() ? box_value(DefaultError) : box_value(code),
      box_value(message),
      box_value(stack),
      value,
  });
  m_reject(args.GetView());
}

} // namespace winrt::Microsoft::ReactNative::Bridge::implementation
