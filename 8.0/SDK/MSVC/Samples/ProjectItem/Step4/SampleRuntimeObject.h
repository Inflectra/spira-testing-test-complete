// SampleRuntimeObject.h : Declaration of the CSampleRuntimeObject

#pragma once

#include "MyPlugInProject.h"
#include "SampleEditItem.h"


// CSampleRuntimeObject

class ATL_NO_VTABLE CSampleRuntimeObject : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSampleRuntimeObject, &CLSID_SampleRuntimeObject>,
	public IDispatchImpl<ISampleRuntimeObject, &IID_ISampleRuntimeObject, &LIBID_MyPlugInProjectLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
	BEGIN_COM_MAP(CSampleRuntimeObject)
		COM_INTERFACE_ENTRY(ISampleRuntimeObject)
		COM_INTERFACE_ENTRY(IDispatch)
	END_COM_MAP()

public:
	CSampleRuntimeObject();
	virtual ~CSampleRuntimeObject();
	void Initialize(CComPtr<ITypeLib> type_lib, GUID disp_intf, CComPtr<ISampleEditItem> project_item, CComPtr<IaqMessenger> messenger);

	// ISampleEditItem Methods
	STDMETHOD(get_Text)(BSTR* pVal);
	STDMETHOD(put_Text)(BSTR newVal);
	STDMETHOD(ShowText)(void);

private:
	CComBSTR                 m_text;
	CComPtr<ISampleEditItem> m_project_item;
	CComPtr<IaqMessenger>    m_messenger;
};
