#pragma once

#include <atlbase.h>
#include <atlapp.h>
extern CAppModule _Module;
#include <atlwin.h>

//#include <atlmisc.h>
#include <atlctrls.h>
#include <atlctrlx.h>
#include <atlimage.h>


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