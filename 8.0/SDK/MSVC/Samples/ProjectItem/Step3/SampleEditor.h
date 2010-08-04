// SampleEditor.h : Declaration of the CSampleEditor

#pragma once

#include "SampleEditItem.h"

#define ID_EDIT 1

// CSampleEditor

class ATL_NO_VTABLE CSampleEditor : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSampleEditor>,
	public CWindowImpl<CSampleEditor>,
	public ItcEditor,
	public IaqIdleProvider
{
	BEGIN_COM_MAP(CSampleEditor)
		COM_INTERFACE_ENTRY(IaqKeyItem)
		COM_INTERFACE_ENTRY(IaqWindowProvider)
		COM_INTERFACE_ENTRY(ItcEditor)
		COM_INTERFACE_ENTRY(IaqIdleProvider)
	END_COM_MAP()

	BEGIN_MSG_MAP(CSampleEditor) 
		MESSAGE_HANDLER(WM_CREATE   , OnCreate  )
		MESSAGE_HANDLER(WM_DESTROY  , OnDestroy )
		MESSAGE_HANDLER(WM_SIZE     , OnSize    )
		MESSAGE_HANDLER(WM_PAINT    , OnPaint   )
		ALT_MSG_MAP(ID_EDIT)
		COMMAND_CODE_HANDLER(EN_CHANGE, OnChange )
	END_MSG_MAP()

	// message handlers
	LRESULT OnCreate (UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize   (UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnPaint  (UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnChange(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	virtual WNDPROC GetWindowProc();
	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

public:
	CSampleEditor();
	~CSampleEditor();
	void Initialize(ISampleEditItem* edit_item, IaqBaseManagerEx* base_manager_ex);

	// IaqWindowProvider Methods
	STDMETHOD(get_CreatePaneAtStartup)(VARIANT_BOOL * Value);
	STDMETHOD(get_AcceptsHandleType)(AQ_HANDLE_TYPE SiteHandleType, VARIANT_BOOL * Value);
	STDMETHOD(put_Visible)(VARIANT_BOOL pValue);
	STDMETHOD(get_Visible)(VARIANT_BOOL * pValue);
	STDMETHOD(SetSite)(AQ_HANDLE_TYPE SiteHandleType, UINT_PTR SiteHandle);
	STDMETHOD(SetBounds)(long Left, long Top, long Width, long Height);

	// ItcEditor Methods
	STDMETHOD_(void, GetCaption)(BSTR * Caption);
	STDMETHOD_(void, Commit)();
	STDMETHOD_(void, Close)();
	STDMETHOD_(void, VisitTo)(LPUNKNOWN Data);
	STDMETHOD_(void, SaveState)(IaqOptionsNode * Storage);
	STDMETHOD_(void, LoadState)(IaqOptionsNode * Storage);
	STDMETHOD_(void, GetEditItem)(ItcEditItem * * Value);
	STDMETHOD(get_ReadOnly)(VARIANT_BOOL * Value);
	STDMETHOD(put_ReadOnly)(VARIANT_BOOL Value);
	STDMETHOD_(long, GetHelpContext)();
	STDMETHOD_(void, SaveLayout)(IaqOptionsNode * Storage);
	STDMETHOD_(void, LoadLayout)(IaqOptionsNode * Storage);
	STDMETHOD_(void, SetFocus)();
	STDMETHOD_(VARIANT_BOOL, CanLeaveByTab)(VARIANT_BOOL ReverseOrder);

	// IaqIdleProvider Methods
	STDMETHOD(OnIdle)();

	// IaqKeyItem Methods
	STDMETHOD_(void, GetKey)(GUID * Value);

private:
	CContainedWindow          m_edit;
	CComPtr<ISampleEditItem>  m_edit_item;
	CComPtr<IaqBaseManagerEx> m_base_manager_ex;
	GUID                      m_key;
	long                      m_obtained_generation;
	DWORD                     m_caret_position;
};
