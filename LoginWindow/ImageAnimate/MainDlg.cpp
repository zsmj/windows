// MainDlg.cpp : implementation of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"

#include "MainDlg.h"

LRESULT CMainDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// center the dialog on the screen
	CenterWindow();

	// set icons
	HICON hIcon = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME), 
		IMAGE_ICON, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON), LR_DEFAULTCOLOR);
	SetIcon(hIcon, TRUE);
	HICON hIconSmall = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME), 
		IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR);
	SetIcon(hIconSmall, FALSE);
	//
	m_nShowIndex = 0;
	//
	CBitmap* pbmp0 = new CBitmap();
	pbmp0->LoadBitmap(IDB_BITMAP_SHOW_0);
	m_arrayShow.push_back(pbmp0);
	//
	CBitmap* pbmp1 = new CBitmap();
	pbmp1->LoadBitmap(IDB_BITMAP_SHOW_1);
	m_arrayShow.push_back(pbmp1);
	//
	CBitmap* pbmp2 = new CBitmap();
	pbmp2->LoadBitmap(IDB_BITMAP_SHOW_2);
	m_arrayShow.push_back(pbmp2);

	//
	m_btnShow0 = GetDlgItem(IDC_RADIO_0);
	m_btnShow0.SetCheck(1);
	//
	return TRUE;
}
void CMainDlg::DoPaint(CDCHandle dc)
{
	CRect rc;
	GetClientRect(&rc);
	dc.FillSolidRect(rc, RGB(255, 255, 255));
	//
	CSize szBmp;
	m_arrayShow[m_nShowIndex]->GetSize(szBmp);
	CDC dcMem;
	dcMem.CreateCompatibleDC(dc.m_hDC);
	CBitmap bmpOld = (HBITMAP)dcMem.SelectBitmap(*(m_arrayShow[m_nShowIndex]));
	
	
	dc.BitBlt(0, 0, szBmp.cx, szBmp.cy, dcMem, 0, 0, SRCCOPY);

	dcMem.SelectBitmap(bmpOld);
}
LRESULT CMainDlg::OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	CPaintDC dc(m_hWnd);
	//
	CSize szBmp;
	m_arrayShow[m_nShowIndex]->GetSize(szBmp);
	CDC dcMem;
	dcMem.CreateCompatibleDC(dc.m_hDC);
	CBitmap bmpOld = (HBITMAP)dcMem.SelectBitmap(*(m_arrayShow[m_nShowIndex]));
	
	
	dc.BitBlt(0, 0, szBmp.cx, szBmp.cy, dcMem, 0, 0, SRCCOPY);

	dcMem.SelectBitmap(bmpOld);
	//
	return 0;
}
LRESULT CMainDlg::OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CSimpleDialog<IDD_ABOUTBOX, FALSE> dlg;
	dlg.DoModal();
	return 0;
}

LRESULT CMainDlg::OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add validation code 
	EndDialog(wID);
	return 0;
}

LRESULT CMainDlg::OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	EndDialog(wID);
	return 0;
}

LRESULT CMainDlg::OnBnClickedRadio0(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add your control notification handler code here
	m_nShowIndex = 0;

	CSize szBmp;
	m_arrayShow[0]->GetSize(szBmp);

	CRect rc;
	rc.left = 0;
	rc.top = 0;
	rc.right = szBmp.cx;
	rc.bottom = szBmp.cy;
	InvalidateRect(rc);
	//UpdateWindow();

	return 0;
}

LRESULT CMainDlg::OnBnClickedRadio1(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add your control notification handler code here
	m_nShowIndex = 1;
	
	CSize szBmp;
	m_arrayShow[0]->GetSize(szBmp);

	CRect rc;
	rc.left = 0;
	rc.top = 0;
	rc.right = szBmp.cx;
	rc.bottom = szBmp.cy;
	InvalidateRect(rc);
	//UpdateWindow();

	return 0;
}

LRESULT CMainDlg::OnBnClickedRadio2(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: Add your control notification handler code here
	m_nShowIndex = 2;

	CSize szBmp;
	m_arrayShow[0]->GetSize(szBmp);

	CRect rc;
	rc.left = 0;
	rc.top = 0;
	rc.right = szBmp.cx;
	rc.bottom = szBmp.cy;
	InvalidateRect(rc);
	//UpdateWindow();

	return 0;
}
