// SampleEditorPlugIn.cpp : Implementation of CSampleEditorPlugIn

#include "stdafx.h"
#include "SampleEditorPlugIn.h"


// CSampleEditorPlugIn

CSampleEditorPlugIn::CSampleEditorPlugIn()
{
}


// IaqBasePlugin Methods

HRESULT STDMETHODCALLTYPE CSampleEditorPlugIn::Initialize(IaqBaseManager * /*Manager*/)
{
	return S_OK;
}


HRESULT STDMETHODCALLTYPE CSampleEditorPlugIn::Update()
{
	return S_OK;
}


HRESULT STDMETHODCALLTYPE CSampleEditorPlugIn::Finalize()
{
	return S_OK;
}


HRESULT STDMETHODCALLTYPE CSampleEditorPlugIn::BaseManagerStateChanged(AQ_MAINMANAGER_STATE /*State*/)
{
	return S_OK;
}


// IaqKeyItem Methods

void STDMETHODCALLTYPE CSampleEditorPlugIn::GetKey(GUID * Value)
{
	_ASSERT( Value != NULL );
	*Value = GetPluginKey();
}


CONST GUID CSampleEditorPlugIn::GetPluginKey()
{
	CONST GUID key = { 0xeb89b72f, 0x3e1f, 0x465f, { 0x87, 0xe, 0x66, 0x60, 0xa3, 0x81, 0xcf, 0xdc } };
	return key;
}


HRESULT CSampleEditorPlugIn::CreatePlugin(IaqBasePlugin * * Value)
{
	_ASSERT( Value != NULL );

	CComObject<CSampleEditorPlugIn>* p;
	HRESULT hr = CComObject<CSampleEditorPlugIn>::CreateInstance(&p);
	if (FAILED(hr)) return hr;

	return p->QueryInterface(Value);
}
