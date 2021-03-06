// =============================================================================================
// SpiraTest Plug-In Registration Class Header - Copyright (c) 2006-2009 Inflectra Corporation
//
// This file is part of the SpiraTest TestComplete Plug-In
//
// =============================================================================================

class ATL_NO_VTABLE CPlugInRegistrator : 
    public CComObjectRootEx<CComSingleThreadModel>,
    public CComCoClass<CPlugInRegistrator>,
    public IaqExtensionRegistrator
{
public:
    CPlugInRegistrator();
  
    BEGIN_COM_MAP(CPlugInRegistrator)
        COM_INTERFACE_ENTRY(IaqExtensionRegistrator)
    END_COM_MAP()
  
    DECLARE_PROTECT_FINAL_CONSTRUCT()
  
    HRESULT FinalConstruct()
    {
        return S_OK;
    }
  
    void FinalRelease() 
    {
    }
  
public:
    // IaqExtensionRegistrator Methods
    STDMETHOD(get_Name)(BSTR * Value);
    STDMETHOD(get_Copyright)(BSTR * Value);
    STDMETHOD(get_TargetIntegrationCount)(long * Value);
    STDMETHOD(get_TargetIntegrationKey)(long Index, GUID * Value);
    STDMETHOD(get_TargetProductCount)(long * Value);
    STDMETHOD(get_TargetProductKey)(long Index, GUID * Value);
    STDMETHOD(get_PluginCount)(long * Value);
    STDMETHOD(get_PluginKey)(long Index, GUID * Value);
    STDMETHOD(get_PluginName)(long Index, BSTR * Value);
    STDMETHOD(get_PluginDescription)(long Index, BSTR * Value);
    STDMETHOD(get_PluginVersion)(long Index, AQ_PLUGIN_VERSION * Value);
    STDMETHOD(get_PluginDefaultSelected)(long Index, VARIANT_BOOL * Value);
    STDMETHOD(get_PluginDependencyCount)(long Index, long * Value);
    STDMETHOD(get_PluginDependencies)(long Index, long DependsIndex, GUID * Value);
    STDMETHOD(get_PluginConflictCount)(long Index, long * Value);
    STDMETHOD(get_PluginConflicts)(long Index, long ConflictIndex, GUID * Value);
    STDMETHOD(CreatePlugin)(long Index, IaqBasePlugin * * Value);
  
    // IaqKeyItem Methods
    STDMETHOD_(void, GetKey)(GUID * Value);
};

