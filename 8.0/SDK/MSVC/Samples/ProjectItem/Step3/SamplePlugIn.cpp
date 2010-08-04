// SamplePlugIn.cpp : Implementation of CSamplePlugIn

#include "stdafx.h"
#include "SampleProjectItem.h"
#include "SampleProjectItemInfo.h"
#include "SamplePlugIn.h"


// CSamplePlugIn

CSamplePlugIn::CSamplePlugIn()
{
	m_project_node_info = NULL;
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

HRESULT STDMETHODCALLTYPE CSamplePlugIn::Initialize(IaqBaseManager * Manager)
{
	HRESULT hr;

	CComPtr<IaqSubsystemManager> subsystem_manager;
	hr = Manager->get_Managers(IID_IaqMessenger, &subsystem_manager);
	if (FAILED(hr)) return hr;

	hr = subsystem_manager->QueryInterface(&m_messenger);
	if (FAILED(hr)) return hr;
	subsystem_manager = NULL;


	hr = Manager->get_Managers(IID_IaqCoreUI, &subsystem_manager);
	if (FAILED(hr)) return hr;

	hr = subsystem_manager->QueryInterface(&m_core_ui);
	if (FAILED(hr)) return hr;
	subsystem_manager = NULL;


	hr = Manager->get_Managers(IID_IaqEventManager, &subsystem_manager);
	if (FAILED(hr)) return hr;

	hr = subsystem_manager->QueryInterface(&m_event_manager);
	if (FAILED(hr)) return hr;
	subsystem_manager = NULL;


	hr = Manager->get_Managers(IID_IaqActionManager, &subsystem_manager);
	if (FAILED(hr)) return hr;

	hr = subsystem_manager->QueryInterface(&m_action_manager);
	if (FAILED(hr)) return hr;
	subsystem_manager = NULL;


	CComObject<CSampleProjectItemInfo>* p;
	hr = CComObject<CSampleProjectItemInfo>::CreateInstance(&p);
	if (FAILED(hr)) return hr;

	p->Initialize(m_messenger);

	return p->QueryInterface(&m_project_node_info);
}


HRESULT STDMETHODCALLTYPE CSamplePlugIn::Update()
{
	return S_OK;
}


HRESULT STDMETHODCALLTYPE CSamplePlugIn::Finalize()
{
	m_project_node_info = NULL;
	m_messenger         = NULL;
	m_core_ui           = NULL;
	m_event_manager     = NULL;
	m_action_manager    = NULL;
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


// ItcProjectNodeFactory Methods

HRESULT STDMETHODCALLTYPE CSamplePlugIn::get_ManagedProjectNodeCount(long * Value)
{
	_ASSERT( Value != NULL );
	*Value = 1;
	return S_OK;
}


HRESULT STDMETHODCALLTYPE CSamplePlugIn::CreateManagedProjectNode(GUID * /*ProjectNodeType*/, GUID * ProjectNodeKey, ItcProjectNodeConfigurationInfo * Configuration, IaqBaseManager * ABaseManager, ItcProjectNode * AOwnerNode, ItcProjectNode * * Value)
{
	CComObject<CSampleProjectItem>* new_item;
	HRESULT hr = CComObject<CSampleProjectItem>::CreateInstance(&new_item);
	if (FAILED(hr)) return hr;

	new_item->Initialize(*ProjectNodeKey, AOwnerNode, m_messenger, m_core_ui, m_event_manager, m_action_manager);
	new_item->Initialize(ABaseManager);

	if (Configuration != NULL)
		new_item->InitializeFromConfiguration(Configuration);

	return new_item->QueryInterface(Value);
}


HRESULT STDMETHODCALLTYPE CSamplePlugIn::CreateProjectNodeFromStorage(IaqBaseManager * ABaseManager, ItcProjectNode * AOwnerNode, BSTR StorageName, ItcProjectNode * * Value)
{
	_ASSERT( Value != NULL );

	HRESULT hr;

	// Get the node name from the file name
	CComBSTR node_name = GetCaptionFromFileName(_bstr_t(StorageName));
	// Check whether the node can be added
	if (NodeExistsInParent(AOwnerNode, node_name)) return ERROR_BAD_ARGUMENTS;

	// Generate the session-independent GUID
	GUID new_key;
	hr = CoCreateGuid(&new_key);
	if (FAILED(hr)) return hr;

	// Create the node
	CComObject<CSampleProjectItem>* new_item;
	hr = CComObject<CSampleProjectItem>::CreateInstance(&new_item);
	if (FAILED(hr)) return hr;

	new_item->Initialize(new_key, AOwnerNode, m_messenger, m_core_ui, m_event_manager, m_action_manager);

	// Initialize the node with the IaqBaseManager object
	hr = new_item->Initialize(ABaseManager);
	if (FAILED(hr)) return hr;

	// Read node's data from a file
	hr = new_item->InitializeFromFile(_bstr_t(StorageName), node_name);
	if (FAILED(hr)) return hr;

	return new_item->QueryInterface(Value);
}


HRESULT STDMETHODCALLTYPE CSamplePlugIn::GetManagedProjectNodeInfo(long ManagedNodeIndex, ItcProjectNodeInfo * * Value)
{
	_ASSERT( Value != NULL );
	_ASSERT( ManagedNodeIndex == 0 );

	if (ManagedNodeIndex == 0)
		return m_project_node_info.CopyTo(Value);
	else
		return ERROR_BAD_ARGUMENTS;
}
