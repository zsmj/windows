#pragma once
#include "MyBitmapButton.h"

typedef CWinTraits<WS_OVERLAPPEDWINDOW> CMyWinTraits;

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
{
public:
	
	CMyWindow()
	{
		
		
	}

	DECLARE_WND_CLASS(_T("My Login In Window"));

	BEGIN_MSG_MAP(CMyWindow)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroyWindow)
		MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
		MESSAGE_HANDLER(WM_COMMAND, OnCommand)
		MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
		MESSAGE_HANDLER(WM_CTLCOLORBTN, OnColorBtn)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
		// REFLECT_NOTIFICATIONS()
	END_MSG_MAP()
	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		CPaintDC dc(m_hWnd);
		
	//	m_il.Draw(dc, 0, 300, 300, 0);



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
		//
	//	DrawMinBox();
		//
		DrawMaxBox();
		//
		CenterWindow();

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
		rc.left = 700;
		rc.top = 10;
		rc.right = 720;
		rc.bottom = 30;

		m_btnMinBox.Create(m_hWnd, rc, 0, 0, 0, IDC_MINIMIZE);
		m_btnMinBox.SetBitmapButtonExtendedStyle(BMPBTN_HOVER);
		m_btnMinBox.SetImageList(il);
		m_btnMinBox.SetImages(0, 2, 1);
		m_btnMinBox.SetToolTipText(_T("test tips"));
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
		rc.left = 350;
		rc.top = 10;
		rc.right = 370;
		rc.bottom = 30;

		m_btnMaxBox.Create(m_hWnd, rc, 0, 0, 0, IDC_CLOSE);
		m_btnMaxBox.SetToolTip(_T("maxbossssssssssssx"));
		m_btnMaxBox.SetBitmapButtonExtendedStyle(BMPBTN_HOVER);
		m_btnMaxBox.SetImageList(il);
		m_btnMaxBox.SetImages(0, 2, 1);
	}
private:
	CFont m_font;
	CBitmapButton m_btnMinBox;
	CMyBitmapButton m_btnMaxBox;
	CImageList m_il;

public:

};