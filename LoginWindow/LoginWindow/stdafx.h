#pragma once



#include <atlbase.h>
#include <atlapp.h>
extern CAppModule _Module;
#include <atlwin.h>

//#include <atlmisc.h>
#include <atlctrls.h>
#include <atlctrlx.h>
#include <atlimage.h>
#include <atlstr.h>

#include "resource.h"
typedef CWinTraits<WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL | ES_READONLY | ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_MULTILINE> CMyEditTraits;

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



#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif


