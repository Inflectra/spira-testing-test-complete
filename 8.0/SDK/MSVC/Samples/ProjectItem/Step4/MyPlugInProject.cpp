// MyPlugInProject.cpp : Implementation of DLL Exports.

#include "stdafx.h"
#include "resource.h"
#include "MyPlugInProject.h"
#include "aqExtensionRegistrator.h"
#include "SampleEditorPlugIn.h"
#include "SamplePlugIn.h"

class CMyPlugInProjectModule : public CAtlDllModuleT< CMyPlugInProjectModule >
{
public :
	DECLARE_LIBID(LIBID_MyPlugInProjectLib)
};

CMyPlugInProjectModule _AtlModule;
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

	CONST GUID key = { 0x798e5def, 0xa919, 0x4420, { 0xb1, 0xe5, 0xa9, 0xc0, 0x27, 0x56, 0x31, 0x3f } };
	p->SetDescription(key, _T("Sample plug-in collection."), cAQACopyright);

	AQ_PLUGIN_VERSION version = { 4, 0 };
	p->AddPlugin( CSamplePlugIn::CreatePlugin,
	              CSamplePlugIn::GetPluginKey(),
	              _T("Sample Project Item"),
	              _T("An example of TestComplete project item."),
	              version);
	p->AddPlugin( CSampleEditorPlugIn::CreatePlugin,
	              CSampleEditorPlugIn::GetPluginKey(),
	              _T("Sample Project Item Editor"),
	              _T("The editor for the sample project item."),
	              version);

	return p->QueryInterface(lpRetVal);
}
