#include "StdAfx.h"
#include "MyWindow.h"

CString StringFormat1(CString str, CString replaceStr)
{
	str.Replace(_T("%1"), replaceStr);
	return str;
}
void tolog(LPCTSTR lpszLog)
{
	::OutputDebugString(lpszLog);
}
LRESULT CMyWindow::OnCtlColorStatic(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{

	bHandled = TRUE;
	CDCHandle dc = (HDC)wParam;

	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(RGB(255, 255, 255));

	return (LRESULT)::CreateSolidBrush(m_clrBk);
	//return 0;
}
void CMyWindow::DrawAllLink()
{
	CRect rc;
	rc.left = 50;
	rc.top = 400;
	rc.right = 110;
	rc.bottom = 430;
	
	DWORD dwStyle = WS_CHILD | WS_VISIBLE | SS_LEFT | SS_NOTIFY;
	m_linkFrgtPsd.Create(m_hWnd, rc, 0, dwStyle);

	m_linkFrgtPsd.SetLabel(_T("зЂВс"));
	m_linkFrgtPsd.SetHyperLink(_T("http://www.wiz.cn/register"));
	m_linkFrgtPsd.SetHyperLinkExtendedStyle(HLINK_UNDERLINEHOVER);
	
	
}