//
// sproxy.exe generated file
// do not modify this file
//
// Created: 08/24/2008@23:13:17
//

#pragma once


#if !defined(_WIN32_WINDOWS) && !defined(_WIN32_WINNT) && !defined(_WIN32_WCE)
#pragma message("warning: defining _WIN32_WINDOWS = 0x0410")
#define _WIN32_WINDOWS 0x0410
#endif

#include "atlsoap.h"

namespace SpiraTestExecuteService
{

template <typename TClient = CSoapSocketClientT<> >
class CTestExecuteT : 
	public TClient, 
	public CSoapRootHandler
{
protected:

	const _soapmap ** GetFunctionMap();
	const _soapmap ** GetHeaderMap();
	void * GetHeaderValue();
	const wchar_t * GetNamespaceUri();
	const char * GetServiceName();
	const char * GetNamespaceUriA();
	HRESULT CallFunction(
		void *pvParam, 
		const wchar_t *wszLocalName, int cchLocalName,
		size_t nItem);
	HRESULT GetClientReader(ISAXXMLReader **ppReader);

public:

	HRESULT __stdcall QueryInterface(REFIID riid, void **ppv)
	{
		if (ppv == NULL)
		{
			return E_POINTER;
		}

		*ppv = NULL;

		if (InlineIsEqualGUID(riid, IID_IUnknown) ||
			InlineIsEqualGUID(riid, IID_ISAXContentHandler))
		{
			*ppv = static_cast<ISAXContentHandler *>(this);
			return S_OK;
		}

		return E_NOINTERFACE;
	}

	ULONG __stdcall AddRef()
	{
		return 1;
	}

	ULONG __stdcall Release()
	{
		return 1;
	}

	CTestExecuteT(ISAXXMLReader *pReader = NULL)
		:TClient(_T("http://localhost/SpiraTest/Services/TestExecute.asmx"))
	{
		SetClient(true);
		SetReader(pReader);
	}
	
	~CTestExecuteT()
	{
		Uninitialize();
	}
	
	void Uninitialize()
	{
		UninitializeSOAP();
	}	

	HRESULT RetrieveServerDateTime(
		BSTR* RetrieveServerDateTimeResult
	);

	HRESULT Disconnect(
	);

	HRESULT Authenticate(
		BSTR userName, 
		BSTR password, 
		bool* AuthenticateResult
	);

	HRESULT RecordTestRun2(
		BSTR userName, 
		BSTR password, 
		int projectId, 
		int testerUserId, 
		int testCaseId, 
		int releaseId, 
		BSTR startDate, 
		BSTR endDate, 
		int executionStatusId, 
		BSTR runnerName, 
		BSTR runnerTestName, 
		int runnerAssertCount, 
		BSTR runnerMessage, 
		BSTR runnerStackTrace, 
		int* RecordTestRun2Result
	);

	HRESULT RetrieveProjectList(
		BSTR* RetrieveProjectListResult
	);

	HRESULT ConnectToProject(
		int projectId, 
		bool* ConnectToProjectResult
	);

	HRESULT RecordTestRun(
		int testerUserId, 
		int testCaseId, 
		int releaseId, 
		BSTR startDate, 
		BSTR endDate, 
		int executionStatusId, 
		BSTR runnerName, 
		BSTR runnerTestName, 
		int runnerAssertCount, 
		BSTR runnerMessage, 
		BSTR runnerStackTrace, 
		int* RecordTestRunResult
	);

	HRESULT RetrieveTestRunById(
		int testRunId, 
		BSTR* RetrieveTestRunByIdResult
	);
};

typedef CTestExecuteT<> CTestExecute;

struct __CTestExecute_RetrieveServerDateTime_struct
{
	BSTR RetrieveServerDateTimeResult;
};

extern __declspec(selectany) const _soapmapentry __CTestExecute_RetrieveServerDateTime_entries[] =
{

	{
		0xDB885A29, 
		"RetrieveServerDateTimeResult", 
		L"RetrieveServerDateTimeResult", 
		sizeof("RetrieveServerDateTimeResult")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_OUT | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		offsetof(__CTestExecute_RetrieveServerDateTime_struct, RetrieveServerDateTimeResult),
		NULL,
		NULL,
		-1,
	},
	{ 0x00000000 }
};

extern __declspec(selectany) const _soapmap __CTestExecute_RetrieveServerDateTime_map =
{
	0xDEAEA8B9,
	"RetrieveServerDateTime",
	L"RetrieveServerDateTimeResponse",
	sizeof("RetrieveServerDateTime")-1,
	sizeof("RetrieveServerDateTimeResponse")-1,
	SOAPMAP_FUNC,
	__CTestExecute_RetrieveServerDateTime_entries,
	sizeof(__CTestExecute_RetrieveServerDateTime_struct),
	1,
	-1,
	SOAPFLAG_NONE | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
	0xA2B55034,
	"http://www.inflectra.com/SpiraTest/Services/v1.2.0/",
	L"http://www.inflectra.com/SpiraTest/Services/v1.2.0/",
	sizeof("http://www.inflectra.com/SpiraTest/Services/v1.2.0/")-1
};


struct __CTestExecute_Disconnect_struct
{
};

extern __declspec(selectany) const _soapmapentry __CTestExecute_Disconnect_entries[] =
{

	{ 0x00000000 }
};

extern __declspec(selectany) const _soapmap __CTestExecute_Disconnect_map =
{
	0x044723D9,
	"Disconnect",
	L"DisconnectResponse",
	sizeof("Disconnect")-1,
	sizeof("DisconnectResponse")-1,
	SOAPMAP_FUNC,
	__CTestExecute_Disconnect_entries,
	sizeof(__CTestExecute_Disconnect_struct),
	0,
	-1,
	SOAPFLAG_NONE | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
	0xA2B55034,
	"http://www.inflectra.com/SpiraTest/Services/v1.2.0/",
	L"http://www.inflectra.com/SpiraTest/Services/v1.2.0/",
	sizeof("http://www.inflectra.com/SpiraTest/Services/v1.2.0/")-1
};


struct __CTestExecute_Authenticate_struct
{
	BSTR userName;
	BSTR password;
	bool AuthenticateResult;
};

extern __declspec(selectany) const _soapmapentry __CTestExecute_Authenticate_entries[] =
{

	{
		0x8253F720, 
		"userName", 
		L"userName", 
		sizeof("userName")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL | SOAPFLAG_NULLABLE,
		offsetof(__CTestExecute_Authenticate_struct, userName),
		NULL,
		NULL,
		-1,
	},
	{
		0x9C439233, 
		"password", 
		L"password", 
		sizeof("password")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL | SOAPFLAG_NULLABLE,
		offsetof(__CTestExecute_Authenticate_struct, password),
		NULL,
		NULL,
		-1,
	},
	{
		0xB13D4C1E, 
		"AuthenticateResult", 
		L"AuthenticateResult", 
		sizeof("AuthenticateResult")-1, 
		SOAPTYPE_BOOLEAN, 
		SOAPFLAG_NONE | SOAPFLAG_OUT | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		offsetof(__CTestExecute_Authenticate_struct, AuthenticateResult),
		NULL,
		NULL,
		-1,
	},
	{ 0x00000000 }
};

extern __declspec(selectany) const _soapmap __CTestExecute_Authenticate_map =
{
	0xF567EBEE,
	"Authenticate",
	L"AuthenticateResponse",
	sizeof("Authenticate")-1,
	sizeof("AuthenticateResponse")-1,
	SOAPMAP_FUNC,
	__CTestExecute_Authenticate_entries,
	sizeof(__CTestExecute_Authenticate_struct),
	1,
	-1,
	SOAPFLAG_NONE | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
	0xA2B55034,
	"http://www.inflectra.com/SpiraTest/Services/v1.2.0/",
	L"http://www.inflectra.com/SpiraTest/Services/v1.2.0/",
	sizeof("http://www.inflectra.com/SpiraTest/Services/v1.2.0/")-1
};


struct __CTestExecute_RecordTestRun2_struct
{
	BSTR userName;
	BSTR password;
	int projectId;
	int testerUserId;
	int testCaseId;
	int releaseId;
	BSTR startDate;
	BSTR endDate;
	int executionStatusId;
	BSTR runnerName;
	BSTR runnerTestName;
	int runnerAssertCount;
	BSTR runnerMessage;
	BSTR runnerStackTrace;
	int RecordTestRun2Result;
};

extern __declspec(selectany) const _soapmapentry __CTestExecute_RecordTestRun2_entries[] =
{

	{
		0x8253F720, 
		"userName", 
		L"userName", 
		sizeof("userName")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL | SOAPFLAG_NULLABLE,
		offsetof(__CTestExecute_RecordTestRun2_struct, userName),
		NULL,
		NULL,
		-1,
	},
	{
		0x9C439233, 
		"password", 
		L"password", 
		sizeof("password")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL | SOAPFLAG_NULLABLE,
		offsetof(__CTestExecute_RecordTestRun2_struct, password),
		NULL,
		NULL,
		-1,
	},
	{
		0x8AE152A4, 
		"projectId", 
		L"projectId", 
		sizeof("projectId")-1, 
		SOAPTYPE_INT, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		offsetof(__CTestExecute_RecordTestRun2_struct, projectId),
		NULL,
		NULL,
		-1,
	},
	{
		0xB1051403, 
		"testerUserId", 
		L"testerUserId", 
		sizeof("testerUserId")-1, 
		SOAPTYPE_INT, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		offsetof(__CTestExecute_RecordTestRun2_struct, testerUserId),
		NULL,
		NULL,
		-1,
	},
	{
		0x703E32E9, 
		"testCaseId", 
		L"testCaseId", 
		sizeof("testCaseId")-1, 
		SOAPTYPE_INT, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		offsetof(__CTestExecute_RecordTestRun2_struct, testCaseId),
		NULL,
		NULL,
		-1,
	},
	{
		0x81AA080E, 
		"releaseId", 
		L"releaseId", 
		sizeof("releaseId")-1, 
		SOAPTYPE_INT, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		offsetof(__CTestExecute_RecordTestRun2_struct, releaseId),
		NULL,
		NULL,
		-1,
	},
	{
		0x9ED2666C, 
		"startDate", 
		L"startDate", 
		sizeof("startDate")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		offsetof(__CTestExecute_RecordTestRun2_struct, startDate),
		NULL,
		NULL,
		-1,
	},
	{
		0x6689F575, 
		"endDate", 
		L"endDate", 
		sizeof("endDate")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		offsetof(__CTestExecute_RecordTestRun2_struct, endDate),
		NULL,
		NULL,
		-1,
	},
	{
		0x592324C5, 
		"executionStatusId", 
		L"executionStatusId", 
		sizeof("executionStatusId")-1, 
		SOAPTYPE_INT, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		offsetof(__CTestExecute_RecordTestRun2_struct, executionStatusId),
		NULL,
		NULL,
		-1,
	},
	{
		0x95383B5B, 
		"runnerName", 
		L"runnerName", 
		sizeof("runnerName")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL | SOAPFLAG_NULLABLE,
		offsetof(__CTestExecute_RecordTestRun2_struct, runnerName),
		NULL,
		NULL,
		-1,
	},
	{
		0x6FFB351B, 
		"runnerTestName", 
		L"runnerTestName", 
		sizeof("runnerTestName")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL | SOAPFLAG_NULLABLE,
		offsetof(__CTestExecute_RecordTestRun2_struct, runnerTestName),
		NULL,
		NULL,
		-1,
	},
	{
		0x46A2EC15, 
		"runnerAssertCount", 
		L"runnerAssertCount", 
		sizeof("runnerAssertCount")-1, 
		SOAPTYPE_INT, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		offsetof(__CTestExecute_RecordTestRun2_struct, runnerAssertCount),
		NULL,
		NULL,
		-1,
	},
	{
		0x079491DF, 
		"runnerMessage", 
		L"runnerMessage", 
		sizeof("runnerMessage")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL | SOAPFLAG_NULLABLE,
		offsetof(__CTestExecute_RecordTestRun2_struct, runnerMessage),
		NULL,
		NULL,
		-1,
	},
	{
		0xB45B0ADF, 
		"runnerStackTrace", 
		L"runnerStackTrace", 
		sizeof("runnerStackTrace")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL | SOAPFLAG_NULLABLE,
		offsetof(__CTestExecute_RecordTestRun2_struct, runnerStackTrace),
		NULL,
		NULL,
		-1,
	},
	{
		0x2A4F14C5, 
		"RecordTestRun2Result", 
		L"RecordTestRun2Result", 
		sizeof("RecordTestRun2Result")-1, 
		SOAPTYPE_INT, 
		SOAPFLAG_NONE | SOAPFLAG_OUT | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		offsetof(__CTestExecute_RecordTestRun2_struct, RecordTestRun2Result),
		NULL,
		NULL,
		-1,
	},
	{ 0x00000000 }
};

extern __declspec(selectany) const _soapmap __CTestExecute_RecordTestRun2_map =
{
	0xFA0E7A55,
	"RecordTestRun2",
	L"RecordTestRun2Response",
	sizeof("RecordTestRun2")-1,
	sizeof("RecordTestRun2Response")-1,
	SOAPMAP_FUNC,
	__CTestExecute_RecordTestRun2_entries,
	sizeof(__CTestExecute_RecordTestRun2_struct),
	1,
	-1,
	SOAPFLAG_NONE | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
	0xA2B55034,
	"http://www.inflectra.com/SpiraTest/Services/v1.2.0/",
	L"http://www.inflectra.com/SpiraTest/Services/v1.2.0/",
	sizeof("http://www.inflectra.com/SpiraTest/Services/v1.2.0/")-1
};


struct __CTestExecute_RetrieveProjectList_struct
{
	BSTR RetrieveProjectListResult;
};

extern __declspec(selectany) const _soapmapentry __CTestExecute_RetrieveProjectList_entries[] =
{

	{
		0xE0D991F8, 
		"RetrieveProjectListResult", 
		L"RetrieveProjectListResult", 
		sizeof("RetrieveProjectListResult")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_OUT | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL | SOAPFLAG_NULLABLE,
		offsetof(__CTestExecute_RetrieveProjectList_struct, RetrieveProjectListResult),
		NULL,
		NULL,
		-1,
	},
	{ 0x00000000 }
};

extern __declspec(selectany) const _soapmap __CTestExecute_RetrieveProjectList_map =
{
	0x7D2D1048,
	"RetrieveProjectList",
	L"RetrieveProjectListResponse",
	sizeof("RetrieveProjectList")-1,
	sizeof("RetrieveProjectListResponse")-1,
	SOAPMAP_FUNC,
	__CTestExecute_RetrieveProjectList_entries,
	sizeof(__CTestExecute_RetrieveProjectList_struct),
	1,
	-1,
	SOAPFLAG_NONE | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
	0xA2B55034,
	"http://www.inflectra.com/SpiraTest/Services/v1.2.0/",
	L"http://www.inflectra.com/SpiraTest/Services/v1.2.0/",
	sizeof("http://www.inflectra.com/SpiraTest/Services/v1.2.0/")-1
};


struct __CTestExecute_ConnectToProject_struct
{
	int projectId;
	bool ConnectToProjectResult;
};

extern __declspec(selectany) const _soapmapentry __CTestExecute_ConnectToProject_entries[] =
{

	{
		0x8AE152A4, 
		"projectId", 
		L"projectId", 
		sizeof("projectId")-1, 
		SOAPTYPE_INT, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		offsetof(__CTestExecute_ConnectToProject_struct, projectId),
		NULL,
		NULL,
		-1,
	},
	{
		0x78047583, 
		"ConnectToProjectResult", 
		L"ConnectToProjectResult", 
		sizeof("ConnectToProjectResult")-1, 
		SOAPTYPE_BOOLEAN, 
		SOAPFLAG_NONE | SOAPFLAG_OUT | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		offsetof(__CTestExecute_ConnectToProject_struct, ConnectToProjectResult),
		NULL,
		NULL,
		-1,
	},
	{ 0x00000000 }
};

extern __declspec(selectany) const _soapmap __CTestExecute_ConnectToProject_map =
{
	0x8A9F0293,
	"ConnectToProject",
	L"ConnectToProjectResponse",
	sizeof("ConnectToProject")-1,
	sizeof("ConnectToProjectResponse")-1,
	SOAPMAP_FUNC,
	__CTestExecute_ConnectToProject_entries,
	sizeof(__CTestExecute_ConnectToProject_struct),
	1,
	-1,
	SOAPFLAG_NONE | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
	0xA2B55034,
	"http://www.inflectra.com/SpiraTest/Services/v1.2.0/",
	L"http://www.inflectra.com/SpiraTest/Services/v1.2.0/",
	sizeof("http://www.inflectra.com/SpiraTest/Services/v1.2.0/")-1
};


struct __CTestExecute_RecordTestRun_struct
{
	int testerUserId;
	int testCaseId;
	int releaseId;
	BSTR startDate;
	BSTR endDate;
	int executionStatusId;
	BSTR runnerName;
	BSTR runnerTestName;
	int runnerAssertCount;
	BSTR runnerMessage;
	BSTR runnerStackTrace;
	int RecordTestRunResult;
};

extern __declspec(selectany) const _soapmapentry __CTestExecute_RecordTestRun_entries[] =
{

	{
		0xB1051403, 
		"testerUserId", 
		L"testerUserId", 
		sizeof("testerUserId")-1, 
		SOAPTYPE_INT, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		offsetof(__CTestExecute_RecordTestRun_struct, testerUserId),
		NULL,
		NULL,
		-1,
	},
	{
		0x703E32E9, 
		"testCaseId", 
		L"testCaseId", 
		sizeof("testCaseId")-1, 
		SOAPTYPE_INT, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		offsetof(__CTestExecute_RecordTestRun_struct, testCaseId),
		NULL,
		NULL,
		-1,
	},
	{
		0x81AA080E, 
		"releaseId", 
		L"releaseId", 
		sizeof("releaseId")-1, 
		SOAPTYPE_INT, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		offsetof(__CTestExecute_RecordTestRun_struct, releaseId),
		NULL,
		NULL,
		-1,
	},
	{
		0x9ED2666C, 
		"startDate", 
		L"startDate", 
		sizeof("startDate")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		offsetof(__CTestExecute_RecordTestRun_struct, startDate),
		NULL,
		NULL,
		-1,
	},
	{
		0x6689F575, 
		"endDate", 
		L"endDate", 
		sizeof("endDate")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		offsetof(__CTestExecute_RecordTestRun_struct, endDate),
		NULL,
		NULL,
		-1,
	},
	{
		0x592324C5, 
		"executionStatusId", 
		L"executionStatusId", 
		sizeof("executionStatusId")-1, 
		SOAPTYPE_INT, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		offsetof(__CTestExecute_RecordTestRun_struct, executionStatusId),
		NULL,
		NULL,
		-1,
	},
	{
		0x95383B5B, 
		"runnerName", 
		L"runnerName", 
		sizeof("runnerName")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL | SOAPFLAG_NULLABLE,
		offsetof(__CTestExecute_RecordTestRun_struct, runnerName),
		NULL,
		NULL,
		-1,
	},
	{
		0x6FFB351B, 
		"runnerTestName", 
		L"runnerTestName", 
		sizeof("runnerTestName")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL | SOAPFLAG_NULLABLE,
		offsetof(__CTestExecute_RecordTestRun_struct, runnerTestName),
		NULL,
		NULL,
		-1,
	},
	{
		0x46A2EC15, 
		"runnerAssertCount", 
		L"runnerAssertCount", 
		sizeof("runnerAssertCount")-1, 
		SOAPTYPE_INT, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		offsetof(__CTestExecute_RecordTestRun_struct, runnerAssertCount),
		NULL,
		NULL,
		-1,
	},
	{
		0x079491DF, 
		"runnerMessage", 
		L"runnerMessage", 
		sizeof("runnerMessage")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL | SOAPFLAG_NULLABLE,
		offsetof(__CTestExecute_RecordTestRun_struct, runnerMessage),
		NULL,
		NULL,
		-1,
	},
	{
		0xB45B0ADF, 
		"runnerStackTrace", 
		L"runnerStackTrace", 
		sizeof("runnerStackTrace")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL | SOAPFLAG_NULLABLE,
		offsetof(__CTestExecute_RecordTestRun_struct, runnerStackTrace),
		NULL,
		NULL,
		-1,
	},
	{
		0xC1A9E893, 
		"RecordTestRunResult", 
		L"RecordTestRunResult", 
		sizeof("RecordTestRunResult")-1, 
		SOAPTYPE_INT, 
		SOAPFLAG_NONE | SOAPFLAG_OUT | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		offsetof(__CTestExecute_RecordTestRun_struct, RecordTestRunResult),
		NULL,
		NULL,
		-1,
	},
	{ 0x00000000 }
};

extern __declspec(selectany) const _soapmap __CTestExecute_RecordTestRun_map =
{
	0xD36D79A3,
	"RecordTestRun",
	L"RecordTestRunResponse",
	sizeof("RecordTestRun")-1,
	sizeof("RecordTestRunResponse")-1,
	SOAPMAP_FUNC,
	__CTestExecute_RecordTestRun_entries,
	sizeof(__CTestExecute_RecordTestRun_struct),
	1,
	-1,
	SOAPFLAG_NONE | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
	0xA2B55034,
	"http://www.inflectra.com/SpiraTest/Services/v1.2.0/",
	L"http://www.inflectra.com/SpiraTest/Services/v1.2.0/",
	sizeof("http://www.inflectra.com/SpiraTest/Services/v1.2.0/")-1
};


struct __CTestExecute_RetrieveTestRunById_struct
{
	int testRunId;
	BSTR RetrieveTestRunByIdResult;
};

extern __declspec(selectany) const _soapmapentry __CTestExecute_RetrieveTestRunById_entries[] =
{

	{
		0xA769C442, 
		"testRunId", 
		L"testRunId", 
		sizeof("testRunId")-1, 
		SOAPTYPE_INT, 
		SOAPFLAG_NONE | SOAPFLAG_IN | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		offsetof(__CTestExecute_RetrieveTestRunById_struct, testRunId),
		NULL,
		NULL,
		-1,
	},
	{
		0x64FD6D62, 
		"RetrieveTestRunByIdResult", 
		L"RetrieveTestRunByIdResult", 
		sizeof("RetrieveTestRunByIdResult")-1, 
		SOAPTYPE_STRING, 
		SOAPFLAG_NONE | SOAPFLAG_OUT | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL | SOAPFLAG_NULLABLE,
		offsetof(__CTestExecute_RetrieveTestRunById_struct, RetrieveTestRunByIdResult),
		NULL,
		NULL,
		-1,
	},
	{ 0x00000000 }
};

extern __declspec(selectany) const _soapmap __CTestExecute_RetrieveTestRunById_map =
{
	0x99B56E32,
	"RetrieveTestRunById",
	L"RetrieveTestRunByIdResponse",
	sizeof("RetrieveTestRunById")-1,
	sizeof("RetrieveTestRunByIdResponse")-1,
	SOAPMAP_FUNC,
	__CTestExecute_RetrieveTestRunById_entries,
	sizeof(__CTestExecute_RetrieveTestRunById_struct),
	1,
	-1,
	SOAPFLAG_NONE | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
	0xA2B55034,
	"http://www.inflectra.com/SpiraTest/Services/v1.2.0/",
	L"http://www.inflectra.com/SpiraTest/Services/v1.2.0/",
	sizeof("http://www.inflectra.com/SpiraTest/Services/v1.2.0/")-1
};

extern __declspec(selectany) const _soapmap * __CTestExecute_funcs[] =
{
	&__CTestExecute_RetrieveServerDateTime_map,
	&__CTestExecute_Disconnect_map,
	&__CTestExecute_Authenticate_map,
	&__CTestExecute_RecordTestRun2_map,
	&__CTestExecute_RetrieveProjectList_map,
	&__CTestExecute_ConnectToProject_map,
	&__CTestExecute_RecordTestRun_map,
	&__CTestExecute_RetrieveTestRunById_map,
	NULL
};

template <typename TClient>
inline HRESULT CTestExecuteT<TClient>::RetrieveServerDateTime(
		BSTR* RetrieveServerDateTimeResult
	)
{
    if ( RetrieveServerDateTimeResult == NULL )
		return E_POINTER;

	HRESULT __atlsoap_hr = InitializeSOAP(NULL);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_INITIALIZE_ERROR);
		return __atlsoap_hr;
	}
	
	CleanupClient();

	CComPtr<IStream> __atlsoap_spReadStream;
	__CTestExecute_RetrieveServerDateTime_struct __params;
	memset(&__params, 0x00, sizeof(__params));

	__atlsoap_hr = SetClientStruct(&__params, 0);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_OUTOFMEMORY);
		goto __skip_cleanup;
	}
	
	__atlsoap_hr = GenerateResponse(GetWriteStream());
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_GENERATE_ERROR);
		goto __skip_cleanup;
	}
	
	__atlsoap_hr = SendRequest(_T("SOAPAction: \"http://www.inflectra.com/SpiraTest/Services/v1.2.0/RetrieveServerDateTime\"\r\n"));
	if (FAILED(__atlsoap_hr))
	{
		goto __skip_cleanup;
	}
	__atlsoap_hr = GetReadStream(&__atlsoap_spReadStream);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_READ_ERROR);
		goto __skip_cleanup;
	}
	
	// cleanup any in/out-params and out-headers from previous calls
	Cleanup();
	__atlsoap_hr = BeginParse(__atlsoap_spReadStream);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_PARSE_ERROR);
		goto __cleanup;
	}

	*RetrieveServerDateTimeResult = __params.RetrieveServerDateTimeResult;
	goto __skip_cleanup;
	
