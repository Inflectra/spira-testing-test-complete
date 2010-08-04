// SampleProjectItem.cpp : Implementation of CSampleProjectItem

#include "stdafx.h"
#include "SampleProjectItem.h"
#include "SampleProjectItemInfo.h"
#include "ChildNodeIterator.h"
#include "SampleRuntimeObject.h"


// CSampleProjectItem

CSampleProjectItem::CSampleProjectItem()
{
	m_caption         = L"";
	m_file_name[0]    = 0;
	m_key             = GUID_NULL;
	m_text            = L"";
	CoCreateGuid(&m_context_key);
	m_bitmap          = NULL;
	m_personal_bitmap = NULL;
	m_scc_status      = -1;
	m_hint            = L"";
}


void CSampleProjectItem::Initialize(GUID key, ItcProjectNode* owner, IaqMessenger* messenger, IaqCoreUI* core_ui, IaqEventManager* event_manager, IaqActionManager* action_manager, ItcCodeCompletionManager* code_completion_manager, ItcRuntimeObjectsManager* runtime_objects_manager)
{
	m_key            = key;
	m_owner          = owner;
	m_messenger      = messenger;
	m_core_ui        = core_ui;
	m_event_manager  = event_manager;
	m_action_manager = action_manager;
	m_code_completion_manager = code_completion_manager;
	m_runtime_objects_manager = runtime_objects_manager;
}


// IaqActionNotifier Methods

AQ_ACTION_EXEC_RESULT STDMETHODCALLTYPE CSampleProjectItem::OnExecute(IaqActionItem * Sender, VARIANT /*InValue*/, VARIANT * /*OutValue*/)
{
	GUID key;
	Sender->GetKey(&key);

	if (key == act_ProjectNode_Save)
	{
		AQ_SAVE_RESULT result;
		Save(&result);
		return AQ_AER_OK;
	}

	if (key == act_ProjectNode_SaveAs)
	{
		SaveAs();
		return AQ_AER_OK;
	}

	return AQ_AER_OK;
}


void STDMETHODCALLTYPE CSampleProjectItem::OnUpdate(IaqActionItem * Sender)
{
	GUID key;
	Sender->GetKey(&key);

	if (key == act_ProjectNode_Save)
	{
		// Sets the enabled property for the Save item
		VARIANT_BOOL dirty;
		get_Dirty(&dirty);

		VARIANT dirty_var;
		dirty_var.vt      = VT_BOOL;
		dirty_var.boolVal = dirty;
		Sender->SetProperties(apEnabled, dirty_var);
	}
	else if (key == act_ProjectNode_SaveAs)
	{
		// Sets the enabled property for the Save As item
		Sender->SetProperties(apEnabled, CComVariant(true));
	}
	else
	{
		_ASSERT( false );
	}
}


// ItcEditItem Methods

void STDMETHODCALLTYPE CSampleProjectItem::GetCaption(BSTR * Value)
{
	m_caption.CopyTo(Value);
}


void STDMETHODCALLTYPE CSampleProjectItem::Commit()
{
	AQ_SAVE_RESULT res;
	Save(&res);
}


void STDMETHODCALLTYPE CSampleProjectItem::Rollback()
{
	Load();
}


long STDMETHODCALLTYPE CSampleProjectItem::GetGeneration()
{
	return m_generation;
}


long STDMETHODCALLTYPE CSampleProjectItem::GetCommittedGeneration()
{
	return m_committed_generation;
}


void STDMETHODCALLTYPE CSampleProjectItem::GetProjectNode(ItcProjectNode * * Value)
{
	m_owner.CopyTo(Value);
}


// ISampleEditItem Methods

void STDMETHODCALLTYPE CSampleProjectItem::GetText(BSTR * Text)
{
	m_text.CopyTo(Text);
}


void STDMETHODCALLTYPE CSampleProjectItem::SetText(BSTR Text)
{
	if (m_text != Text)
	{
		put_Dirty(VARIANT_TRUE);
		m_text = Text;
	}
}


// ItcProjectContextItem Methods

void STDMETHODCALLTYPE CSampleProjectItem::GetContextKey(GUID * Value)
{
	_ASSERT( Value != NULL );
	*Value = m_context_key;
}


// ItcProjectNodeInternal Methods

