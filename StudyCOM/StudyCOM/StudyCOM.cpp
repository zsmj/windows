// StudyCOM.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <comutil.h>
#pragma comment(lib, "comsuppw.lib")

#include "../DictComp/UnKnown.h"
#include "../DictComp/SpellCheck.h"
#include "../DictComp/Dictionary.h"


extern "C" const GUID CLSID_Dictionary = 
		{ 0x54bf6567, 0x1007, 0x11d1,
		{ 0xb0, 0xaa, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00} } ;

HMODULE hModule;
BOOL CreateObject(const CLSID& clsid, const IID& iid, void** ppv)
{
	hModule = LoadLibrary(_T("DictComp.dll"));
	if (hModule == NULL)
	{
		return FALSE;
	}
	typedef BOOL (_stdcall* MyFunctionType)(const CLSID& clsid, const IID& iid, void** ppv);
	//
	MyFunctionType fnCreateObject = NULL;
	fnCreateObject = (MyFunctionType)GetProcAddress(hModule, "CreateObject");
	if (fnCreateObject == NULL)
	{
		FreeLibrary(hModule);
		return FALSE;
	}
	return fnCreateObject(clsid, iid, ppv);
}
int _tmain(int argc, _TCHAR* argv[])
{
	IMyUnknown* pMyUnknown = NULL;
	IDictionary* pDictionary = NULL;
	ISpellCheck* pSpellCheck = NULL;
	String strResult;
	BOOL bResult;
	HRESULT hResult;
	//
	bResult = CreateObject(CLSID_Dictionary, IID_IUnknown, (void** )&pMyUnknown);
	if (bResult == FALSE)
	{
		printf("Create object failed!\n");
		return -1;
	}
	hResult = pMyUnknown->QueryInterface(IID_Dictionary, (void**)&pDictionary);
	if (hResult != S_OK)
	{
		pMyUnknown->Release();
		printf("QueryInteface Idictionary failed! \n");
		return -2;
	}
	bResult = pDictionary->LoadLibrary((String)L"animal.dict");
	if (bResult)
	{
		bResult = pDictionary->LookupWord((String)L"tiger", &strResult);
		if (bResult)
		{
			char* pTiger = _com_util::ConvertBSTRToString((BSTR)strResult);
			printf("find the word \"tiger\"--%s\n", pTiger);
			delete pTiger;
		}
		//
		pDictionary->InsertWord((String)L"elephant", (String)L"Ïó");
		bResult = pDictionary->LookupWord((String)L"elephant", &strResult);
		if (bResult)
		{
			pDictionary->RestoreLibrary((String)L"animal1.dict");
		}
	}
	else
	{
		printf("Load library \"animal,dict\" failed.\n");
		return -2;
	}
	hResult = pDictionary->QueryInterface(IID_SpellCheck, (void**)&pSpellCheck);
	pDictionary->Release();
	if (hResult != S_OK)
	{
		pMyUnknown->Release();
		printf("QueryInterface ISpellCheck failed! \n");
		return -2;
	}
	bResult = pSpellCheck->CheckWord((String)L"lion", &strResult);
	if (bResult)
	{
		printf("Word \"lion\" spelling right. \n");
	}
	else
	{
		char* pLion = _com_util::ConvertBSTRToString((BSTR)strResult);
		printf("Word \"lion\" spelling is wrong. Maybe it is &s. \n", pLion);
		delete pLion;
	}
	//
	//
	//
	pSpellCheck->Release();
	if (pMyUnknown->Release() == 0)
	{
		FreeLibrary(hModule);
	}
	return 0;
}