__cleanup:
	Cleanup();
__skip_cleanup:
	ResetClientState(true);
	memset(&__params, 0x00, sizeof(__params));
	return __atlsoap_hr;
}

template <typename TClient>
inline HRESULT CTestExecuteT<TClient>::Disconnect(
	)
{

	HRESULT __atlsoap_hr = InitializeSOAP(NULL);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_INITIALIZE_ERROR);
		return __atlsoap_hr;
	}
	
	CleanupClient();

	CComPtr<IStream> __atlsoap_spReadStream;
	__CTestExecute_Disconnect_struct __params;
	memset(&__params, 0x00, sizeof(__params));

	__atlsoap_hr = SetClientStruct(&__params, 1);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_OUTOFMEMORY);
		goto __skip_cleanup;
	}
	
	__atlsoap_hr = GenerateResponse(GetWriteStream());
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_GENERATE_ERROR);
		goto __skip_cleanup;
	}
	
	__atlsoap_hr = SendRequest(_T("SOAPAction: \"http://www.inflectra.com/SpiraTest/Services/v1.2.0/Disconnect\"\r\n"));
	if (FAILED(__atlsoap_hr))
	{
		goto __skip_cleanup;
	}
	__atlsoap_hr = GetReadStream(&__atlsoap_spReadStream);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_READ_ERROR);
		goto __skip_cleanup;
	}
	
	// cleanup any in/out-params and out-headers from previous calls
	Cleanup();
	__atlsoap_hr = BeginParse(__atlsoap_spReadStream);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_PARSE_ERROR);
		goto __cleanup;
	}

	goto __skip_cleanup;
	
