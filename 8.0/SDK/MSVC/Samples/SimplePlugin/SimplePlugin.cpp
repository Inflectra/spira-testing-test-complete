// SimplePlugin.cpp : Implementation of DLL Exports.

#include "stdafx.h"
#include "SimplePlugin.h"
#include "MySimplePluginRegistrator.h"


class CSimplePluginModule : public CAtlDllModuleT< CSimplePluginModule >
{
public :
	DECLARE_LIBID(LIBID_SimplePluginLib)
};

CSimplePluginModule _AtlModule;


// DLL Entry Point
extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	hInstance;
	return _AtlModule.DllMain(dwReason, lpReserved); 
}


EXTERN_C HRESULT STDAPICALLTYPE GetPluginRegistrator(IaqExtensionRegistrator** lpRetVal)
{
	CComObject<CMySimplePluginRegistrator>* p;
	HRESULT hr = CComObject<CMySimplePluginRegistrator>::CreateInstance(&p);
	if (FAILED(hr)) return hr;

	return p->QueryInterface(lpRetVal);
}
