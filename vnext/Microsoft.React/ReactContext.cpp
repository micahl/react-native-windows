#include "pch.h"
#include "ReactContext.h"
#if __has_include("ReactContext.g.cpp")
#include "ReactContext.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::Microsoft::ReactNative::implementation
{
	Microsoft::ReactNative::IReactInstance ReactContext::ReactInstance()
	{
		throw winrt::hresult_not_implemented(L"ReactContext.ReactInstance.get");
	}
}
