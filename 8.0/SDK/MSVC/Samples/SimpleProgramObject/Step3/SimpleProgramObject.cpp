// ISimpleProgramObject.cpp : Implementation of CSimpleProgramObject

#include "stdafx.h"
#include "SimpleProgramObject.h"

#define MIN_FREQUENCY (0x25   + 200)
#define MAX_FREQUENCY (0x7FFF - 200)
#define MIN_DURATION  (0      + 20 )
#define MAX_DURATION  (2000   - 20 )

// CSimpleProgramObject

CSimpleProgramObject::CSimpleProgramObject()
{
}

void CSimpleProgramObject::Initialize(long frequency, long duration)
{
	TCHAR module_name[MAX_PATH];
	GetModuleFileName(hInstance, module_name, MAX_PATH);

	CComPtr<ITypeLib> type_lib;
	LoadTypeLib(CComBSTR(module_name), &type_lib);

	CComPtr<ITypeInfo> type_info;
	type_lib->GetTypeInfoOfGuid(IID_ISimpleProgramObject, &type_info);
	_ASSERT( type_info != NULL );

	CComPtr<ITypeInfo2> type_info2;
	type_info->QueryInterface(&type_info2);
	_ASSERT( type_info2 != NULL );

	_tih.m_pInfo = type_info2.Detach();
	_pAtlModule->AddTermFunc(_tih.Cleanup, (DWORD_PTR)&_tih);


	m_frequency = frequency;
	m_duration  = duration;
}


// ISimpleProgramObject Methods

STDMETHODIMP CSimpleProgramObject::Sound()
{
	Beep(m_frequency + 200, m_duration - 20);
	Beep(m_frequency      , m_duration     );
	Beep(m_frequency - 200, m_duration + 20);

	return S_OK;
}

STDMETHODIMP CSimpleProgramObject::get_Frequency(long * Value)
{
	_ASSERT( Value != NULL );
	*Value = m_frequency;
	return S_OK;
}

STDMETHODIMP CSimpleProgramObject::put_Frequency(long Value)
{
	if ((Value < MIN_FREQUENCY) || (Value > MAX_FREQUENCY)) return E_INVALIDARG;
	m_frequency = Value;
	return S_OK;
}

STDMETHODIMP CSimpleProgramObject::get_Duration(long * Value)
{
	_ASSERT( Value != NULL );
	*Value = m_duration;
	return S_OK;
}

STDMETHODIMP CSimpleProgramObject::put_Duration(long Value)
{
	if ((Value < MIN_DURATION) || (Value > MAX_DURATION)) return E_INVALIDARG;
	m_duration = Value;
	return S_OK;
}
