// SampleProjectItem.h : Declaration of the CSampleProjectItem

#pragma once

#include "SampleEditItem.h"

// CSampleProjectItem

class ATL_NO_VTABLE CSampleProjectItem : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSampleProjectItem>,
	public ItcProjectNodeInternal,
	public ItcProjectItem,
	public ItcProjectContextItem,
	public ISampleEditItem,
	public IaqActionNotifier
{
	BEGIN_COM_MAP(CSampleProjectItem)
		COM_INTERFACE_ENTRY2(ItcProjectNode, ItcPersistentProjectNode)
		COM_INTERFACE_ENTRY (ItcPersistentProjectNode)
		COM_INTERFACE_ENTRY (ItcProjectNodeInternal)
		COM_INTERFACE_ENTRY (ItcProjectItem)
		COM_INTERFACE_ENTRY (ItcProjectContextItem)
		COM_INTERFACE_ENTRY (ISampleEditItem)
		COM_INTERFACE_ENTRY (ItcEditItem)
		COM_INTERFACE_ENTRY (IaqActionNotifier)
	END_COM_MAP()

public:
	CSampleProjectItem();
	void Initialize(GUID key, ItcProjectNode* owner, IaqMessenger* messenger, IaqCoreUI* core_ui, IaqEventManager* event_manager, IaqActionManager* action_manager);

	// IaqActionNotifier Methods
	STDMETHOD_(AQ_ACTION_EXEC_RESULT, OnExecute)(IaqActionItem * Sender, VARIANT InValue, VARIANT * OutValue);
	STDMETHOD_(void, OnUpdate)(IaqActionItem * Sender);

	// ISampleEditItem Methods
	STDMETHOD_(void, GetText)(BSTR * Text);
	STDMETHOD_(void, SetText)(BSTR Text);

	// ItcEditItem Methods
	STDMETHOD_(void, GetCaption)(BSTR * Value);
	STDMETHOD_(void, Commit)();
	STDMETHOD_(void, Rollback)();
	STDMETHOD_(long, GetGeneration)();
	STDMETHOD_(long, GetCommittedGeneration)();
	STDMETHOD_(void, GetProjectNode)(ItcProjectNode * * Value);

	// ItcProjectContextItem Methods
	STDMETHOD_(void, GetContextKey)(GUID * Value);

	// ItcProjectNodeInternal Methods
	STDMETHOD(Initialize)(IaqBaseManager * BaseManager);
	STDMETHOD(Finalize)();
	STDMETHOD(DeletePermanently)();
	STDMETHOD(QueryClose)(VARIANT_BOOL * Value);

	// ItcPersistentProjectNode Methods
	STDMETHOD(get_Dirty)(VARIANT_BOOL * Value);
	STDMETHOD(put_Dirty)(VARIANT_BOOL Value);
	STDMETHOD(Save)(AQ_SAVE_RESULT * Value);
	STDMETHOD(InitializeFromPersistentInfo)(IaqOptionsNode * PersistentInfo, VARIANT_BOOL * Value);
	STDMETHOD(StorePersistentInfo)(IaqOptionsNode * PersistentInfo);

	// ItcProjectNode Methods
	STDMETHOD(get_Caption)(BSTR * Value);
	STDMETHOD(put_Caption)(BSTR Value);
	STDMETHOD(get_NodeType)(GUID * Value);
	STDMETHOD(get_NodeProperty)(TC_PROJECT_NODE_PROP PropID, VARIANT * Value);
	STDMETHOD(put_NodeProperty)(enum TC_PROJECT_NODE_PROP PropID, VARIANT Value);
	STDMETHOD(GetNodeGUIDProperty)(enum TC_PROJECT_NODE_GUIDPROP PropID, GUID * Value);
	STDMETHOD(SetNodeGUIDProperty)(enum TC_PROJECT_NODE_GUIDPROP PropID, GUID * Value);
	STDMETHOD(get_OwnerNode)(ItcProjectNode * * Value);
	STDMETHOD(CreateChildIterator)(ItcProjectNodeIterator * * Value);
	STDMETHOD(get_HasTests)(VARIANT_BOOL * Value);
	STDMETHOD(GetTest)(BSTR Moniker, ItcTest * * Value);
	STDMETHOD(EnumTest)(ItcTestIterator * * Value);

	// IaqKeyItem Methods
	STDMETHOD_(void, GetKey)(GUID * Value);

	HRESULT InitializeFromConfiguration(CComPtr<ItcProjectNodeConfigurationInfo> configuration);
	HRESULT InitializeFromFile(CONST TCHAR* file_name, CComBSTR caption);

private:
	HRESULT Load();
	HRESULT SaveAs();
	void RenameNode(CONST TCHAR*  new_file_name, BOOL delete_source = TRUE, BOOL overwrite = FALSE);
	void ShowLastWindowsError();
	void SendNodeDataChangedEvent();

private:
	CComBSTR                  m_caption;
	TCHAR                     m_file_name[MAX_PATH];
	CComPtr<ItcProjectNode>   m_owner;
	GUID                      m_key;
	CComBSTR                  m_text;
	GUID                      m_context_key;
	HBITMAP                   m_personal_bitmap;
	CComVariant               m_scc_status;
	CComBSTR                  m_hint;

	CComPtr<IaqMessenger>     m_messenger;
	CComPtr<IaqCoreUI>        m_core_ui;
	CComPtr<IaqEventManager>  m_event_manager;
	CComPtr<IaqActionManager> m_action_manager;

	long                     m_generation;
	long                     m_committed_generation;
};
