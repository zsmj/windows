#pragma once
#include "MyBitmapButton.h"
#include "MyHyperLink.h"

typedef CWinTraits<WS_POPUPWINDOW> CMyWinTraits;

CString StringFormat1(CString str, CString replaceStr);
void tolog(LPCTSTR lpszLog);

class CMyWindow
	: public CWindowImpl<CMyWindow, CWindow, CMyWinTraits>
	, public CDoubleBufferImpl<CMyWindow>
	//, public CUpdateUI<CMyWindow>
{
public:
	
	CMyWindow()
	{
		m_bkgnd.Load(_T("./image/Bg_Login.png"));
		CImage img;
		img.Load(_T("./image/Input_Login_Normal_Focus.png"));
		m_editil.Create(img.GetWidth()/ 2, img.GetHeight(), ILC_COLOR32, 0, 0);
		m_editil.Add(img);

		m_editbkimg.Load(_T("./image/Text_Login_User_Normal.png"));

		m_clrBk = RGB(72, 169, 220);
		CreateFont(m_font);
		
		m_rcCaption.left = 0;
		m_rcCaption.top = 0;
		m_rcCaption.right = 800;
		m_rcCaption.bottom = 50;

	}

	DECLARE_WND_CLASS(_T("My Login In Window"));

	//BEGIN_UPDATE_UI_MAP(CMainFrame)
	//END_UPDATE_UI_MAP()

	BEGIN_MSG_MAP(CMyWindow)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroyWindow)
		// MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
		MESSAGE_HANDLER(WM_COMMAND, OnCommand)
		//MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
		MESSAGE_HANDLER(WM_NCHITTEST, OnNcHitTest);
		MESSAGE_HANDLER(WM_CTLCOLOREDIT, OnCtlColorEdit)
		MESSAGE_HANDLER(WM_CTLCOLORSTATIC, OnCtlColorStatic)
		MESSAGE_HANDLER(WM_CTLCOLORBTN, OnCtlColorBtn)
		//MESSAGE_HANDLER(WM_PAINT, OnPaint)
		// REFLECT_NOTIFICATIONS()
		// CHAIN_MSG_MAP(CUpdateUI<CMyWindow>)
		CHAIN_MSG_MAP(CDoubleBufferImpl<CMyWindow>)
	END_MSG_MAP()
	LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		if(wParam != NULL)
		{
			RECT rect = { 0 };
			GetClientRect(&rect);
			
			DoPaint((HDC)wParam);
		}
		else
		{
			CPaintDC dc(m_hWnd);
			DoPaint(dc.m_hDC);
		}		
		return 0;
	}
	LRESULT DoPaint(CDCHandle dc)
	{
		tolog(_T("WM_PAINT in parent"));
		ATLASSERT(m_bkgnd.IsNull() == NULL);

		if (!m_bkgnd.IsNull())
		{
			m_bkgnd.Draw(dc, m_rcClient);
		}
		PaintEdit(dc.m_hDC);

		return 0;
	}
	LRESULT OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		tolog(_T("in parent erase."));
		bHandled = TRUE;
		return 1;
	}
	LRESULT OnCtlColorEdit(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		
		CDCHandle dc = (HDC)wParam;
	//	m_editil.Draw(dc, 0, -5, -8, 0);
		HBRUSH hbr = ::CreateSolidBrush(RGB(253, 254, 255));

	//	m_editbkimg.Draw(dc, 40, 20, 230, 15);
		
		//return (LRESULT)::CreatePatternBrush(m_editbkimg);
		
		//dc.SetBkColor(RGB(253, 254, 255));

		return 0;
	}
	LRESULT OnCtlColorStatic(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnCtlColorBtn(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
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
		if (wID == IDC_EDIT_USERNAME && wCode == EN_SETFOCUS)
		{
			SetEditState(TRUE);
			Invalidate();
		}

		bHandled = FALSE;
		return 0;
	}
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LONG lStyle = GetWindowLong(GWL_STYLE);
		lStyle &= ~WS_CLIPCHILDREN;
		SetWindowLong(GWL_STYLE, lStyle);

		//
		CRect rect;
		GetClientRect(&rect);
		rect.bottom = rect.top + 500;
		rect.right = rect.left + 800;
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

		CRect rcEdit;
		rcEdit.left = 40;
		rcEdit.top = 80;
		rcEdit.right = 275;
		rcEdit.bottom = 105;
		
		DrawEdit(rcEdit);

		return 0;
	}
	LRESULT OnDestroyWindow(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		PostQuitMessage(0);
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
		
		ncm.lfMenuFont.lfHeight -= 3;
		ncm.lfMenuFont.lfWeight = FW_NORMAL;

		m_font.CreateFontIndirectW(&ncm.lfMenuFont);
	}
	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		tolog(_T("in OnMouseMove"));
		

		return 0;
	}
