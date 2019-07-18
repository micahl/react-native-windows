// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include "pch.h"
#include "NativeModulesProvider.h"
#include <ReactUWP/ReactUwp.h>
#include "ABIModule.h"

#include <folly/json.h>
#include <windows.foundation.h>
#include "winrt\Windows.Foundation.Collections.h"
#include "winrt\Windows.Foundation.h"

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
    winrt::Microsoft::ReactNative::INativeModule const &module) {
  m_modules.push_back(module);
}
