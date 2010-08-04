// MyPlugin.cpp : Implementation of CMyPlugin

#include "stdafx.h"
#include "MyPlugin.h"


// CMyPlugin

HRESULT STDMETHODCALLTYPE CMyPlugin::Initialize(IaqBaseManager * Manager)
{
	HRESULT hr;

	m_base_manager = Manager;

	CComPtr<IaqSubsystemManager> subsystem_manager;
	hr = m_base_manager->get_Managers(IID_IaqMessenger, &subsystem_manager);
	if (FAILED(hr)) return hr;

	CComPtr<IaqMessenger> messenger;
	hr = subsystem_manager->QueryInterface(&messenger);
	if (FAILED(hr)) return hr;

	hr = messenger->ShowInformation(CComBSTR("My plugin initialized."), 0, CComBSTR(_T("")));
	if (FAILED(hr)) return hr;

	return S_OK;
}


HRESULT STDMETHODCALLTYPE CMyPlugin::Update()
{
	return S_OK;
}


HRESULT STDMETHODCALLTYPE CMyPlugin::Finalize()
{
	m_base_manager = NULL;
	return S_OK;
}


HRESULT STDMETHODCALLTYPE CMyPlugin::BaseManagerStateChanged(AQ_MAINMANAGER_STATE /*State*/)
{
	return S_OK;
}


void STDMETHODCALLTYPE CMyPlugin::GetKey(GUID * Value)
{
	_ASSERT( Value != NULL );
	*Value = GetPluginKey();
}


CONST GUID CMyPlugin::GetPluginKey()
{
	CONST GUID key = {0x8602b65d, 0x3182, 0x4ee9, {0xb4, 0xf8, 0xeb, 0xfa, 0x68, 0x50, 0x8d, 0xdd}};
	return key;
}
