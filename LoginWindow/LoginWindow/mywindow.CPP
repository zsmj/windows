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
LRESULT CMyWindow::OnCtlColorStatic(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{

	bHandled = TRUE;
	CDCHandle dc = (HDC)wParam;

	dc.SetBkMode(TRANSPARENT);

	return (LRESULT)GetStockObject(HOLLOW_BRUSH);

}
LRESULT CMyWindow::OnCtlColorBtn(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = TRUE;
	CDCHandle dc = (HDC)wParam;

	dc.SetBkMode(TRANSPARENT);

	return (LRESULT)GetStockObject(HOLLOW_BRUSH);
}
LRESULT CMyWindow::OnParentDraw(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect rc = *(CRect* )lParam;
	CDCHandle dc = (HDC)wParam;


	CRect rc2;
	rc2.left = 0;
	rc2.top = 0;
	rc2.right = rc.right - rc.left;
	rc2.bottom = rc.bottom - rc.top;


	m_bkgnd.Draw(dc, rc2, rc);

	return 1;
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
void CMyWindow::DrawDBufferLink(CMyDBufferHyperLink& hl, CRect rc, LPCTSTR lpszLabel, LPCTSTR lpszURL, DWORD dwLinkExStyle)
{
	DWORD dwStyle = WS_CHILD | WS_VISIBLE | SS_NOTIFY;
	hl.Create(m_hWnd, rc, 0, dwStyle);

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
	
	DrawRegLink(m_linkReg, rcReg, _T("注册"), _T("http://www.wiz.cn/register"), dwLinkExStyle);

	CRect rcFrgt;
	rcFrgt.left = 100;
	rcFrgt.top = 400;
	rcFrgt.right = 160;
	rcFrgt.bottom = 420;

	DrawFrgtPsdLink(m_linkFrgtPsd, rcFrgt, _T("忘记密码"), _T("http://as.wiz.cn/wizas/htmlpages/reset_password_zh_CN.html"), dwLinkExStyle);
	
	CRect rcProxy;
	rcProxy.left = 170;
	rcProxy.top = 400;
	rcProxy.right = 230;
	rcProxy.bottom = 420;

	DrawDBufferLink(m_linkProxySet, rcProxy, _T("代理设置"), _T("http://www.wiz.cn"), dwLinkExStyle); 
}