#include "StdAfx.h"
#include "MyWindow.h"

int arrayShadowColor[11] = {214, 221, 229, 234, 239, 244, 248, 250, 252, 253, 254};

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
	//m_editil.Draw(dc, nImageIndex, 36, 72, 0);

	m_editil.Draw(dc, nImageIndex, 36, 192, 0);

	//m_imgDropDown.Draw(dc, m_rcDropDown);

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
	
	if (pMsg->message == WM_KEYUP && (DWORD)pMsg->wParam == VK_TAB)
	{
		SetChildFocus();
		tolog(_T("vk_tab up."));
	}
	static bool bFocus = 0;
	if (pMsg->hwnd == m_comboUserName && pMsg->message == WM_PAINT)
	{
		tolog(_T("combo username wm_paint"));
		if (bFocus != 1)
		{
			SetChildFocus();
		}
		bFocus = 1;
		
	}
	if ((pMsg->hwnd == m_comboUserName || pMsg->hwnd == m_editUserName) && (pMsg->message == WM_LBUTTONDOWN))
	{
		SetChildFocus();
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
	lStyle &= ~WS_BORDER;
	SetWindowLong(GWL_STYLE, lStyle);
	
	//
	CRect rect;
	GetClientRect(&rect);
	rect.bottom = rect.top + 450;
	rect.right = rect.left + 600;
	
	SetWindowPos(0, 0, 0, 600, 450, SWP_NOMOVE);
	//
	

	m_rcClient = rect;
	//
	DrawMinBox();
	//
	DrawMaxBox();

	//
	DrawAllLink();
	//
	DrawListBox();

	//
	DrawComboBox();
	//
	DrawAllEdit();

	
	ResetWindowRgn();
	
	m_shadow.Create(m_hWnd, 40);

	//DrawUI();

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
	rcReg.left = 36;
	rcReg.top = 400;
	rcReg.right = 80;
	rcReg.bottom = 420;
	
	DrawRegLink(m_linkReg, rcReg, _T("注册"), _T("http://www.wiz.cn/register"), dwLinkExStyle);

	CRect rcFrgt;
	rcFrgt.left = 86;
	rcFrgt.top = 400;
	rcFrgt.right = 160;
	rcFrgt.bottom = 420;

	DrawFrgtPsdLink(m_linkFrgtPsd, rcFrgt, _T("忘记密码"), _T("http://as.wiz.cn/wizas/htmlpages/reset_password_zh_CN.html"), dwLinkExStyle);
	
	CRect rcProxy;
	rcProxy.left = 156;
	rcProxy.top = 400;
	rcProxy.right = 230;
	rcProxy.bottom = 420;

	DrawDBufferLink(m_linkProxySet, rcProxy, _T("代理设置"), _T("http://www.wiz.cn"), dwLinkExStyle); 
}
void CMyWindow::DrawMinBox()
{
	CImage img;
	CString strSkinPath = GetAppPath() + _T("/image/");
	img.Load(strSkinPath + _T("Btn_Window_Min.png"));
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
	CString strSkinPath = GetAppPath() + _T("/image/");
	img.Load(strSkinPath + _T("Btn_Window_Close.png"));
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
void CMyWindow::DrawEdit(CEdit& edit, CRect rc, UINT nID, DWORD dwStyle = 0)
{

	DWORD dwComStyle = WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL;
	dwComStyle |= dwStyle;
	edit.Create(m_hWnd, rc, NULL, dwComStyle, 0, nID);
	edit.SetFont(m_font);

	
	//m_editUserName.SetMargins(5, 8);

}
void CMyWindow::DrawAllEdit()
{
	
	//DrawEdit(m_editUserName, m_rcUserName, IDC_EDIT_USERNAME);

	DrawEdit(m_editPassword, m_rcPassword, IDC_EDIT_PASSWORD, ES_PASSWORD);
	m_editPassword.SetPasswordChar(_T('*'));

	m_queChildTab.push(&m_editPassword);
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
	int nSelIndex = -1;
	if (wID == IDC_LIST_USERNAME)
	{
		switch(wCode)
		{
		case LBN_SELCHANGE:
			tolog(_T("SEL CHANGE"));
			m_listBoxUN.ShowWindow(SW_HIDE);
			nSelIndex = m_listBoxUN.GetCurSel();
			if (nSelIndex != -1)
			{
				m_listBoxUN.GetText(nSelIndex, strUserName);
				m_editUserName.SetWindowText(strUserName);
			}

			m_bDropDownShow = FALSE;
			break;
		case LBN_SETFOCUS:
			tolog(_T("list set focus"));
			break;
		}
	}
	if (wID == IDC_COMBO_USERNAME)
	{
		if (wCode == CBN_DROPDOWN)
		{
			tolog(_T("cbn_dropdown in parent."));
			//::SendMessage((HWND)lParam, OCM__BASE + uMsg, wParam, lParam);
		}
		if (wCode == CBN_SELENDOK)
		{
			tolog(_T("parent CBN_SELENDOK"));
		}
		
	}
	bHandled = FALSE;
	return 0;
}
LRESULT CMyWindow::OnCtlColorEdit(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{	
	CDCHandle dc = (HDC)wParam;
	HBRUSH hbr = NULL;
	
	if (m_bTransparent)
	{
		dc.SetBkMode(TRANSPARENT);
	}
	if ((HWND)lParam == GetDlgItem(IDC_EDIT_PASSWORD))
	{
		tolog(_T("on edit IDC_EDIT_PASSWORD ctl color."));
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
	if ((HWND)lParam == GetDlgItem(IDC_COMBO_USERNAME))
	{
		tolog(_T("on edit IDC_COMBO_USERNAME color."));
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
bool CMyWindow::HitTestAutoLogin(const CPoint& pt)
{
	if (m_rcAutoLogin.PtInRect(pt) || m_rcLoginCheck.PtInRect(pt))
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
	if (HitTestAutoLogin(pt))
	{
		tolog(_T("login"));
		m_bAuto = m_bAuto ? FALSE : TRUE;

		InvalidateRect(m_rcLoginCheck);
	}
	if (HitTestInQQLogin(pt))
	{
		m_QQState = PRESS;
		InvalidateRect(m_rcQQLogin);
	}
	if (HitTestInSinaWbLogin(pt))
	{
		m_SinaWbState = PRESS;
		InvalidateRect(m_rcSinaWbLogin);
	}
	if (HitTestInQQWbLogin(pt))
	{
		m_QQWbState = PRESS;
		InvalidateRect(m_rcQQWbLogin);
	}
	if (HitTestInLogin(pt))
	{
		m_LoginState = PRESS;
		
		InvalidateRect(m_rcLogin);
	}
	return 1;
}
LRESULT CMyWindow::OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	//tolog(_T("on mouse up"));
	bHandled = FALSE;

	//ReleaseCapture();
	return 0;
}
LRESULT CMyWindow::OnListBeginDrag(int nID, LPNMHDR lpnm, BOOL& bHandled)
{
	tolog(_T("begin drag"));
	return 1;
}
void CMyWindow::DrawComboBoxDrowDownImg(CDCHandle dc)
{
	m_imgDropDown.Draw(dc, m_rcComboDropDown);
}
LRESULT CMyWindow::OnDrawItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	tolog(_T("on parent draw item"));

	bHandled = FALSE;

	return 0;
}
void CMyWindow::DrawComboBox()
{
	DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBS_DROPDOWN | CBS_AUTOHSCROLL;

	CRect rc = m_rcComboUserName;


	m_comboUserName.Create(m_hWnd, rc, 0, dwStyle, 0, IDC_COMBO_USERNAME);

	m_comboUserName.SetFont(m_font);
	m_comboUserName.AddString(_T("example@wiz.cn"));
	m_comboUserName.AddString(_T("example@qq.cn"));
	m_comboUserName.AddString(_T("example@gmail.com"));
	//
	m_queChildTab.push(static_cast<CWindow*>(&m_comboUserName));
	

}
bool CMyWindow::HitTestInQQLogin(const CPoint& pt)
{
	if (m_rcQQLogin.PtInRect(pt))
	{
		return true;
	}
	return false;
}
bool CMyWindow::HitTestInSinaWbLogin(const CPoint& pt)
{
	if (m_rcSinaWbLogin.PtInRect(pt))
	{
		return true;
	}
	return false;
}
bool CMyWindow::HitTestInQQWbLogin(const CPoint& pt)
{
	if (m_rcQQWbLogin.PtInRect(pt))
	{
		return true;
	}
	return false;
}
bool CMyWindow::HitTestInLogin(const CPoint& pt)
{
	if (m_rcLogin.PtInRect(pt))
	{
		return true;
	}
	return false;
}
LRESULT CMyWindow::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	//tolog(_T("on mouse move"));
	bHandled = FALSE;

	POINT pt = {GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)};
	if (HitTestInQQLogin(pt))
	{
		m_QQState = HOVER;
		InvalidateRect(m_rcQQLogin);

	}
	if (HitTestInSinaWbLogin(pt))
	{
		m_SinaWbState = HOVER;
		InvalidateRect(m_rcSinaWbLogin);

	}
	if (HitTestInQQWbLogin(pt))
	{
		m_QQWbState = HOVER;
		InvalidateRect(m_rcQQWbLogin);
	}
	if (HitTestInLogin(pt))
	{
		m_LoginState = HOVER;
		InvalidateRect(m_rcLogin);

	}
	return 1;
}
LRESULT CMyWindow::OnMouseLeave(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = FALSE;
	
	POINT pt = {GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)};
	if (!HitTestInQQLogin(pt))
	{
		if (m_QQState != NORMAL)
		{
			m_QQState = NORMAL;
			InvalidateRect(m_rcQQLogin);
		}
	}
	if (!HitTestInSinaWbLogin(pt))
	{
		if (m_SinaWbState != NORMAL)
		{
			m_SinaWbState = NORMAL;
			InvalidateRect(m_rcSinaWbLogin);
		}
	}
	if (!HitTestInQQWbLogin(pt))
	{
		if (m_QQWbState != NORMAL)
		{
			m_QQWbState = NORMAL;
			InvalidateRect(m_rcQQWbLogin);
		}
	}
	if (!HitTestInLogin(pt))
	{
		
		if (m_LoginState != NORMAL)
		{
			tolog(_T("HitTestInLogin mouse leave."));
			m_LoginState = NORMAL;
			InvalidateRect(m_rcLogin);
		}
	}
	return 0;
}
void CMyWindow::InitThirdPartyAccount(CImageList& il, ButtonState& btnState, CRect& rcBtn, int nBtnX, int nBtnY, LPCTSTR lpszImageFileName, BOOL bHorizontal)
{

	btnState = NORMAL;
	CImage imgLogin;
	imgLogin.Load(lpszImageFileName);

	int nWidth = imgLogin.GetWidth();
	int nHeight = imgLogin.GetHeight();


	//
	
	if (bHorizontal)
	{
		il.Create(nWidth / 3, nHeight, ILC_COLOR32, 0, 3);
		il.Add(imgLogin);
		rcBtn.left = nBtnX;
		rcBtn.top = nBtnY;
		rcBtn.right = rcBtn.left + nWidth / 3;
		rcBtn.bottom = rcBtn.top + nHeight;
		return;
	}
	il.Create(nWidth, nHeight / 3, ILC_COLOR32, 0, 3);
	rcBtn.left = nBtnX;
	rcBtn.top = nBtnY;
	rcBtn.right = rcBtn.left + nWidth;
	rcBtn.bottom = rcBtn.top + nHeight/3;
	//
	CImage img;
	img.Create(nWidth, nHeight / 3, imgLogin.GetBPP());
	//
	imgLogin.BitBlt(img.GetDC(), 0, 0, nWidth, nHeight / 3, 0, 0, SRCCOPY );		
	img.ReleaseDC();
	int nIndex = il.Add(img);
	
	//
	imgLogin.BitBlt(img.GetDC(), 0, 0, nWidth, nHeight / 3, 0 , nHeight / 3,SRCCOPY);
	img.ReleaseDC();
	il.Add(img);

	imgLogin.BitBlt(img.GetDC(), 0, 0, nWidth, nHeight / 3, 0, (nHeight / 3)*2, SRCCOPY);
	img.ReleaseDC();
	il.Add(img);

	int nCount = il.GetImageCount();

}
void CMyWindow::PaintThirdPartyBtn(const CDCHandle& dc, CImageList& il, const CRect& rc, ButtonState& btnState)
{
	if (btnState == NORMAL)
	{
		//tolog(_T("normal"));
		il.Draw(dc, 0, rc.left, rc.top, ILD_NORMAL);
	}
	if (btnState == HOVER)
	{
		//tolog(_T("hover"));
		il.Draw(dc, 1, rc.left, rc.top, ILD_NORMAL);
	}
	if (btnState == PRESS)
	{
		//tolog(_T("press"));
		il.Draw(dc, 2, rc.left, rc.top, ILD_NORMAL);
	}
}
void CMyWindow::DrawVertialLine(CDCHandle& dc)
{
	int nState = dc.SaveDC();
	dc.SelectPen(m_pen);
	dc.SetBkMode(TRANSPARENT);
	dc.MoveTo(310, 60);
	//dc.SetDCPenColor(RGB(255, 0, 0));
	dc.LineTo(310, 360);


	dc.RestoreDC(nState);
}
void CMyWindow::DrawUI()
{

	CDC dc = GetDC();
	CRect rcClient;
	GetClientRect(rcClient);
	CMemoryDC dcMem(dc.m_hDC, rcClient);
	//dcMem.FillSolidRect(rcClient, RGB(255, 0, 0));
	m_bkgnd.Draw(dcMem, rcClient);

	CPoint ptWnd;
	ClientToScreen(rcClient);
	ptWnd.x = rcClient.left;
	ptWnd.y = rcClient.top;
	
	CPoint pt(0, 0);
	CSize psize(rcClient.right - rcClient.left, rcClient.bottom - rcClient.top);
	BLENDFUNCTION blendFunc32bpp;
	blendFunc32bpp.AlphaFormat = AC_SRC_ALPHA;
	blendFunc32bpp.BlendFlags = 0;
	blendFunc32bpp.BlendOp = AC_SRC_OVER;
	blendFunc32bpp.SourceConstantAlpha = 255;

	int nRet = ::UpdateLayeredWindow(m_hWnd, dc, &ptWnd, &psize, dcMem, &pt, 0, &blendFunc32bpp, ULW_ALPHA);
}
void CMyWindow::ResetWindowRgn()
{
	CRect rc;
	GetClientRect(rc);
	HRGN hrgn = CreateRoundRectRgn(rc.left, rc.top, rc.right, rc.bottom, 11, 11);
	
	SetWindowRgn(hrgn);
}
LRESULT CMyWindow::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	
	bHandled = FALSE;
	
	int cx = LOWORD(lParam);
	int cy = HIWORD(lParam);
	//tolog(StringFormat2(_T("on size. cx: %1, cy: %2."), Int2Str(cx), Int2Str(cy)));
	m_shadow.OnShadowCastingWndNewSize(cx, cy);

	return 1;
}
LRESULT CMyWindow::OnSizing(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	//tolog(_T("on sizing."));
	bHandled = FALSE;
	
	CRect rc = *(RECT* )lParam;
	m_shadow.OnShadowCastingWndNewSize(rc);

	return 1;
}
LRESULT CMyWindow::OnMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = FALSE;
	
	int x = LOWORD(lParam);
	int y = HIWORD(lParam);
	//tolog(StringFormat2(_T("onmove.x: %1, y: %2"), Int2Str(x), Int2Str(y)));
	m_shadow.OnShadowCastingWndNewPos(x, y);

	return 1;
}
LRESULT CMyWindow::OnMoving(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	//tolog(_T("on moving"));
	bHandled = FALSE;
	
	CRect rc = *(RECT* )lParam;
	m_shadow.OnShadowCastingWndNewPos(rc.left, rc.top);

	return 1;
}
LRESULT CMyWindow::OnShowWindow(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{

	//tolog(StringFormat1(_T("show window.bshow: %1"), Int2Str((BOOL)wParam)));

	m_shadow.ShowShadow();
	return 1;
}
LRESULT CMyWindow::OnKeyUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = FALSE;
	


	return 1;
}
void CMyWindow::SetChildFocus()
{
	CWindow* pTabFocus = m_queChildTab.front();
	pTabFocus->SetFocus();
	//
	m_queChildTab.pop();
	m_queChildTab.push(pTabFocus);

}
LRESULT CMyWindow::OnSwitchFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	SetChildFocus();
	return 0;
}