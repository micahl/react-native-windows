#include "pch.h"
#include "ReactInstance.h"
#if __has_include("Bridge.ReactInstance.g.cpp")
#include "Bridge.ReactInstance.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::Microsoft::ReactNative::Bridge::implementation
{
	void ReactInstance::InvokeFunction(hstring moduleName, hstring method, Windows::Data::Json::JsonArray arguments, hstring tracingName)
	{
		throw winrt::hresult_not_implemented(L"ReactInstance.InvokeFunction");
	}

	void ReactInstance::InvokeCallback(int callbackId, Windows::Data::Json::JsonArray arguments)
	{
		throw winrt::hresult_not_implemented(L"ReactInstance.InvokeCallback");
	}
}
