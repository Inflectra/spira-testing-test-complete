// SampleEditorPlugIn.h : Declaration of the CSampleEditorPlugIn

#pragma once

// CSampleEditorPlugIn

class ATL_NO_VTABLE CSampleEditorPlugIn : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSampleEditorPlugIn>,
	public IaqBasePlugin,
	public ItcEditorProvider 
{
	BEGIN_COM_MAP(CSampleEditorPlugIn)
		COM_INTERFACE_ENTRY(IaqBasePlugin)
		COM_INTERFACE_ENTRY(ItcEditorProvider)
	END_COM_MAP()

public:
	CSampleEditorPlugIn();

	static HRESULT CreatePlugin(IaqBasePlugin * * Value);
	static CONST GUID GetPluginKey();

	// IaqBasePlugin Methods
	STDMETHOD(Initialize)(IaqBaseManager * Manager);
	STDMETHOD(Update)();
	STDMETHOD(Finalize)();
	STDMETHOD(BaseManagerStateChanged)(AQ_MAINMANAGER_STATE State);

	// ItcEditorProvider Methods
	STDMETHOD_(long, GetBitmap)();
	STDMETHOD_(void, GetDescription)(BSTR * Value);
	STDMETHOD_(VARIANT_BOOL, IsSupportEditItem)(ItcEditItem * AItem);
	STDMETHOD_(void, CreateEditor)(ItcEditItem * EditItem, ItcEditor * * ppEditor);
	STDMETHOD_(EDITOR_MULTIPLE_INSTANCE, AllowMultipleInstances)();

	// IaqKeyItem Methods
	STDMETHOD_(void, GetKey)(GUID * Value);

private:
	CComPtr<IaqBaseManagerEx> m_base_manager_ex;
};