__cleanup:
	Cleanup();
__skip_cleanup:
	ResetClientState(true);
	memset(&__params, 0x00, sizeof(__params));
	return __atlsoap_hr;
}

template <typename TClient>
inline HRESULT CTestExecuteT<TClient>::Authenticate(
		BSTR userName, 
		BSTR password, 
		bool* AuthenticateResult
	)
{
    if ( AuthenticateResult == NULL )
		return E_POINTER;

	HRESULT __atlsoap_hr = InitializeSOAP(NULL);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_INITIALIZE_ERROR);
		return __atlsoap_hr;
	}
	
	CleanupClient();

	CComPtr<IStream> __atlsoap_spReadStream;
	__CTestExecute_Authenticate_struct __params;
	memset(&__params, 0x00, sizeof(__params));
	__params.userName = userName;
	__params.password = password;

	__atlsoap_hr = SetClientStruct(&__params, 2);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_OUTOFMEMORY);
		goto __skip_cleanup;
	}
	
	__atlsoap_hr = GenerateResponse(GetWriteStream());
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_GENERATE_ERROR);
		goto __skip_cleanup;
	}
	
	__atlsoap_hr = SendRequest(_T("SOAPAction: \"http://www.inflectra.com/SpiraTest/Services/v1.2.0/Authenticate\"\r\n"));
	if (FAILED(__atlsoap_hr))
	{
		goto __skip_cleanup;
	}
	__atlsoap_hr = GetReadStream(&__atlsoap_spReadStream);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_READ_ERROR);
		goto __skip_cleanup;
	}
	
	// cleanup any in/out-params and out-headers from previous calls
	Cleanup();
	__atlsoap_hr = BeginParse(__atlsoap_spReadStream);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_PARSE_ERROR);
		goto __cleanup;
	}

	*AuthenticateResult = __params.AuthenticateResult;
	goto __skip_cleanup;
	
