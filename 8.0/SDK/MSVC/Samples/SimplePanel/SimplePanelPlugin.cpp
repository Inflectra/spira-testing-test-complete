// SimplePanelPlugin.cpp : Implementation of CSimplePanelPlugin

#include "stdafx.h"
#include "MyPanelForm.h"
#include "SimplePanelPlugin.h"


// CSimplePanelPlugin

CSimplePanelPlugin::CSimplePanelPlugin()
{
	m_panel     = NULL;
	m_iteration = 0;
}


// IaqBasePlugin Methods

HRESULT STDMETHODCALLTYPE CSimplePanelPlugin::Initialize(IaqBaseManager * Manager)
{
	_ASSERT( Manager != NULL );

	HRESULT hr;
	CComPtr<IaqSubsystemManager> subsystem_manager;

	hr = Manager->get_Managers(IID_IaqActionsCustomizer, &subsystem_manager);
	if (FAILED(hr)) return hr;
	hr = subsystem_manager->QueryInterface(&m_action_customizer);
	if (FAILED(hr)) return hr;
	subsystem_manager = NULL;

	hr = Manager->get_Managers(IID_IaqMessenger, &subsystem_manager);
	if (FAILED(hr)) return hr;
	hr = subsystem_manager->QueryInterface(&m_messenger);
	if (FAILED(hr)) return hr;
	subsystem_manager = NULL;

	hr = Manager->get_Managers(IID_IaqActionManager, &subsystem_manager);
	if (FAILED(hr)) return hr;
	hr = subsystem_manager->QueryInterface(&m_action_manager);
	if (FAILED(hr)) return hr;
	subsystem_manager = NULL;
	
	return S_OK;
}


HRESULT STDMETHODCALLTYPE CSimplePanelPlugin::Update()
{
	return S_OK;
}


HRESULT STDMETHODCALLTYPE CSimplePanelPlugin::Finalize()
{
	if (m_panel != NULL)
	{
		if (m_panel->IsWindow()) m_panel->DestroyWindow();
		delete m_panel;
	}
	m_panel             = NULL;

	m_action_customizer = NULL;
	m_messenger         = NULL;
	m_action_manager    = NULL;

	return S_OK;
}


HRESULT STDMETHODCALLTYPE CSimplePanelPlugin::BaseManagerStateChanged(AQ_MAINMANAGER_STATE /*State*/)
{
	return S_OK;
}


// IaqKeyItem Methods

void STDMETHODCALLTYPE CSimplePanelPlugin::GetKey(GUID * Value)
{
	_ASSERT( Value != NULL );
	*Value = GetPluginKey();
}


CONST GUID CSimplePanelPlugin::GetPluginKey()
{
	CONST GUID key = { 0x690e39fb, 0xa748, 0x4a58, { 0xb4, 0x15, 0x63, 0xd9, 0x26, 0x61, 0xe4, 0xe7 } };
	return key;
}


HRESULT CSimplePanelPlugin::CreatePlugin(IaqBasePlugin * * Value)
{
	_ASSERT( Value != NULL );

	CComObject<CSimplePanelPlugin>* p;
	HRESULT hr = CComObject<CSimplePanelPlugin>::CreateInstance(&p);
	if (FAILED(hr)) return hr;

	return p->QueryInterface(IID_IaqBasePlugin, (void**)Value);
}


HRESULT CSimplePanelPlugin::get_Name(BSTR * Value)
{
	_ASSERT( Value != NULL );
	CComBSTR name(_T("My Panel"));
	return name.CopyTo(Value);
}


HRESULT CSimplePanelPlugin::get_Category(BSTR * Value)
{
	_ASSERT( Value != NULL );
	CComBSTR category(_T(""));
	return category.CopyTo(Value);
}


HRESULT CSimplePanelPlugin::get_Image(AQ_RESOURCE_INFO * Value)
{
	_ASSERT( Value != NULL );
	HBITMAP hbitmap = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_MY_PANEL));
	_ASSERT( hbitmap != NULL );
	*Value = AQ_RESOURCE_INFO(hbitmap);
	return S_OK;
}


HRESULT CSimplePanelPlugin::get_HelpFileName(BSTR * Value)
{
	_ASSERT( Value != NULL );
	CComBSTR filename(_T(""));
	return filename.CopyTo(Value);
}


HRESULT CSimplePanelPlugin::get_HelpContext(long * Value)
{
	_ASSERT( Value != NULL );
	*Value = 0;
	return S_OK;
}


// IaqWindowProvider Methods

HRESULT CSimplePanelPlugin::get_CreatePaneAtStartup(VARIANT_BOOL * Value)
{
	_ASSERT( Value != NULL );
	*Value = VARIANT_TRUE;
	return S_OK;
}


HRESULT CSimplePanelPlugin::get_AcceptsHandleType(AQ_HANDLE_TYPE SiteHandleType, VARIANT_BOOL * Value)
{
	_ASSERT( Value != NULL );
	*Value = (SiteHandleType == htWindowHandle) ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}


