#include "stdafx.h"

CString Int2Str(int n)
{
	TCHAR str[30] = {0};
	_itot_s(n, str, sizeof(str)/sizeof(TCHAR), 16);



	return str;
}
CString StringFormat1(CString str, CString replaceStr)
{
	str.Replace(_T("%1"), replaceStr);
	return str;
}
void tolog(LPCTSTR lpszLog)
{
	::OutputDebugString(lpszLog);
}