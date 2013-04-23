#pragma once

typedef CWinTraits<WS_POPUP> CMyWinTraits;
class CMyWindow
	: public CWindowImpl<CMyWindow, CWindow, CMyWinTraits>
{
public:

	CMyWindow()
	{
		m_rcEditUser.left = 40;
		m_rcEditUser.top = 20;
		m_rcEditUser.right = 276;
		m_rcEditUser.bottom = 45;


		m_img.Load(_T("test.jpg"));
		CImage img;
		
		int nWidth;
		int nHeight;
		if (SUCCEEDED(img.Load(_T("box_close.png"))))
		{
			nWidth = img.GetWidth() / 4;
			nHeight = img.GetHeight();
			m_ilClose.Create(nWidth, nHeight, ILC_COLOR32 | ILC_MASK, 0, 0);
			m_ilClose.Add(img, RGB(0, 0, 0));
		}
		CImage img2;
		if (SUCCEEDED(img2.Load(_T("./image/Input_Login_Normal_Focus.png"))))
		{
			nWidth = img2.GetWidth() / 2;
			nHeight = img2.GetHeight();
			m_ilEdit.Create(nWidth, nHeight, ILC_COLOR32 | ILC_MASK, 0, 0);
			m_ilEdit.Add(img2, RGB(0, 0, 0));
		}
		m_imgBkgnd.Load(_T("./image/Bg_Login.png"));
		// 
		CreateFont(m_font);
		
	}

	DECLARE_WND_CLASS(_T("My Login In Window"));

	BEGIN_MSG_MAP(CMyWindow)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
	//	MESSAGE_HANDLER(WM_LBUTTONDBLCLK, OnDBclick)
	//	MESSAGE_HANDLER(WM_NCLBUTTONDBLCLK, OnNCDBclick)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroyWindow)
		MESSAGE_HANDLER(WM_NCHITTEST, OnNCHitTest)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
		MESSAGE_HANDLER(WM_CTLCOLOREDIT, OnCtlColorEdit)
		// REFLECT_NOTIFICATIONS()
	END_MSG_MAP()

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		CRect rect;
		GetClientRect(&rect);
		rect.bottom = rect.top + 500;
		rect.right = rect.left + 800;
		MoveWindow(&rect);
		

		const DWORD dwEditStyle = WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_BORDER;

		m_editUser.Create(m_hWnd, m_rcEditUser, NULL, dwEditStyle);
		m_editUser.SetFont(m_font);
		int nMargins = m_editUser.GetMargins();
		WORD wRightMargins = LOWORD(nMargins);
		m_editUser.SetMargins(LOWORD(nMargins), 0);

		nMargins = m_editUser.GetMargins();
		
		CRect rcBtn;
		rcBtn.left = 700;
		rcBtn.top = 0;
		rcBtn.right = 750;
		rcBtn.bottom = 50;
		m_btnMinBox.Create(m_hWnd, rcBtn, NULL, WS_CHILD | WS_VISIBLE, BMPBTN_AUTOSIZE);
		
		CImage imgBtn;
		CImageList imlBtn;
		if (SUCCEEDED(imgBtn.Load(_T("./image/Btn_Window_Min.png"))))
		{
			imlBtn.Create(imgBtn.GetWidth() / 3, imgBtn.GetHeight(), ILC_COLOR32 | ILC_MASK, 0, 0);
			imlBtn.Add(imgBtn, RGB(0, 0, 0));
			m_btnMinBox.SetImageList(imlBtn);
			m_btnMinBox.SetImages(0, 1, 2);
		}
		m_btnMinBox.SetToolTipText(_T("Min Btn Box"));
		// m_btnMinBox.SetCapture();


		CenterWindow();

		return 0;
	}
	LRESULT OnDBclick(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		DestroyWindow();
		return 0;
	}
	LRESULT OnNCDBclick(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		DestroyWindow();
		return 0;
	}
	LRESULT OnDestroyWindow(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		PostQuitMessage(0);
		return 0;
	}
	LRESULT OnNCHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		WORD wPointX = LOWORD(lParam);
		WORD wPointY = HIWORD(lParam);
		CPoint pt(wPointX, wPointY);
		
		CRect rc;
		GetClientRect(&rc);
		ClientToScreen(&rc);
		
		DWORD dwRet = DefWindowProc(uMsg, wParam, lParam);
		
		CRect rcTestButton;
		rcTestButton.left = 10;
		rcTestButton.top = 2;
		rcTestButton.right = 30;
		rcTestButton.bottom = 22;
		ClientToScreen(&rcTestButton);
		if (PtInRect(&rcTestButton, pt))
		{
			return HTCAPTION;
		}
		return dwRet;
		
	}
	LRESULT OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
	{
		// TODO: Add your message handler code here and/or call default
		HDC dc = GetDC();

	//	m_img.Draw(dc, 10, 2, 20, 20);
		m_ilClose.Draw(dc, 1, 100, 100, 0);

		CRect rc;
		GetClientRect(&rc);

		// m_imgBkgnd.Draw(dc, rc);


		bHandled = FALSE;
		
		return 0;
	}
	void CreateFont(CFont& font)
	{
		NONCLIENTMETRICS ncm;
		ZeroMemory(&ncm, sizeof(NONCLIENTMETRICS));
#if (WINVER >= 0x0600)
		ncm.cbSize = sizeof(NONCLIENTMETRICS) - sizeof(ncm.iPaddedBorderWidth);
#else
		ncm.cbSize = sizeof(NONCLIENTMETRICS);
#endif
		//
		::SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(NONCLIENTMETRICS), &ncm, 0);

		ncm.lfMenuFont.lfWeight = FW_NORMAL;

		m_font.CreateFontIndirectW(&ncm.lfMenuFont);
	}
private:
	CFont m_font;
	CImage m_img;
	CImageList m_ilClose;
	CImageList m_ilEdit;
	CEdit m_editUser;
	CRect m_rcEditUser;
	CImage m_imgBkgnd;
	CBitmapButton m_btnMinBox;
	CBitmapButton m_btnMaxBox;
	
public:
	LRESULT OnCtlColorEdit(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
	{
		HDC dc = (HDC)wParam;
	//	m_ilEdit.Draw(dc, 0, -5, -8, 0);

	//	::SetBkColor(dc, RGB(255, 0, 0));
		

		return 0;
	}
};