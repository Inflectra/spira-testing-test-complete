// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

#ifndef STRICT
#define STRICT
#endif

// Modify the following defines if you have to target a platform prior to the ones specified below.
// Refer to MSDN for the latest info on corresponding values for different platforms.
#ifndef WINVER				// Allow use of features specific to Windows 95 and Windows NT 4 or later.
#define WINVER 0x0400		// Change this to the appropriate value to target Windows 98 and Windows 2000 or later.
#endif

#ifndef _WIN32_WINNT		// Allow use of features specific to Windows NT 4 or later.
#define _WIN32_WINNT 0x0400	// Change this to the appropriate value to target Windows 2000 or later.
#endif						

#ifndef _WIN32_WINDOWS		// Allow use of features specific to Windows 98 or later.
#define _WIN32_WINDOWS 0x0410 // Change this to the appropriate value to target Windows Me or later.
#endif

#ifndef _WIN32_IE			// Allow use of features specific to IE 4.0 or later.
#define _WIN32_IE 0x0400	// Change this to the appropriate value to target IE 5.0 or later.
#endif

#define _ATL_APARTMENT_THREADED
#define _ATL_NO_AUTOMATIC_NAMESPACE

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// some CString constructors will be explicit

// turns off ATL's hiding of some common and often safely ignored warning messages
#define _ATL_ALL_WARNINGS


#include "resource.h"
#include <atlbase.h>
#include <atlcom.h>
#include <atlwin.h>
#include <vector>
#include <aqConsts.h>
#include <tcProductKeys.h>
#include <ActionsConst.h>

#import "..\..\..\..\Bin\TestComplete.exe" \
	raw_interfaces_only, raw_native_types, named_guids, auto_search, no_namespace, \
	exclude("tagRECT", "UINT_PTR"), \
	rename("PlaySound", "PlaySoundR"), \
	rename("GetMessage", "GetMessageR")

using namespace ATL;

extern HINSTANCE hInstance;


static const GUID MY_ACTION_KEY = // {9B073EC9-13AB-4f2c-9283-0ED6AF7CD8CA}
		{ 0x9b073ec9, 0x13ab, 0x4f2c, { 0x92, 0x83, 0xe, 0xd6, 0xaf, 0x7c, 0xd8, 0xca } };
static const GUID MY_TOOLBAR_KEY = // {E2C01BD0-5946-4fa4-9C15-DFD0BA752D10}
		{ 0xe2c01bd0, 0x5946, 0x4fa4, { 0x9c, 0x15, 0xdf, 0xd0, 0xba, 0x75, 0x2d, 0x10 } };
static const GUID MY_POPUP_KEY = // {401460A8-8601-416e-8172-DB09F78A176D}
		{ 0x401460a8, 0x8601, 0x416e, { 0x81, 0x72, 0xdb, 0x9, 0xf7, 0x8a, 0x17, 0x6d } };

