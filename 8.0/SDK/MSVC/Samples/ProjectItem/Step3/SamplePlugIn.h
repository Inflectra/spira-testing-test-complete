// SamplePlugIn.h : Declaration of the CSamplePlugIn

#pragma once

// CSamplePlugIn

class ATL_NO_VTABLE CSamplePlugIn : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSamplePlugIn>,
	public IaqBasePlugin,
	public ItcProjectNodeFactory 
{
	BEGIN_COM_MAP(CSamplePlugIn)
		COM_INTERFACE_ENTRY(IaqBasePlugin)
		COM_INTERFACE_ENTRY(ItcProjectNodeFactory)
	END_COM_MAP()

public:
	CSamplePlugIn();

	static HRESULT CreatePlugin(IaqBasePlugin * * Value);
	static CONST GUID GetPluginKey();

	// IaqBasePlugin Methods
	STDMETHOD(Initialize)(IaqBaseManager * Manager);
	STDMETHOD(Update)();
	STDMETHOD(Finalize)();
	STDMETHOD(BaseManagerStateChanged)(AQ_MAINMANAGER_STATE State);

	// IaqKeyItem Methods
	STDMETHOD_(void, GetKey)(GUID * Value);

	// ItcProjectNodeFactory Methods
	STDMETHOD(get_ManagedProjectNodeCount)(long * Value);
	STDMETHOD(CreateManagedProjectNode)(GUID * ProjectNodeType, GUID * ProjectNodeKey, ItcProjectNodeConfigurationInfo * Configuration, IaqBaseManager * ABaseManager, ItcProjectNode * AOwnerNode, ItcProjectNode * * Value);
	STDMETHOD(CreateProjectNodeFromStorage)(IaqBaseManager * ABaseManager, ItcProjectNode * AOwnerNode, BSTR StorageName, ItcProjectNode * * Value);
	STDMETHOD(GetManagedProjectNodeInfo)(long ManagedNodeIndex, ItcProjectNodeInfo * * Value);

private:
	CComPtr<ItcProjectNodeInfo> m_project_node_info;
	CComPtr<IaqMessenger>       m_messenger;
	CComPtr<IaqCoreUI>          m_core_ui;
	CComPtr<IaqEventManager>    m_event_manager;
	CComPtr<IaqActionManager>   m_action_manager;
};
