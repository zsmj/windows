#include "StdAfx.h"
#include "MyWindow.h"

CString StringFormat1(CString str, CString replaceStr)
{
	str.Replace(_T("%1"), replaceStr);
	return str;
}
void tolog(LPCTSTR lpszLog)
{
	::OutputDebugString(lpszLog);
}
void CMyWindow::PaintEdit(CDCHandle dc)
{
	int nImageIndex = 0;
	if (m_bEditState)
	{
		nImageIndex = 1;
	}
	else 
	{
		nImageIndex = 0;
	}
	m_editil.Draw(dc, nImageIndex, 36, 72, 0);

	m_editil.Draw(dc, nImageIndex, 36, 132, 0);

	m_imgDropDown.Draw(dc, m_rcDropDown);

	dc.FillSolidRect(m_rcEditBk, RGB(239, 247, 253));
}
BOOL CMyWindow::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_LBUTTONDOWN || pMsg->message == WM_NCLBUTTONDOWN
		|| pMsg->message == WM_LBUTTONDBLCLK || pMsg->message == WM_NCLBUTTONDBLCLK
		|| pMsg->message == WM_RBUTTONDOWN || pMsg->message == WM_NCRBUTTONDOWN
		|| pMsg->message == WM_RBUTTONDBLCLK || pMsg->message == WM_NCRBUTTONDBLCLK )
	{
		POINT pt = {GET_X_LPARAM(pMsg->lParam), GET_Y_LPARAM(pMsg->lParam)};
		if (!HitTestInDropDown(pt))
		{
			if (m_bDropDownShow)
			{
				m_listBoxUN.ShowWindow(SW_HIDE);
				m_bDropDownShow = FALSE;
			}	
		}
	}
	if (pMsg->hwnd == m_editPassword && pMsg->message == WM_LBUTTONDOWN)
	{
		tolog(_T("password edit lbuttondown."));
		//CDC dc = GetDC();

		//dc.FillSolidRect(m_rcEditBk, RGB(255, 255, 255));
	}
	return FALSE;
}
LRESULT CMyWindow::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{

	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->AddMessageFilter(this);

	LONG lStyle = GetWindowLong(GWL_STYLE);
	//lStyle &= ~WS_CLIPCHILDREN;
	lStyle |= WS_CLIPCHILDREN;
	SetWindowLong(GWL_STYLE, lStyle);

	//
	CRect rect;
	GetClientRect(&rect);
	rect.bottom = rect.top + 450;
	rect.right = rect.left + 600;
	MoveWindow(&rect);

	m_rcClient = rect;
	//
	DrawMinBox();
	//
	DrawMaxBox();
	//
	CenterWindow();
	//
	DrawAllLink();
	//
	DrawListBox();

	//
	DrawAllEdit();
	//
	

	return 0;
}
LRESULT CMyWindow::OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT pt = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)};
	ScreenToClient(&pt);
	if (PtInRect(m_rcCaption, pt))
	{
		return HTCAPTION;
	}

	return ::DefWindowProc(m_hWnd, uMsg, wParam, lParam);
}
LRESULT CMyWindow::OnCtlColorStatic(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{

	bHandled = TRUE;
	CDCHandle dc = (HDC)wParam;

	dc.SetBkMode(TRANSPARENT);

	return (LRESULT)GetStockObject(HOLLOW_BRUSH);

}
LRESULT CMyWindow::OnCtlColorBtn(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = TRUE;
	CDCHandle dc = (HDC)wParam;

	dc.SetBkMode(TRANSPARENT);

	return (LRESULT)GetStockObject(HOLLOW_BRUSH);
}
LRESULT CMyWindow::OnParentDraw(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect rc = *(CRect* )lParam;
	CDCHandle dc = (HDC)wParam;


	CRect rc2;
	rc2.left = 0;
	rc2.top = 0;
	rc2.right = rc.right - rc.left;
	rc2.bottom = rc.bottom - rc.top;

	m_bkgnd.Draw(dc, rc2, rc);

	return 1;
}
void CMyWindow::DrawFrgtPsdLink(CMyDBufferHyperLink& hl, CRect rc, LPCTSTR lpszLabel, LPCTSTR lpszURL, DWORD dwLinkExStyle)
{
	DWORD dwStyle = WS_CHILD | WS_VISIBLE | SS_NOTIFY;
	hl.Create(m_hWnd, rc, 0, dwStyle);

	hl.SetLabel(lpszLabel);
	hl.SetHyperLink(lpszURL);
	hl.SetHyperLinkExtendedStyle(dwLinkExStyle);
}
void CMyWindow::DrawRegLink(CMyDBufferHyperLink& hl, CRect rc, LPCTSTR lpszLabel, LPCTSTR lpszURL, DWORD dwLinkExStyle)
{
	DWORD dwStyle = WS_CHILD | WS_VISIBLE | SS_NOTIFY;
	hl.Create(m_hWnd, rc, 0, dwStyle);

	hl.SetLabel(lpszLabel);
	hl.SetHyperLink(lpszURL);
	hl.SetHyperLinkExtendedStyle(dwLinkExStyle);
}
void CMyWindow::DrawDBufferLink(CMyDBufferHyperLink& hl, CRect rc, LPCTSTR lpszLabel, LPCTSTR lpszURL, DWORD dwLinkExStyle)
{
	DWORD dwStyle = WS_CHILD | WS_VISIBLE | SS_NOTIFY;
	hl.Create(m_hWnd, rc, 0, dwStyle);

	hl.SetLabel(lpszLabel);
	hl.SetHyperLink(lpszURL);
	hl.SetHyperLinkExtendedStyle(dwLinkExStyle);
}
void CMyWindow::DrawAllLink()
{
	DWORD dwLinkExStyle = HLINK_UNDERLINEHOVER | HLINK_NOTOOLTIP;
	CRect rcReg;
	rcReg.left = 50;
	rcReg.top = 400;
	rcReg.right = 80;
	rcReg.bottom = 420;
	
	DrawRegLink(m_linkReg, rcReg, _T("注册"), _T("http://www.wiz.cn/register"), dwLinkExStyle);

	CRect rcFrgt;
	rcFrgt.left = 100;
	rcFrgt.top = 400;
	rcFrgt.right = 160;
	rcFrgt.bottom = 420;

	DrawFrgtPsdLink(m_linkFrgtPsd, rcFrgt, _T("忘记密码"), _T("http://as.wiz.cn/wizas/htmlpages/reset_password_zh_CN.html"), dwLinkExStyle);
	
	CRect rcProxy;
	rcProxy.left = 170;
	rcProxy.top = 400;
	rcProxy.right = 230;
	rcProxy.bottom = 420;

	DrawDBufferLink(m_linkProxySet, rcProxy, _T("代理设置"), _T("http://www.wiz.cn"), dwLinkExStyle); 
}
void CMyWindow::DrawMinBox()
{
	CImage img;
	img.Load(_T("./image/Btn_Window_Min.png"));
	int nWidth = img.GetWidth() / 3;
	int nHeight = img.GetHeight();
	CImageList il;
	il.Create(nWidth, nHeight, ILC_COLOR32 | ILC_MASK, 0, 0);
	il.Add(img);
	
	CRect rc;
	rc.left = 510;
	rc.top = 20;
	rc.right = 530;
	rc.bottom = 40;

	m_btnMinBox.Create(m_hWnd, rc, 0, 0, 0, IDC_MINIMIZE);
	m_btnMinBox.SetToolTip(_T("min"));
	m_btnMinBox.SetBitmapButtonExtendedStyle(BMPBTN_HOVER);
	m_btnMinBox.SetImageList(il);
	m_btnMinBox.SetImages(0, 2, 1);

	//m_btnMinBox.SetBackground(RGB(72, 169, 220));
}
void CMyWindow::DrawMaxBox()
{
	CImage img;
	img.Load(_T("./image/Btn_Window_Close.png"));
	int nWidth = img.GetWidth() / 3;
	int nHeight = img.GetHeight();
	CImageList il;
	il.Create(nWidth, nHeight, ILC_COLOR32 | ILC_MASK, 0, 0);
	il.Add(img);
	
	CRect rc;
	rc.left = 540;
	rc.top = 20;
	rc.right = 560;
	rc.bottom = 40;

	m_btnMaxBox.Create(m_hWnd, rc, 0, 0, 0, IDC_CLOSE);
	m_btnMaxBox.SetToolTip(_T("close"));
	m_btnMaxBox.SetBitmapButtonExtendedStyle(BMPBTN_HOVER);
	m_btnMaxBox.SetImageList(il);
	m_btnMaxBox.SetImages(0, 2, 1);
	//m_btnMaxBox.SetBackground(RGB(72, 169, 220));
}
void CMyWindow::DrawEdit(CEdit& edit, CRect rc, UINT nID)
{

	edit.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL, 0, nID);
	edit.SetFont(m_font);

	
	//m_editUserName.SetMargins(5, 8);

}
void CMyWindow::DrawAllEdit()
{
	
	DrawEdit(m_editUserName, m_rcUserName, IDC_EDIT_USERNAME);

	CRect rcPassword;
	rcPassword.left = 40;
	rcPassword.top = 140;
	rcPassword.right = 260;
	rcPassword.bottom = 160;

	DrawEdit(m_editPassword, rcPassword, IDC_EDIT_PASSWORD);
}