HRESULT CSimplePanelPlugin::get_Visible(VARIANT_BOOL * pValue)
{
	_ASSERT( pValue != NULL );
	if (m_panel == NULL) return ERROR_INVALID_STATE;
	*pValue = m_panel->IsWindowVisible() ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}


HRESULT CSimplePanelPlugin::put_Visible(VARIANT_BOOL visible)
{
	if (m_panel != NULL)
		m_panel->ShowWindow(visible ? SW_SHOW : SW_HIDE);

	return S_OK;
}


HRESULT CSimplePanelPlugin::SetSite(AQ_HANDLE_TYPE SiteHandleType, UINT_PTR SiteHandle)
{
	_ASSERT( SiteHandleType == htWindowHandle );

	if (m_panel == NULL)
	{
		m_panel = new CMyPanelForm(m_action_customizer);
	}

	if (! m_panel->IsWindow())
	{
		RECT rect = { 0, 0, 0, 0 };
		m_panel->Create((HWND)SiteHandle, rect, NULL, WS_CHILD | WS_VISIBLE);
	}

	if (SiteHandle == NULL)
	{
		// Hide Control before detaching it from the parent.
		m_panel->ShowWindow(SW_HIDE);
	}
	else
	{
		_ASSERT( IsWindow((HWND)SiteHandle) );
		m_panel->SetParent((HWND)SiteHandle);
	}

	return S_OK;
}


HRESULT CSimplePanelPlugin::SetBounds(long Left, long Top, long Width, long Height)
{
	if (m_panel != NULL)
		m_panel->MoveWindow(Left, Top, Width, Height);
	return S_OK;
}


// IaqActionNotifier Methods

AQ_ACTION_EXEC_RESULT STDMETHODCALLTYPE CSimplePanelPlugin::OnExecute(IaqActionItem * Sender, VARIANT /*InValue*/, VARIANT * /*OutValue*/)
{
	GUID sender_key;
	Sender->GetKey(&sender_key);

	if (sender_key == MY_ACTION_KEY)
	{
		TCHAR msg[64];
		_stprintf(msg, _T("Iteration %d"), m_iteration);

		if (FAILED(m_messenger->ShowInformation(CComBSTR(msg), 0, CComBSTR(_T(""))))) return AQ_AER_ACTION_CANCELED;
		m_iteration++;
	}
	else
	{
		_ASSERT( false );
	}

	return AQ_AER_OK;
}


void STDMETHODCALLTYPE CSimplePanelPlugin::OnUpdate(IaqActionItem * Sender)
{
	GUID sender_key;
	Sender->GetKey(&sender_key);

	if (sender_key == MY_ACTION_KEY)
	{
		TCHAR msg[64];
		_stprintf(msg, _T("Iteration %d"), m_iteration);
		Sender->SetProperties(apCaption, CComVariant(msg) );
	}
	else
		_ASSERT( false );
}


// IaqActionProvider Methods

HRESULT CSimplePanelPlugin::CreateActions()
{
	HRESULT hr;

	CComPtr<IaqActionItem> action_item;
	hr = m_action_manager->CreateEmptyAction(atButton, MY_ACTION_KEY, CComBSTR("My Panel Actions"), VARIANT_FALSE, NULL_CONTEXT, &action_item);
	if (FAILED(hr)) return hr;
	_ASSERT( action_item != NULL );

	action_item->SetProperties(apCaption, CComVariant(_T("My panel")));
	action_item->SetProperties(apEnabled, CComVariant(VARIANT_TRUE));

	hr = m_action_manager->AddAction(action_item, GetPluginKey());
	if (FAILED(hr)) return hr;
	hr = m_action_manager->AddActionNotifier(MY_ACTION_KEY, NULL_CONTEXT, this);
	if (FAILED(hr)) return hr;

	return S_OK;
}


HRESULT CSimplePanelPlugin::ConfigureActions()
{
	HRESULT hr;

	CComPtr<IaqToolbar> toolbar;
	hr = m_action_customizer->AddToolbar(MY_TOOLBAR_KEY, GetPluginKey(), &toolbar);
	if (FAILED(hr)) return hr;

	hr = toolbar->put_Caption(CComBSTR(_T("My Panel")));
	if (FAILED(hr)) return hr;

	hr = toolbar->AddAction(MY_ACTION_KEY, mmFirst, NULL);
	if (FAILED(hr)) return hr;

	CComPtr<IaqPopupMenu> popup;
	hr = m_action_customizer->AddPopupMenu(MY_POPUP_KEY, GetPluginKey(), &popup);
	if (FAILED(hr)) return hr;

	hr = popup->AddAction(MY_ACTION_KEY, mmFirst, NULL);
	if (FAILED(hr)) return hr;

	return S_OK;
}


HRESULT CSimplePanelPlugin::ActionsRemoved()
{
	return S_OK;
}
