#pragma once
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include "ReactSupport.h"
#include <NativeModuleProvider.h>
#include <winrt\Microsoft.ReactNative.h>
#include <winrt\Microsoft.ReactNative.Bridge.h>
//
namespace winrt::Microsoft::ReactNative::Bridge {
using namespace winrt;
using namespace Microsoft::ReactNative;

class NativeModulesProvider final
    : public facebook::react::NativeModuleProvider {
 public:
  virtual std::vector<facebook::react::NativeModuleDescription> GetModules(
      const std::shared_ptr<facebook::react::MessageQueueThread>
          &defaultQueueThread) override;
  void RegisterModule(INativeModule const &module);

 private:
  std::vector<INativeModule> m_modules;
};
} // namespace winrt::Microsoft::ReactNative::Bridge::implementation
