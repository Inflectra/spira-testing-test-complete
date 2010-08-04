// dllmain.h : Declaration of module class.

class CSpiraTestCompletePlugInModule : public CAtlDllModuleT< CSpiraTestCompletePlugInModule >
{
public :
	DECLARE_LIBID(LIBID_SpiraTestCompletePlugInLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_SPIRATESTCOMPLETEPLUGIN, "{4A0A8302-2C66-4BD7-80BD-DAC87A1FAC30}")
};

extern class CSpiraTestCompletePlugInModule _AtlModule;
