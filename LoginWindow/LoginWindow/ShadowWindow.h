#pragma once


typedef CWinTraits<WS_POPUP, WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW> CShadowTraits;

extern int arrayShadowColor[11];

class CShadowWindow
	: public CWindowImpl<CShadowWindow, CWindow, CShadowTraits>
{
public:
	//DECLARE_WND_CLASS(_T("shadow window"));
	static ATL::CWndClassInfo& GetWndClassInfo()
	{ 
		static ATL::CWndClassInfo wc = 
		{ 
			{ sizeof(WNDCLASSEX), CS_DBLCLKS, StartWindowProc, 
			  0, 0, NULL, NULL, NULL, (HBRUSH)(COLOR_WINDOW + 1), NULL, _T("shadow wnd"), NULL }, 
			NULL, NULL, IDC_ARROW, TRUE, 0, _T("") 
		}; 
		return wc; 
	}
	//
	typedef CWindowImpl<CShadowWindow, CWindow, CShadowTraits> _baseClass;
public:
	CShadowWindow()
	{
		m_nDeltaLeft = 10;
		m_nDeltaTop = 10;
		m_nDeltaRight = 10;
		m_nDeltaBottom = 10;

		m_bCreated = FALSE;

		CString strSkinPath = GetAppPath() + _T("/image/");
		m_imgTest.Load(strSkinPath + _T("test_shadow.png"));

	}
	BEGIN_MSG_MAP(CShadowWindow)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
	END_MSG_MAP();

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		return 0;
	}
	HWND Create(HWND hParent, int nAlpha)
	{
		m_wndParent = hParent;
		m_nAlpha = nAlpha;
		//根据投射阴影的窗口的尺寸和各参数计算出阴影的尺寸。

		m_wndParent.GetWindowRect(&m_rect);
		//
		m_rect.left -= m_nDeltaLeft;
		m_rect.top -= m_nDeltaTop;
		m_rect.right += m_nDeltaRight;
		m_rect.bottom += m_nDeltaBottom;

		_baseClass::Create(GetDesktopWindow(), m_rect);

		m_bCreated = TRUE;
		ResetWindowRgn();
		//
		CustomizedPaint(m_rect);

		return m_hWnd;
	}
	void CustomizedPaint(CRect& rc)
	{
		if (!m_bCreated)
			return;

		CDC dc = GetDC();

		CMemoryDC dcMem(dc.m_hDC, rc);

		dcMem.FillSolidRect(rc, RGB(0, 0, 0));
		//m_imgTest.Draw(dcMem, rc);
		
		
		DrawShadow(dcMem, rc);

		CPoint ptWnd;

		ptWnd.x = rc.left;
		ptWnd.y = rc.top;
		
		CPoint pt(0, 0);
		CSize psize(rc.right - rc.left, rc.bottom - rc.top);

		BLENDFUNCTION blendFunc32bpp;
		blendFunc32bpp.AlphaFormat = AC_SRC_ALPHA;
		blendFunc32bpp.BlendFlags = 0;
		blendFunc32bpp.BlendOp = AC_SRC_OVER;
		blendFunc32bpp.SourceConstantAlpha = m_nAlpha;

		int nRet = ::UpdateLayeredWindow(m_hWnd, dc, &ptWnd, &psize, dcMem, &pt, 0, &blendFunc32bpp, ULW_ALPHA);

	}
	void OnShadowCastingWndNewPos(int x, int y)
	{
		if ( !m_bCreated )
			return;
		//tolog(StringFormat2(_T("in shadow new pos, x: %1, y: %2"), Int2Str(x), Int2Str(y)));
		SetWindowPos(0, x - m_nDeltaLeft, y - m_nDeltaTop, 0, 0, SWP_NOSIZE );
	}
	
	void OnShadowCastingWndNewSize(CRect rc)
	{
		if (!m_bCreated)
			return;
		//SetWindowPos(0, 0, 0, rc.Width() + m_nDeltaLeft + m_nDeltaRight, rc.Height() - m_nDeltaTop + m_nDeltaBottom, SWP_NOMOVE);
		
		m_rect = rc;
		m_rect.left -= m_nDeltaLeft;
		m_rect.top -= m_nDeltaTop;
		m_rect.right += m_nDeltaRight;
		m_rect.bottom += m_nDeltaBottom;

		CustomizedPaint(m_rect);
	}
	void OnShadowCastingWndNewSize(int cx, int cy)
	{
		if (!m_bCreated)
			return;
		//SetWindowPos(0, 0, 0, cx + m_nDeltaLeft + m_nDeltaRight, cy + m_nDeltaTop + m_nDeltaBottom, SWP_NOMOVE);

		m_wndParent.GetWindowRect(m_rect);
		AddShadow();
	

		CustomizedPaint(m_rect);
	}
	void SetAlpha( int alpha )
	{
		m_nAlpha = alpha;
		CustomizedPaint(m_rect);
	}
	void ResetWindowRgn()
	{
		CRect rc;
		GetClientRect(rc);
		HRGN hrgn = CreateRoundRectRgn(rc.left, rc.top, rc.right, rc.bottom, 30, 30);
		
		SetWindowRgn(hrgn);
	}
	void AddShadow()
	{
		m_rect.left -= m_nDeltaLeft;
		m_rect.top -= m_nDeltaTop;
		m_rect.right += m_nDeltaRight;
		m_rect.bottom += m_nDeltaBottom;
	}
	void ShowShadow()
	{
		if (!m_bCreated)
			return;
		m_wndParent.GetWindowRect(&m_rect);
		AddShadow();
		CustomizedPaint(m_rect);


		ShowWindow(SW_NORMAL);
	}
	void DrawShadow(CMemoryDC& dc, CRect& rc)
	{
		int nWidth = rc.Width();
		int nHeight = rc.Height();
		for (int row = 0; row < nHeight; row ++)
		{
			for (int col = 0; col < nWidth; col ++)
			{
				COLORREF clr;
				if (row < m_nDeltaTop)
				{
					clr = RGB(arrayShadowColor[m_nDeltaTop-1-row], arrayShadowColor[m_nDeltaTop-1-row], arrayShadowColor[m_nDeltaTop-1-row]);
					SetPixel(dc, rc.left + col, rc.top + row, clr);
				}
				else if (row >= nHeight - m_nDeltaBottom)
				{
					
					clr = RGB(arrayShadowColor[nHeight- row - 1], arrayShadowColor[nHeight - row - 1], arrayShadowColor[nHeight - row - 1]);
					SetPixel(dc, rc.left + col, rc.top + row, clr);
				}
				else 
				{
					if (col < m_nDeltaLeft)
					{
						clr = RGB(arrayShadowColor[m_nDeltaLeft - 1 - col], arrayShadowColor[m_nDeltaLeft - 1 - col], arrayShadowColor[m_nDeltaLeft - 1 - col]);
						SetPixel(dc, rc.left + col, rc.top + row, clr);
					}
					else if (col >= nWidth - m_nDeltaRight)
					{
						clr = RGB(arrayShadowColor[nWidth - col - 1], arrayShadowColor[nWidth - col - 1], arrayShadowColor[nWidth - col - 1]);
						SetPixel(dc, rc.left + col, rc.top + row, clr);
					}
					else 
					{
						clr = RGB(255, 0, 0);
						//SetPixel(dc, rc.left + col, rc.top + row, clr);
					}
				}
			}
		}
	}

private:
	//
	CWindow m_wndParent;
	int m_nAlpha;
	//
	int m_nDeltaLeft;
	int m_nDeltaTop;
	int m_nDeltaRight;
	int m_nDeltaBottom;
	CRect m_rect;
	//
	BOOL m_bCreated;

	CImage m_imgTest;

};