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
CString StringFormat2(CString str, CString replaceStr1, CString replaceStr2)
{
	str.Replace(_T("%1"), replaceStr1);
	str.Replace(_T("%2"), replaceStr2);
	return str;
}
void tolog(LPCTSTR lpszLog)
{
	::OutputDebugString(lpszLog);
}
CString GetAppPath()
{
	TCHAR szFileName[MAX_PATH+1] = {0};
	::GetModuleFileName(NULL, szFileName, MAX_PATH);
	
	TCHAR szDriver[MAX_PATH+1] = {0};
	TCHAR szDir[MAX_PATH+1] = {0};

	_tsplitpath_s(szFileName, szDriver, MAX_PATH, szDir, MAX_PATH, NULL, 0, NULL, 0);

	return CString(szDriver) + szDir;
}