#pragma once
#include "MyBitmapButton.h"

typedef CWinTraits<WS_POPUPWINDOW> CMyWinTraits;

CString StringFormat1(CString str, CString replaceStr)
{
	str.Replace(_T("%1"), replaceStr);
	return str;
}
void tolog(LPCTSTR lpszLog)
{
	::OutputDebugString(lpszLog);
}

class CMyWindow
	: public CWindowImpl<CMyWindow, CWindow, CMyWinTraits>
	//, public CUpdateUI<CMyWindow>
{
public:
	
	CMyWindow()
	{
		m_bkgnd.Load(_T("./image/Bg_Login.png"));
		
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
		//MESSAGE_HANDLER(WM_CTLCOLORBTN, OnColorBtn)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
		// REFLECT_NOTIFICATIONS()
		// CHAIN_MSG_MAP(CUpdateUI<CMyWindow>)
	END_MSG_MAP()
	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		CPaintDC dc(m_hWnd);
		
		ATLASSERT(m_bkgnd.IsNull() == NULL);

		if (!m_bkgnd.IsNull())
		{
			m_bkgnd.Draw(dc, m_rcClient);
		}

		bHandled = FALSE;
		return 0;
	}
	LRESULT OnColorBtn(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		
		return 0;
	}
	LRESULT OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		HDC dc = (HDC)(wParam);
		HBRUSH hBr = ::CreateSolidBrush(RGB(0, 200, 200));
		if (hBr)
		{
			CRect rc;
			GetClientRect(&rc);
			::FillRect(dc, &rc, hBr);
		}

		// bHandled = FALSE;
	//	SetBkMode(dc, TRANSPARENT);
	//	m_il.Draw(dc, 0, 10, 10, ILD_TRANSPARENT);
		
		return 1;
	}
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
		return 0;
	}
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
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
		
		CRect rcEdit;
		rcEdit.left = 100;
		rcEdit.top = 100;
		rcEdit.right = 260;
		rcEdit.bottom = 140;

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

		ncm.lfMenuFont.lfWeight = FW_NORMAL;

//		m_font.CreateFontIndirectW(&ncm.lfMenuFont);
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
		m_btnMinBox.SetBackground(RGB(72, 169, 220));
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
		m_btnMaxBox.SetBackground(RGB(72, 169, 220));
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
		m_editUserName.Create(m_hWnd, rc);
	}
private:
	CFont m_font;
	CMyBitmapButton m_btnMinBox;
	CMyBitmapButton m_btnMaxBox;
	CImageList m_il;
	CBitmapButton m_btn;
	CImage m_bkgnd;
	CRect m_rcClient;
	CWizEditBase m_editUserName;

public:

};