HRESULT STDMETHODCALLTYPE CSampleProjectItem::Initialize(IaqBaseManager * /*BaseManager*/)
{
	_ASSERT( m_key       != GUID_NULL );
	_ASSERT( m_owner          != NULL );
	_ASSERT( m_messenger      != NULL );
	_ASSERT( m_core_ui        != NULL );
	_ASSERT( m_event_manager  != NULL );
	_ASSERT( m_action_manager != NULL );
	_ASSERT( m_runtime_objects_manager != NULL );

	CComPtr<IaqActionNotifier> self;
	QueryInterface(IID_IaqActionNotifier, (void**)&self);
	m_action_manager->AddActionNotifier(act_ProjectNode_Save  , m_context_key, self);
	m_action_manager->AddActionNotifier(act_ProjectNode_SaveAs, m_context_key, self);

	if (m_code_completion_manager != NULL)
	{
		GUID key;
		m_owner->GetKey(&key);

		CComPtr<ItcCodeCompletionProvider> ccp;
		QueryInterface(IID_ItcCodeCompletionProvider, (void**)&ccp);
		m_code_completion_manager->AddProvider(ccp, &key);
	}

	CComPtr<IaqEventsListenerProvider> elp;
	QueryInterface(IID_IaqEventsListenerProvider, (void**)&elp);
	m_event_manager->AddEventsProvider(elp);

	return S_OK;
}


HRESULT STDMETHODCALLTYPE CSampleProjectItem::Finalize()
{
	_ASSERT( m_action_manager          != NULL );
	_ASSERT( m_event_manager           != NULL );
	_ASSERT( m_owner                   != NULL );

	m_action_manager->RemoveActionNotifier(act_ProjectNode_Save  , m_context_key);
	m_action_manager->RemoveActionNotifier(act_ProjectNode_SaveAs, m_context_key);

	GUID key;
	GetKey(&key);
	if (m_code_completion_manager != NULL)
	{
		GUID owner_key;
		m_owner->GetKey(&owner_key);

		m_code_completion_manager->RemoveProvider(&key, &owner_key);
	}

	m_event_manager->RemoveEventsProvider(&key);

	m_owner          = NULL;
	m_messenger      = NULL;
	m_core_ui        = NULL;
	m_event_manager  = NULL;
	m_action_manager = NULL;
	m_code_completion_manager = NULL;
	m_runtime_objects_manager = NULL;

	if (m_bitmap != NULL)
	{
		DeleteObject(m_bitmap);
		m_bitmap = NULL;
	}
	if (m_personal_bitmap != NULL)
	{
		DeleteObject(m_personal_bitmap);
		m_personal_bitmap = NULL;
	}

	return S_OK;
}


HRESULT STDMETHODCALLTYPE CSampleProjectItem::DeletePermanently()
{
	Finalize();
	DeleteFile(m_file_name);
	return S_OK;
}


HRESULT STDMETHODCALLTYPE CSampleProjectItem::QueryClose(VARIANT_BOOL * Value)
{
	_ASSERT( Value != NULL );
	*Value = VARIANT_TRUE;
	return S_OK;
}


// ItcPersistentProjectNode Methods

HRESULT STDMETHODCALLTYPE CSampleProjectItem::get_Dirty(VARIANT_BOOL * Value)
{
	_ASSERT( Value != NULL );
	*Value = (m_committed_generation == m_generation) ? VARIANT_FALSE : VARIANT_TRUE;
	return S_OK;
}


HRESULT STDMETHODCALLTYPE CSampleProjectItem::put_Dirty(VARIANT_BOOL Value)
{
	if (Value)
	{
		m_generation ++;
	}
	else
	{
		m_committed_generation = m_generation;
	}
	return S_OK;
}


HRESULT STDMETHODCALLTYPE CSampleProjectItem::Save(AQ_SAVE_RESULT * Value)
{
	_ASSERT( Value != NULL );
	*Value = AQ_SR_CANCEL;

	HRESULT hr = ForceDirectoriesForFile(m_file_name);
	if (FAILED(hr)) return hr;

	FILE* f = _tfopen(m_file_name, _T("wb"));
	if (f == NULL) return ERROR_FILE_NOT_FOUND;

	CW2A buf(m_text);
	size_t written = fwrite(buf, 1, m_text.Length(), f);

	fclose(f);

	if (written != m_text.Length()) return STG_E_WRITEFAULT;

	put_Dirty(VARIANT_FALSE);
	*Value = AQ_SR_OK;
	return S_OK;
}


HRESULT STDMETHODCALLTYPE CSampleProjectItem::InitializeFromPersistentInfo(IaqOptionsNode * PersistentInfo, VARIANT_BOOL * Value)
{
	_ASSERT( Value != NULL );
	_ASSERT( PersistentInfo != NULL );
	*Value = VARIANT_FALSE;

	CComPtr<IaqProperties> props;
	PersistentInfo->GetProperties(&props);

	m_file_name[0] = 0;
	_bstr_t fn = m_file_name;
	HRESULT hr = props->GetString(CComBSTR(cFileNameProperty), CComBSTR(L""), fn.GetAddress());
	if (FAILED(hr)) return hr;
	_tcsncpy(m_file_name, fn, MAX_PATH);  m_file_name[MAX_PATH - 1] = 0;

	m_generation = 0;
	put_Dirty(VARIANT_FALSE);

	if (m_file_name[0] != 0)
	{
		m_caption = GetCaptionFromFileName(m_file_name);

		hr = Load();
		if (FAILED(hr)) return hr;

		*Value = VARIANT_TRUE;
	}

	return S_OK;
}


HRESULT STDMETHODCALLTYPE CSampleProjectItem::StorePersistentInfo(IaqOptionsNode * PersistentInfo)
{
	HRESULT hr;

	CComPtr<IaqProperties> props;
	PersistentInfo->GetProperties(&props);

	hr = props->SetString(CComBSTR(cFileNameProperty), CComBSTR(m_file_name));
	if (FAILED(hr)) return hr;

	return S_OK;
}


// ItcProjectNode Methods

HRESULT STDMETHODCALLTYPE CSampleProjectItem::get_Caption(BSTR * Value)
{
	_ASSERT( Value != NULL );
	return m_caption.CopyTo(Value);
}


HRESULT STDMETHODCALLTYPE CSampleProjectItem::put_Caption(BSTR Value)
{
	_bstr_t name = (Value == NULL) ? L"" : Value;

	TCHAR new_file_name[MAX_PATH];
	TCHAR path         [_MAX_DIR];
	TCHAR extension    [_MAX_EXT];
	_tsplitpath(m_file_name, new_file_name, path, NULL, extension);

	_tcscat(new_file_name, path);
	_tcscat(new_file_name, name);
	_tcscat(new_file_name, extension);

	RenameNode(new_file_name);
	return S_OK;
}


HRESULT STDMETHODCALLTYPE CSampleProjectItem::get_NodeType(GUID * Value)
{
	_ASSERT( Value != NULL );
	*Value = CSampleProjectItemInfo::GetKey();
	return S_OK;
}


