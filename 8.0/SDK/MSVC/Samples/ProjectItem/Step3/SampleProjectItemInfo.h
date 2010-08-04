// SampleProjectItemInfo.h : Declaration of the CSampleProjectItemInfo

#pragma once

// CSampleProjectItemInfo

class ATL_NO_VTABLE CSampleProjectItemInfo : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSampleProjectItemInfo>,
	public ItcFileProjectNodeInfo
{
	BEGIN_COM_MAP(CSampleProjectItemInfo)
		COM_INTERFACE_ENTRY(IaqKeyItem)
		COM_INTERFACE_ENTRY(ItcProjectNodeInfo)
		COM_INTERFACE_ENTRY(ItcFileProjectNodeInfo)
	END_COM_MAP()

public:
	CSampleProjectItemInfo();
	~CSampleProjectItemInfo();
	void Initialize(CComPtr<IaqMessenger> messenger);

	// ItcProjectNodeInfo Methods
	STDMETHOD(get_InfoProperty)(TC_PROJECT_NODE_INFO_PROP PropID, VARIANT * Value);
	STDMETHOD(get_SupportedParentType)(GUID * Value);
	STDMETHOD(CreateConfigurationParams)(ItcProjectNode * AParentNode, ItcProjectNodeConfigurationInfo * * Value);

	// ItcFileProjectNodeInfo Methods
	STDMETHOD(get_DefaultFileName)(BSTR * Value);
	STDMETHOD(get_FileExtension)(BSTR * Value);

	// IaqKeyItem Methods
	STDMETHOD_(void, GetKey)(GUID * Value);

	static CONST GUID GetKey();

private:
	CComBSTR GetPath(CComPtr<ItcProjectNode> node);
	CComBSTR GetName(CComPtr<ItcProjectNode> node, int index);

	CComPtr<IaqMessenger> m_messenger;
	HBITMAP               m_bitmap;
};
