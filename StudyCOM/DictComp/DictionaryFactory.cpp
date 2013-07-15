#include "stdafx.h"
#include "IDictFactory.h"
#include "DictionaryFactory.h"
#include "DictComp.h"


extern ULONG g_LockNumber;
extern ULONG g_DictionaryNumber;

extern "C" const IID IID_IDictFactory = 
		{ 0x655f71e1, 0xf630, 0x416f,
		{ 0xa8, 0xc7, 0xbf, 0xc1, 0x3b, 0xd4, 0xab, 0xa4} } ;

CDictFactory::CDictFactory()
{
	m_ulRef = 0;
}
CDictFactory::~CDictFactory()
{
}

HRESULT CDictFactory::QueryInterface(const IID& iid, void** ppv)
{
	if (iid == IID_IUnknown)
	{
		*ppv = (IUnknown* )this;
		((IUnknown*)(*ppv))->AddRef();
	}
	else if (iid == IID_IDictFactory)
	{
		*ppv = (IDictFactory* )this;
		((IDictFactory*)(*ppv))->AddRef();
	}
	else
	{
		*ppv = NULL;
		return E_NOINTERFACE;
	}
	return S_OK;
}
ULONG CDictFactory::AddRef()
{
	m_ulRef ++;
	return (ULONG)m_ulRef;
}
ULONG CDictFactory::Release()
{
	m_ulRef --;
	if (m_ulRef == 0)
	{
		delete this;
		return 0;
	}
	return m_ulRef;
}
HRESULT CDictFactory::CreateInstance(IUnknown* pUnknownOuter, const IID& iid, void** ppv)
{
	CDictionary* pObj = NULL;
	HRESULT hr;
	*ppv = NULL;
	//
	hr = E_OUTOFMEMORY;
	if (pUnknownOuter != NULL)
		return CLASS_E_NOAGGREGATION;
	pObj = new CDictionary();
	if (pObj == NULL)
		return hr;
	hr = pObj->QueryInterface(iid, ppv);
	if (hr != S_OK)
	{
		g_DictionaryNumber --;
		delete pObj;
	}
	return hr;
}
HRESULT CDictFactory::LockServer(BOOL bLock)
{
	if (bLock)
		g_LockNumber ++;
	else
		g_LockNumber --;
	//
	return NOERROR;
}