HRESULT STDMETHODCALLTYPE CSampleProjectItem::get_NodeProperty(TC_PROJECT_NODE_PROP PropID, VARIANT * Value)
{
	_ASSERT( Value != NULL );

	CComVariant val;
	val.Attach(Value);

	switch(PropID)
	{
		case pnpStorageName:
			// We return the file name, since our project item is a persistent node
			val = m_file_name;
			break;
		case pnpDescription:
			// No additional info
			val = L"";
			break;
		case pnpIsReadOnly:
			// The node is not read-only
			val = false;
			break;
		case pnpSettingsStorage:
			// We don't have a Settings Storage
			break;
		case pnpPersonalBitmap:
			if (m_personal_bitmap != NULL)
				val = (long)CopyImage(m_personal_bitmap, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
			break;
		case pnpHint:
			// No hint
			val = L"";
			break;
		case pnpSCCStatus:
			val = m_scc_status;
			break;
		case pnpCanDeletePermanently:
			val = true;
			break;
		default:
			_ASSERT( false );
			return E_INVALIDARG;
	}

	return val.Detach(Value);
}


HRESULT STDMETHODCALLTYPE CSampleProjectItem::put_NodeProperty(TC_PROJECT_NODE_PROP PropID, VARIANT Value)
{
	CComVariant val = Value;

	switch (PropID)
	{
		case pnpPersonalBitmap:
		{
			if (val.ChangeType(VT_I4) != S_OK)
				return E_INVALIDARG;
			bool b = (m_personal_bitmap != NULL);
			if (m_personal_bitmap != NULL)
				DeleteObject(m_personal_bitmap);
			m_personal_bitmap = (HBITMAP)val.lVal; 
			if (b || (m_personal_bitmap != NULL))
			{
				SendNodeDataChangedEvent();
			}
			return S_OK;
		}
		case pnpHint:
		{
			if (val.ChangeType(VT_BSTR) != S_OK)
				return E_INVALIDARG;
			if (m_hint != val.bstrVal)
			{
				m_hint = val.bstrVal;
				SendNodeDataChangedEvent();
			}
			return S_OK;
		}
		case pnpSCCStatus:
		{
			m_scc_status = Value;
			return S_OK;
		}
		default:
		{
			return E_INVALIDARG;
		}
	}
}


HRESULT STDMETHODCALLTYPE CSampleProjectItem::GetNodeGUIDProperty(TC_PROJECT_NODE_GUIDPROP PropID, GUID * Value)
{
	_ASSERT( Value != NULL );
	switch(PropID)
	{
		case pngpContextKey:
			*Value = m_context_key;
			return S_OK;
		default:
			_ASSERT( false );
			return S_OK;
	}
}


HRESULT STDMETHODCALLTYPE CSampleProjectItem::SetNodeGUIDProperty(TC_PROJECT_NODE_GUIDPROP /*PropID*/, GUID * /*Value*/)
{
	return E_NOTIMPL;
}


HRESULT STDMETHODCALLTYPE CSampleProjectItem::get_OwnerNode(ItcProjectNode * * Value)
{
	_ASSERT( Value != NULL );
	return m_owner.CopyTo(Value);
}


HRESULT STDMETHODCALLTYPE CSampleProjectItem::CreateChildIterator(ItcProjectNodeIterator * * Value)
{
	_ASSERT( Value != NULL );
	CComObject<CChildNodeIterator>* iterator;
	HRESULT hr = CComObject<CChildNodeIterator>::CreateInstance(&iterator);
	if (FAILED(hr)) return hr;
	return iterator->QueryInterface(Value);
}


HRESULT STDMETHODCALLTYPE CSampleProjectItem::get_HasTests(VARIANT_BOOL * Value)
{
	_ASSERT( Value != NULL );
	*Value = VARIANT_FALSE;
	return S_OK;
}


HRESULT STDMETHODCALLTYPE CSampleProjectItem::GetTest(BSTR /*Moniker*/, ItcTest * * Value)
{
	_ASSERT( Value != NULL );
	*Value = NULL;
	return S_OK;
}


HRESULT STDMETHODCALLTYPE CSampleProjectItem::EnumTest(ItcTestIterator * * Value)
{
	_ASSERT( Value != NULL );
	*Value = NULL;
	return S_OK;
}


// IaqKeyItem Methods

void STDMETHODCALLTYPE CSampleProjectItem::GetKey(GUID * Value)
{
	_ASSERT( Value != NULL );
	*Value = m_key;
}


HRESULT CSampleProjectItem::InitializeFromConfiguration(CComPtr<ItcProjectNodeConfigurationInfo> configuration)
{
	if (configuration != NULL)
	{
		HRESULT hr;

		CComVariant caption;
		hr = configuration->get_ParameterValue(0, &caption);
		if (FAILED(hr)) return hr;

		hr = caption.CopyTo(&m_caption);
		if (FAILED(hr)) return hr;

		CComVariant path;
		hr = configuration->get_ParameterValue(1, &path);
		if (FAILED(hr)) return hr;

		if (path.vt != VT_BSTR) return ERROR_BAD_ARGUMENTS;
		_bstr_t file_name = path.bstrVal + _bstr_t(m_caption) + "." + cDefaultFileExtension;

		_tcsncpy(m_file_name, file_name, MAX_PATH);
		m_file_name[MAX_PATH - 1] = 0;
	}

	return S_OK;
}


HRESULT CSampleProjectItem::InitializeFromFile(CONST TCHAR* file_name, CComBSTR caption)
{
	m_caption = caption;
	_tcsncpy(m_file_name, file_name, MAX_PATH);
	m_file_name[MAX_PATH - 1] = 0;

	HRESULT hr = Load();
	if (FAILED(hr)) return hr;

	m_generation = 0;
	put_Dirty(VARIANT_FALSE);
	return S_OK;
}


HRESULT CSampleProjectItem::Load()
{
	m_text = L"";

	FILE* f = _tfopen(m_file_name, _T("rb"));
	if (f == NULL) return ERROR_FILE_NOT_FOUND;

	size_t len = _filelength(_fileno(f));
	char* buf = (char*)malloc((len + 1) * sizeof(char));

	size_t read = fread(buf, 1, len, f);
	fclose(f);

	if (read != len)
	{
		free(buf);
		return STG_E_READFAULT;
	}

	buf[len] = 0;
	m_text = CComBSTR(buf);
	free(buf);

	return S_OK;
}


void CSampleProjectItem::ShowLastWindowsError()
{
	DWORD err = GetLastError();

	TCHAR* msg;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
	              0,
	              err,
	              MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
	              (LPTSTR)&msg,
	              256,
	              NULL);
	m_messenger->ShowMildError(CComBSTR(msg), 0, CComBSTR(L""));
	LocalFree(msg);
}


