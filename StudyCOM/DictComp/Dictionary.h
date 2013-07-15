#ifndef __Dictionary_h__
#define __Dictionary_h__


#include "unknwn.h"


typedef unsigned short *String;

// {54BF6568-1007-11D1-B0AA-444553540000}
extern "C" const IID IID_Dictionary;

class IDictionary : public IUnknown
{
public:
	virtual BOOL __stdcall Initialize() = 0;
	virtual BOOL __stdcall LoadLibrary(String) = 0;
	virtual BOOL __stdcall InsertWord(String, String) = 0;
	virtual void __stdcall DeleteWord(String) = 0;
	virtual BOOL __stdcall LookupWord(String, String *) = 0;
	virtual BOOL __stdcall RestoreLibrary(String) = 0;
	virtual void __stdcall FreeLibrary() = 0;
};

#endif __Dictionary_h__