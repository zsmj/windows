#pragma once

const UINT WM_DBUFFER_PARENT_DRAWBACKGRAND = ::RegisterWindowMessage(_T("WM_DBUFFER_PARENT_DRAWBACKGRAND"));


#include "MyBitmapButton.h"
#include "MyDBufferBitmapButton.h"
#include "MyHyperLink.h"
#include "MyDBufferHyperLink.h"
#include "MyComboBox.h"
#include "ShadowWindow.h"


typedef CWinTraits<WS_POPUPWINDOW> CMyWinTraits;

enum ButtonState
{
	NORMAL = 0,
	HOVER,
	PRESS
};

class CMyWindow
	: public CWindowImpl<CMyWindow, CWindow, CMyWinTraits>
	, public CMessageFilter
	, public CDoubleBufferImpl<CMyWindow>
{
public:
	typedef CWindowImpl<CMyWindow, CWindow, CMyWinTraits> _baseClass;

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CMyWindow()
	{
		m_bkgnd.Load(_T("./image/Bg_Login.png"));
		CImage img;
		img.Load(_T("./image/Input_Login_Normal_Focus.png"));
		m_editil.Create(img.GetWidth()/ 2, img.GetHeight(), ILC_COLOR32, 0, 0);
		m_editil.Add(img);

		m_rcEditBk.left = 36 + 2;
		m_rcEditBk.top = 192 + 2;
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

		m_rcComboUserName.left = 36;
		m_rcComboUserName.top = 120;
		m_rcComboUserName.right = 275;
		m_rcComboUserName.bottom = 400;

		m_rcPassword.left = 40;
		m_rcPassword.top = 200;
		m_rcPassword.right = 260;
		m_rcPassword.bottom = 220;

		m_rcComboDropDown.left = 200;
		m_rcComboDropDown.top = 200;
		m_rcComboDropDown.right = 220;
		m_rcComboDropDown.bottom = 236;
		
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
		//
		CImage imgLoginCheck;
		imgLoginCheck.Load(_T("./image/Input_Check.png"));
		
		m_ilLoginCheck.Create(imgLoginCheck.GetWidth() / 2, imgLoginCheck.GetHeight(), ILC_COLOR32, 0, 0);
		m_ilLoginCheck.Add(imgLoginCheck);
		//	
		m_rcLoginCheck.left = 36;
		m_rcLoginCheck.top = 270;
		m_rcLoginCheck.right = m_rcLoginCheck.left + imgLoginCheck.GetWidth() / 2;
		m_rcLoginCheck.bottom = m_rcLoginCheck.top + imgLoginCheck.GetHeight();
		//
		int nSep = 3;
		int nFontExtent = 4;
		m_rcAutoLogin.left = m_rcLoginCheck.left + imgLoginCheck.GetWidth()/2 + nSep;
		m_rcAutoLogin.top = m_rcLoginCheck.top - nFontExtent;
		m_rcAutoLogin.right = m_rcAutoLogin.left + 80;
		m_rcAutoLogin.bottom = m_rcAutoLogin.top + 20;

		m_bAuto = TRUE;
		//
		InitThirdPartyAccount(m_ilQQLogin, m_QQState, m_rcQQLogin, 350, 120, _T("./image/Btn_Login_QQ.png"), FALSE);
		InitThirdPartyAccount(m_ilSinaWbLogin, m_SinaWbState, m_rcSinaWbLogin, 350, 180, _T("./image/Btn_Login_Weibo.png"), FALSE);
		InitThirdPartyAccount(m_ilQQWbLogin, m_QQWbState, m_rcQQWbLogin, 350, 240, _T("./image/Btn_Login_QQT.png"), FALSE);
		InitThirdPartyAccount(m_ilLogin, m_LoginState, m_rcLogin, 115, 320, _T("./image/Btn_Login_Normal_Over_Down.png"));
		//
		m_pen.CreatePen(PS_SOLID, 1, RGB(222, 218, 218));
	}
	~CMyWindow()
	{
	}

	DECLARE_WND_CLASS(_T("My Login In Window"));


	BEGIN_MSG_MAP(CMyWindow)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroyWindow)
		MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
		MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseLeave)
		MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
		MESSAGE_HANDLER(WM_NCLBUTTONUP, OnLButtonUp)
		MESSAGE_HANDLER(WM_LBUTTONDBLCLK, OnLButtonDblClk)
		MESSAGE_HANDLER(WM_SIZE, OnSize);
		MESSAGE_HANDLER(WM_SIZING, OnSizing);
		MESSAGE_HANDLER(WM_MOVE, OnMove);
		MESSAGE_HANDLER(WM_MOVING, OnMoving);
		MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
		MESSAGE_HANDLER(WM_NCHITTEST, OnNcHitTest);
		MESSAGE_HANDLER(WM_CTLCOLOREDIT, OnCtlColorEdit)
		MESSAGE_HANDLER(WM_CTLCOLORSTATIC, OnCtlColorStatic)
		MESSAGE_HANDLER(WM_CTLCOLORBTN, OnCtlColorBtn)
		MESSAGE_HANDLER(WM_CTLCOLORBTN, OnCtlColorBtn)
		//MESSAGE_HANDLER(WM_DRAWITEM, OnDrawItem);
		MESSAGE_HANDLER(WM_DBUFFER_PARENT_DRAWBACKGRAND, OnParentDraw);
		MESSAGE_HANDLER(WM_SHOWWINDOW, OnShowWindow)
		
		NOTIFY_HANDLER(IDC_LIST_USERNAME, DL_BEGINDRAG, OnListBeginDrag);
		MESSAGE_HANDLER(WM_COMMAND, OnCommand)
		CHAIN_MSG_MAP(CDoubleBufferImpl<CMyWindow>)
		REFLECT_NOTIFICATIONS()
		
	END_MSG_MAP()
	LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT DoPaint(CDCHandle dc)
	{
		//tolog(_T("WM_PAINT in parent..."));
		ATLASSERT(m_bkgnd.IsNull() == NULL);


		dc.SelectFont(m_miniFont);
		//
		CRect rcClient;
		GetClientRect(rcClient);
		

		if (!m_bkgnd.IsNull())
		{
			m_bkgnd.Draw(dc, m_rcClient);
		}
		PaintEdit(dc.m_hDC);
		//
		//DrawComboBoxDrowDownImg(dc.m_hDC);
		CRect rc;
		rc.left = 38;
		rc.top = 90;
		rc.right = 200;
		rc.bottom = 110;
		dc.SetBkMode(TRANSPARENT);
		dc.SetTextColor(RGB(203, 234, 255));
		
		dc.DrawText(_T("为知笔记帐号"), 6, rc, DT_LEFT);

		CRect rcMoreLogin;
		rcMoreLogin.left = 350;
		rcMoreLogin.top = 90;
		rcMoreLogin.right = 450;
		rcMoreLogin.bottom = 110;
		dc.DrawText(_T("其他帐号登陆"), 6, rcMoreLogin, DT_LEFT);
		
		if (m_bAuto)
		{
			m_ilLoginCheck.Draw(dc, 1, m_rcLoginCheck.left, m_rcLoginCheck.top, ILD_NORMAL);
		}
		else 
		{
			m_ilLoginCheck.Draw(dc, 0, m_rcLoginCheck.left, m_rcLoginCheck.top, ILD_NORMAL);
		}
		dc.DrawText(_T("自动登陆"), 4, m_rcAutoLogin, DT_LEFT);
		//
		//PaintThirdPartyBtn(dc, m_ilQQLogin, m_rcQQLogin, m_QQState);
		//PaintThirdPartyBtn(dc, m_ilSinaWbLogin, m_rcSinaWbLogin, m_SinaWbState);
		//PaintThirdPartyBtn(dc, m_ilQQWbLogin, m_rcQQWbLogin, m_QQWbState);
		PaintThirdPartyBtn(dc, m_ilLogin, m_rcLogin, m_LoginState);

		DrawVertialLine(dc);
		return 0;
	}
	LRESULT OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		//tolog(_T("in parent erase."));
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
	LRESULT OnDrawItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroyWindow(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		if (m_shadow.IsWindow())
		{
			m_shadow.DestroyWindow();
		}
		//
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
		
		NONCLIENTMETRICS miniNcm = ncm;

		ncm.lfMenuFont.lfHeight -= 3;
		ncm.lfMenuFont.lfWeight = FW_NORMAL;

		m_font.CreateFontIndirectW(&ncm.lfMenuFont);
		
		miniNcm.lfMenuFont.lfHeight -= 1;
		ncm.lfMenuFont.lfWeight = FW_NORMAL;
		m_miniFont.CreateFontIndirectW(&miniNcm.lfMenuFont);
	}
	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnMouseLeave(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnLButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnParentDraw(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnListBeginDrag(int nID, LPNMHDR lpnm, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSizing(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnMoving(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnShowWindow(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
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
	void DrawEdit(CEdit& edit, CRect rc, UINT nID, DWORD dwStyle);
	void PaintEdit(CDCHandle dc);
	void SetEditState(BOOL bState)
	{
		m_bEditState = bState;
	}
	void DrawListBox();
	bool HitTestInDropDown(const CPoint& pt);
	bool HitTestAutoLogin(const CPoint& pt);
	void DrawComboBox();
	void DrawComboBoxDrowDownImg(CDCHandle dc);
	bool HitTestInQQLogin(const CPoint& pt);
	bool HitTestInSinaWbLogin(const CPoint& pt);
	bool HitTestInQQWbLogin(const CPoint& pt);
	bool HitTestInLogin(const CPoint& pt);
	void InitThirdPartyAccount(CImageList& il, ButtonState& btnState, CRect& rcBtn, int nBtnX, int nBtnY, LPCTSTR lpszImageFileName, BOOL bHorizontal = TRUE);
	void PaintThirdPartyBtn(const CDCHandle& dc, CImageList& il, const CRect& rc, ButtonState& btnState);
public:
	void DrawAllLink();
	void DrawRegLink(CMyDBufferHyperLink& hl, CRect rc, LPCTSTR lpszLabel, LPCTSTR lpszURL, DWORD dwLinkExStyle);
	void DrawFrgtPsdLink(CMyDBufferHyperLink& hl, CRect rc, LPCTSTR lpszLabel, LPCTSTR lpszURL, DWORD dwLinkExStyle);
	void DrawDBufferLink(CMyDBufferHyperLink& hl, CRect rc, LPCTSTR lpszLabel, LPCTSTR lpszURL, DWORD dwLinkExStyle);
	void DrawVertialLine(CDCHandle& dc);
	void DrawUI();
	void ResetWindowRgn();
	void OnPasswordFocus(HWND hCtl);
	void OnPasswordKillFocus(HWND hCtl);
	
private:
	COLORREF m_clrBk;
	CFont m_font;
	CFont m_miniFont;
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

	CRect m_rcPassword;
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
	CMyComboBox m_comboUserName;
	CRect m_rcComboUserName;
	CRect m_rcComboDropDown;
	//
	CImageList m_editil;
	CImage m_editbkimg;
	

	CMyDBufferHyperLink m_linkReg;
	CMyDBufferHyperLink m_linkFrgtPsd;
	CMyDBufferHyperLink m_linkProxySet;

	BOOL m_bEditState;
	//
	BOOL m_bAuto;
	CRect m_rcLoginCheck;
	CRect m_rcAutoLogin;
	CImageList m_ilLoginCheck;
	//
	ButtonState m_QQState;
	CRect m_rcQQLogin;
	CImageList m_ilQQLogin;
	//
	ButtonState m_SinaWbState;
	CRect m_rcSinaWbLogin;
	CImageList m_ilSinaWbLogin;
	//
	ButtonState m_QQWbState;
	CRect m_rcQQWbLogin;
	CImageList m_ilQQWbLogin;
	//
	ButtonState m_LoginState;
	CRect m_rcLogin;
	CImageList m_ilLogin;
	//
	CPen m_pen;
	//
	CShadowWindow m_shadow;
public:

};