__cleanup:
	Cleanup();
__skip_cleanup:
	ResetClientState(true);
	memset(&__params, 0x00, sizeof(__params));
	return __atlsoap_hr;
}

template <typename TClient>
inline HRESULT CTestExecuteT<TClient>::RecordTestRun2(
		BSTR userName, 
		BSTR password, 
		int projectId, 
		int testerUserId, 
		int testCaseId, 
		int releaseId, 
		BSTR startDate, 
		BSTR endDate, 
		int executionStatusId, 
		BSTR runnerName, 
		BSTR runnerTestName, 
		int runnerAssertCount, 
		BSTR runnerMessage, 
		BSTR runnerStackTrace, 
		int* RecordTestRun2Result
	)
{
    if ( RecordTestRun2Result == NULL )
		return E_POINTER;

	HRESULT __atlsoap_hr = InitializeSOAP(NULL);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_INITIALIZE_ERROR);
		return __atlsoap_hr;
	}
	
	CleanupClient();

	CComPtr<IStream> __atlsoap_spReadStream;
	__CTestExecute_RecordTestRun2_struct __params;
	memset(&__params, 0x00, sizeof(__params));
	__params.userName = userName;
	__params.password = password;
	__params.projectId = projectId;
	__params.testerUserId = testerUserId;
	__params.testCaseId = testCaseId;
	__params.releaseId = releaseId;
	__params.startDate = startDate;
	__params.endDate = endDate;
	__params.executionStatusId = executionStatusId;
	__params.runnerName = runnerName;
	__params.runnerTestName = runnerTestName;
	__params.runnerAssertCount = runnerAssertCount;
	__params.runnerMessage = runnerMessage;
	__params.runnerStackTrace = runnerStackTrace;

	__atlsoap_hr = SetClientStruct(&__params, 3);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_OUTOFMEMORY);
		goto __skip_cleanup;
	}
	
	__atlsoap_hr = GenerateResponse(GetWriteStream());
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_GENERATE_ERROR);
		goto __skip_cleanup;
	}
	
	__atlsoap_hr = SendRequest(_T("SOAPAction: \"http://www.inflectra.com/SpiraTest/Services/v1.2.0/RecordTestRun2\"\r\n"));
	if (FAILED(__atlsoap_hr))
	{
		goto __skip_cleanup;
	}
	__atlsoap_hr = GetReadStream(&__atlsoap_spReadStream);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_READ_ERROR);
		goto __skip_cleanup;
	}
	
	// cleanup any in/out-params and out-headers from previous calls
	Cleanup();
	__atlsoap_hr = BeginParse(__atlsoap_spReadStream);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_PARSE_ERROR);
		goto __cleanup;
	}

	*RecordTestRun2Result = __params.RecordTestRun2Result;
	goto __skip_cleanup;
	
