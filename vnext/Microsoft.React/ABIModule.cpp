#include "pch.h"
#include "ABIModule.h"
#include "NativeModulesProvider.h"
#include <ReactUWP/ReactUwp.h>

#include <folly/json.h>
#include <windows.foundation.h>
#include "winrt\Windows.Foundation.h"
#include "winrt\Windows.Foundation.Collections.h"

std::string ABIModule::getName()
{
  auto name = m_module.Name();

  return winrt::to_string(name);
}

std::map<std::string, folly::dynamic> ABIModule::getConstants()
{
  using namespace winrt::Windows::Foundation;
  using namespace winrt::Windows::Foundation::Collections;

  auto constantsMapView = m_module.Constants();
  auto constantsIter = constantsMapView.First();

  std::map<std::string, folly::dynamic> ret;
  boolean hasCurrent;

  do
  {
    hasCurrent = constantsIter.HasCurrent();

    if (!hasCurrent)
      break;

    auto pair = constantsIter.Current();

    winrt::hstring key, value;
    key = pair.Key();
    value = pair.Value();

    ret.emplace(winrt::to_string(key), folly::parseJson(winrt::to_string(value)));
    constantsIter.MoveNext();
  } while (hasCurrent);

  return ret;
}

std::vector<facebook::xplat::module::CxxModule::Method> ABIModule::getMethods()
{
  using namespace ABI::Windows::Foundation;
  using namespace ABI::Windows::Foundation::Collections;

  std::vector<facebook::xplat::module::CxxModule::Method> ret;
  boolean hasCurrent;

  // Add methods without callback
  auto methodsMapView = m_module.Methods();
  auto methodsIter = methodsMapView.First();

  do
  {
    hasCurrent = methodsIter.HasCurrent();

    if (!hasCurrent)
      break;

    auto pair = methodsIter.Current();

    winrt::hstring key;
    winrt::Microsoft::React::MethodDelegate value;
    key = pair.Key();
    value = pair.Value();

    ret.push_back(facebook::xplat::module::CxxModule::Method(winrt::to_string(key), [this, value](folly::dynamic args)
    {
      std::string str = folly::toJson(args);

      winrt::hstring para = winrt::to_hstring(str);
      value(para);
    }));

    methodsIter.MoveNext();

  } while (hasCurrent);

  // Add methods with callback

  auto methodsWithCallBackMapView = m_module.MethodsWithCallback();
  auto methodsWithCallBackIter = methodsWithCallBackMapView.First();

  do
  {
    if (!methodsWithCallBackIter.HasCurrent())
      break;

    auto pair = methodsWithCallBackIter.Current();

    winrt::hstring key;
    winrt::Microsoft::React::MethodWithCallbackDelegate value;
    key = pair.Key();
    value = pair.Value();

    ret.push_back(
      facebook::xplat::module::CxxModule::Method(winrt::to_string(key), [this, value](folly::dynamic args, Callback cb)
    {
      std::string str = folly::toJson(args);

      winrt::hstring para = winrt::to_hstring(str);

      auto callback = winrt::Microsoft::React::MethodCallback(
        [cb](winrt::Windows::Foundation::Collections::IVectorView<winrt::hstring> argVectorView)
      {
        std::vector<folly::dynamic> args;

        if (argVectorView != nullptr)
        {
          unsigned int size = argVectorView.Size();

          for (unsigned int i = 0; i < size; i++)
          {
            winrt::hstring itemString;
            itemString = argVectorView.GetAt(i);
            if (itemString.empty())
              args.push_back(nullptr);
            else
              args.push_back(folly::parseJson(winrt::to_string(itemString)));
          }
        }

        cb(args);
      });

      value(para, callback);
    }));

    methodsWithCallBackIter.MoveNext();
  } while (true);

  return ret;
}
