// MySimplePluginRegistrator.cpp : Implementation of CMySimplePluginRegistrator

#include "stdafx.h"
#include "MySimplePluginRegistrator.h"
#include "MyPlugin.h"


CMySimplePluginRegistrator::CMySimplePluginRegistrator()
{
}

HRESULT STDMETHODCALLTYPE CMySimplePluginRegistrator::get_Name(BSTR * Value)
{ 
	_ASSERT( Value != NULL );
	CComBSTR name(_T("Simple Plugin"));
	return name.CopyTo(Value);
}

HRESULT STDMETHODCALLTYPE CMySimplePluginRegistrator::get_Copyright(BSTR * Value)
{
	_ASSERT( Value != NULL );
	CComBSTR copyright(cAQACopyright);
	return copyright.CopyTo(Value);
}

HRESULT STDMETHODCALLTYPE CMySimplePluginRegistrator::get_TargetIntegrationCount(long * Value)
{
	_ASSERT( Value != NULL );
	*Value = sizeof(cAllIntegrationType) / sizeof(cAllIntegrationType[0]);
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CMySimplePluginRegistrator::get_TargetIntegrationKey(long Index, GUID * Value)
{
	_ASSERT( Value != NULL );
	if (Index < 0) return E_INVALIDARG;
	if (Index >= (sizeof(cAllIntegrationType) / sizeof(cAllIntegrationType[0]))) return E_INVALIDARG;
	*Value = *(cAllIntegrationType[Index]);
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CMySimplePluginRegistrator::get_TargetProductCount(long * Value)
{
	_ASSERT( Value != NULL );
	*Value = sizeof(cAllProduct) / sizeof(cAllProduct[0]);
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CMySimplePluginRegistrator::get_TargetProductKey(long Index, GUID * Value)
{
	_ASSERT( Value != NULL );
	if (Index < 0) return E_INVALIDARG;
	if (Index >= (sizeof(cAllProduct) / sizeof(cAllProduct[0]))) return E_INVALIDARG;
	*Value = *(cAllProduct[Index]);
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CMySimplePluginRegistrator::get_PluginCount(long * Value)
{
	_ASSERT( Value != NULL );
	*Value = 1;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CMySimplePluginRegistrator::get_PluginKey(long Index, GUID * Value)
{
	_ASSERT( Value != NULL );
	if (Index != 0) return E_INVALIDARG;
	*Value = CMyPlugin::GetPluginKey();
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CMySimplePluginRegistrator::get_PluginName(long Index, BSTR * Value)
{
	_ASSERT( Value != NULL );
	if (Index != 0) return E_INVALIDARG;
	CComBSTR name(_T("My Plugin"));
	return name.CopyTo(Value);
}

HRESULT STDMETHODCALLTYPE CMySimplePluginRegistrator::get_PluginDescription(long Index, BSTR * Value)
{
	_ASSERT( Value != NULL );
	if (Index != 0) return E_INVALIDARG;
	CComBSTR description(_T("My Plugin Description"));
	return description.CopyTo(Value);
}

HRESULT STDMETHODCALLTYPE CMySimplePluginRegistrator::get_PluginVersion(long Index, AQ_PLUGIN_VERSION * Value)
{
	_ASSERT( Value != NULL );
	if (Index != 0) return E_INVALIDARG;
	Value->Major = 4;
	Value->Minor = 0;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CMySimplePluginRegistrator::get_PluginDefaultSelected(long Index, VARIANT_BOOL * Value)
{
	_ASSERT( Value != NULL );
	if (Index != 0) return E_INVALIDARG;
	*Value = VARIANT_TRUE;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CMySimplePluginRegistrator::get_PluginDependencyCount(long Index, long * Value)
{
	_ASSERT( Value != NULL );
	if (Index != 0) return E_INVALIDARG;
	*Value = 0;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CMySimplePluginRegistrator::get_PluginDependencies(long /*Index*/, long /*DependsIndex*/, GUID * /*Value*/)
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE CMySimplePluginRegistrator::get_PluginConflictCount(long Index, long * Value)
{
	_ASSERT( Value != NULL );
	if (Index != 0) return E_INVALIDARG;
	*Value = 0;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CMySimplePluginRegistrator::get_PluginConflicts(long /*Index*/, long /*ConflictIndex*/, GUID * /*Value*/)
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE CMySimplePluginRegistrator::CreatePlugin(long Index, IaqBasePlugin * * Value)
{
	_ASSERT( Value != NULL );
	if (Index != 0) return E_INVALIDARG;

	CComObject<CMyPlugin>* p;
	HRESULT hr = CComObject<CMyPlugin>::CreateInstance(&p);
	if (FAILED(hr)) return hr;

	return p->QueryInterface(IID_IaqBasePlugin, (void**)Value);
}


// IaqKeyItem Methods
void STDMETHODCALLTYPE CMySimplePluginRegistrator::GetKey(GUID * Value)
{
	_ASSERT( Value != NULL );
	CONST GUID key = {0x1e01cb7, 0x822f, 0x431b, { 0x8c, 0x26, 0x14, 0x5, 0x58, 0xf3, 0x24, 0x13 }};
	*Value = key;
}