protected:
	void DrawMinBox()
	{
		CImage img;
		img.Load(_T("./image/Btn_Window_Min.png"));
		int nWidth = img.GetWidth() / 3;
		int nHeight = img.GetHeight();
		CImageList il;
		il.Create(nWidth, nHeight, ILC_COLOR32 | ILC_MASK, 0, 0);
		il.Add(img);
		
		CRect rc;
		rc.left = 710;
		rc.top = 20;
		rc.right = 730;
		rc.bottom = 40;

		m_btnMinBox.Create(m_hWnd, rc, 0, 0, 0, IDC_MINIMIZE);
		m_btnMinBox.SetToolTip(_T("min"));
		m_btnMinBox.SetBitmapButtonExtendedStyle(BMPBTN_HOVER);
		m_btnMinBox.SetImageList(il);
		m_btnMinBox.SetImages(0, 2, 1);

		//m_btnMinBox.SetBackground(RGB(72, 169, 220));
	}
	void DrawMaxBox()
	{
		CImage img;
		img.Load(_T("./image/Btn_Window_Close.png"));
		int nWidth = img.GetWidth() / 3;
		int nHeight = img.GetHeight();
		CImageList il;
		il.Create(nWidth, nHeight, ILC_COLOR32 | ILC_MASK, 0, 0);
		il.Add(img);
		
		CRect rc;
		rc.left = 740;
		rc.top = 20;
		rc.right = 760;
		rc.bottom = 40;

		m_btnMaxBox.Create(m_hWnd, rc, 0, 0, 0, IDC_CLOSE);
		m_btnMaxBox.SetToolTip(_T("close"));
		m_btnMaxBox.SetBitmapButtonExtendedStyle(BMPBTN_HOVER);
		m_btnMaxBox.SetImageList(il);
		m_btnMaxBox.SetImages(0, 2, 1);
		//m_btnMaxBox.SetBackground(RGB(72, 169, 220));
	}
	void InitButton()
	{
		CImage img;
		img.Load(_T("./image/Btn_Window_Close.png"));
		CImageList il;
		il.Create(img.GetWidth() / 3, img.GetHeight(), ILC_COLOR32, 0, 0);
		il.Add(img);
		
		RECT rc;
		rc.left = 10;
		rc.top = 10;
		rc.right = 40;
		rc.bottom = 40;

		m_btn.Create(m_hWnd, rc);
		m_btn.SetBitmapButtonExtendedStyle(BMPBTN_HOVER);
		m_btn.SetToolTipText(_T("my tooltips string"));
		m_btn.SetImageList(il);
		m_btn.SetImages(0, 2, 1);

	}
	void DrawEdit(CRect rc)
	{

		m_editUserName.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL, 0, IDC_EDIT_USERNAME);
		m_editUserName.SetFont(m_font);

		
		m_editUserName.SetMargins(5, 8);

	}

	void PaintEdit(CDCHandle dc)
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
	}
	void SetEditState(BOOL bState)
	{
		m_bEditState = bState;
	}
public:
	void DrawAllLink();
	void DrawRegLink(CMyHyperLink& hl, CRect rc, LPCTSTR lpszLabel, LPCTSTR lpszURL, DWORD dwLinkExStyle);
	void DrawFrgtPsdLink(CMyHyperLink& hl, CRect rc, LPCTSTR lpszLabel, LPCTSTR lpszURL, DWORD dwLinkExStyle);
private:
	COLORREF m_clrBk;
	CFont m_font;
	CMyBitmapButton m_btnMinBox;
	CMyBitmapButton m_btnMaxBox;
	CImageList m_il;
	CBitmapButton m_btn;
	CImage m_bkgnd;
	CRect m_rcClient;
	CRect m_rcCaption;
	CEdit m_editUserName;
	CImageList m_editil;
	CImage m_editbkimg;

	CMyHyperLink m_linkReg;
	CMyHyperLink m_linkFrgtPsd;
	CMyHyperLink m_linkProxySet;

	BOOL m_bEditState;

public:

};