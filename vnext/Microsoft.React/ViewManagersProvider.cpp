/********************************************************************************
	ViewManagersProvider.cpp

	Copyright (c) Microsoft Corporation. All rights reserved.
 ********************************************************************************/
#include "pch.h"
#include "ViewManagersProvider.h"

#include <ReactUWP/ReactUwp.h>


  /*-------------------------------------------------------------------------------
	  ViewManagersProvider::GetViewManagers
  -------------------------------------------------------------------------------*/
std::vector<react::uwp::NativeViewManager> ViewManagersProvider::GetViewManagers(const std::shared_ptr<react::uwp::IReactInstance>& instance)
{
	std::vector<react::uwp::NativeViewManager> viewManagers;

	//viewManagers.emplace_back(std::make_unique<Outlook::CalendarViewViewManager>(instance));

	return viewManagers;
}
