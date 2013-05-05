#pragma once

class CMyComboBox
	: public CWindowImpl<CMyComboBox, CComboBox>
{
public:
	CMyComboBox()
	{
		m_rcDropDown.left = 200;
		m_rcDropDown.top = 0;
		m_rcDropDown.right = 220;
		m_rcDropDown.bottom = 36;

		m_bkColor = RGB(233, 242, 247);
		m_itemBrush.CreateSolidBrush(m_bkColor);
		
		m_bkHoverColor = RGB(218, 231, 242);
		m_imgDropDown.Load(_T("./image/Btn_User_Down.png"));
	}
	BEGIN_MSG_MAP(CMyComboBox)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
		MESSAGE_HANDLER(WM_DRAWITEM, OnDrawItem)
		MESSAGE_HANDLER(WM_MEASUREITEM, OnMeasureItem)
		MESSAGE_HANDLER(WM_CTLCOLORLISTBOX, OnCtlColorListBox)
		MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
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

		m_imgDropDown.Draw(dc, m_rcDropDown);
		return 1;
	}
	LRESULT OnDrawItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		tolog(_T("in draw item."));
		
		LPDRAWITEMSTRUCT lpDrawItem = (LPDRAWITEMSTRUCT)lParam;

		CDCHandle dc = lpDrawItem->hDC;
		
		dc.SelectFont(m_font);
		dc.SetBkMode(m_bkColor);
		dc.FillRect(&lpDrawItem->rcItem, m_itemBrush);
		dc.DrawText((LPCTSTR)lpDrawItem->itemData, _tcslen((LPCTSTR)lpDrawItem->itemData), &lpDrawItem->rcItem, DT_LEFT);
		
		return 0;
	}
	LRESULT OnMeasureItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LPMEASUREITEMSTRUCT lpMeasureItem = (LPMEASUREITEMSTRUCT)lParam;

		lpMeasureItem->itemHeight = 50;
		return 0;
	}
	LRESULT OnCtlColorListBox(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return (LRESULT)::CreateSolidBrush(m_bkColor);
	}
	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		tolog(_T("mouse move."));
		return 0;
	}
	void SetFont(const CFont& font) { m_font = font; }
public:

	CBrush m_itemBrush;
	COLORREF m_bkColor;
	COLORREF m_bkHoverColor;
	CFont m_font;
	CImage m_imgDropDown;
	CRect m_rcDropDown;
};