__cleanup:
	Cleanup();
__skip_cleanup:
	ResetClientState(true);
	memset(&__params, 0x00, sizeof(__params));
	return __atlsoap_hr;
}

template <typename TClient>
inline HRESULT CTestExecuteT<TClient>::RetrieveProjectList(
		BSTR* RetrieveProjectListResult
	)
{
    if ( RetrieveProjectListResult == NULL )
		return E_POINTER;

	HRESULT __atlsoap_hr = InitializeSOAP(NULL);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_INITIALIZE_ERROR);
		return __atlsoap_hr;
	}
	
	CleanupClient();

	CComPtr<IStream> __atlsoap_spReadStream;
	__CTestExecute_RetrieveProjectList_struct __params;
	memset(&__params, 0x00, sizeof(__params));

	__atlsoap_hr = SetClientStruct(&__params, 4);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_OUTOFMEMORY);
		goto __skip_cleanup;
	}
	
	__atlsoap_hr = GenerateResponse(GetWriteStream());
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_GENERATE_ERROR);
		goto __skip_cleanup;
	}
	
	__atlsoap_hr = SendRequest(_T("SOAPAction: \"http://www.inflectra.com/SpiraTest/Services/v1.2.0/RetrieveProjectList\"\r\n"));
	if (FAILED(__atlsoap_hr))
	{
		goto __skip_cleanup;
	}
	__atlsoap_hr = GetReadStream(&__atlsoap_spReadStream);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_READ_ERROR);
		goto __skip_cleanup;
	}
	
	// cleanup any in/out-params and out-headers from previous calls
	Cleanup();
	__atlsoap_hr = BeginParse(__atlsoap_spReadStream);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_PARSE_ERROR);
		goto __cleanup;
	}

	*RetrieveProjectListResult = __params.RetrieveProjectListResult;
	goto __skip_cleanup;
	
