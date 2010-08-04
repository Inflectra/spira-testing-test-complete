// MyPlugin.h : Declaration of the CMyPlugin

#pragma once

// CMyPlugin

class ATL_NO_VTABLE CMyPlugin : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CMyPlugin>,
	public IaqBasePlugin
{
public:
	CMyPlugin() {}

	BEGIN_COM_MAP(CMyPlugin)
		COM_INTERFACE_ENTRY(IaqBasePlugin)
	END_COM_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease() 
	{
	}

public:
	static CONST GUID GetPluginKey();

	// IaqBasePlugin Methods
	STDMETHOD(Initialize)(IaqBaseManager * Manager);
	STDMETHOD(Update    )();
	STDMETHOD(Finalize  )();
	STDMETHOD(BaseManagerStateChanged)(AQ_MAINMANAGER_STATE State);

	// IaqKeyItem Methods
	STDMETHOD_(void, GetKey)(GUID * Value);

private:
	CComPtr<IaqBaseManager> m_base_manager;
};

