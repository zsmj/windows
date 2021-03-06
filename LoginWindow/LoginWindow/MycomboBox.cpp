#include "stdafx.h"
#include "MyComboBox.h"
#include "MyWindow.h"

HWND CMyComboBox::Create(HWND hParent, RECT& rc, LPCTSTR lpszWindowName = NULL, DWORD dwStyle = 0, DWORD dwExStyle = 0, UINT nMenuOrID = 0)
{
	dwStyle |= WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
	dwStyle |= CBS_OWNERDRAWFIXED;
	dwStyle |= CBS_HASSTRINGS;

	return CWindowImpl<CMyComboBox, CComboBox>::Create(hParent, rc, lpszWindowName, dwStyle, dwExStyle, nMenuOrID);

}
LRESULT CMyComboBox::OnSetFont(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	tolog(_T("combo box set font."));

	return 1;
}
LRESULT CMyComboBox::OnCtlColorEdit(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	tolog(_T("on combo box edit color edit"));
	CDCHandle dc = (HDC)wParam;
	if (m_edit.m_hWnd == 0)
	{
		COMBOBOXINFO info;
		info.cbSize = sizeof(COMBOBOXINFO);
	
		GetComboBoxInfo(&info);
		m_list = info.hwndList;
		ModifyListBox();

		m_edit = info.hwndItem;
		ModifyEdit();
	}
	tolog(_T("combo color edit."));

	CString strEdit;
	GetWindowText(strEdit);
	if (!strEdit.IsEmpty())
	{
		if (m_bFocus)
		{
			return (LRESULT)(HBRUSH)::GetStockObject(WHITE_BRUSH);
		}
		else
		{
			return (LRESULT)(HBRUSH)m_haveTextBrush;
		}
	}

	if (m_bTransparent)
	{
		dc.SetBkMode(TRANSPARENT);
		return (LRESULT)(HBRUSH)m_editBkFocusBrush;
	}
	
	return (LRESULT)(HBRUSH)m_editBkNormalBrush;
}
LRESULT CMyComboBox::OnMeasureItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	
	LPMEASUREITEMSTRUCT lpMeasureItem = (LPMEASUREITEMSTRUCT)lParam;
	
	if (lpMeasureItem->itemID == -1)
	{
		tolog(_T("on measure edit item."));
		lpMeasureItem->itemHeight = 30;
	}
	else
	{
		tolog(_T("on measure listbox item."));
		lpMeasureItem->itemHeight = 20;
	}

	return 0;
}
LRESULT CMyComboBox::OnCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = FALSE;
	
	if (uMsg == OCM_COMMAND)
	{
		tolog(_T("in ocm_command"));
	}
	HWND hWnd = (HWND)lParam;
	tolog(StringFormat1(_T("in combo command, wcode: %1"), Int2Str(HIWORD(wParam))));
	if (m_edit.IsWindow())
	{
		WORD wCode = HIWORD(wParam);
		CString str;
		CDC dc = GetDC();
		CRect rcCombo;
		GetClientRect(rcCombo);
		CDC dcEdit = m_edit.GetDC();
		CRect rcEdit;
		m_edit.GetRect(rcEdit);
		CString strEdit;
		GetWindowText(strEdit);
		switch(wCode)
		{
		case CBN_SELENDOK:
			tolog(_T("CBN_SELENDOK"));
			
			GetLBText(GetCurSel(), str);
			if (!str.IsEmpty())
			{
				SetWindowText(str);
			}
			bHandled = TRUE;

			::PostMessage(GetParent(), WM_SWITCH_FOCUS, 0, 0);
			break;
		case CBN_KILLFOCUS:
			
			dc.FillSolidRect(rcEdit, RGB(233, 242, 247));
			if (strEdit.IsEmpty())
			{
				dcEdit.FillRect(rcEdit, m_editBkNormalBrush);
				m_bTransparent = FALSE;
			}
			else 
			{
				dcEdit.FillRect(rcEdit, ::CreateSolidBrush(RGB(233, 242, 247)));
				m_bTransparent = TRUE;
			}
			m_bFocus = FALSE;
			//tolog(_T("CBN_KILLFOCUS"));
			break;
		case CBN_EDITUPDATE:
			
			dc.FillSolidRect(rcCombo, RGB(255, 255, 255));
			m_imgDropDown.Draw(dc, rcCombo.right - m_imgDropDown.GetWidth(), rcCombo.top);
			
			if (strEdit.IsEmpty())
			{
				m_bTransparent = TRUE;
			}
			else 
			{
				m_bTransparent = FALSE;
			}
			//tolog(_T("CBN_EDITUPDATE"));
		}
	}
	
	return 0;
}
LRESULT CMyComboBox::OnSetFocus(WORD wCode, WORD wID, HWND hWndCombo, BOOL& bHandled)
{
	if (m_edit.IsWindow())
	{
		CDC dc = ::GetDC(hWndCombo);
		CRect rcCombo;
		GetClientRect(rcCombo);
		//
		CDC dcEdit = m_edit.GetDC();
		CRect rcEdit;
		m_edit.GetRect(rcEdit);
		//
		dcEdit.FillRect(rcEdit, m_editBkFocusBrush);
		//
		dc.FillSolidRect(rcCombo, RGB(255, 255, 255));
		//
		m_bFocus = TRUE;
		m_bTransparent = TRUE;
		tolog(_T("CBN_SETFOCUS"));
	}

	return 0;
}
void CMyComboBox::SetListBoxPos()
{
	CRect rcCombo;
	GetClientRect(rcCombo);
	ClientToScreen(rcCombo);

	POINT pt;
	pt.x = rcCombo.left;
	pt.y = rcCombo.bottom + m_nHeightListTop;
	m_list.SetWindowPos(0, pt.x, pt.y, 0, 0, SWP_NOACTIVATE | SWP_NOZORDER | SWP_NOSIZE);
	
}
void CMyComboBox::ModifyListBox()
{
	if (m_list.IsWindow())
	{
		m_list.SetFont(m_font);
		m_list.ModifyStyle(WS_BORDER, 0);
	}
}
void CMyComboBox::ModifyEdit()
{
	m_edit.SetFont(m_font);
	m_edit.SetWindowPos(0, 3, 8, 215, 20, SWP_NOACTIVATE | SWP_NOZORDER);
	Invalidate();
}