// SampleRuntimeObject.cpp : Implementation of CSampleRuntimeObject

#include "stdafx.h"
#include "SampleRuntimeObject.h"


// CSampleRuntimeObject

CSampleRuntimeObject::CSampleRuntimeObject()
{
	m_project_item = NULL;
}


void CSampleRuntimeObject::Initialize(CComPtr<ITypeLib> type_lib, GUID disp_intf, CComPtr<ISampleEditItem> project_item, CComPtr<IaqMessenger> messenger)
{
	CComPtr<ITypeInfo> type_info;
//	type_lib->GetTypeInfoOfGuid(*_tih.m_pguid, &type_info);
	type_lib->GetTypeInfoOfGuid(disp_intf, &type_info);
	_ASSERT( type_info != NULL );

	CComPtr<ITypeInfo2> type_info2;
	type_info->QueryInterface(&type_info2);
	_ASSERT( type_info2 != NULL );

	_tih.m_pInfo = type_info2.Detach();
	_pAtlModule->AddTermFunc(_tih.Cleanup, (DWORD_PTR)&_tih);


	m_project_item = project_item;
	m_messenger    = messenger;
}


CSampleRuntimeObject::~CSampleRuntimeObject()
{
	m_project_item = NULL;
}


// ISampleEditItem Methods

STDMETHODIMP CSampleRuntimeObject::get_Text(BSTR* pVal)
{
	_ASSERT( m_project_item != NULL );
	_ASSERT( pVal != NULL );

	m_project_item->GetText(pVal);
	return S_OK;
}

STDMETHODIMP CSampleRuntimeObject::put_Text(BSTR newVal)
{
	_ASSERT( m_project_item != NULL );
	m_project_item->SetText(newVal);
	return S_OK;
}

STDMETHODIMP CSampleRuntimeObject::ShowText(void)
{
	_ASSERT( m_messenger != NULL );
	
	CComBSTR text;
	get_Text(&text);
	return m_messenger->ShowInformation(text, 0, CComBSTR(_T("")));
}
