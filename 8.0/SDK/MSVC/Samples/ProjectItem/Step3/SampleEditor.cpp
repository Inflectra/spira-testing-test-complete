// SampleEditor.cpp : Implementation of CSampleEditor

#include "stdafx.h"
#include "SampleEditor.h"


// CSampleEditor

CSampleEditor::CSampleEditor()
	: m_edit(_T("Edit"), this, ID_EDIT)
{
	CoCreateGuid(&m_key);
}


CSampleEditor::~CSampleEditor()
{
}


void CSampleEditor::Initialize(ISampleEditItem* edit_item, IaqBaseManagerEx* base_manager_ex)
{
	m_base_manager_ex = base_manager_ex;
	m_edit_item = edit_item;
}


LRESULT CSampleEditor::OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	RECT rect;
	GetClientRect(&rect);
	m_edit.Create(m_hWnd, rect, _T(""), WS_CHILD | WS_VISIBLE | ES_MULTILINE, WS_EX_CLIENTEDGE);

	CComBSTR text;
	m_edit_item->GetText(&text);
	m_edit.SetWindowText(CW2CT(text));
	m_obtained_generation = m_edit_item->GetGeneration();
	m_edit.SendMessage(EM_SETSEL, m_caret_position, m_caret_position);

	CComPtr<IaqIdleProvider> idle_provider;
	QueryInterface(IID_IaqIdleProvider, (void**)&idle_provider);
	m_base_manager_ex->RegisterSubsystemExtender(IID_IaqIdleManager, idle_provider);

	return TRUE;
}


LRESULT CSampleEditor::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	m_edit.SendMessage(EM_GETSEL, (WPARAM)&m_caret_position, NULL);

	CComPtr<IaqIdleProvider> idle_provider;
	QueryInterface(IID_IaqIdleProvider, (void**)&idle_provider);
	m_base_manager_ex->UnregisterSubsystemExtender(IID_IaqIdleManager, idle_provider);

	return TRUE;
}


LRESULT CSampleEditor::OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL &/*bHandled*/)
{
	RECT rect;
	GetClientRect(&rect);

	m_edit.MoveWindow(&rect);
	return TRUE;
}


LRESULT CSampleEditor::OnChange(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// EN_CHANGE
	CComBSTR text;
	m_edit.GetWindowText(&text);
	m_edit_item->SetText(text);
	m_obtained_generation = m_edit_item->GetGeneration();

	return TRUE;
}


LRESULT CSampleEditor::OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL & bHandled)
{
	OnIdle();
	bHandled = FALSE;
	return TRUE;
}


LRESULT CALLBACK CSampleEditor::WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_COMMAND)
	{
		CWindowImplBaseT<CWindow>* pThis = (CWindowImplBaseT<CWindow>*)hWnd;
		LRESULT lRes;
		pThis->ProcessWindowMessage(pThis->m_hWnd, uMsg, wParam, lParam, lRes, ID_EDIT);
		return lRes;
	}
	else
	{
		return CWindowImpl<CSampleEditor>::WindowProc(hWnd, uMsg, wParam, lParam);
	}
}

WNDPROC CSampleEditor::GetWindowProc()
{
	return WindowProc;
}


// IaqWindowProvider Methods

HRESULT STDMETHODCALLTYPE CSampleEditor::get_CreatePaneAtStartup(VARIANT_BOOL * Value)
{
	_ASSERT( Value != NULL );
	*Value = VARIANT_TRUE;
	return S_OK;
}


HRESULT STDMETHODCALLTYPE CSampleEditor::get_AcceptsHandleType(AQ_HANDLE_TYPE SiteHandleType, VARIANT_BOOL * Value)
{
	_ASSERT( Value != NULL );
	*Value = (SiteHandleType == htWindowHandle) ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}


HRESULT STDMETHODCALLTYPE CSampleEditor::put_Visible(VARIANT_BOOL pValue)
{
	if (IsWindow())
	{
		long style = GetWindowLong(GWL_STYLE);
		if (pValue)
			style |= WS_VISIBLE;
		else
			style &= ~WS_VISIBLE;
		SetWindowLong(GWL_STYLE, style);
	}
	return S_OK;
}


HRESULT STDMETHODCALLTYPE CSampleEditor::get_Visible(VARIANT_BOOL * pValue)
{
	_ASSERT( pValue != NULL );
	if (IsWindow())
		*pValue = (GetWindowLong(GWL_STYLE) & WS_VISIBLE) ? VARIANT_TRUE : VARIANT_FALSE;
	else
		*pValue = VARIANT_FALSE;
	return S_OK;
}


