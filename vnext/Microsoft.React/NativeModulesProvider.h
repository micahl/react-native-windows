#pragma once
#include "ReactSupport.h"
#include <NativeModuleProvider.h>
#include <winrt\Microsoft.ReactNative.h>

class NativeModulesProvider final : public facebook::react::NativeModuleProvider
{
public:
	virtual std::vector<facebook::react::NativeModuleDescription> GetModules(const std::shared_ptr<facebook::react::MessageQueueThread>& defaultQueueThread) override;
  void RegisterModule(winrt::Microsoft::ReactNative::INativeModule const& module);

private:
	std::vector<winrt::Microsoft::ReactNative::INativeModule> m_modules;
};