void CSampleProjectItem::SendNodeDataChangedEvent()
{
	CComPtr<IUnknown> project_event_unknown;
	GUID event_id = IID_ItcProjectEvent;
	m_event_manager->GetNotifier(&event_id, VARIANT_TRUE, &project_event_unknown);
	CComQIPtr<ItcProjectEvent> project_event = project_event_unknown;
	_ASSERT( project_event_unknown != NULL );

	CComPtr<ItcProjectNode> project_node;
	QueryInterface(IID_ItcProjectNode, (void**)&project_node);
	project_event->OnProjectNodeEvent(TC_NODE_DATA_CHANGED, project_node);
}


void CSampleProjectItem::RenameNode(CONST TCHAR* new_file_name, BOOL delete_source, BOOL overwrite)
{
	_ASSERT( m_messenger != NULL );

	CComBSTR caption = GetCaptionFromFileName(new_file_name);

	if ((caption != m_caption) && NodeExistsInParent(m_owner, caption))
	{
		m_messenger->ShowMildError(CComBSTR(L"Cannot rename the node.\n\rThe parent node already has a child with the specified name."), 0, CComBSTR(L""));
		return;
	}

	if (overwrite)
		if (DeleteFile(new_file_name) == FALSE)
		{
			ShowLastWindowsError();
			return;
		}

	if (CopyFile(m_file_name, new_file_name, TRUE) == FALSE)
	{
		ShowLastWindowsError();
		return;
	}

	if (delete_source)
		if (DeleteFile(m_file_name) == FALSE)
			ShowLastWindowsError();

	m_caption = caption;
	_tcscpy(m_file_name, new_file_name);
	put_Dirty(VARIANT_TRUE);

	// Set the "dirty" flag of the parent node to True
	// in order to save the updated file name
	CComPtr<ItcPersistentProjectNode> owner;
	if (SUCCEEDED(m_owner->QueryInterface(&owner)))
		owner->put_Dirty(VARIANT_TRUE);

	// Send notifications that the node's caption has been changed
	SendNodeDataChangedEvent();
}


HRESULT CSampleProjectItem::SaveAs()
{
	GUID dialog_key = IID_ItcProjectSuiteManager;
	CComBSTR file_name = m_caption;
	CComBSTR mask = CComBSTR(L"SampleItem files (*.");
	mask.Append(cDefaultFileExtension);
	mask.Append(L")|*.");
	mask.Append(cDefaultFileExtension);
	mask.Append(L"|All files (*.*)|*.*");
	long filter_index = 1;
  
	VARIANT_BOOL r;
	m_core_ui->ShowSaveFileDialog(
			&dialog_key,
			CComBSTR(L"Save to File"),
			&file_name,
			mask,
			&filter_index,
			CComBSTR(cDefaultFileExtension),
			AQ_FDO_OVERWRITE_PROMPT,
			&r
	);

	if (r)
	{
		TCHAR new_file_name[MAX_PATH];
		_tcsncpy(new_file_name, _bstr_t(file_name), MAX_PATH);
		new_file_name[MAX_PATH - 1] = 0;
		RenameNode(new_file_name, FALSE, TRUE);
	}
	
	return S_OK;
}


// IaqBaseEvent Methods

HRESULT STDMETHODCALLTYPE CSampleProjectItem::get_EventInfo(BSTR * Value)
{
	_ASSERT( Value != NULL );
	CComBSTR(L"CSampleProjectItem").CopyTo(Value);
	return S_OK;
}


// IaqEventsListenerProvider Methods

long STDMETHODCALLTYPE CSampleProjectItem::GetCountListenedEvent()
{
	return 1;
}


void STDMETHODCALLTYPE CSampleProjectItem::GetListenedEventInfo(long Index, AQ_EVENT_INFO * Value)
{
	_ASSERT( Value != NULL );
	_ASSERT( Index == 0 );
	if (Index != 0) return;

	Value->EventID            = IID_ItcTestEngineEvent;
	Value->NotifyInMainThread = VARIANT_FALSE;
}


// ItcCodeCompletionProvider Methods

