#pragma once

class CMyComboBox
	: public CWindowImpl<CMyComboBox, CWindow, CControlWinTraits>
{
public:
	CEdit m_edit;
	CListBox m_list;
public:
	DECLARE_WND_CLASS(_T("My ComboBox"));

	BEGIN_MSG_MAP(CMyComboBox)
		
	END_MSG_MAP()
};