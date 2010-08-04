// SampleEditorPlugIn.cpp : Implementation of CSampleEditorPlugIn

#include "stdafx.h"
#include "SampleEditorPlugIn.h"
#include "SampleEditor.h"
#include "MyPlugInProject.h"

// CSampleEditorPlugIn

CSampleEditorPlugIn::CSampleEditorPlugIn()
{
}


// IaqBasePlugin Methods

HRESULT STDMETHODCALLTYPE CSampleEditorPlugIn::Initialize(IaqBaseManager * Manager)
{
	HRESULT hr = Manager->QueryInterface(IID_IaqBaseManagerEx, (void**)&m_base_manager_ex);
	if (FAILED(hr)) return hr;

	return S_OK;
}


HRESULT STDMETHODCALLTYPE CSampleEditorPlugIn::Update()
{
	return S_OK;
}


HRESULT STDMETHODCALLTYPE CSampleEditorPlugIn::Finalize()
{
	m_base_manager_ex = NULL;
	return S_OK;
}


HRESULT STDMETHODCALLTYPE CSampleEditorPlugIn::BaseManagerStateChanged(AQ_MAINMANAGER_STATE /*State*/)
{
	return S_OK;
}


// ItcEditorProvider Methods

long STDMETHODCALLTYPE CSampleEditorPlugIn::GetBitmap()
{
	HBITMAP bitmap = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_SAMPLEITEM));
	_ASSERT( bitmap != NULL );
	return (long)bitmap;
}


void STDMETHODCALLTYPE CSampleEditorPlugIn::GetDescription(BSTR * Value)
{
	CComBSTR (_T("Custom Project Item Editor")).CopyTo(Value);
}


VARIANT_BOOL STDMETHODCALLTYPE CSampleEditorPlugIn::IsSupportEditItem(ItcEditItem * AItem)
{
	CComPtr<ISampleEditItem> p;
	if (FAILED(AItem->QueryInterface(&p))) return VARIANT_FALSE;
	if (p == NULL) return VARIANT_FALSE;
	return VARIANT_TRUE;
}


void STDMETHODCALLTYPE CSampleEditorPlugIn::CreateEditor(ItcEditItem * EditItem, ItcEditor * * ppEditor)
{
	CComPtr<ISampleEditItem> m_edit_item;
	EditItem->QueryInterface(IID_ISampleEditItem, (void**)&m_edit_item);

	_ASSERT( m_edit_item != NULL );

	CComObject<CSampleEditor>* editor;
	CComObject<CSampleEditor>::CreateInstance(&editor);

	editor->Initialize(m_edit_item, m_base_manager_ex);

	editor->QueryInterface(ppEditor);

	editor = NULL;
}


EDITOR_MULTIPLE_INSTANCE STDMETHODCALLTYPE CSampleEditorPlugIn::AllowMultipleInstances()
{
	return emiAllow;
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
