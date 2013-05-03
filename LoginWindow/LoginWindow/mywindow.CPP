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

	return (LRESULT)GetStockObject(HOLLOW_BRUSH);

}
void CMyWindow::DrawFrgtPsdLink(CMyHyperLink& hl, CRect rc, LPCTSTR lpszLabel, LPCTSTR lpszURL, DWORD dwLinkExStyle)
{
	DWORD dwStyle = WS_CHILD | WS_VISIBLE | SS_NOTIFY;
	hl.Create(m_hWnd, rc, 0, dwStyle, WS_EX_TRANSPARENT);

	hl.SetLabel(lpszLabel);
	hl.SetHyperLink(lpszURL);
	hl.SetHyperLinkExtendedStyle(dwLinkExStyle);
}
void CMyWindow::DrawRegLink(CMyHyperLink& hl, CRect rc, LPCTSTR lpszLabel, LPCTSTR lpszURL, DWORD dwLinkExStyle)
{
	DWORD dwStyle = WS_CHILD | WS_VISIBLE | SS_NOTIFY;
	hl.Create(m_hWnd, rc, 0, dwStyle, WS_EX_TRANSPARENT);

	hl.SetLabel(lpszLabel);
	hl.SetHyperLink(lpszURL);
	hl.SetHyperLinkExtendedStyle(dwLinkExStyle);
}
void CMyWindow::DrawAllLink()
{
	DWORD dwLinkExStyle = HLINK_UNDERLINEHOVER | HLINK_NOTOOLTIP;
	CRect rcReg;
	rcReg.left = 50;
	rcReg.top = 400;
	rcReg.right = 80;
	rcReg.bottom = 420;
	
	DrawRegLink(m_linkReg, rcReg, _T("×¢²á"), _T("http://www.wiz.cn/register"), dwLinkExStyle);

	CRect rcFrgt;
	rcFrgt.left = 100;
	rcFrgt.top = 400;
	rcFrgt.right = 160;
	rcFrgt.bottom = 420;

	DrawRegLink(m_linkFrgtPsd, rcFrgt, _T("Íü¼ÇÃÜÂë"), _T("http://as.wiz.cn/wizas/htmlpages/reset_password_zh_CN.html"), dwLinkExStyle);
	
}
LRESULT CMyWindow::OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT pt = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)};
	ScreenToClient(&pt);
	if (PtInRect(m_rcCaption, pt))
	{
		return HTCAPTION;
	}

	return ::DefWindowProc(m_hWnd, uMsg, wParam, lParam);
}