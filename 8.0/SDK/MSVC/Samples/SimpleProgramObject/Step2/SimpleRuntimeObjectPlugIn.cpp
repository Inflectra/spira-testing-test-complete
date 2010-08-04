// SimpleRuntimeObjectPlugIn.cpp : Implementation of CSimpleRuntimeObjectPlugIn

#include "stdafx.h"
#include "SimpleRuntimeObjectPlugIn.h"
#include "SimpleProgramObject.h"

// CSimpleRuntimeObjectPlugIn

CSimpleRuntimeObjectPlugIn::CSimpleRuntimeObjectPlugIn()
{
}


// IaqBasePlugin Methods

HRESULT STDMETHODCALLTYPE CSimpleRuntimeObjectPlugIn::Initialize(IaqBaseManager * Manager)
{
	_ASSERT( Manager != NULL );
	HRESULT hr;
	CComPtr<IaqSubsystemManager> subsystem_manager;

	hr = Manager->get_Managers(IID_ItcRuntimeObjectsManager, &subsystem_manager);
	if (FAILED(hr)) return hr;

	hr = subsystem_manager->QueryInterface(&m_runtime_objects_manager);
	if (FAILED(hr)) return hr;
	subsystem_manager = NULL;


	CComPtr<ItcRuntimeObjectFactory> factory;
	this->QueryInterface(IID_ItcRuntimeObjectFactory, (void**)&factory);
	_ASSERT( factory != NULL );

	GUID key = GUID_NULL;
	m_runtime_object_cookie = m_runtime_objects_manager->RegisterRuntimeObjectFactory(
		CComBSTR(cObjectName),
		VARIANT_FALSE,
		&key,
		factory);

	return S_OK;
}


HRESULT STDMETHODCALLTYPE CSimpleRuntimeObjectPlugIn::Update()
{
	return S_OK;
}


HRESULT STDMETHODCALLTYPE CSimpleRuntimeObjectPlugIn::Finalize()
{
	m_runtime_objects_manager->RemoveRuntimeObject(m_runtime_object_cookie);

	m_runtime_objects_manager = NULL;

	return S_OK;
}


HRESULT STDMETHODCALLTYPE CSimpleRuntimeObjectPlugIn::BaseManagerStateChanged(AQ_MAINMANAGER_STATE /*State*/)
{
	return S_OK;
}


// IaqKeyItem Methods

void STDMETHODCALLTYPE CSimpleRuntimeObjectPlugIn::GetKey(GUID * Value)
{
	_ASSERT( Value != NULL );
	*Value = GetPluginKey();
}


CONST GUID CSimpleRuntimeObjectPlugIn::GetPluginKey()
{
	CONST GUID key = // {337AF963-1B72-4efe-B232-ECA15BC0AC5D}
	{ 0x337af963, 0x1b72, 0x4efe, { 0xb2, 0x32, 0xec, 0xa1, 0x5b, 0xc0, 0xac, 0x5d } };
	return key;
}


HRESULT CSimpleRuntimeObjectPlugIn::CreatePlugin(IaqBasePlugin * * Value)
{
	_ASSERT( Value != NULL );

	CComObject<CSimpleRuntimeObjectPlugIn>* p;
	HRESULT hr = CComObject<CSimpleRuntimeObjectPlugIn>::CreateInstance(&p);
	if (FAILED(hr)) return hr;

	return p->QueryInterface(Value);
}


// ItcRuntimeObjectFactory Methods

void STDMETHODCALLTYPE CSimpleRuntimeObjectPlugIn::CreateRuntimeObject(BSTR ObjectName, GUID * /*ProjectKey*/, IDispatch * * Value)
{
	_ASSERT( Value != NULL );
	if (CComBSTR(ObjectName) == cObjectName)
	{
		CComObject<CSimpleProgramObject>* runtime_obj;
		CComObject<CSimpleProgramObject>::CreateInstance(&runtime_obj);
		runtime_obj->Initialize();
		runtime_obj->QueryInterface(Value);
		_ASSERT( *Value != NULL );
	}
	else
	{
		*Value = NULL;
	}
}
