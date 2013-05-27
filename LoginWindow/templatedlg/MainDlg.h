// MainDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

class CMainDlg
	: public CAxDialogImpl<CMainDlg>
	, public CWinDataExchange<CMainDlg>
{
public:
	enum { IDD = IDD_MAINDLG };

	BEGIN_DDX_MAP(CMainDlg)
		DDX_TEXT(IDC_USERNAME_TEST, m_strUserName)
	END_DDX_MAP()
	//
	BEGIN_MSG_MAP(CMainDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		
		COMMAND_ID_HANDLER(ID_APP_ABOUT, OnAppAbout)
		COMMAND_ID_HANDLER(IDOK, OnOK)
		COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
		COMMAND_ID_HANDLER(IDC_TEST, OnTest)
	END_MSG_MAP()

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnTest(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		DoDataExchange(true);
		MessageBox(m_strUserName);
		return 0;
	}
private:
	static HGLOBAL CreateDlgTemplate()
	{
		HGLOBAL hgbl = GlobalAlloc(GMEM_ZEROINIT, 1024);
		if (!hgbl)
			return NULL;
		//
		LPDLGTEMPLATE lpdt = (LPDLGTEMPLATE)GlobalLock(hgbl);
		// Define a dialog box.
		lpdt->style = DS_SETFONT | DS_FIXEDSYS | WS_POPUP;
		lpdt->cdit = 0;         // Number of controls
		lpdt->x  = 0;  lpdt->y  = 0;
		lpdt->cx = 100; lpdt->cy = 100;
		//
		LPWORD lpw = (LPWORD)(lpdt + 1);
		*lpw++ = 0;             // No menu
		*lpw++ = 0;             // Predefined dialog box class (by default)
		//
		LPWSTR lpwsz = (LPWSTR)lpw;
		int nchar = 1 + MultiByteToWideChar(CP_ACP, 0, "Dialog", -1, lpwsz, 50);
		lpw += nchar;
		//
	    GlobalUnlock(hgbl);
		return hgbl; 
	}
public:
	int ShowModalDialog(HWND hWndParent = ::GetActiveWindow(), LPARAM dwInitParam = NULL)
	{
		HGLOBAL hGlobal = CreateDlgTemplate();
		if (!hGlobal)
			return -1;
		//
		BOOL result;

		ATLASSUME(m_hWnd == NULL);

		// Allocate the thunk structure here, where we can fail
		// gracefully.

		result = m_thunk.Init(NULL,NULL);
		if (result == FALSE) 
		{
			SetLastError(ERROR_OUTOFMEMORY);
			return -1;
		}

		_AtlWinModule.AddCreateWndData(&m_thunk.cd, (CDialogImpl< CMainDlg >*)this);
#ifdef _DEBUG
		m_bModal = true;
#endif //_DEBUG
		int ret = (int)::DialogBoxIndirectParam(_AtlBaseModule.GetResourceInstance(), (LPDLGTEMPLATE)hGlobal,
					hWndParent, CMainDlg::StartDialogProc, dwInitParam);
		//
		GlobalFree(hGlobal); 
		//
		return ret; 
	}
private:
	CButton m_btnTest;
	CEdit m_editUser;

	CString m_strUserName;
};
