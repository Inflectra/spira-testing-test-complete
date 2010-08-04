// SampleEditorPlugIn.h : Declaration of the CSampleEditorPlugIn

#pragma once

// CSampleEditorPlugIn

class ATL_NO_VTABLE CSampleEditorPlugIn : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSampleEditorPlugIn>,
	public IaqBasePlugin 
{
	BEGIN_COM_MAP(CSampleEditorPlugIn)
		COM_INTERFACE_ENTRY(IaqBasePlugin)
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

	// IaqKeyItem Methods
	STDMETHOD_(void, GetKey)(GUID * Value);
};
