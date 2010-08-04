// SimpleRuntimeObjectPlugIn.h : Declaration of the CSimpleRuntimeObjectPlugIn

#pragma once
#include "SimpleProgramObjectLib.h"


// CSimpleRuntimeObjectPlugIn

class ATL_NO_VTABLE CSimpleRuntimeObjectPlugIn : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSimpleRuntimeObjectPlugIn>,
	public IaqBasePlugin,
	public ItcRuntimeObjectFactory,
	public ItcCodeCompletionProvider
{
	BEGIN_COM_MAP(CSimpleRuntimeObjectPlugIn)
		COM_INTERFACE_ENTRY(ItcCodeCompletionProvider)
		COM_INTERFACE_ENTRY(ItcRuntimeObjectFactory)
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

	// ItcRuntimeObjectFactory Methods
	STDMETHOD_(void, CreateRuntimeObject)(BSTR ObjectName, GUID * ProjectKey, IDispatch * * Value);

	// ItcCodeCompletionProvider Methods
	STDMETHOD_(void, GetName)(BSTR * Value);
	STDMETHOD_(void, GetDescription)(BSTR * Value);
	STDMETHOD_(long, GetBitmapReference)();
	STDMETHOD_(long, GetTypeInformationCount)();
	STDMETHOD_(void, GetTypeInformation)(long Index, LPUNKNOWN * Value);
 
private:
	CComPtr<ItcRuntimeObjectsManager> m_runtime_objects_manager;
	long     m_runtime_object_cookie;
	HBITMAP  m_bitmap;
};
