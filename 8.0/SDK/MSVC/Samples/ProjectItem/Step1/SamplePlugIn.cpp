// SamplePlugIn.cpp : Implementation of CSamplePlugIn

#include "stdafx.h"
#include "SamplePlugIn.h"


// CSamplePlugIn

CSamplePlugIn::CSamplePlugIn()
{
}


CONST GUID CSamplePlugIn::GetPluginKey()
{
	CONST GUID key = { 0x88f425e2, 0x3015, 0x430b, { 0xbb, 0xe4, 0xa2, 0x8d, 0x94, 0xb1, 0xf3, 0x79 } };
	return key;
}


HRESULT CSamplePlugIn::CreatePlugin(IaqBasePlugin * * Value)
{
	_ASSERT( Value != NULL );

	CComObject<CSamplePlugIn>* p;
	HRESULT hr = CComObject<CSamplePlugIn>::CreateInstance(&p);
	if (FAILED(hr)) return hr;

	return p->QueryInterface(Value);
}


// IaqBasePlugin Methods

HRESULT STDMETHODCALLTYPE CSamplePlugIn::Initialize(IaqBaseManager * /*Manager*/)
{
	return S_OK;
}


HRESULT STDMETHODCALLTYPE CSamplePlugIn::Update()
{
	return S_OK;
}


HRESULT STDMETHODCALLTYPE CSamplePlugIn::Finalize()
{
	return S_OK;
}


HRESULT STDMETHODCALLTYPE CSamplePlugIn::BaseManagerStateChanged(AQ_MAINMANAGER_STATE /*State*/)
{
	return S_OK;
}


// IaqKeyItem Methods

void STDMETHODCALLTYPE CSamplePlugIn::GetKey(GUID * Value)
{
	_ASSERT( Value != NULL );
	*Value = GetPluginKey();
}
