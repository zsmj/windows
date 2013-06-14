#pragma once

class CMyTabCtrl
	: public CWindowImpl<CMyTabCtrl, CTabCtrl, ATL::CControlWinTraits>
	, public CDoubleBufferImpl<CMyTabCtrl>
{
public:
	typedef CWindowImpl<CMyTabCtrl, CTabCtrl, ATL::CControlWinTraits> _baseClass;
	//
	BEGIN_MSG_MAP(CMyTabCtrl)
	
		CHAIN_MSG_MAP(CDoubleBufferImpl<CMyTabCtrl>)
	END_MSG_MAP()


	void DoPaint(CDCHandle dc)
	{
		CRect rc;
		GetClientRect(&rc);
		dc.FillSolidRect(rc, RGB(255, 0, 0));
		//
		CRect rcItem;
		for (int i = 0; i < GetItemCount(); i ++)
		{
			GetItemRect(i, rcItem);
			dc.FillSolidRect(&rcItem, RGB(0, 0, 255));
			dc.SetBkMode(TRANSPARENT);
			dc.DrawText(_T("hello"), 5, rcItem, DT_LEFT);
		}
	}
public:
	static DWORD GetWndStyle(DWORD dwStyle)
	{
		return WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | TCS_TOOLTIPS | TCS_HOTTRACK;
	}
	BOOL SubclassWindow(HWND hWnd)
	{
		return _baseClass::SubclassWindow(hWnd);
	}
	
};