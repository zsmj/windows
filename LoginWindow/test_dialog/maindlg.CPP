#include "StdAfx.h"
#include "AboutDlg.h"
#include "MainDlg.h"

LRESULT CMainDlg::OnBnClickedButtonDesktop(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add your control notification handler code here
	
	HWND hDeskWnd = ::GetDesktopWindow();
	HDC dc = ::GetDC(hDeskWnd);
	HBITMAP hBmp = ::CreateCompatibleBitmap(dc, 200, 200);

	CImage img;
	img.Attach(hBmp);
	img.Save(_T("desktop.bmp"));


	return 0;
}
