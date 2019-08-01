// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include "pch.h"
#include "ABIModule.h"
#include "NativeModulesProvider.h"

#include <ReactUWP/ReactUwp.h>
#include <folly/json.h>
#include <windows.foundation.h>
#include "winrt/Windows.Foundation.Collections.h"
#include "winrt/Windows.Foundation.h"

namespace winrt::Microsoft::ReactNative::Bridge {
/*-------------------------------------------------------------------------------
  NativeModulesProvider::GetModules
-------------------------------------------------------------------------------*/
std::vector<facebook::react::NativeModuleDescription>
NativeModulesProvider::GetModules(
    const std::shared_ptr<facebook::react::MessageQueueThread>
        &defaultQueueThread) {
  std::shared_ptr<facebook::react::MessageQueueThread> queueThread(
      defaultQueueThread);
  std::vector<facebook::react::NativeModuleDescription> modules;
  modules.reserve(m_modules.size());

  for (auto module : m_modules) {
    modules.emplace_back(
        winrt::to_string(module.Name()),
        [module]() { return std::make_unique<ABIModule>(module); },
        queueThread);
  }

  return modules;
}

void NativeModulesProvider::RegisterModule(
    winrt::Microsoft::ReactNative::Bridge::INativeModule const &module) {
  // TODO: This is taking a naive approach right now and just adding everything.
  // Consider whether to add the CanOverrideExistingModule on INativeModule and
  // then check it here to see whether a module being registered is allowed to
  // take precedence over one that was already registered.
  m_modules.push_back(module);
}

} // namespace winrt::Microsoft::ReactNative::Bridge
