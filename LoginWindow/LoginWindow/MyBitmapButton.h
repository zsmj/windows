template <class T, class TBase = CButton, class TWinTraits = ATL::CControlWinTraits>
class ATL_NO_VTABLE CMyBitmapButtonImpl : public ATL::CWindowImpl< T, TBase, TWinTraits>
{
public:
	DECLARE_WND_SUPERCLASS(NULL, TBase::GetWndClassName())

	enum
	{
		_nImageNormal = 0,
		_nImagePushed,
		_nImageFocusOrHover,
		_nImageDisabled,

		_nImageCount = 4,
	};

	enum
	{
		ID_TIMER_FIRST = 1000,
		ID_TIMER_REPEAT = 1001
	};

	// Bitmap button specific extended styles
	DWORD m_dwExtendedStyle;

	CImageList m_ImageList;
	int m_nImage[_nImageCount];

	CToolTipCtrl m_tip;
	LPTSTR m_lpstrToolTipText;

	// Internal states
	unsigned m_fMouseOver:1;
	unsigned m_fFocus:1;
	unsigned m_fPressed:1;


// Constructor/Destructor
	CMyBitmapButtonImpl(DWORD dwExtendedStyle = BMPBTN_AUTOSIZE, HIMAGELIST hImageList = NULL) : 
			m_ImageList(hImageList), m_dwExtendedStyle(dwExtendedStyle), 
			m_lpstrToolTipText(NULL),
			m_fMouseOver(0), m_fFocus(0), m_fPressed(0)
	{
		m_nImage[_nImageNormal] = -1;
		m_nImage[_nImagePushed] = -1;
		m_nImage[_nImageFocusOrHover] = -1;
		m_nImage[_nImageDisabled] = -1;
	}

	~CMyBitmapButtonImpl()
	{
		if((m_dwExtendedStyle & BMPBTN_SHAREIMAGELISTS) == 0)
			m_ImageList.Destroy();
		delete [] m_lpstrToolTipText;
	}

	// overridden to provide proper initialization
	BOOL SubclassWindow(HWND hWnd)
	{
#if (_MSC_VER >= 1300)
		BOOL bRet = ATL::CWindowImpl< T, TBase, TWinTraits>::SubclassWindow(hWnd);
#else // !(_MSC_VER >= 1300)
		typedef ATL::CWindowImpl< T, TBase, TWinTraits>   _baseClass;
		BOOL bRet = _baseClass::SubclassWindow(hWnd);
#endif // !(_MSC_VER >= 1300)
		if(bRet)
			Init();
		return bRet;
	}

// Attributes
	DWORD GetBitmapButtonExtendedStyle() const
	{
		return m_dwExtendedStyle;
	}

	DWORD SetBitmapButtonExtendedStyle(DWORD dwExtendedStyle, DWORD dwMask = 0)
	{
		DWORD dwPrevStyle = m_dwExtendedStyle;
		if(dwMask == 0)
			m_dwExtendedStyle = dwExtendedStyle;
		else
			m_dwExtendedStyle = (m_dwExtendedStyle & ~dwMask) | (dwExtendedStyle & dwMask);
		return dwPrevStyle;
	}

	HIMAGELIST GetImageList() const
	{
		return m_ImageList;
	}

	HIMAGELIST SetImageList(HIMAGELIST hImageList)
	{
		HIMAGELIST hImageListPrev = m_ImageList;
		m_ImageList = hImageList;
		if((m_dwExtendedStyle & BMPBTN_AUTOSIZE) != 0 && ::IsWindow(m_hWnd))
			SizeToImage();
		return hImageListPrev;
	}

	int GetToolTipTextLength() const
	{
		return (m_lpstrToolTipText == NULL) ? -1 : lstrlen(m_lpstrToolTipText);
	}

	bool GetToolTipText(LPTSTR lpstrText, int nLength) const
	{
		ATLASSERT(lpstrText != NULL);
		if(m_lpstrToolTipText == NULL)
			return false;

		errno_t nRet = SecureHelper::strncpy_x(lpstrText, nLength, m_lpstrToolTipText, _TRUNCATE);

		return (nRet == 0 || nRet == STRUNCATE);
	}