__cleanup:
	Cleanup();
__skip_cleanup:
	ResetClientState(true);
	memset(&__params, 0x00, sizeof(__params));
	return __atlsoap_hr;
}

template <typename TClient>
inline HRESULT CTestExecuteT<TClient>::ConnectToProject(
		int projectId, 
		bool* ConnectToProjectResult
	)
{
    if ( ConnectToProjectResult == NULL )
		return E_POINTER;

	HRESULT __atlsoap_hr = InitializeSOAP(NULL);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_INITIALIZE_ERROR);
		return __atlsoap_hr;
	}
	
	CleanupClient();

	CComPtr<IStream> __atlsoap_spReadStream;
	__CTestExecute_ConnectToProject_struct __params;
	memset(&__params, 0x00, sizeof(__params));
	__params.projectId = projectId;

	__atlsoap_hr = SetClientStruct(&__params, 5);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_OUTOFMEMORY);
		goto __skip_cleanup;
	}
	
	__atlsoap_hr = GenerateResponse(GetWriteStream());
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_GENERATE_ERROR);
		goto __skip_cleanup;
	}
	
	__atlsoap_hr = SendRequest(_T("SOAPAction: \"http://www.inflectra.com/SpiraTest/Services/v1.2.0/ConnectToProject\"\r\n"));
	if (FAILED(__atlsoap_hr))
	{
		goto __skip_cleanup;
	}
	__atlsoap_hr = GetReadStream(&__atlsoap_spReadStream);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_READ_ERROR);
		goto __skip_cleanup;
	}
	
	// cleanup any in/out-params and out-headers from previous calls
	Cleanup();
	__atlsoap_hr = BeginParse(__atlsoap_spReadStream);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_PARSE_ERROR);
		goto __cleanup;
	}

	*ConnectToProjectResult = __params.ConnectToProjectResult;
	goto __skip_cleanup;
	
__cleanup:
	Cleanup();
__skip_cleanup:
	ResetClientState(true);
	memset(&__params, 0x00, sizeof(__params));
	return __atlsoap_hr;
}

template <typename TClient>
inline HRESULT CTestExecuteT<TClient>::RecordTestRun(
		int testerUserId, 
		int testCaseId, 
		int releaseId, 
		BSTR startDate, 
		BSTR endDate, 
		int executionStatusId, 
		BSTR runnerName, 
		BSTR runnerTestName, 
		int runnerAssertCount, 
		BSTR runnerMessage, 
		BSTR runnerStackTrace, 
		int* RecordTestRunResult
	)
{
    if ( RecordTestRunResult == NULL )
		return E_POINTER;

	HRESULT __atlsoap_hr = InitializeSOAP(NULL);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_INITIALIZE_ERROR);
		return __atlsoap_hr;
	}
	
	CleanupClient();

	CComPtr<IStream> __atlsoap_spReadStream;
	__CTestExecute_RecordTestRun_struct __params;
	memset(&__params, 0x00, sizeof(__params));
	__params.testerUserId = testerUserId;
	__params.testCaseId = testCaseId;
	__params.releaseId = releaseId;
	__params.startDate = startDate;
	__params.endDate = endDate;
	__params.executionStatusId = executionStatusId;
	__params.runnerName = runnerName;
	__params.runnerTestName = runnerTestName;
	__params.runnerAssertCount = runnerAssertCount;
	__params.runnerMessage = runnerMessage;
	__params.runnerStackTrace = runnerStackTrace;

	__atlsoap_hr = SetClientStruct(&__params, 6);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_OUTOFMEMORY);
		goto __skip_cleanup;
	}
	
	__atlsoap_hr = GenerateResponse(GetWriteStream());
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_GENERATE_ERROR);
		goto __skip_cleanup;
	}
	
	__atlsoap_hr = SendRequest(_T("SOAPAction: \"http://www.inflectra.com/SpiraTest/Services/v1.2.0/RecordTestRun\"\r\n"));
	if (FAILED(__atlsoap_hr))
	{
		goto __skip_cleanup;
	}
	__atlsoap_hr = GetReadStream(&__atlsoap_spReadStream);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_READ_ERROR);
		goto __skip_cleanup;
	}
	
	// cleanup any in/out-params and out-headers from previous calls
	Cleanup();
	__atlsoap_hr = BeginParse(__atlsoap_spReadStream);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_PARSE_ERROR);
		goto __cleanup;
	}

	*RecordTestRunResult = __params.RecordTestRunResult;
	goto __skip_cleanup;
	
