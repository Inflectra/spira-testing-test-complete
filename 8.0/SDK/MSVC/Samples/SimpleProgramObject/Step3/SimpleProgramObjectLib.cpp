// SimpleProgramObject.cpp : Implementation of DLL Exports.

#include "stdafx.h"
#include "resource.h"
#include "aqExtensionRegistrator.h"
#include "SimpleRuntimeObjectPlugIn.h"

class CSimpleProgramObjectModule : public CAtlDllModuleT< CSimpleProgramObjectModule >
{
public :
	DECLARE_LIBID(LIBID_SimpleProgramObjectLib)
};

CSimpleProgramObjectModule _AtlModule;
HINSTANCE hInstance;

// DLL Entry Point
extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	::hInstance = hInstance;
	return _AtlModule.DllMain(dwReason, lpReserved); 
}


EXTERN_C HRESULT STDAPICALLTYPE GetPluginRegistrator(IaqExtensionRegistrator** lpRetVal)
{
	CComObject<CaqExtensionRegistrator>* p;
	HRESULT hr = CComObject<CaqExtensionRegistrator>::CreateInstance(&p);
	if (FAILED(hr)) return hr;

	CONST GUID key = { 0xA97B0A16, 0x6296, 0x43B4, { 0xBB, 0xE0, 0x59, 0x9C, 0x09, 0x4E, 0x3B, 0xB6 } };
	p->SetDescription(key, _T("Simple Program Object Plug-in Registrator"), cAQACopyright);

	AQ_PLUGIN_VERSION version = { 4, 0 };
	p->AddPlugin( CSimpleRuntimeObjectPlugIn::CreatePlugin,
	              CSimpleRuntimeObjectPlugIn::GetPluginKey(),
	              _T("Simple Program Object Plug-In"),
	              _T("Demonstrates creation of runtime objects."),
	              version);

	return p->QueryInterface(lpRetVal);
}
