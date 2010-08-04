// ISimpleProgramObject.h : Declaration of the CSimpleProgramObject

#pragma once
#include "SimpleProgramObjectLib.h"

extern "C" const TCHAR __declspec(selectany) cObjectName[] = _T("MyRuntimeObject");
extern "C" const TCHAR __declspec(selectany) cObjectDescription[] = _T("This is a sample program object.");


// CSimpleProgramObject

class ATL_NO_VTABLE CSimpleProgramObject : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSimpleProgramObject, &CLSID_SimpleProgramObject>,
	public IDispatchImpl<ISimpleProgramObject, &IID_ISimpleProgramObject, &LIBID_SimpleProgramObjectLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
	BEGIN_COM_MAP(CSimpleProgramObject)
		COM_INTERFACE_ENTRY(ISimpleProgramObject)
		COM_INTERFACE_ENTRY(IDispatch)
	END_COM_MAP()

public:
	CSimpleProgramObject();
	void Initialize(long frequency = 600, long duration = 300);

	// ISimpleProgramObject Methods
	STDMETHOD(Sound)();
	STDMETHOD(get_Frequency)(long * Value);
	STDMETHOD(put_Frequency)(long Value);
	STDMETHOD(get_Duration )(long * Value);
	STDMETHOD(put_Duration )(long Value);

private:
	long m_frequency;
	long m_duration;
};
