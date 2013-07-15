#include "stdafx.h"

#include <windows.h>
#include "Dictionary.h"

CDictionary::CDictionary()
{
	m_nRef = 0;
}
ULONG CDictionary::AddRef()
{
	m_nRef ++;
	return (ULONG)m_nRef;
}
ULONG CDictionary::Release()
{
	m_nRef --;
	if (m_nRef == 0)
	{
		delete this;
		return 0;
	}
	return (ULONG)m_nRef;
}


