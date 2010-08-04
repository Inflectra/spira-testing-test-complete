// SampleProjectItemInfo.cpp : Implementation of CSampleProjectItemInfo

#include "stdafx.h"
#include "SampleProjectItemInfo.h"
#include "SamplePlugInConfiguration.h"


// CSampleProjectItemInfo

CSampleProjectItemInfo::CSampleProjectItemInfo()
{
	m_bitmap = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_SAMPLEITEM));
	_ASSERT( m_bitmap != NULL );
}


CSampleProjectItemInfo::~CSampleProjectItemInfo()
{
	DeleteObject(m_bitmap);
}


void CSampleProjectItemInfo::Initialize(CComPtr<IaqMessenger> messenger)
{
	m_messenger = messenger;
}


// ItcProjectNodeInfo Methods

HRESULT STDMETHODCALLTYPE CSampleProjectItemInfo::get_InfoProperty(TC_PROJECT_NODE_INFO_PROP PropID, VARIANT * Value)
{
	_ASSERT( Value != NULL );

	CComVariant default_node_name     (cDefaultName);
	CComVariant bitmap                ((LONG)m_bitmap);
	CComVariant name                  (_T("Sample Project Item"));
	CComVariant description           (_T("SampleItem project item."));
	CComVariant description_ex        (_T(""));
	CComVariant help_context          (0);
	CComVariant help_context_file_name(_T(""));
	CComVariant help_topic            (_T(""));
	CComVariant help_topic_file_name  (_T(""));
	CComVariant is_alone              (false);
	CComVariant is_required           (false);
	CComVariant can_edit_name         (true);
	CComVariant can_delete            (true);
	CComVariant recorder_create_only  (false);

	switch (PropID)
	{
		case pniDefaultNodeName:     return VariantCopy(Value, &default_node_name);
		case pniBitmapReference:     return VariantCopy(Value, &bitmap);
		case pniName:                return VariantCopy(Value, &name);
		case pniDescription:         return VariantCopy(Value, &description);
		case pniDescriptionEx:       return VariantCopy(Value, &description_ex);
		case pniHelpContext:         return VariantCopy(Value, &help_context);
		case pniHelpContextFileName: return VariantCopy(Value, &help_context_file_name);
		case pniHelpTopic:           return VariantCopy(Value, &help_topic);
		case pniHelpTopicFileName:   return VariantCopy(Value, &help_topic_file_name);
		case pniIsAlone:             return VariantCopy(Value, &is_alone);
		case pniIsRequired:          return VariantCopy(Value, &is_required);
		case pniCanEditName:         return VariantCopy(Value, &can_edit_name);
		case pniCanDelete:           return VariantCopy(Value, &can_delete);
		case pniRecorderCreateOnly:  return VariantCopy(Value, &recorder_create_only);
		default:
			_ASSERT( false );
			return ERROR_BAD_ARGUMENTS;
	}
}


HRESULT STDMETHODCALLTYPE CSampleProjectItemInfo::get_SupportedParentType(GUID * Value)
{
	_ASSERT( Value != NULL );
	*Value = c_ProjectNodeType_Project;
	return S_OK;
}


CComBSTR CSampleProjectItemInfo::GetPath(CComPtr<ItcProjectNode> node)
{
	CComVariant val;
	if (FAILED(node->get_NodeProperty(pnpStorageName, &val))) return CComBSTR(_T(""));
	if (val.vt != VT_BSTR) return CComBSTR(_T(""));

	TCHAR* path = _tcsdup(_bstr_t(val));
	TCHAR* s = _tcsrchr(path, '\\');
	if (s == NULL)
		path[0] = 0;
	else
		s[1] = 0;

	CComBSTR rv_path(path);
	free(path);

	rv_path.Append(cDefaultFolder);
	rv_path.Append(_T("\\"));

	return rv_path;
}


CComBSTR CSampleProjectItemInfo::GetName(CComPtr<ItcProjectNode> node, int index)
{
	CComBSTR name;
	do
	{
		index++;

		if (FAILED(get_DefaultFileName(&name))) return CComBSTR(_T(""));

		TCHAR number[64];
		name.Append(_itot(index, number, 10));
	}
	while (NodeExistsInParent(node, name));
	return name;
}


HRESULT STDMETHODCALLTYPE CSampleProjectItemInfo::CreateConfigurationParams(ItcProjectNode * AParentNode, ItcProjectNodeConfigurationInfo * * Value)
{
	HRESULT hr;

	// Get location path
	CComBSTR path = GetPath(AParentNode);

	// Choose the name
	CComBSTR name = GetName(AParentNode, 0);

	CComObject<CSamplePlugInConfiguration>* conf;
	hr = CComObject<CSamplePlugInConfiguration>::CreateInstance(&conf);
	if (FAILED(hr)) return hr;
  
	conf->Initialize( name,
	                  path,
	                  AParentNode,
	                  m_messenger );

	return conf->QueryInterface(Value);
}


// ItcFileProjectNodeInfo Methods

HRESULT STDMETHODCALLTYPE CSampleProjectItemInfo::get_DefaultFileName(BSTR * Value)
{
	_ASSERT( Value != NULL );
	CComBSTR def_name(cDefaultName);
	return def_name.CopyTo(Value);
}


HRESULT STDMETHODCALLTYPE CSampleProjectItemInfo::get_FileExtension(BSTR * Value)
{
	_ASSERT( Value != NULL );
	CComBSTR def_ext(cDefaultFileExtension);
	return def_ext.CopyTo(Value);
}


// IaqKeyItem Methods

void STDMETHODCALLTYPE CSampleProjectItemInfo::GetKey(GUID * Value)
{
	_ASSERT( Value != NULL );
	*Value = GetKey();
}


CONST GUID CSampleProjectItemInfo::GetKey()
{
	CONST GUID key = // {C0A98807-C21D-4bee-BC5F-A88FAD41BBD7}
		{ 0xc0a98807, 0xc21d, 0x4bee, { 0xbc, 0x5f, 0xa8, 0x8f, 0xad, 0x41, 0xbb, 0xd7 } };
	return key;
}