	bool SetToolTipText(LPCTSTR lpstrText)
	{
		if(m_lpstrToolTipText != NULL)
		{
			delete [] m_lpstrToolTipText;
			m_lpstrToolTipText = NULL;
		}

		if(lpstrText == NULL)
		{
			if(m_tip.IsWindow())
				m_tip.Activate(FALSE);
			return true;
		}

		int cchLen = lstrlen(lpstrText) + 1;
		ATLTRY(m_lpstrToolTipText = new TCHAR[cchLen]);
		if(m_lpstrToolTipText == NULL)
			return false;

		SecureHelper::strcpy_x(m_lpstrToolTipText, cchLen, lpstrText);
		if(m_tip.IsWindow())
		{
			m_tip.Activate(TRUE);
			m_tip.AddTool(m_hWnd, m_lpstrToolTipText);
		}

		return true;
	}

// Operations
	void SetImages(int nNormal, int nPushed = -1, int nFocusOrHover = -1, int nDisabled = -1)
	{
		if(nNormal != -1)
			m_nImage[_nImageNormal] = nNormal;
		if(nPushed != -1)
			m_nImage[_nImagePushed] = nPushed;
		if(nFocusOrHover != -1)
			m_nImage[_nImageFocusOrHover] = nFocusOrHover;
		if(nDisabled != -1)
			m_nImage[_nImageDisabled] = nDisabled;
	}

