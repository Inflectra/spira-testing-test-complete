
#include "StdAfx.h"
#include "MyPanelForm.h"


CMyPanelForm::CMyPanelForm(CComPtr<IaqActionsCustomizer> action_customizer)
	: m_label1(_T("Static"), this, ID_LABEL1)
{
	_ASSERT( action_customizer != NULL );
	m_action_customizer = action_customizer;
}


CMyPanelForm::~CMyPanelForm()
{
	m_action_customizer = NULL;
}


LRESULT CMyPanelForm::OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	RECT rect;
	GetClientRect(&rect);
	m_label1.Create(m_hWnd, rect, _T("My Panel"), WS_CHILD | WS_VISIBLE | SS_CENTER);
	return TRUE;
}


LRESULT CMyPanelForm::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	return TRUE;
}


LRESULT CMyPanelForm::OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL &/*bHandled*/)
{
	RECT rect;
	GetClientRect(&rect);

	m_label1.MoveWindow(&rect);

	return TRUE;
}


LRESULT CMyPanelForm::OnRightButtonUp(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& bHandled)
{
	POINT p = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
	ClientToScreen(&p);

	CComPtr<IaqPopupMenu> popup;
	if (FAILED(m_action_customizer->get_PopupMenus(MY_POPUP_KEY, &popup))) return TRUE;

	if (FAILED(popup->PopUpAtPos(p.x, p.y))) return TRUE;

	bHandled = TRUE;

	return TRUE;
}
