// SimpleRuntimeObjectPlugIn.cpp : Implementation of CSimpleRuntimeObjectPlugIn

#include "stdafx.h"
#include "SimpleRuntimeObjectPlugIn.h"


// CSimpleRuntimeObjectPlugIn

CSimpleRuntimeObjectPlugIn::CSimpleRuntimeObjectPlugIn()
{
}


// IaqBasePlugin Methods

HRESULT STDMETHODCALLTYPE CSimpleRuntimeObjectPlugIn::Initialize(IaqBaseManager * /*Manager*/)
{
	return S_OK;
}


HRESULT STDMETHODCALLTYPE CSimpleRuntimeObjectPlugIn::Update()
{
	return S_OK;
}


HRESULT STDMETHODCALLTYPE CSimpleRuntimeObjectPlugIn::Finalize()
{
	return S_OK;
}


HRESULT STDMETHODCALLTYPE CSimpleRuntimeObjectPlugIn::BaseManagerStateChanged(AQ_MAINMANAGER_STATE /*State*/)
{
	return S_OK;
}


// IaqKeyItem Methods

void STDMETHODCALLTYPE CSimpleRuntimeObjectPlugIn::GetKey(GUID * Value)
{
	_ASSERT( Value != NULL );
	*Value = GetPluginKey();
}


CONST GUID CSimpleRuntimeObjectPlugIn::GetPluginKey()
{
	CONST GUID key = // {337AF963-1B72-4efe-B232-ECA15BC0AC5D}
	{ 0x337af963, 0x1b72, 0x4efe, { 0xb2, 0x32, 0xec, 0xa1, 0x5b, 0xc0, 0xac, 0x5d } };
	return key;
}


HRESULT CSimpleRuntimeObjectPlugIn::CreatePlugin(IaqBasePlugin * * Value)
{
	_ASSERT( Value != NULL );

	CComObject<CSimpleRuntimeObjectPlugIn>* p;
	HRESULT hr = CComObject<CSimpleRuntimeObjectPlugIn>::CreateInstance(&p);
	if (FAILED(hr)) return hr;

	return p->QueryInterface(Value);
}