void CMyWindow::OnPasswordFocus(HWND hCtl)
{
	CDC dc = GetDC();

	dc.FillSolidRect(m_rcEditBk, RGB(255, 255, 255));

}
void CMyWindow::OnPasswordKillFocus(HWND hCtl)
{
	CDC dc = GetDC();
	dc.FillSolidRect(m_rcEditBk, RGB(239, 247, 253));

}
LRESULT CMyWindow::OnCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	int nID = LOWORD(wParam);
	if (nID == IDC_MINIMIZE)
	{
		ShowWindow(SW_SHOWMINIMIZED);
	}
	if (nID == IDC_CLOSE)
	{
		DestroyWindow();
	}

	WORD wCode = HIWORD(wParam);
	WORD wID = LOWORD(wParam);
	//if (wID == IDC_EDIT_USERNAME && wCode == EN_SETFOCUS)
	//{
	//	SetEditState(TRUE);
	//	Invalidate();
	//}
	if (wID == IDC_EDIT_PASSWORD)
	{
		CDC dc = GetDC();
		CDC dcControl = ::GetDC((HWND)lParam);
		CRect rcControl;
		::GetClientRect((HWND)lParam, rcControl);
		HBRUSH hbr;
		CString strText;
		switch(wCode)
		{
		case EN_SETFOCUS:
			tolog(_T("set focus."));
			
			OnPasswordFocus((HWND)lParam);
			hbr = ::CreatePatternBrush(m_imgLoginPassFocus);
			dcControl.FillRect(rcControl, hbr);
			m_bTransparent = TRUE;
			m_bFocus = TRUE;

			break;
		case EN_KILLFOCUS:
			tolog(_T("kill focus."));
			OnPasswordKillFocus((HWND)lParam);
			
			
			m_editPassword.GetWindowTextW(strText);
			if (!strText.IsEmpty())
			{
				m_bTransparent = FALSE;
			}
			else
			{
				m_bTransparent = TRUE;
			}
			m_bFocus = FALSE;
			
			break;
		case EN_CHANGE:
			tolog(_T("en change."));
			break;
		case EN_UPDATE:
			tolog(_T("en update."));
			OnPasswordFocus((HWND)lParam);
			
			m_editPassword.GetWindowTextW(strText);
			if (!strText.IsEmpty())
			{
				m_bTransparent = FALSE;
			}
			else
			{
				m_bTransparent = TRUE;
			}
			
			break;
		}
	}
	CString strUserName;
	if (wID == IDC_LIST_USERNAME)
	{
		switch(wCode)
		{
		case LBN_SELCHANGE:
			tolog(_T("SEL CHANGE"));
			m_listBoxUN.ShowWindow(SW_HIDE);
			m_listBoxUN.GetText(0, strUserName);
			m_editUserName.SetWindowText(strUserName);
			m_bDropDownShow = FALSE;
			break;
		case LBN_SETFOCUS:
			tolog(_T("list set focus"));
			break;
		}
	}
	bHandled = FALSE;
	return 0;
}
LRESULT CMyWindow::OnCtlColorEdit(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{	
	CDCHandle dc = (HDC)wParam;
	HBRUSH hbr;
	
	if (m_bTransparent)
	{
		dc.SetBkMode(TRANSPARENT);
	}
	if ((HWND)lParam == GetDlgItem(IDC_EDIT_PASSWORD))
	{
		tolog(_T("on edit ctl color"));
		CString strText;
		CWindow wnd = (HWND)lParam;
		wnd.GetWindowText(strText);

		if (m_bFocus)
		{
			if (!strText.IsEmpty())
			{
				hbr = ::CreateSolidBrush(RGB(255, 255, 255));
			}
			else 
			{
				hbr = ::CreatePatternBrush(m_imgLoginPassFocus);
			}
		}
		else 
		{
			if (m_bEditInit)
			{
				hbr = ::CreatePatternBrush(m_imgLoginPass);
				m_bEditInit = FALSE;
			}
			else 
			{
				if (strText.IsEmpty())
				{
					hbr = ::CreatePatternBrush(m_imgLoginPass);
				}
				else 
				{
					hbr = ::CreateSolidBrush(RGB(239, 247, 253));
				}
			}
		}
	}
	if ((HWND)lParam == GetDlgItem(IDC_EDIT_USERNAME))
	{
		//hbr = ::CreatePatternBrush(m_editbkimg);
		hbr = ::CreateSolidBrush(RGB(255, 255, 255));
	}
	return (LRESULT)hbr;
}
void CMyWindow::DrawListBox()
{
	DWORD dwStyle = WS_CHILD | WS_CLIPSIBLINGS | LBS_NOTIFY;
	m_listBoxUN.Create(m_hWnd, m_rcDropDownList, 0, dwStyle, 0, IDC_LIST_USERNAME);
	
	m_listBoxUN.SetFont(m_font);
	m_listBoxUN.AddString(_T("example@wiz.cn"));
	m_listBoxUN.AddString(_T("example@qq.cn"));
	m_listBoxUN.AddString(_T("example@gmail.cn"));
	
}
bool CMyWindow::HitTestInDropDown(const CPoint& pt)
{
	if (m_rcDropDown.PtInRect(pt))
	{
		return true;
	}
	return false;
}
LRESULT CMyWindow::OnLButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = FALSE;
	POINT pt = {GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)};
	
	if (HitTestInDropDown(pt))
	{
		if (m_bDropDownShow)
		{


			m_listBoxUN.ShowWindow(SW_HIDE);
			
			m_bDropDownShow = FALSE;
		}
		else 
		{
			m_listBoxUN.BringWindowToTop();
			
			m_bDropDownShow = TRUE;
		}
	}
	return 0;
}
LRESULT CMyWindow::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	tolog(_T("on lbutton down."));
	bHandled = FALSE;

	POINT pt = {GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)};
	
	if (HitTestInDropDown(pt))
	{
		if (m_bDropDownShow)
		{
			m_listBoxUN.ShowWindow(SW_HIDE);
			m_bDropDownShow = FALSE;
		}
		else 
		{
			m_listBoxUN.ShowWindow(SW_NORMAL);
			m_bDropDownShow = TRUE;
		}	
	}
	
	
	return 0;
}
LRESULT CMyWindow::OnListBeginDrag(int nID, LPNMHDR lpnm, BOOL& bHandled)
{
	tolog(_T("begin drag"));
	return 1;
}