__cleanup:
	Cleanup();
__skip_cleanup:
	ResetClientState(true);
	memset(&__params, 0x00, sizeof(__params));
	return __atlsoap_hr;
}

template <typename TClient>
inline HRESULT CTestExecuteT<TClient>::RetrieveTestRunById(
		int testRunId, 
		BSTR* RetrieveTestRunByIdResult
	)
{
    if ( RetrieveTestRunByIdResult == NULL )
		return E_POINTER;

	HRESULT __atlsoap_hr = InitializeSOAP(NULL);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_INITIALIZE_ERROR);
		return __atlsoap_hr;
	}
	
	CleanupClient();

	CComPtr<IStream> __atlsoap_spReadStream;
	__CTestExecute_RetrieveTestRunById_struct __params;
	memset(&__params, 0x00, sizeof(__params));
	__params.testRunId = testRunId;

	__atlsoap_hr = SetClientStruct(&__params, 7);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_OUTOFMEMORY);
		goto __skip_cleanup;
	}
	
	__atlsoap_hr = GenerateResponse(GetWriteStream());
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_GENERATE_ERROR);
		goto __skip_cleanup;
	}
	
	__atlsoap_hr = SendRequest(_T("SOAPAction: \"http://www.inflectra.com/SpiraTest/Services/v1.2.0/RetrieveTestRunById\"\r\n"));
	if (FAILED(__atlsoap_hr))
	{
		goto __skip_cleanup;
	}
	__atlsoap_hr = GetReadStream(&__atlsoap_spReadStream);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_READ_ERROR);
		goto __skip_cleanup;
	}
	
	// cleanup any in/out-params and out-headers from previous calls
	Cleanup();
	__atlsoap_hr = BeginParse(__atlsoap_spReadStream);
	if (FAILED(__atlsoap_hr))
	{
		SetClientError(SOAPCLIENT_PARSE_ERROR);
		goto __cleanup;
	}

	*RetrieveTestRunByIdResult = __params.RetrieveTestRunByIdResult;
	goto __skip_cleanup;
	
__cleanup:
	Cleanup();
__skip_cleanup:
	ResetClientState(true);
	memset(&__params, 0x00, sizeof(__params));
	return __atlsoap_hr;
}

template <typename TClient>
ATL_NOINLINE inline const _soapmap ** CTestExecuteT<TClient>::GetFunctionMap()
{
	return __CTestExecute_funcs;
}

