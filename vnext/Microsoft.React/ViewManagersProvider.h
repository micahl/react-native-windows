#pragma once
/********************************************************************************
        ViewManagersProvider.h

        Copyright (c) Microsoft Corporation. All rights reserved.
 ********************************************************************************/
#pragma once

#include <ReactUWP/ViewManagerProvider.h>
#include <ReactWindowsCore/ViewManager.h>
#include "ReactSupport.h"

class ViewManagersProvider final : public react::uwp::ViewManagerProvider {
 public:
  virtual std::vector<react::uwp::NativeViewManager> GetViewManagers(
      const std::shared_ptr<react::uwp::IReactInstance> &instance) override;
};
