#pragma once

const UINT WM_DBUFFER_PARENT_DRAWBACKGRAND = ::RegisterWindowMessage(_T("WM_DBUFFER_PARENT_DRAWBACKGRAND"));

#include "MyBitmapButton.h"
#include "MyDBufferBitmapButton.h"
#include "MyHyperLink.h"
#include "MyDBufferHyperLink.h"
#include "MyComboBox.h"


typedef CWinTraits<WS_POPUPWINDOW> CMyWinTraits;

CString StringFormat1(CString str, CString replaceStr);
void tolog(LPCTSTR lpszLog);

class CMyWindow
	: public CWindowImpl<CMyWindow, CWindow, CMyWinTraits>
	, public CMessageFilter
	, public CDoubleBufferImpl<CMyWindow>
	//, public CUpdateUI<CMyWindow>
{
public:
	
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CMyWindow()
	{
		m_bkgnd.Load(_T("./image/Bg_Login.png"));
		CImage img;
		img.Load(_T("./image/Input_Login_Normal_Focus.png"));
		m_editil.Create(img.GetWidth()/ 2, img.GetHeight(), ILC_COLOR32, 0, 0);
		m_editil.Add(img);

		m_rcEditBk.left = 36 + 2;
		m_rcEditBk.top = 132 + 2;
		m_rcEditBk.right = m_rcEditBk.left + img.GetWidth() / 2 - 4;
		m_rcEditBk.bottom = m_rcEditBk.top + img.GetHeight() - 4;

		m_editbkimg.Load(_T("./image/Text_Login_User.png"));
		m_imgLoginPass.Load(_T("./image/Text_Login_Pass.png"));
		m_imgLoginPassFocus.Load(_T("./image/Text_Login_Pass_Focus.png"));

		m_clrBk = RGB(72, 169, 220);
		CreateFont(m_font);
		
		m_rcCaption.left = 0;
		m_rcCaption.top = 0;
		m_rcCaption.right = 800;
		m_rcCaption.bottom = 50;

		m_bTransparent = FALSE;
		m_bFocus = FALSE;
		m_bEditInit = TRUE;

		m_rcUserName.left = 40;
		m_rcUserName.top = 80;
		m_rcUserName.right = 250;
		m_rcUserName.bottom = 100;
		
		m_rcDropDown.left = 251;
		m_rcDropDown.top = 72;
		m_rcDropDown.right = 271;
		m_rcDropDown.bottom = 108;

		m_rcDropDownList.left = 37;
		m_rcDropDownList.top = 108;
		m_rcDropDownList.right = 275;
		m_rcDropDownList.bottom = 220;

		m_bDropDownShow = FALSE;

		m_imgDropDown.Load(_T("./image/Btn_User_Down.png"));
	}

	DECLARE_WND_CLASS(_T("My Login In Window"));

	//BEGIN_UPDATE_UI_MAP(CMainFrame)
	//END_UPDATE_UI_MAP()

	BEGIN_MSG_MAP(CMyWindow)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroyWindow)
		// MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
		MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
		MESSAGE_HANDLER(WM_NCLBUTTONDOWN, OnLButtonDown)
		MESSAGE_HANDLER(WM_LBUTTONDBLCLK, OnLButtonDblClk)
		MESSAGE_HANDLER(WM_COMMAND, OnCommand)
		//MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
		MESSAGE_HANDLER(WM_NCHITTEST, OnNcHitTest);
		MESSAGE_HANDLER(WM_CTLCOLOREDIT, OnCtlColorEdit)
		MESSAGE_HANDLER(WM_CTLCOLORSTATIC, OnCtlColorStatic)
		MESSAGE_HANDLER(WM_CTLCOLORBTN, OnCtlColorBtn)
		MESSAGE_HANDLER(WM_CTLCOLORBTN, OnCtlColorBtn)
		MESSAGE_HANDLER(WM_DBUFFER_PARENT_DRAWBACKGRAND, OnParentDraw);
		NOTIFY_HANDLER(IDC_LIST_USERNAME, DL_BEGINDRAG, OnListBeginDrag);
		//MESSAGE_HANDLER(WM_PAINT, OnPaint)
		// REFLECT_NOTIFICATIONS()
		// CHAIN_MSG_MAP(CUpdateUI<CMyWindow>)
		CHAIN_MSG_MAP(CDoubleBufferImpl<CMyWindow>)
	END_MSG_MAP()
	LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	//LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	//{
	//	if(wParam != NULL)
	//	{
	//		RECT rect = { 0 };
	//		GetClientRect(&rect);
	//		
	//		DoPaint((HDC)wParam);
	//	}
	//	else
	//	{
	//		CPaintDC dc(m_hWnd);
	//		DoPaint(dc.m_hDC);
	//	}		
	//	return 0;
	//}
	LRESULT DoPaint(CDCHandle dc)
	{
		tolog(_T("WM_PAINT in parent"));
		ATLASSERT(m_bkgnd.IsNull() == NULL);

		CRect rcClient;
		GetClientRect(rcClient);
		//dc.FillSolidRect(rcClient, RGB(255, 255, 255));

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
		
		if (lParam != 0)
		{
			CRect rc = *(CRect* )lParam;
			CDCHandle dc = (HDC)wParam;
			m_bkgnd.Draw(dc, rc);
		}


		return 1;
	}
	LRESULT OnCtlColorEdit(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnCtlColorStatic(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnCtlColorBtn(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
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
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnParentDraw(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	void OnPasswordFocus(HWND hCtl);
	void OnPasswordKillFocus(HWND hCtl);
	LRESULT OnListBeginDrag(int nID, LPNMHDR lpnm, BOOL& bHandled);
protected:
	void DrawMinBox();
	void DrawMaxBox();
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
	void DrawAllEdit();
	void DrawEdit(CEdit& edit, CRect rc, UINT nID);
	void PaintEdit(CDCHandle dc);
	void SetEditState(BOOL bState)
	{
		m_bEditState = bState;
	}
	void DrawListBox();
	bool HitTestInDropDown(const CPoint& pt);
public:
	void DrawAllLink();
	void DrawRegLink(CMyDBufferHyperLink& hl, CRect rc, LPCTSTR lpszLabel, LPCTSTR lpszURL, DWORD dwLinkExStyle);
	void DrawFrgtPsdLink(CMyDBufferHyperLink& hl, CRect rc, LPCTSTR lpszLabel, LPCTSTR lpszURL, DWORD dwLinkExStyle);
	void DrawDBufferLink(CMyDBufferHyperLink& hl, CRect rc, LPCTSTR lpszLabel, LPCTSTR lpszURL, DWORD dwLinkExStyle);
private:
	COLORREF m_clrBk;
	CFont m_font;
	CMyDBufferBitmapButton m_btnMinBox;
	CMyDBufferBitmapButton m_btnMaxBox;
	CImageList m_il;
	CBitmapButton m_btn;
	CImage m_bkgnd;
	CRect m_rcClient;
	CRect m_rcCaption;
	//
	CEdit m_editUserName;
	CRect m_rcUserName;
	BOOL m_bDropDownShow;

	CEdit m_editPassword;
	CRect m_rcEditBk;
	CRect m_rcDropDown;
	CRect m_rcDropDownList;
	CImage m_imgDropDown;

	//
	BOOL m_bTransparent;
	BOOL m_bFocus;
	BOOL m_bEditInit;
	CImage m_imgLoginPass;
	CImage m_imgLoginPassFocus;
	//
	CListBox m_listBoxUN;
	//
	CImageList m_editil;
	CImage m_editbkimg;
	

	CMyDBufferHyperLink m_linkReg;
	CMyDBufferHyperLink m_linkFrgtPsd;
	CMyDBufferHyperLink m_linkProxySet;

	BOOL m_bEditState;

public:

};