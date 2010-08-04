// SampleEditItem.h : Declaration of the ISampleEditItem

#pragma once

extern "C" const GUID __declspec(selectany) IID_ISampleEditItem =
    {0x65DCCB1B,0xB578,0x4A09,{0xAD,0x99,0xB2,0x8D,0xFD,0xFF,0x8C,0x70}};


struct __declspec(uuid("65DCCB1B-B578-4A09-AD99-B28DFDFF8C70"))
ISampleEditItem : ItcEditItem
{
	//
	// Raw methods provided by interface
	//

	virtual void __stdcall GetText (
		/*[out]*/ BSTR * Text ) = 0;

	virtual void __stdcall SetText (
		/*[in]*/ BSTR Text ) = 0;
};
