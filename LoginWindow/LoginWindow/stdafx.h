#pragma once

#define WINVER		0x0500
#define _WIN32_WINNT	0x0501
#define _WIN32_IE	0x0501
#define _RICHEDIT_VER	0x0200


#include <atlbase.h>
#include <atlapp.h>
extern CAppModule _Module;
#include <atlwin.h>

#include <atlframe.h>
//#include <atlmisc.h>
#include <atlctrls.h>
#include <atlctrlx.h>
#include <atlimage.h>

#include "resource.h"
typedef CWinTraits<WS_CHILD | WS_VISIBLE > CMyEditTraits;

class CWizEditBase
	: public CWindowImpl<CWizEditBase, CEdit, CMyEditTraits>
{
public:
	DECLARE_WND_CLASS(_T("Wiz Edit"));

	BEGIN_MSG_MAP(CWizEditBase)
	END_MSG_MAP()
	
};
class CTestEdit
	: public CWindowImpl<CTestEdit, CEdit>
{
public:

};


class CMyHyperLink : public CHyperLinkImpl<CMyHyperLink>
{
public:
	DECLARE_WND_SUPERCLASS(_T("WTL_HyperLink"), _T("static"));

	void Init()
	{
		CHyperLinkImpl<CMyHyperLink>::Init();
		m_clrLink = m_clrVisited = RGB(255, 255, 255);
		
		CreateFont(m_hFont, TRUE);
		CreateFont(m_hFontNormal, FALSE);

	}
	void CreateFont(HFONT& font, BOOL bUnderLine)
	{
		NONCLIENTMETRICS ncm;
		ZeroMemory(&ncm, sizeof(NONCLIENTMETRICS));
#if (WINVER >= 0x0600)
		ncm.cbSize = sizeof(NONCLIENTMETRICS) - sizeof(ncm.iPaddedBorderWidth);
#else
		ncm.cbSize = sizeof(NONCLIENTMETRICS);
#endif
		//
		::SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(NONCLIENTMETRICS), &ncm, 0);
		
		ncm.lfMenuFont.lfHeight -= 3;
		ncm.lfMenuFont.lfWeight = FW_NORMAL;
		if (bUnderLine)
		{
			ncm.lfMenuFont.lfUnderline = true;
		}

		font = ::CreateFontIndirectW(&ncm.lfMenuFont);
	}
};


//#if defined _M_IX86
//#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
//#elif defined _M_IA64
//#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
//#elif defined _M_X64
//#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
//#else
//#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
//#endif


#if defined _M_IX86
  #pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
  #pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
  #pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
  #pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif