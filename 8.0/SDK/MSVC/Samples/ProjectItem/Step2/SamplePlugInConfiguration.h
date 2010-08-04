// SamplePlugInConfiguration.h : Declaration of the CSamplePlugInConfiguration

#pragma once

// CSamplePlugInConfiguration

class ATL_NO_VTABLE CSamplePlugInConfiguration : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CSamplePlugInConfiguration>,
	public ItcProjectNodeConfigurationInfo
{
	BEGIN_COM_MAP(CSamplePlugInConfiguration)
		COM_INTERFACE_ENTRY(ItcProjectNodeConfigurationInfo)
	END_COM_MAP()

public:
	CSamplePlugInConfiguration();
	void Initialize(CComBSTR                name,
	                CComBSTR                location,
	                CComPtr<ItcProjectNode> owner,
	                CComPtr<IaqMessenger>   messenger);

	// ItcProjectNodeConfigurationInfo Methods
	STDMETHOD(get_ParameterCount)(long * Value);
	STDMETHOD(get_ParameterCaption)(long Index, BSTR * Value);
	STDMETHOD(get_ParameterValue)(long Index, VARIANT * Value);
	STDMETHOD(put_ParameterValue)(long Index, VARIANT Value);
	STDMETHOD(IsValid)(long * InvalidParamIndex, VARIANT_BOOL * Value);

private:
	CComBSTR                m_name;
	CComBSTR                m_location;
	CComPtr<ItcProjectNode> m_owner;
	CComPtr<IaqMessenger>   m_messenger;
};
