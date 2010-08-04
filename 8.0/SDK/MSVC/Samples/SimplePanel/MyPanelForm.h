#pragma once

#define ID_LABEL1  1


// window class of the plug-in panel 
class CMyPanelForm : public CWindowImpl<CMyPanelForm>
{
public:
	CMyPanelForm(CComPtr<IaqActionsCustomizer> action_customizer);
	~CMyPanelForm();

protected:
	BEGIN_MSG_MAP(CMyPanelForm) 
		MESSAGE_HANDLER(WM_CREATE   , OnCreate       )          
		MESSAGE_HANDLER(WM_DESTROY  , OnDestroy      )        
		MESSAGE_HANDLER(WM_SIZE     , OnSize         ) 
		MESSAGE_HANDLER(WM_RBUTTONUP, OnRightButtonUp)   // this handler displays the popup menu
		ALT_MSG_MAP(ID_LABEL1)
	END_MSG_MAP()

	// message handlers
	LRESULT OnCreate       (UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy      (UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize         (UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnRightButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled); 

	CContainedWindow m_label1;
	CComPtr<IaqActionsCustomizer> m_action_customizer;
};
