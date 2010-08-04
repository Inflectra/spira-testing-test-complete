// SimpleRuntimeObjectPlugIn.h : Declaration of the CSimpleRuntimeObjectPlugIn

#pragma once
#include "SimpleProgramObjectLib.h"


// CSimpleRuntimeObjectPlugIn

class ATL_NO_VTABLE CSimpleRuntimeObjectPlugIn : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSimpleRuntimeObjectPlugIn>,
	public IaqBasePlugin 
{
	BEGIN_COM_MAP(CSimpleRuntimeObjectPlugIn)
		COM_INTERFACE_ENTRY(IaqBasePlugin)
	END_COM_MAP()

public:
	static HRESULT CreatePlugin(IaqBasePlugin * * Value);
	static CONST GUID GetPluginKey();

	CSimpleRuntimeObjectPlugIn();

	// IaqBasePlugin Methods
	STDMETHOD(Initialize)(IaqBaseManager * Manager);
	STDMETHOD(Update)();
	STDMETHOD(Finalize)();
	STDMETHOD(BaseManagerStateChanged)(AQ_MAINMANAGER_STATE State);

	// IaqKeyItem Methods
	STDMETHOD_(void, GetKey)(GUID * Value);
};
