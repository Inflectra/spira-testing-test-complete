// SimplePanel.cpp : Implementation of DLL Exports.

#include "stdafx.h"
#include "SimplePanel.h"
#include "aqExtensionRegistrator.h"
#include "MyPanelForm.h"
#include "SimplePanelPlugin.h"

class CSimplePanelModule : public CAtlDllModuleT< CSimplePanelModule >
{
public :
	DECLARE_LIBID(LIBID_SimplePanelLib)
};


CSimplePanelModule _AtlModule;
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

	CONST GUID key = { 0xa42cdd5, 0xfde4, 0x468c, { 0xbf, 0xa8, 0xc3, 0x62, 0x28, 0x2c, 0x40, 0x58 } };
	p->SetDescription(key, _T("Simple Panel Plugin"), cAQACopyright);

	AQ_PLUGIN_VERSION version = { 4, 0 };
	p->AddPlugin( CSimplePanelPlugin::CreatePlugin,
	              CSimplePanelPlugin::GetPluginKey(),
	              _T("My Panel"),
	              _T("My Panel Description"),
	              version);

	return p->QueryInterface(lpRetVal);
}