template <typename TClient>
ATL_NOINLINE inline const _soapmap ** CTestExecuteT<TClient>::GetHeaderMap()
{
	static const _soapmapentry __CTestExecute_RetrieveServerDateTime_atlsoapheader_entries[] =
	{
		{ 0x00000000 }
	};

	static const _soapmap __CTestExecute_RetrieveServerDateTime_atlsoapheader_map = 
	{
		0xDEAEA8B9,
		"RetrieveServerDateTime",
		L"RetrieveServerDateTimeResponse",
		sizeof("RetrieveServerDateTime")-1,
		sizeof("RetrieveServerDateTimeResponse")-1,
		SOAPMAP_HEADER,
		__CTestExecute_RetrieveServerDateTime_atlsoapheader_entries,
		0,
		0,
		-1,
		SOAPFLAG_NONE | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		0xA2B55034,
		"http://www.inflectra.com/SpiraTest/Services/v1.2.0/",
		L"http://www.inflectra.com/SpiraTest/Services/v1.2.0/",
		sizeof("http://www.inflectra.com/SpiraTest/Services/v1.2.0/")-1
	};

	static const _soapmapentry __CTestExecute_Disconnect_atlsoapheader_entries[] =
	{
		{ 0x00000000 }
	};

	static const _soapmap __CTestExecute_Disconnect_atlsoapheader_map = 
	{
		0x044723D9,
		"Disconnect",
		L"DisconnectResponse",
		sizeof("Disconnect")-1,
		sizeof("DisconnectResponse")-1,
		SOAPMAP_HEADER,
		__CTestExecute_Disconnect_atlsoapheader_entries,
		0,
		0,
		-1,
		SOAPFLAG_NONE | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		0xA2B55034,
		"http://www.inflectra.com/SpiraTest/Services/v1.2.0/",
		L"http://www.inflectra.com/SpiraTest/Services/v1.2.0/",
		sizeof("http://www.inflectra.com/SpiraTest/Services/v1.2.0/")-1
	};

	static const _soapmapentry __CTestExecute_Authenticate_atlsoapheader_entries[] =
	{
		{ 0x00000000 }
	};

	static const _soapmap __CTestExecute_Authenticate_atlsoapheader_map = 
	{
		0xF567EBEE,
		"Authenticate",
		L"AuthenticateResponse",
		sizeof("Authenticate")-1,
		sizeof("AuthenticateResponse")-1,
		SOAPMAP_HEADER,
		__CTestExecute_Authenticate_atlsoapheader_entries,
		0,
		0,
		-1,
		SOAPFLAG_NONE | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		0xA2B55034,
		"http://www.inflectra.com/SpiraTest/Services/v1.2.0/",
		L"http://www.inflectra.com/SpiraTest/Services/v1.2.0/",
		sizeof("http://www.inflectra.com/SpiraTest/Services/v1.2.0/")-1
	};

	static const _soapmapentry __CTestExecute_RecordTestRun2_atlsoapheader_entries[] =
	{
		{ 0x00000000 }
	};

	static const _soapmap __CTestExecute_RecordTestRun2_atlsoapheader_map = 
	{
		0xFA0E7A55,
		"RecordTestRun2",
		L"RecordTestRun2Response",
		sizeof("RecordTestRun2")-1,
		sizeof("RecordTestRun2Response")-1,
		SOAPMAP_HEADER,
		__CTestExecute_RecordTestRun2_atlsoapheader_entries,
		0,
		0,
		-1,
		SOAPFLAG_NONE | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		0xA2B55034,
		"http://www.inflectra.com/SpiraTest/Services/v1.2.0/",
		L"http://www.inflectra.com/SpiraTest/Services/v1.2.0/",
		sizeof("http://www.inflectra.com/SpiraTest/Services/v1.2.0/")-1
	};

	static const _soapmapentry __CTestExecute_RetrieveProjectList_atlsoapheader_entries[] =
	{
		{ 0x00000000 }
	};

	static const _soapmap __CTestExecute_RetrieveProjectList_atlsoapheader_map = 
	{
		0x7D2D1048,
		"RetrieveProjectList",
		L"RetrieveProjectListResponse",
		sizeof("RetrieveProjectList")-1,
		sizeof("RetrieveProjectListResponse")-1,
		SOAPMAP_HEADER,
		__CTestExecute_RetrieveProjectList_atlsoapheader_entries,
		0,
		0,
		-1,
		SOAPFLAG_NONE | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		0xA2B55034,
		"http://www.inflectra.com/SpiraTest/Services/v1.2.0/",
		L"http://www.inflectra.com/SpiraTest/Services/v1.2.0/",
		sizeof("http://www.inflectra.com/SpiraTest/Services/v1.2.0/")-1
	};

	static const _soapmapentry __CTestExecute_ConnectToProject_atlsoapheader_entries[] =
	{
		{ 0x00000000 }
	};

	static const _soapmap __CTestExecute_ConnectToProject_atlsoapheader_map = 
	{
		0x8A9F0293,
		"ConnectToProject",
		L"ConnectToProjectResponse",
		sizeof("ConnectToProject")-1,
		sizeof("ConnectToProjectResponse")-1,
		SOAPMAP_HEADER,
		__CTestExecute_ConnectToProject_atlsoapheader_entries,
		0,
		0,
		-1,
		SOAPFLAG_NONE | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		0xA2B55034,
		"http://www.inflectra.com/SpiraTest/Services/v1.2.0/",
		L"http://www.inflectra.com/SpiraTest/Services/v1.2.0/",
		sizeof("http://www.inflectra.com/SpiraTest/Services/v1.2.0/")-1
	};

	static const _soapmapentry __CTestExecute_RecordTestRun_atlsoapheader_entries[] =
	{
		{ 0x00000000 }
	};

	static const _soapmap __CTestExecute_RecordTestRun_atlsoapheader_map = 
	{
		0xD36D79A3,
		"RecordTestRun",
		L"RecordTestRunResponse",
		sizeof("RecordTestRun")-1,
		sizeof("RecordTestRunResponse")-1,
		SOAPMAP_HEADER,
		__CTestExecute_RecordTestRun_atlsoapheader_entries,
		0,
		0,
		-1,
		SOAPFLAG_NONE | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		0xA2B55034,
		"http://www.inflectra.com/SpiraTest/Services/v1.2.0/",
		L"http://www.inflectra.com/SpiraTest/Services/v1.2.0/",
		sizeof("http://www.inflectra.com/SpiraTest/Services/v1.2.0/")-1
	};

	static const _soapmapentry __CTestExecute_RetrieveTestRunById_atlsoapheader_entries[] =
	{
		{ 0x00000000 }
	};

	static const _soapmap __CTestExecute_RetrieveTestRunById_atlsoapheader_map = 
	{
		0x99B56E32,
		"RetrieveTestRunById",
		L"RetrieveTestRunByIdResponse",
		sizeof("RetrieveTestRunById")-1,
		sizeof("RetrieveTestRunByIdResponse")-1,
		SOAPMAP_HEADER,
		__CTestExecute_RetrieveTestRunById_atlsoapheader_entries,
		0,
		0,
		-1,
		SOAPFLAG_NONE | SOAPFLAG_PID | SOAPFLAG_DOCUMENT | SOAPFLAG_LITERAL,
		0xA2B55034,
		"http://www.inflectra.com/SpiraTest/Services/v1.2.0/",
		L"http://www.inflectra.com/SpiraTest/Services/v1.2.0/",
		sizeof("http://www.inflectra.com/SpiraTest/Services/v1.2.0/")-1
	};


	static const _soapmap * __CTestExecute_headers[] =
	{
		&__CTestExecute_RetrieveServerDateTime_atlsoapheader_map,
		&__CTestExecute_Disconnect_atlsoapheader_map,
		&__CTestExecute_Authenticate_atlsoapheader_map,
		&__CTestExecute_RecordTestRun2_atlsoapheader_map,
		&__CTestExecute_RetrieveProjectList_atlsoapheader_map,
		&__CTestExecute_ConnectToProject_atlsoapheader_map,
		&__CTestExecute_RecordTestRun_atlsoapheader_map,
		&__CTestExecute_RetrieveTestRunById_atlsoapheader_map,
		NULL
	};
	
	return __CTestExecute_headers;
}

template <typename TClient>
ATL_NOINLINE inline void * CTestExecuteT<TClient>::GetHeaderValue()
{
	return this;
}

template <typename TClient>
ATL_NOINLINE inline const wchar_t * CTestExecuteT<TClient>::GetNamespaceUri()
{
	return L"http://www.inflectra.com/SpiraTest/Services/v1.2.0/";
}

template <typename TClient>
ATL_NOINLINE inline const char * CTestExecuteT<TClient>::GetServiceName()
{
	return NULL;
}

template <typename TClient>
ATL_NOINLINE inline const char * CTestExecuteT<TClient>::GetNamespaceUriA()
{
	return "http://www.inflectra.com/SpiraTest/Services/v1.2.0/";
}

template <typename TClient>
ATL_NOINLINE inline HRESULT CTestExecuteT<TClient>::CallFunction(
	void *, 
	const wchar_t *, int,
	size_t)
{
	return E_NOTIMPL;
}

template <typename TClient>
ATL_NOINLINE inline HRESULT CTestExecuteT<TClient>::GetClientReader(ISAXXMLReader **ppReader)
{
	if (ppReader == NULL)
	{
		return E_INVALIDARG;
	}
	
	CComPtr<ISAXXMLReader> spReader = GetReader();
	if (spReader.p != NULL)
	{
		*ppReader = spReader.Detach();
		return S_OK;
	}
	return TClient::GetClientReader(ppReader);
}

} // namespace TestExecute
