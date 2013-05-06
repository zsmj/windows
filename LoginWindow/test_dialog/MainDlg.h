// MainDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include "MycomboBox.h"

class CMainDlg : public CDialogImpl<CMainDlg>, public CUpdateUI<CMainDlg>,
		public CMessageFilter, public CIdleHandler
{
public:
	enum { IDD = IDD_MAINDLG };

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnIdle();

	BEGIN_UPDATE_UI_MAP(CMainDlg)
	END_UPDATE_UI_MAP()

	BEGIN_MSG_MAP(CMainDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		COMMAND_ID_HANDLER(ID_APP_ABOUT, OnAppAbout)
		COMMAND_ID_HANDLER(IDOK, OnOK)
		COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
		REFLECT_NOTIFICATIONS()
	END_MSG_MAP()

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	void CreateToolTipForRect(HWND hwndParent)
	{
		HINSTANCE hInst = _Module.GetModuleInstance();
		// Create a tooltip.
		HWND hwndTT = CreateWindowEx(WS_EX_TOPMOST, TOOLTIPS_CLASS, NULL, 
									 WS_POPUP | TTS_NOPREFIX | TTS_ALWAYSTIP, 
									 CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 
									 hwndParent, NULL, hInst,NULL);

		::SetWindowPos(hwndTT, HWND_TOPMOST, 0, 0, 0, 0, 
					 SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);

		// Set up "tool" information. In this case, the "tool" is the entire parent window.
	    
		TOOLINFO ti = { 0 };
		ti.cbSize   = sizeof(TOOLINFO);
		ti.uFlags   = TTF_SUBCLASS;
		ti.hwnd     = hwndParent;
		ti.hinst    = hInst;
		ti.lpszText = TEXT("This is your tooltip string.");;
	    
		::GetClientRect (hwndParent, &ti.rect);

		// Associate the tooltip with the "tool" window.
		::SendMessage(hwndTT, TTM_ADDTOOL, 0, (LPARAM) (LPTOOLINFO) &ti);
	} 
	void CloseDialog(int nVal);
	void InitButton()
	{
		CImage img;
		img.Load(_T("./Btn_Window_Close.png"));
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
private:
	CBitmapButton m_btn;
	CEdit m_editTest;

	CMyComboBox m_combo;
};