void STDMETHODCALLTYPE CSampleProjectItem::GetName(BSTR * Value)
{
	_ASSERT( Value != NULL );
	m_caption.CopyTo(Value);
}


void STDMETHODCALLTYPE CSampleProjectItem::GetDescription(BSTR * Value)
{
	_ASSERT( Value != NULL );
	CComBSTR(L"Provides scripting access the SampleItem object.").CopyTo(Value);
}


long STDMETHODCALLTYPE CSampleProjectItem::GetBitmapReference()
{
	if (m_bitmap == NULL)
	{
		m_bitmap = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_SAMPLEITEM));
	}

	_ASSERT( m_bitmap != NULL );
	return (long)m_bitmap;
}


long STDMETHODCALLTYPE CSampleProjectItem::GetTypeInformationCount()
{
	return 1;
}


void STDMETHODCALLTYPE CSampleProjectItem::GetTypeInformation(long Index, LPUNKNOWN * Value)
{
	_ASSERT( Index == 0 );
	_ASSERT( Value != NULL );
	if (Index != 0) return;

	TCHAR module_name[MAX_PATH];
	GetModuleFileName(hInstance, module_name, MAX_PATH);

	CComPtr<ITypeLib> type_lib;
	LoadTypeLib(CComBSTR(module_name), &type_lib);


	CComPtr<ISampleEditItem> sei;
	QueryInterface(IID_ISampleEditItem, (void**)&sei);

	CComObject<CSampleRuntimeObject>* tmp_runtime_obj;
	CComObject<CSampleRuntimeObject>::CreateInstance(&tmp_runtime_obj);
	tmp_runtime_obj->AddRef();
	tmp_runtime_obj->Initialize(type_lib, IID_ISampleRuntimeObject, sei, m_messenger);

	CComPtr<ITypeInfo> type_info;
	tmp_runtime_obj->GetTypeInfo(0, 0, &type_info);
	_ASSERT( type_info != NULL );

	type_info->QueryInterface(Value);

	tmp_runtime_obj->Release();
}


// ItcRuntimeObjectFactory Methods

void STDMETHODCALLTYPE CSampleProjectItem::CreateRuntimeObject(BSTR /*ObjectName*/, GUID * /*ProjectKey*/, LPDISPATCH * Value)
{
	TCHAR module_name[MAX_PATH];
	GetModuleFileName(hInstance, module_name, MAX_PATH);

	CComPtr<ITypeLib> type_lib;
	LoadTypeLib(CComBSTR(module_name), &type_lib);


	CComPtr<ISampleEditItem> sei;
	QueryInterface(IID_ISampleEditItem, (void**)&sei);

	CComObject<CSampleRuntimeObject>* runtime_obj;
	CComObject<CSampleRuntimeObject>::CreateInstance(&runtime_obj);
	runtime_obj->Initialize(type_lib, IID_ISampleRuntimeObject, sei, m_messenger);
	runtime_obj->QueryInterface(Value);
	runtime_obj = NULL;
}


// ItcTestEngineEvent Methods

HRESULT STDMETHODCALLTYPE CSampleProjectItem::OnTestEvent(TC_TESTENGINE_EVENT Event, ItcTest * Test)
{
	switch (Event)
	{
		case TC_PLAYING_START:
		{
			if (m_runtime_object_cookie == 0)
			{
				GUID key;
				m_owner->GetKey(&key);

				m_runtime_object_cookie = 
					m_runtime_objects_manager->RegisterRuntimeObjectFactory(m_caption, VARIANT_FALSE, &key, this);
			}

			break;
		}

		case TC_PLAYING_START_FAILED:
		case TC_PLAYING_STOP:
		{
			if (m_runtime_object_cookie != 0)
			{
				GUID test_project_key;
				Test->GetProjectKey(&test_project_key);
				
				if (test_project_key == GUID_NULL)
				{
					m_runtime_objects_manager->RemoveRuntimeObject(m_runtime_object_cookie);
					m_runtime_object_cookie = 0;
				}
			}

			break;
		}
	}

	return S_OK;
}


HRESULT STDMETHODCALLTYPE CSampleProjectItem::OnEngineEvent(TC_TESTENGINE_EVENT)
{
	_ASSERT( m_runtime_objects_manager != NULL );
	_ASSERT( m_owner != NULL );

	if (m_runtime_object_cookie != 0)
	{
		m_runtime_objects_manager->RemoveRuntimeObject(m_runtime_object_cookie);
		m_runtime_object_cookie = 0;
	}

	return S_OK;
}
