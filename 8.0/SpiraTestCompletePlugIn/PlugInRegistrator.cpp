// =============================================================================================
// SpiraTest Plug-In Registration Class - Copyright (c) 2006-2009 Inflectra Corporation
//
// This file is part of the SpiraTest TestComplete Plug-In
//
// =============================================================================================

#include "stdafx.h"
#include "SpiraTestCompletePlugIn.h"
#include "spiraConsts.h"
#include "PlugInRegistrator.h"

CPlugInRegistrator::CPlugInRegistrator()
{
}

HRESULT STDMETHODCALLTYPE CPlugInRegistrator::get_Name(BSTR * Value)
{ 
	_ASSERT( Value != NULL );
	CComBSTR name(spiraTestPlugInName);
	return name.CopyTo(Value);
}

HRESULT STDMETHODCALLTYPE CPlugInRegistrator::get_Copyright(BSTR * Value)
{
	_ASSERT( Value != NULL );
	CComBSTR copyright(inflectraCopyright);
	return copyright.CopyTo(Value);
}

HRESULT STDMETHODCALLTYPE CPlugInRegistrator::get_TargetIntegrationCount(long * Value)
{
	_ASSERT( Value != NULL );
	*Value = sizeof(cAllIntegrationType) / sizeof(cAllIntegrationType[0]);
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CPlugInRegistrator::get_TargetIntegrationKey(long Index, GUID * Value)
{
	_ASSERT( Value != NULL );
	if (Index < 0) return E_INVALIDARG;
	if (Index >= (sizeof(cAllIntegrationType) / sizeof(cAllIntegrationType[0]))) return E_INVALIDARG;
	*Value = *(cAllIntegrationType[Index]);
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CPlugInRegistrator::get_TargetProductCount(long * Value)
{
	_ASSERT( Value != NULL );
	*Value = sizeof(cAllProduct) / sizeof(cAllProduct[0]);
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CPlugInRegistrator::get_TargetProductKey(long Index, GUID * Value)
{
	_ASSERT( Value != NULL );
	if (Index < 0) return E_INVALIDARG;
	if (Index >= (sizeof(cAllProduct) / sizeof(cAllProduct[0]))) return E_INVALIDARG;
	*Value = *(cAllProduct[Index]);
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CPlugInRegistrator::get_PluginCount(long * Value)
{
	_ASSERT( Value != NULL );
	*Value = 1;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CPlugInRegistrator::get_PluginKey(long Index, GUID * Value)
{
	_ASSERT( Value != NULL );
	if (Index != 0) return E_INVALIDARG;
	*Value = CSpiraTestPlugIn::GetPluginKey();
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CPlugInRegistrator::get_PluginName(long Index, BSTR * Value)
{
	_ASSERT( Value != NULL );
	if (Index != 0) return E_INVALIDARG;
	CComBSTR name(spiraTestPlugInName);
	return name.CopyTo(Value);
}

HRESULT STDMETHODCALLTYPE CPlugInRegistrator::get_PluginDescription(long Index, BSTR * Value)
{
	_ASSERT( Value != NULL );
	if (Index != 0) return E_INVALIDARG;
	CComBSTR description(spiraTestPlugInDesc);
	return description.CopyTo(Value);
}

HRESULT STDMETHODCALLTYPE CPlugInRegistrator::get_PluginVersion(long Index, AQ_PLUGIN_VERSION * Value)
{
	_ASSERT( Value != NULL );
	if (Index != 0) return E_INVALIDARG;
	Value->Major = spiraTestPlugInMajorVersion;
	Value->Minor = spiraTestPlugInMinorVersion;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CPlugInRegistrator::get_PluginDefaultSelected(long Index, VARIANT_BOOL * Value)
{
	_ASSERT( Value != NULL );
	if (Index != 0) return E_INVALIDARG;
	*Value = VARIANT_TRUE;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CPlugInRegistrator::get_PluginDependencyCount(long Index, long * Value)
{
	_ASSERT( Value != NULL );
	if (Index != 0) return E_INVALIDARG;
	*Value = 0;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CPlugInRegistrator::get_PluginDependencies(long /*Index*/, long /*DependsIndex*/, GUID * /*Value*/)
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE CPlugInRegistrator::get_PluginConflictCount(long Index, long * Value)
{
	_ASSERT( Value != NULL );
	if (Index != 0) return E_INVALIDARG;
	*Value = 0;
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CPlugInRegistrator::get_PluginConflicts(long /*Index*/, long /*ConflictIndex*/, GUID * /*Value*/)
{
	return E_NOTIMPL;
}

HRESULT STDMETHODCALLTYPE CPlugInRegistrator::CreatePlugin(long Index, IaqBasePlugin * * Value)
{
	_ASSERT( Value != NULL );
	if (Index != 0) return E_INVALIDARG;

	CComObject<CSpiraTestPlugIn>* p;
	HRESULT hr = CComObject<CSpiraTestPlugIn>::CreateInstance(&p);
	if (FAILED(hr)) return hr;

	return p->QueryInterface(IID_IaqBasePlugin, (void**)Value);
}

void STDMETHODCALLTYPE CPlugInRegistrator::GetKey(GUID * Value)
{
    _ASSERT( Value != NULL );
    CONST GUID key = {0x1e01cb7, 0x822f, 0x431b, { 0x8c, 0x26, 0x14, 0x5, 0x58, 0xf3, 0x24, 0x13 }};
    *Value = key;
}
