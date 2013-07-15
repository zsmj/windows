#ifndef __IDictFactory_h__
#define __IDictFactory_h__

#include "unknwn.h"

extern "C" const IID IID_IDictFactory;

class IDictFactory : public IUnknown
{
	virtual HRESULT _stdcall CreateInstance(IUnknown* pUnknownOuter, const IID& iid, void** ppv) = 0; 
	virtual HRESULT _stdcall LockServer(BOOL bLock) = 0;
};

#endif //__IDictFactory_h__