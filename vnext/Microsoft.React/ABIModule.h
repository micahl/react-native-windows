#pragma once

#include "ReactSupport.h"
#include <winrt\Microsoft.React.h>

class ABIModule : public facebook::xplat::module::CxxModule
{
public:
  ABIModule(winrt::Microsoft::React::INativeModule const& module)
    : m_module(module)
  {
    assert(module != nullptr);
  }

  std::string getName() override;

  std::map<std::string, folly::dynamic> getConstants() override;
  std::vector<facebook::xplat::module::CxxModule::Method> getMethods() override;

private:
  winrt::Microsoft::React::INativeModule m_module{ nullptr };
};