	BOOL SizeToImage()
	{
		ATLASSERT(::IsWindow(m_hWnd) && m_ImageList.m_hImageList != NULL);
		int cx = 0;
		int cy = 0;
		if(!m_ImageList.GetIconSize(cx, cy))
			return FALSE;
		return ResizeClient(cx, cy);
	}

// Overrideables
	void DoPaint(CDCHandle dc)
	{
		ATLASSERT(m_ImageList.m_hImageList != NULL);   // image list must be set
		ATLASSERT(m_nImage[0] != -1);                  // main bitmap must be set

		// set bitmap according to the current button state
		int nImage = -1;
		bool bHover = IsHoverMode();
		if(!IsWindowEnabled())
			nImage = m_nImage[_nImageDisabled];
		else if(m_fPressed == 1)
			nImage = m_nImage[_nImagePushed];
		else if((!bHover && m_fFocus == 1) || (bHover && m_fMouseOver == 1))
			nImage = m_nImage[_nImageFocusOrHover];
		if(nImage == -1)   // not there, use default one
			nImage = m_nImage[_nImageNormal];

		// draw the button image
		int xyPos = 0;
		if((m_fPressed == 1) && ((m_dwExtendedStyle & (BMPBTN_AUTO3D_SINGLE | BMPBTN_AUTO3D_DOUBLE)) != 0) && (m_nImage[_nImagePushed] == -1))
			xyPos = 1;
		m_ImageList.Draw(dc, nImage, xyPos, xyPos, ILD_NORMAL);

		// draw 3D border if required
		if((m_dwExtendedStyle & (BMPBTN_AUTO3D_SINGLE | BMPBTN_AUTO3D_DOUBLE)) != 0)
		{
			RECT rect;
			GetClientRect(&rect);

			if(m_fPressed == 1)
				dc.DrawEdge(&rect, ((m_dwExtendedStyle & BMPBTN_AUTO3D_SINGLE) != 0) ? BDR_SUNKENOUTER : EDGE_SUNKEN, BF_RECT);
			else if(!bHover || m_fMouseOver == 1)
				dc.DrawEdge(&rect, ((m_dwExtendedStyle & BMPBTN_AUTO3D_SINGLE) != 0) ? BDR_RAISEDINNER : EDGE_RAISED, BF_RECT);

			if(!bHover && m_fFocus == 1)
			{
				::InflateRect(&rect, -2 * ::GetSystemMetrics(SM_CXEDGE), -2 * ::GetSystemMetrics(SM_CYEDGE));
				dc.DrawFocusRect(&rect);
			}
		}
	}

// Message map and handlers
	BEGIN_MSG_MAP(CBitmapButtonImpl)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		MESSAGE_RANGE_HANDLER(WM_MOUSEFIRST, WM_MOUSELAST, OnMouseMessage)
		MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBackground)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
		MESSAGE_HANDLER(WM_PRINTCLIENT, OnPaint)
		MESSAGE_HANDLER(WM_SETFOCUS, OnFocus)
		MESSAGE_HANDLER(WM_KILLFOCUS, OnFocus)
		MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
		MESSAGE_HANDLER(WM_LBUTTONDBLCLK, OnLButtonDblClk)
		MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
		MESSAGE_HANDLER(WM_CAPTURECHANGED, OnCaptureChanged)
		MESSAGE_HANDLER(WM_ENABLE, OnEnable)
		MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
		MESSAGE_HANDLER(WM_MOUSELEAVE, OnMouseLeave)
		MESSAGE_HANDLER(WM_KEYDOWN, OnKeyDown)
		MESSAGE_HANDLER(WM_KEYUP, OnKeyUp)
		MESSAGE_HANDLER(WM_TIMER, OnTimer)
		MESSAGE_HANDLER(WM_UPDATEUISTATE, OnUpdateUiState)
	END_MSG_MAP()

	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
	{
		Init();
		bHandled = FALSE;
		return 1;
	}

	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
	{
		if(m_tip.IsWindow())
		{
			m_tip.DestroyWindow();
			m_tip.m_hWnd = NULL;
		}
		bHandled = FALSE;
		return 1;
	}

	LRESULT OnMouseMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		//MSG msg = { m_hWnd, uMsg, wParam, lParam };
		//if(m_tip.IsWindow())
		//	m_tip.RelayEvent(&msg);

		TooltipRelayEvent();
		bHandled = FALSE;
		return 1;
	}

	LRESULT OnEraseBackground(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		return 1;   // no background needed
	}

	LRESULT OnPaint(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		T* pT = static_cast<T*>(this);
		if(wParam != NULL)
		{
			pT->DoPaint((HDC)wParam);
		}
		else
		{
			CPaintDC dc(m_hWnd);
			pT->DoPaint(dc.m_hDC);
		}
		return 0;
	}

	LRESULT OnFocus(UINT uMsg, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
	{
		m_fFocus = (uMsg == WM_SETFOCUS) ? 1 : 0;
		Invalidate();
		UpdateWindow();
		bHandled = FALSE;
		return 1;
	}

	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
	{
		LRESULT lRet = 0;
		if(IsHoverMode())
			SetCapture();
		else
			lRet = DefWindowProc(uMsg, wParam, lParam);
		if(::GetCapture() == m_hWnd)
		{
			m_fPressed = 1;
			Invalidate();
			UpdateWindow();
		}
		if((m_dwExtendedStyle & BMPBTN_AUTOFIRE) != 0)
		{
			int nElapse = 250;
			int nDelay = 0;
			if(::SystemParametersInfo(SPI_GETKEYBOARDDELAY, 0, &nDelay, 0))
				nElapse += nDelay * 250;   // all milli-seconds
			SetTimer(ID_TIMER_FIRST, nElapse);
		}
		return lRet;
	}

	LRESULT OnLButtonDblClk(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
	{
		LRESULT lRet = 0;
		if(!IsHoverMode())
			lRet = DefWindowProc(uMsg, wParam, lParam);
		if(::GetCapture() != m_hWnd)
			SetCapture();
		if(m_fPressed == 0)
		{
			m_fPressed = 1;
			Invalidate();
			UpdateWindow();
		}
		return lRet;
	}

	LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
	{
		LRESULT lRet = 0;
		bool bHover = IsHoverMode();
		if(!bHover)
			lRet = DefWindowProc(uMsg, wParam, lParam);
		if(::GetCapture() == m_hWnd)
		{
			if(bHover && m_fPressed == 1)
				::SendMessage(GetParent(), WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(), BN_CLICKED), (LPARAM)m_hWnd);
			::ReleaseCapture();
		}
		return lRet;
	}

	LRESULT OnCaptureChanged(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
	{
		if(m_fPressed == 1)
		{
			m_fPressed = 0;
			Invalidate();
			UpdateWindow();
		}
		bHandled = FALSE;
		return 1;
	}

	LRESULT OnEnable(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
	{
		Invalidate();
		UpdateWindow();
		bHandled = FALSE;
		return 1;
	}

	LRESULT OnMouseMove(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& bHandled)
	{
		//
		//TooltipRelayEvent();
		//
		if(::GetCapture() == m_hWnd)
		{
			POINT ptCursor = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
			ClientToScreen(&ptCursor);
			RECT rect = { 0 };
			GetWindowRect(&rect);
			unsigned int uPressed = ::PtInRect(&rect, ptCursor) ? 1 : 0;
			if(m_fPressed != uPressed)
			{
				m_fPressed = uPressed;
				Invalidate();
				UpdateWindow();
			}
		}
		else if(IsHoverMode() && m_fMouseOver == 0)
		{
			m_fMouseOver = 1;
			Invalidate();
			UpdateWindow();
			StartTrackMouseLeave();
		}
		bHandled = FALSE;
		return 1;
	}

	LRESULT OnMouseLeave(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
	//	TooltipRelayEvent();
		//
		if(m_fMouseOver == 1)
		{
			m_fMouseOver = 0;
			Invalidate();
			UpdateWindow();
		}
		return 0;
	}

	LRESULT OnKeyDown(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& bHandled)
	{
		if(wParam == VK_SPACE && IsHoverMode())
			return 0;   // ignore if in hover mode
		if(wParam == VK_SPACE && m_fPressed == 0)
		{
			m_fPressed = 1;
			Invalidate();
			UpdateWindow();
		}
		bHandled = FALSE;
		return 1;
	}

	LRESULT OnKeyUp(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& bHandled)
	{
		if(wParam == VK_SPACE && IsHoverMode())
			return 0;   // ignore if in hover mode
		if(wParam == VK_SPACE && m_fPressed == 1)
		{
			m_fPressed = 0;
			Invalidate();
			UpdateWindow();
		}
		bHandled = FALSE;
		return 1;
	}

	LRESULT OnTimer(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		ATLASSERT((m_dwExtendedStyle & BMPBTN_AUTOFIRE) != 0);
		switch(wParam)   // timer ID
		{
		case ID_TIMER_FIRST:
			KillTimer(ID_TIMER_FIRST);
			if(m_fPressed == 1)
			{
				::SendMessage(GetParent(), WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(), BN_CLICKED), (LPARAM)m_hWnd);
				int nElapse = 250;
				int nRepeat = 40;
				if(::SystemParametersInfo(SPI_GETKEYBOARDSPEED, 0, &nRepeat, 0))
					nElapse = 10000 / (10 * nRepeat + 25);   // milli-seconds, approximated
				SetTimer(ID_TIMER_REPEAT, nElapse);
			}
			break;
		case ID_TIMER_REPEAT:
			if(m_fPressed == 1)
				::SendMessage(GetParent(), WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(), BN_CLICKED), (LPARAM)m_hWnd);
			else if(::GetCapture() != m_hWnd)
				KillTimer(ID_TIMER_REPEAT);
			break;
		default:	// not our timer
			break;
		}
		return 0;
	}

	LRESULT OnUpdateUiState(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		// If the control is subclassed or superclassed, this message can cause
		// repainting without WM_PAINT. We don't use this state, so just do nothing.
		return 0;
	}

// Implementation
	void Init()
	{
		// We need this style to prevent Windows from painting the button
		ModifyStyle(0, BS_OWNERDRAW);

		//if(m_ImageList.m_hImageList != NULL && (m_dwExtendedStyle & BMPBTN_AUTOSIZE) != 0)
		//	SizeToImage();
	}
	void SetToolTip(LPCTSTR lpszText)
	{
		// create a tool tip
		if (!m_tip.IsWindow())
		{
			m_tip.Create(m_hWnd, rcDefault, NULL, WS_POPUP | TTS_ALWAYSTIP | TTS_NOPREFIX);
		}
		//
		m_tip.AddTool(m_hWnd, lpszText);
	}
	void TooltipRelayEvent()	
	{
		if (!m_tip.IsWindow())
		{
			return;
		}
		const MSG* pMsg = GetCurrentMessage();
		if (pMsg)
		{
			MSG msg = *pMsg;
			m_tip.RelayEvent(&msg);
		}
	}
	BOOL StartTrackMouseLeave()
	{
		TRACKMOUSEEVENT tme = { 0 };
		tme.cbSize = sizeof(tme);
		tme.dwFlags = TME_LEAVE;
		tme.hwndTrack = m_hWnd;
		return _TrackMouseEvent(&tme);
	}

	bool IsHoverMode() const
	{
		return ((m_dwExtendedStyle & BMPBTN_HOVER) != 0);
	}
};


class CMyBitmapButton : public CMyBitmapButtonImpl<CMyBitmapButton>
{
public:
	DECLARE_WND_SUPERCLASS(_T("WTL_BitmapButton"), GetWndClassName())

	CMyBitmapButton(DWORD dwExtendedStyle = BMPBTN_AUTOSIZE, HIMAGELIST hImageList = NULL) : 
		CMyBitmapButtonImpl<CMyBitmapButton>(dwExtendedStyle, hImageList)
	{ }
};