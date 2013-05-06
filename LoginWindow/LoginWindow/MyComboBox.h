#pragma once

class CMyComboBox
	: public CWindowImpl<CMyComboBox, CComboBox>
{
public:
	CMyComboBox()
	{
		m_rcDropDown.left = 220;
		m_rcDropDown.top = 0;
		m_rcDropDown.right = 240;
		m_rcDropDown.bottom = 36;

		m_bkColor = RGB(233, 242, 247);
		m_itemBrush.CreateSolidBrush(m_bkColor);
		
		m_bkHoverColor = RGB(218, 231, 242);
		m_itemBkBrush.CreateSolidBrush(m_bkHoverColor);
		
		//m_comboBkBrush.CreateSolidBrush(RGB(233, 242, 247));

		//m_editBkBrush.CreateSolidBrush(RGB(239, 247, 253));
		m_imgDropDown.Load(_T("./image/Btn_User_Down.png"));

		m_nHeightListTop = 2;
		m_editBkNormal.Load(_T("./image/Text_Login_User_Normal.png"));
		m_editBkBrush.CreatePatternBrush(m_editBkNormal);
		m_editBkFocus.Load(_T("./image/Text_Login_User_Focus.png"));
		m_editBkFocusBrush.CreatePatternBrush(m_editBkFocus);
		
		m_haveTextBrush.CreateSolidBrush(RGB(233, 242, 247));
		m_bFocus = FALSE;
		m_bTransparent = FALSE;
	}
	BEGIN_MSG_MAP(CMyComboBox)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
		MESSAGE_HANDLER(WM_DRAWITEM, OnDrawItem)
		MESSAGE_HANDLER(OCM_DRAWITEM, OnDrawItem)
		MESSAGE_HANDLER(OCM_MEASUREITEM, OnMeasureItem)
		MESSAGE_HANDLER(WM_MEASUREITEM, OnMeasureItem)
		MESSAGE_HANDLER(WM_CTLCOLORLISTBOX, OnCtlColorListBox)
		MESSAGE_HANDLER(WM_CTLCOLOREDIT, OnCtlColorEdit)
		MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
		MESSAGE_HANDLER(WM_COMMAND, OnCommand)
		MESSAGE_HANDLER(OCM_COMMAND, OnCommand)

	END_MSG_MAP()
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		
		return 0;
	}
	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		tolog(_T("in combo paint."));
		CPaintDC dc(m_hWnd);

		CRect rc;
		GetClientRect(rc);
		if (m_bFocus)
		{
			dc.FillSolidRect(rc, RGB(255, 255, 255));
		}
		else 
		{
			dc.FillSolidRect(rc, RGB(233, 242, 247));
		}

		m_imgDropDown.Draw(dc, m_rcDropDown);
		
		return 1;
	}
	LRESULT OnDrawItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LPDRAWITEMSTRUCT lpDrawItem = (LPDRAWITEMSTRUCT)lParam;

		//CString strOut = Int2Str(lpDrawItem->itemAction);
		//tolog(StringFormat1(_T("on draw item action:%1"), strOut));
		//CString strState = Int2Str(lpDrawItem->itemState);
		//tolog(StringFormat1(_T("on draw item state:%1"), strState));
		//
		CDCHandle dc = lpDrawItem->hDC;
		
		dc.SetBkMode(TRANSPARENT);


		if (lpDrawItem->itemState & ODS_SELECTED)
		{
			dc.FillRect(&(lpDrawItem->rcItem), m_itemBkBrush);
		}
		else 
		{
			//tolog(_T("always in here"));
			dc.FillRect(&(lpDrawItem->rcItem), m_itemBrush);
		}
		CRect rcText = lpDrawItem->rcItem;
		rcText.left += 3;
		if (GetWindowLong(GWL_STYLE) & CBS_HASSTRINGS)
		{
			CString strItem;
			GetLBText(lpDrawItem->itemID, strItem);
			dc.DrawText(strItem, strItem.GetLength(), rcText, DT_LEFT);
		}
		else 
		{
			dc.DrawText((LPCTSTR)lpDrawItem->itemData, _tcslen((LPCTSTR)lpDrawItem->itemData), rcText, DT_LEFT);
		}
		
		return 1;
	}
	LRESULT OnCtlColorListBox(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		if (m_list.m_hWnd == 0)
		{
			if ((HWND)lParam != 0 && m_list.m_hWnd != (HWND)lParam)
			{
				tolog(_T("list is a window."));
				m_list = (HWND)lParam;
				//m_list.SetFont(m_font);
				//m_list.ModifyStyle(WS_BORDER, 0);
			}
		}
		if (m_list.IsWindow())
		{
			SetListBoxPos();
		}
		return (LRESULT)::CreateSolidBrush(m_bkColor);
	}
	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		//tolog(_T("mouse move."));
		return 0;
	}
	LRESULT OnSetFont(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	void SetFont(const CFont& font)
	{
		m_font = font;
	}
	LRESULT OnCtlColorEdit(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnMeasureItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	HWND Create(HWND hParent, RECT& rc, LPCTSTR lpszWindowName, DWORD dwStyle, DWORD dwExStyle, UINT nMenuOrID);
private:

	void SetListBoxPos();
	void ModifyListBoxProperty();
	void ModifyEditProperty();
public:
	CBrush m_haveTextBrush;
	CImage m_editBkNormal;
	CBrush m_editBkNormalBrush;
	CImage m_editBkFocus;
	CBrush m_editBkFocusBrush;
	BOOL m_bFocus;
	BOOL m_bTransparent;

	CBrush m_comboBkBrush;
	CListBox m_list;
	CEdit m_edit;
	//
	COLORREF m_bkColor;
	CBrush m_itemBrush;
	COLORREF m_bkHoverColor;
	CBrush m_itemBkBrush;
	CBrush m_editBkBrush;
	//
	CFont m_font;
	CImage m_imgDropDown;
	CRect m_rcDropDown;
	
	int m_nHeightListTop;
};
