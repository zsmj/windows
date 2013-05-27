#pragma once

class CMyEdit
	: public CWindowImpl<CMyEdit, CEdit>
{
public:
	CMyEdit()
	{
		m_bFocus = FALSE;
		m_bBkgndTransparent = FALSE;
	}
	BEGIN_MSG_MAP(CMyEdit)
		MESSAGE_HANDLER(WM_CTLCOLOREDIT, OnClrColorEdit)
		MESSAGE_HANDLER(OCM_CTLCOLOREDIT, OnClrColorEdit)
		COMMAND_CODE_HANDLER(EN_SETFOCUS, OnSetFocus)
		REFLECTED_COMMAND_CODE_HANDLER(EN_SETFOCUS, OnSetFocus)
		COMMAND_CODE_HANDLER(EN_KILLFOCUS, OnKillFocus)
		REFLECTED_COMMAND_CODE_HANDLER(EN_KILLFOCUS, OnKillFocus)
		COMMAND_CODE_HANDLER(EN_UPDATE, OnUpdate)
		REFLECTED_COMMAND_CODE_HANDLER(EN_UPDATE, OnUpdate)
	END_MSG_MAP()
	HWND Create(HWND hParent, RECT& rc, LPCTSTR lpszWindowName, DWORD dwStyle, DWORD dwExStyle, UINT nMenuOrID)
	{
		if (dwStyle == 0)
		{
			dwStyle = WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL;
		}
		return CWindowImpl<CMyEdit, CEdit>::Create(hParent, rc, lpszWindowName, dwStyle, dwExStyle, nMenuOrID);
	}
	LRESULT OnClrColorEdit(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		
		tolog(_T("on edit IDC_EDIT_PASSWORD ctl color."));
		CString strText;
		CWindow wnd = (HWND)lParam;
		wnd.GetWindowText(strText);
		CDCHandle dc;
		if (wParam != 0)
		{
			dc = (HDC)wParam; 
		}
		else 
		{
			dc = ::GetDC((HWND)lParam);
		}
		if (m_bBkgndTransparent)
		{
			dc.SetBkMode(TRANSPARENT);
		}
		HBRUSH hbr;
		if (m_bFocus)
		{
			if (!strText.IsEmpty())
			{
				hbr = (HBRUSH)::GetStockObject(WHITE_BRUSH);
			}
			else 
			{
				hbr = m_brFocus;
			}
		}
		else 
		{
			//if (m_bEditInit)
			//{
			//	hbr = m_brNormal;
			//	m_bEditInit = FALSE;
			//}
			//else 
			//{
				if (strText.IsEmpty())
				{
					hbr = m_brNormal;
				}
				else 
				{
					//hbr = ::CreateSolidBrush(RGB(239, 247, 253));
					hbr = m_brHaveText;
				}
			//}
		}

		return (LRESULT)hbr;
	}
	LRESULT OnSetFocus(WORD wCode, WORD wID, HWND hWndEdit, BOOL& bHandled)
	{
		tolog(_T("set focus."));
		CDCHandle dc = ::GetDC(hWndEdit);
		CRect rc;
		GetClientRect(&rc);
		//OnPasswordFocus((HWND)lParam);
		dc.FillRect(rc, m_brNormal);
		//	
		m_bBkgndTransparent = TRUE;
		m_bFocus = TRUE;

		return 0;
	}
	LRESULT OnKillFocus(WORD wCode, WORD wID, HWND hWndEdit, BOOL& bHandled)
	{
		tolog(_T("kill focus."));
		//OnPasswordKillFocus((HWND)lParam);
		CString strText;
		GetWindowTextW(strText);
		if (!strText.IsEmpty())
		{
			m_bBkgndTransparent = FALSE;
		}
		else
		{
			m_bBkgndTransparent = TRUE;
		}
		m_bFocus = FALSE;
		return 0;
	}
	LRESULT OnUpdate(WORD wCode, WORD wID, HWND hWndEdit, BOOL& bHandled)
	{
		tolog(_T("en update."));
		//OnPasswordFocus((HWND)lParam);
		CString strText;
		GetWindowTextW(strText);
		if (!strText.IsEmpty())
		{
			m_bBkgndTransparent = FALSE;
		}
		else
		{
			m_bBkgndTransparent = TRUE;
		}
		return 0;
	}
public:
	void SetBkgndNormalBrush(HBRUSH hBrush) { m_brNormal.Attach(hBrush); }
	HBRUSH GetBkgndNormalBrush() const { return m_brNormal; }
	void SetBkgndFocusBrush(HBRUSH hBrush) { m_brFocus.Attach(hBrush); }
	HBRUSH GetBkgndFocusBrush() const { return m_brFocus; }
	void SetHaveTextBrush(HBRUSH hBrush) { m_brHaveText.Attach(hBrush); }
	HBRUSH GetHaveTextBrush() const { return m_brHaveText; }
public:
	CBrush m_brNormal;
	CBrush m_brFocus;
	CBrush m_brHaveText;
	//
	BOOL m_bFocus;
	BOOL m_bBkgndTransparent;
};