HRESULT STDMETHODCALLTYPE CSampleEditor::SetSite(AQ_HANDLE_TYPE SiteHandleType, UINT_PTR SiteHandle)
{
	_ASSERT( SiteHandleType == htWindowHandle );
	if (SiteHandleType != htWindowHandle) return ERROR_BAD_ARGUMENTS;

	if (SiteHandle == NULL)
	{
		// Hide Control before detaching it from the parent.
		if (IsWindow()) ShowWindow(SW_HIDE);
	}
	else
	{
		_ASSERT( ::IsWindow((HWND)SiteHandle) );

		if (IsWindow())
		{
			SetParent((HWND)SiteHandle);
		}
		else
		{
			RECT rect = { 0, 0, 0, 0 };
			Create((HWND)SiteHandle, rect, NULL, WS_CHILD);
		}
	}

	return S_OK;
}


HRESULT STDMETHODCALLTYPE CSampleEditor::SetBounds(long Left, long Top, long Width, long Height)
{
	if (IsWindow()) MoveWindow(Left, Top, Width, Height);
	return S_OK;
}


// ItcEditor Methods

void STDMETHODCALLTYPE CSampleEditor::GetCaption(BSTR * Caption)
{
	_ASSERT( m_edit_item != NULL );
	m_edit_item->GetCaption(Caption);
}


void STDMETHODCALLTYPE CSampleEditor::Commit()
{
	if (IsWindow())
	{
		CComBSTR text;
		m_edit.GetWindowText(&text);
		m_edit_item->SetText(text);
	}
}


void STDMETHODCALLTYPE CSampleEditor::Close()
{
	DestroyWindow();
}


void STDMETHODCALLTYPE CSampleEditor::VisitTo(LPUNKNOWN /*Data*/)
{
}


void STDMETHODCALLTYPE CSampleEditor::SaveState(IaqOptionsNode * Storage)
{
	if (m_edit.IsWindow())
		m_edit.SendMessage(EM_GETSEL, (WPARAM)&m_caret_position, NULL);

	CComPtr<IaqProperties> props;
	Storage->GetProperties(&props);

	props->SetInteger(CComBSTR(_T("CaretPosInEdit")), m_caret_position);
}


void STDMETHODCALLTYPE CSampleEditor::LoadState(IaqOptionsNode * Storage)
{
	CComPtr<IaqProperties> props;
	Storage->GetProperties(&props);

	props->GetInteger(CComBSTR(_T("CaretPosInEdit")), 0, (long*)&m_caret_position);

	if (m_edit.IsWindow())
		m_edit.SendMessage(EM_SETSEL, m_caret_position, m_caret_position);
}


void STDMETHODCALLTYPE CSampleEditor::SaveLayout(IaqOptionsNode * /*Storage*/)
{
}


void STDMETHODCALLTYPE CSampleEditor::LoadLayout(IaqOptionsNode * /*Storage*/)
{
}


void STDMETHODCALLTYPE CSampleEditor::SetFocus()
{
	m_edit.SetFocus();
}


VARIANT_BOOL STDMETHODCALLTYPE CSampleEditor::CanLeaveByTab(VARIANT_BOOL)
{
	return VARIANT_TRUE;
}


void STDMETHODCALLTYPE CSampleEditor::GetEditItem(ItcEditItem * * Value)
{
	_ASSERT( Value != NULL );
	_ASSERT( m_edit_item != NULL );

	m_edit_item.QueryInterface(Value);
}


HRESULT STDMETHODCALLTYPE CSampleEditor::get_ReadOnly(VARIANT_BOOL * Value)
{
	_ASSERT( Value != NULL );
	if (IsWindow())
		*Value = (m_edit.GetStyle() & ES_READONLY) ? VARIANT_TRUE : VARIANT_FALSE;
	else
		*Value = VARIANT_TRUE;
	return S_OK;
}


HRESULT STDMETHODCALLTYPE CSampleEditor::put_ReadOnly(VARIANT_BOOL Value)
{
	if (IsWindow())
		m_edit.SendMessage(EM_SETREADONLY, (Value == VARIANT_FALSE) ? FALSE : TRUE, 0);
	return S_OK;
}


long STDMETHODCALLTYPE CSampleEditor::GetHelpContext()
{
	return 0; // We do not use any help file for our editor
}


HRESULT STDMETHODCALLTYPE CSampleEditor::OnIdle()
{
	if (m_edit.IsWindow())
	{
		long generation = m_edit_item->GetGeneration();
		if (generation != m_obtained_generation)
		{
			DWORD start_pos, end_pos;
			m_edit.SendMessage(EM_GETSEL, (WPARAM)&start_pos, (LPARAM)&end_pos);

			CComBSTR text;
			m_edit_item->GetText(&text);
			m_edit.SetWindowText(CW2CT(text));
			m_obtained_generation = generation;

			m_edit.SendMessage(EM_SETSEL, start_pos, end_pos);
		}
	}

	return S_OK;
}


// IaqKeyItem Methods

void STDMETHODCALLTYPE CSampleEditor::GetKey(GUID * Value)
{
	_ASSERT( Value != NULL );
	*Value = m_key;
}
