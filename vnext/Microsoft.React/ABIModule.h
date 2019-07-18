#pragma once

#include <winrt\Microsoft.ReactNative.h>
#include "ReactSupport.h"

class ABIModule : public facebook::xplat::module::CxxModule {
 public:
  ABIModule(winrt::Microsoft::ReactNative::INativeModule const &module)
      : m_module(module) {
    assert(module != nullptr);
  }

  std::string getName() override;

  std::map<std::string, folly::dynamic> getConstants() override;
  std::vector<facebook::xplat::module::CxxModule::Method> getMethods() override;

 private:
  winrt::Microsoft::ReactNative::INativeModule m_module{nullptr};
};
