//#include "stdafx.h"
//#include "MyWindow.h"
//
//
//CAppModule _Module;
//int WINAPI _tWinMain(HINSTANCE hInstance,
//    HINSTANCE hPrevInstance,
//    LPTSTR lpCmdLine,
//    int nCmdShow
//)
//{
//
//	AtlInitCommonControls(ICC_BAR_CLASSES);	// add flags to support other controls
//	// ::CoInitialize(NULL);
//	_Module.Init(NULL, hInstance);
//	
//	CMyWindow mainWnd;
//	if (NULL == mainWnd.Create(NULL, CWindow::rcDefault, _T("Test")))
//	{
//		return 1;
//	}
//	mainWnd.ShowWindow(nCmdShow);
//	mainWnd.UpdateWindow();
//
//	MSG msg;
//	while(GetMessage(&msg, mainWnd, 0, 0))
//	{
//		TranslateMessage(&msg); 
//        DispatchMessage(&msg);
//	}
//	_Module.Term();
//	// ::CoUninitialize();
//	return 0;
//}

// test_sdiwnd.cpp : main source file for test_sdiwnd.exe
//

#include "stdafx.h"
#include "MyWindow.h"

CAppModule _Module;

int Run(LPTSTR /*lpstrCmdLine*/ = NULL, int nCmdShow = SW_SHOWDEFAULT)
{
	CMessageLoop theLoop;
	_Module.AddMessageLoop(&theLoop);

	CMyWindow mainWnd;

	HWND hWnd;
	if((hWnd = mainWnd.Create(NULL, CWindow::rcDefault, _T("Test"))) == NULL)
	{
		ATLTRACE(_T("Main window creation failed!\n"));
		return 0;
	}

	mainWnd.ShowWindow(nCmdShow);

	int nRet = theLoop.Run();

	//MSG msg;
	//while(GetMessage(&msg, mainWnd, 0, 0))
	//{
	//	::TranslateMessage(&msg);
	//	::DispatchMessage(&msg);
	//}

	_Module.RemoveMessageLoop();
	
	//int nRet = 1;
	return nRet;
}

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR lpstrCmdLine, int nCmdShow)
{
	HRESULT hRes;
	// HRESULT hRes = ::CoInitialize(NULL);
// If you are running on NT 4.0 or higher you can use the following call instead to 
// make the EXE free threaded. This means that calls come in on a random RPC thread.
//	HRESULT hRes = ::CoInitializeEx(NULL, COINIT_MULTITHREADED);
	// ATLASSERT(SUCCEEDED(hRes));

	// this resolves ATL window thunking problem when Microsoft Layer for Unicode (MSLU) is used
	::DefWindowProc(NULL, 0, 0, 0L);

	// AtlInitCommonControls(ICC_BAR_CLASSES);	// add flags to support other controls

	hRes = _Module.Init(NULL, hInstance);
	ATLASSERT(SUCCEEDED(hRes));

	int nRet = Run(lpstrCmdLine, nCmdShow);

	_Module.Term();
//	::CoUninitialize();

	return nRet;
}


