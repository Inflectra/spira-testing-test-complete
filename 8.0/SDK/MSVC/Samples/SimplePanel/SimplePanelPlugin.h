// SimplePanelPlugin.h : Declaration of the CSimplePanelPlugin

#pragma once

// CSimplePanelPlugin

class ATL_NO_VTABLE CSimplePanelPlugin : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSimplePanelPlugin>,
	public IaqExtendedPlugin,
	public IaqWindowProvider,
	public IaqActionNotifier,
	public IaqActionProvider
{
	BEGIN_COM_MAP(CSimplePanelPlugin)
		COM_INTERFACE_ENTRY(IaqBasePlugin)
		COM_INTERFACE_ENTRY(IaqExtendedPlugin)
		COM_INTERFACE_ENTRY(IaqWindowProvider)
		COM_INTERFACE_ENTRY(IaqActionNotifier)
		COM_INTERFACE_ENTRY(IaqActionProvider)
	END_COM_MAP()

public:
	CSimplePanelPlugin();

	static HRESULT CreatePlugin(IaqBasePlugin * * Value);
	static CONST GUID GetPluginKey();

	// IaqBasePlugin Methods
	STDMETHOD(Initialize)(IaqBaseManager * Manager);
	STDMETHOD(Update)();
	STDMETHOD(Finalize)();
	STDMETHOD(BaseManagerStateChanged)(AQ_MAINMANAGER_STATE State);

	// IaqKeyItem Methods
	STDMETHOD_(void, GetKey)(GUID * Value);

	// IaqExtendedPlugin Methods
	STDMETHOD(get_Name)(BSTR * Value);
	STDMETHOD(get_Category)(BSTR * Value);
	STDMETHOD(get_Image)(AQ_RESOURCE_INFO * Value);
	STDMETHOD(get_HelpFileName)(BSTR * Value);
	STDMETHOD(get_HelpContext)(long * Value);

	// IaqWindowProvider Methods
	STDMETHOD(get_CreatePaneAtStartup)(VARIANT_BOOL * Value);
	STDMETHOD(get_AcceptsHandleType)(AQ_HANDLE_TYPE SiteHandleType, VARIANT_BOOL * Value);
	STDMETHOD(put_Visible)(VARIANT_BOOL pValue);
	STDMETHOD(get_Visible)(VARIANT_BOOL * pValue);
	STDMETHOD(SetSite)(AQ_HANDLE_TYPE SiteHandleType, UINT_PTR SiteHandle);
	STDMETHOD(SetBounds)(long Left, long Top, long Width, long Height);

	// IaqActionNotifier Methods
	STDMETHOD_(AQ_ACTION_EXEC_RESULT, OnExecute)(IaqActionItem * Sender, VARIANT InValue, VARIANT * OutValue);
	STDMETHOD_(void, OnUpdate)(IaqActionItem * Sender);

	// IaqActionProvider Methods
	STDMETHOD(CreateActions)();
	STDMETHOD(ConfigureActions)();
	STDMETHOD(ActionsRemoved)();

private:
	CComPtr<IaqActionsCustomizer> m_action_customizer;
	CComPtr<IaqMessenger>         m_messenger;
	CComPtr<IaqActionManager>     m_action_manager;
	CMyPanelForm*                 m_panel;
	int                           m_iteration;
};
