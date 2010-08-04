// SamplePlugIn.h : Declaration of the CSamplePlugIn

#pragma once

// CSamplePlugIn

class ATL_NO_VTABLE CSamplePlugIn : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSamplePlugIn>,
	public IaqBasePlugin 
{
	BEGIN_COM_MAP(CSamplePlugIn)
		COM_INTERFACE_ENTRY(IaqBasePlugin)
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
};
