///////////////////////////////////////////////////////////////////
// EnBSTR
// Copyright (C) 2001 Morten Abrahamsen (mabraha@online.no)
// All rights reserved.
//
// The code and information is provided "as-is" without
// warranty of any kind, either expressed or implied.
///////////////////////////////////////////////////////////////////
// 2001-02-25: 
//	- Initial Release
// 2001-02-28:
//	- Added upper, lower, reverse
//	- Added replace, spanInclude, spanExclude
///////////////////////////////////////////////////////////////////


#ifndef __ENBSTR_H__
#define __ENBSTR_H__

#pragma once

#ifndef __cplusplus
	#error ATL requires C++ compilation (use a .cpp suffix)
#endif

#include "comdef.h"

class CEnBSTR : public _bstr_t
{
public:
	// Constructors
	CEnBSTR() : _bstr_t() {}
	CEnBSTR(const char* s) : _bstr_t(s) {}
    CEnBSTR(const CEnBSTR& s) : _bstr_t(s) {}
    CEnBSTR(const _bstr_t& s) : _bstr_t(s) {}
    CEnBSTR(const wchar_t* s) : _bstr_t(s) {}
    CEnBSTR(const _variant_t& var) : _bstr_t(var) {}
    CEnBSTR(BSTR bstr, bool fCopy) : _bstr_t(bstr, fCopy) {}

	// Analysis
	int find(const _bstr_t& bstr) const
	{
		const wchar_t* pstr = _bstr_t::operator const wchar_t*();
		const wchar_t* pdest = wcsstr(pstr, bstr);
		return pdest ? pdest - pstr : -1;
	}
	int find(const wint_t& ch) const
	{
		const wchar_t* pstr = _bstr_t::operator const wchar_t*();
		const wchar_t* pdest = wcschr(pstr, ch);
		return pdest ? pdest - pstr : -1;
	}
	int find(const _bstr_t& bstr, const unsigned int nStart) const
	{
		const wchar_t* pstr = _bstr_t::operator const wchar_t*();
		if (nStart >= length()) return -1;

		const wchar_t* pdest = wcsstr(pstr+nStart, bstr);
		return pdest ? pdest - pstr : -1;
	}
	int find(const wint_t& ch, const unsigned int nStart) const
	{
		const wchar_t* pstr = _bstr_t::operator const wchar_t*();

		if (nStart >= length()) return -1;

		const wchar_t* pdest = wcschr(pstr+nStart, ch);
		return pdest ? pdest - pstr : -1;
	}

	/////////////////////////////////////////////////////////////////////
	// Extraction
	CEnBSTR mid(const unsigned int nFirst, unsigned int nCount = 0) const
	{
		unsigned int nLength = _bstr_t::length();
		if (nCount == 0) 
			nCount = nLength-nFirst;

		if (nFirst == 0 && nCount >= nLength)
			return *this;


		const wchar_t* pstr = _bstr_t::operator const wchar_t*();
		CEnBSTR bstr;

		if (nLength >= (nFirst+nCount))
		{
			wchar_t* pNewStr = new wchar_t[nCount+1];
			ZeroMemory(pNewStr, sizeof(wchar_t)*(nCount+1));
			wcsncpy(pNewStr, pstr+nFirst, nCount);
			bstr = pNewStr;
			delete [] pNewStr;
		}

		return bstr;
	}

	CEnBSTR left(const unsigned int nCount) const
	{
		return mid(0, nCount);
	}

	CEnBSTR right(const unsigned int nCount) const
	{
		unsigned int nLength = _bstr_t::length();
		if (nLength >= nCount)
			return mid(nLength-nCount, nCount);

		return *this;
	}

	CEnBSTR spanInclude(const _bstr_t& bstrCharset) const
	{
		const wchar_t* pstr = _bstr_t::operator const wchar_t*();
		unsigned int nLen = wcsspn(pstr, bstrCharset);
		
		return nLen ? mid(0, nLen) : "";
	}

	CEnBSTR spanExclude(const _bstr_t& bstrCharset) const
	{
		const wchar_t* pstr = _bstr_t::operator const wchar_t*();
		unsigned int nLen = wcscspn(pstr, bstrCharset);
		
		return nLen ? mid(0, nLen) : "";
	}

	/////////////////////////////////////////////////////////////////////
	// Manipulation
	void upper()
	{
		_bstr_t bstr(*this, true);
		_wcsupr((wchar_t*)bstr);
		*this = bstr;
	}

	void lower()
	{
		_bstr_t bstr(*this, true);
		_wcslwr((wchar_t*)bstr);
		*this = bstr;
	}

	void reverse()
	{
		_bstr_t bstr(*this, true);
		_wcsrev((wchar_t*)bstr);
		*this = bstr;
	}

	unsigned int replace(const wint_t& chFind, const wint_t& chReplace)
	{
		const wchar_t* pstr = _bstr_t::operator const wchar_t*();
		if (pstr == NULL) return 0;
		if (chFind == chReplace) return 0;

		// Make a copy of the string to avoid reference counting problems.
		_bstr_t bstrNew(*this, true);
		pstr = (wchar_t*)bstrNew;


		unsigned int nCount = 0;
		wchar_t* pSearchPos = 0;
		while (pSearchPos = wcschr(pSearchPos ? (wchar_t*)pSearchPos : (wchar_t*)pstr, chFind))
		{
			*pSearchPos = chReplace;
			++nCount;			
		}

		// Assign the new string (avoids refcount and deletes cached char-string)
		*this = bstrNew;
		return nCount;
	}

	unsigned int replace(const _bstr_t& bstrFind, const _bstr_t& bstrReplace)
	{
		const wchar_t* pSrcStr = _bstr_t::operator const wchar_t*();
		if (pSrcStr == NULL) return 0;

		unsigned int nCount = 0;
		unsigned int nSearchStrLen = bstrFind.length();

		// Calculate new length
		wchar_t* pSearchPos = 0;
		while (pSearchPos = wcsstr(pSearchPos ? (wchar_t*)pSearchPos : (wchar_t*)pSrcStr, bstrFind))
		{
			pSearchPos += nSearchStrLen;
			++nCount;			
		}

		// Replace bstrFind substrings with bstrReplace substrings
		if (nCount)
		{
			unsigned int nReplaceStrLen = bstrReplace.length();
			unsigned int nOrgStrLen = length();
			unsigned int nNewStrLength = nOrgStrLen - (nSearchStrLen - nReplaceStrLen)*nCount;
			nCount = 0;

			wchar_t* pNewStr = SysAllocStringLen(0, nNewStrLength);
			wchar_t* pSrcPos = (wchar_t*)pSrcStr;
			wchar_t* pDestPos = pNewStr;

			wchar_t* pNextSrcPos = 0;
			while (pNextSrcPos = wcsstr(pSrcPos, bstrFind))
			{
				if (pSrcPos != pNextSrcPos)
				{
					unsigned int nCopyLength = pNextSrcPos-pSrcPos;
					wcsncpy(pDestPos, pSrcPos, nCopyLength);
					pDestPos += nCopyLength;

					pSrcPos = pNextSrcPos;
				}

				wcsncpy(pDestPos, bstrReplace, nReplaceStrLen);
				pDestPos += nReplaceStrLen;
				pSrcPos += nSearchStrLen;
				++nCount;
			}

			wcsncpy(pDestPos, pSrcPos, nOrgStrLen - (pSrcPos-pSrcStr));

			*this = bstr_t(pNewStr, false);
		}
		return nCount;
	}

};

#endif (__ENBSTR_H__)