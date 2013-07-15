#ifndef __DictionaryFactory_h__
#define __DictionaryFactory_h__


#ifndef __IDictFactory_h__
#include "IDictFactory.h"
#endif


class CDictFactory : public IDictFactory
{
protected:
	ULONG m_ulRef;
public:
	CDictFactory();
	~CDictFactory();
	//
	HRESULT _stdcall QueryInterface(const IID& iid, void** ppv);
	ULONG _stdcall AddRef();
	ULONG _stdcall Release();
	//
	HRESULT _stdcall CreateInstance(IUnknown* pUnknownOuter, const IID& iid, void** ppv);
	HRESULT _stdcall LockServer(BOOL bLock);
};


#endif //__DictionaryFactory_h__