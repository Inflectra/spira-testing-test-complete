// =============================================================================================
// SpiraTest Plug-In Header - Copyright (c) 2006-2009 Inflectra Corporation
//
// This file is part of the SpiraTest TestComplete Plug-In
//
// =============================================================================================

struct STestResult
{
	BSTR strMoniker;
	BSTR strTestName;
	BSTR strTestItemName;
	CEnBSTR strRootLogFileName;
	int iExecutionStatus;
	long lAssertCount;
	long lTestCaseId;
	long lReleaseId;
	long lProjectId;
};

class ATL_NO_VTABLE CSpiraTestPlugIn :
    public CComObjectRootEx<CComSingleThreadModel>,
    public CComCoClass<CSpiraTestPlugIn>,
    public IaqBasePlugin,
	public IaqActionNotifier,
	public IaqEventsListenerProvider,
	public ItcTestEngineEvent
{
public:
    CSpiraTestPlugIn()
	{
	}
  
    BEGIN_COM_MAP(CSpiraTestPlugIn)
        COM_INTERFACE_ENTRY (IaqBasePlugin)
		COM_INTERFACE_ENTRY (IaqActionNotifier)
		COM_INTERFACE_ENTRY2(IaqBaseEvent, IaqEventsListenerProvider)
		COM_INTERFACE_ENTRY (IaqEventsListenerProvider)
		COM_INTERFACE_ENTRY (ItcTestEngineEvent)
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
    static CONST GUID GetPluginKey();
  
    // IaqBasePlugin Methods
    STDMETHOD(Initialize)(IaqBaseManager * Manager);
    STDMETHOD(Update)();
    STDMETHOD(Finalize)();
    STDMETHOD(BaseManagerStateChanged)(AQ_MAINMANAGER_STATE State);
  
    // IaqKeyItem Methods
    STDMETHOD_(void, GetKey)(GUID * Value);

	// IaqActionNotifier Methods
	STDMETHOD_(AQ_ACTION_EXEC_RESULT, OnExecute)(IaqActionItem * Sender, VARIANT InValue, VARIANT * OutValue);
	STDMETHOD_(void, OnUpdate)(IaqActionItem * Sender);

	// IaqBaseEvent Methods
	STDMETHOD(get_EventInfo)(BSTR * Value);

	// IaqEventsListenerProvider Methods
	STDMETHOD_(long, GetCountListenedEvent)();
	STDMETHOD_(void, GetListenedEventInfo)(long Index, AQ_EVENT_INFO * Value);

	// ItcTestEngineEvent Methods
	STDMETHOD(OnTestEvent)(TC_TESTENGINE_EVENT Event, ItcTest * Test);
	STDMETHOD(OnEngineEvent)(TC_TESTENGINE_EVENT Event);

private:
	STDMETHOD(DisplayMessage)(BSTR message);

	typedef vector<STestResult> TESTRESULTS;
	TESTRESULTS m_test_results;
	BSTR m_strLogin;
	BSTR m_strPassword;

	CTestExecuteT<> m_spiraTestExecuteService;
	CComPtr<IaqBaseManager> m_base_manager;
	IXMLDOMDocumentPtr m_pXmlDocument;

	long CSpiraTestPlugIn::FileSize(wchar_t *);
	STDMETHOD(RecordTestResult)(int, ItcTest *);
	STDMETHOD(RecordTestResults)(TESTRESULTS::iterator);
	STDMETHOD(ExtractLogMessages)(BSTR, wchar_t *, int *);

	enum ExecutionStatus
	{
		ExecutionStatus_Failed = 1,
		ExecutionStatus_Passed = 2,
		ExecutionStatus_NotRun = 3,
		ExecutionStatus_NotApplicable = 4,
		ExecutionStatus_Blocked = 5,
		ExecutionStatus_Caution = 6
	};
};