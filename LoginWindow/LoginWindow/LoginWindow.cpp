#include "stdafx.h"
#include "MyWindow.h"


CAppModule _Module;
int WINAPI _tWinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPTSTR lpCmdLine,
    int nCmdShow
)
{

	// ::CoInitialize(NULL);
	_Module.Init(NULL, hInstance);
	
	CMyWindow mainWnd;
	if (NULL == mainWnd.Create(NULL, CWindow::rcDefault, _T("Test")))
	{
		return 1;
	}
	mainWnd.ShowWindow(nCmdShow);
	mainWnd.UpdateWindow();

	MSG msg;
	while(GetMessage(&msg, mainWnd, 0, 0))
	{
		TranslateMessage(&msg); 
        DispatchMessage(&msg);
	}
	_Module.Term();
	// ::CoUninitialize();
	return 0;
}