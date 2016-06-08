// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Reminder.h"
#include "TickerItem.h"
#include "MainFrm.h"
#include <cfgmgr32.h>

//extern "C"
//{
//#define NTKERNELAPI DECLSPEC_IMPORT     
VOID KeQuerySystemTime(OUT PLARGE_INTEGER  CurrentTime);
//}

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_ACTIVATE()
	ON_WM_WINDOWPOSCHANGED()
//	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_SCROLLRIGHT, OnScrollRight)
	ON_BN_CLICKED(IDC_SCROLLLEFT, OnScrollLeft)
	ON_BN_CLICKED(IDC_CLOSE, OnClose)
	ON_BN_CLICKED(IDC_EDGETOP, OnTopEdge)
	ON_BN_CLICKED(IDC_EDGEBOTTOM, OnBottomEdge)
	ON_BN_CLICKED(IDC_PROPERTIES, OnProperties)
	ON_BN_CLICKED(IDC_QHELP, OnHelp)
	ON_MESSAGE(WM_ACCESSBAR,OnAccessBar)
	ON_MESSAGE(WM_SLIDERSET,OnSliderSet)
	ON_MESSAGE(WM_DISPLAYCHANGE,OnDisplayChange)
	ON_WM_PAINT()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	m_bDirection = true;
	m_bTimerActive = false;
	m_nTimerValue = 20;
}

CMainFrame::~CMainFrame()
{
	APPBARDATA abd;

	abd.cbSize = sizeof(APPBARDATA);
	abd.hWnd = GetSafeHwnd();

	SHAppBarMessage(ABM_REMOVE,&abd);

	m_InfoPos = m_MsgList.GetHeadPosition();

	delete m_MainBitmap;
	delete m_MainDC;

	while(m_InfoPos)
	{
		m_pCurrentItem = (CTickerItem*)m_MsgList.GetNext(m_InfoPos);			
		delete m_pCurrentItem;
	}
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
//	cs.style &= ~WS_BORDER;
	cs.style &= ~WS_DLGFRAME;
	return CFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	CRect rc;

	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_bIsScrolling = false;

	APPBARDATA abd;

	abd.cbSize = sizeof(APPBARDATA);
	abd.hWnd = GetSafeHwnd();
	abd.uCallbackMessage = WM_ACCESSBAR;
	if(!SHAppBarMessage(ABM_NEW,&abd)) return -1;

	m_btnClose.Create(NULL, WS_VISIBLE | WS_CHILD | BS_OWNERDRAW,
		CRect(0,0,0,0), this, IDC_CLOSE);
	m_btnClose.LoadBitmaps(IDB_BTNCLOSEUP,IDB_CLOSEDOWN);
	m_btnClose.SizeToContent();

	m_btnProperties.Create(NULL, WS_VISIBLE | WS_CHILD | BS_OWNERDRAW,
		CRect(0,0,0,0), this, IDC_PROPERTIES);
	m_btnProperties.LoadBitmaps(IDB_PROPUP,IDB_PROPDOWN);
	m_btnProperties.SizeToContent();

	m_btnHelp.Create(NULL, WS_VISIBLE | WS_CHILD | BS_OWNERDRAW,
		CRect(0,0,0,0), this, IDC_QHELP);
	m_btnHelp.LoadBitmaps(IDB_HELPUP,IDB_HELPDOWN);
	m_btnHelp.SizeToContent();

	m_btnScrollRight.Create(NULL, WS_VISIBLE | WS_CHILD | BS_OWNERDRAW,
		CRect(21,2,20,20), this, IDC_SCROLLRIGHT);
	m_btnScrollRight.LoadBitmaps(IDB_BTNRUP,IDB_BTNRDOWN);
	m_btnScrollRight.SizeToContent();

	m_btnScrollLeft.Create(NULL, WS_VISIBLE | WS_CHILD | BS_OWNERDRAW,
		CRect(0,2,20,20), this, IDC_SCROLLLEFT);
	m_btnScrollLeft.LoadBitmaps(IDB_BTNLUP,IDB_BTNLDOWN);
	m_btnScrollLeft.SizeToContent();

	m_btnEdgeTop.Create(NULL, WS_VISIBLE | WS_CHILD | BS_OWNERDRAW,
		CRect(42,2,20,20), this, IDC_EDGETOP);
	m_btnEdgeTop.LoadBitmaps(IDB_TOPUP,IDB_TOPDOWN);
	m_btnEdgeTop.SizeToContent();
	
	m_btnEdgeBottom.Create(NULL, WS_VISIBLE | WS_CHILD | BS_OWNERDRAW,
		CRect(63,2,20,20), this, IDC_EDGEBOTTOM);
	m_btnEdgeBottom.LoadBitmaps(IDB_BOTTOMUP,IDB_BOTTOMDOWN);
	m_btnEdgeBottom.SizeToContent();
	
	CalcPosition(m_uEdge = ABE_BOTTOM);

	m_pCurrentItem = NULL;
	m_InfoPos = 0;
	m_bInitialPaint = false;

	CString str = "Sample 1";
	AddMessage(str,RGB(0,255,0),"Sherwood");

	str = "Sample 2";
	AddMessage(str,RGB(0,255,0),"Ariel");
	
	str = "Sample 3";
	AddMessage(str,RGB(0,255,0),"Ariel");
	
	str = "Sample 4";
	AddMessage(str,RGB(0,255,0),"Gaslight");

	return 0;
}

void CMainFrame::CalcPosition(UINT uEdge)
{
	APPBARDATA abd;

	abd.cbSize = sizeof(APPBARDATA);
	abd.hWnd = GetSafeHwnd();
	abd.uEdge = uEdge;

	CRect rc(0,0,GetSystemMetrics(SM_CXSCREEN),GetSystemMetrics(SM_CYSCREEN));
	abd.rc = rc;

	SHAppBarMessage(ABM_QUERYPOS,&abd);

	switch(uEdge)
	{
		case ABE_TOP:
			abd.rc.bottom = abd.rc.top + DEF_BAR_HEIGHT;
			break;
		case ABE_BOTTOM:
			abd.rc.top = abd.rc.bottom - DEF_BAR_HEIGHT;
			break;
	}

	SHAppBarMessage(ABM_SETPOS,&abd);
	MoveWindow(&abd.rc);

	CalcChildren(uEdge);
}

LRESULT CMainFrame::OnAccessBar(WPARAM wParam, LPARAM lParam)
{
	UINT uState;
	APPBARDATA abd;

	abd.cbSize = sizeof(APPBARDATA);
	abd.hWnd = GetSafeHwnd();

	switch(wParam)
	{
		case ABN_STATECHANGE:
			uState = SHAppBarMessage(ABM_GETSTATE,&abd);
			SetWindowPos((ABS_ALWAYSONTOP & uState) ? &wndTopMost:&wndBottom,
				0,0,0,0,SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
			break;

		case ABN_FULLSCREENAPP:
			uState = SHAppBarMessage(ABM_GETSTATE,&abd);

			if(lParam)
			{
				SetWindowPos((ABS_ALWAYSONTOP & uState) ? &wndTopMost:&wndBottom,
					0,0,0,0,SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
			}
			else
			{
				if(uState & ABS_ALWAYSONTOP)
				{
					SetWindowPos(&wndTopMost,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
				}
			}

		case ABN_POSCHANGED:
			CalcPosition(m_uEdge);
			break;
	}

	return 0L;
}


void CMainFrame::OnClose() 
{
	KillPeriodicTimer();
	APPBARDATA abd;
	abd.cbSize = sizeof(APPBARDATA);
	abd.hWnd = GetSafeHwnd();
	SHAppBarMessage(ABM_REMOVE, &abd);
	DestroyWindow();
}

void CMainFrame::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) 
{
	CFrameWnd::OnActivate(nState, pWndOther, bMinimized);
	
	APPBARDATA abd;
	abd.cbSize = sizeof(APPBARDATA);
	abd.hWnd = GetSafeHwnd();
	SHAppBarMessage(ABM_ACTIVATE, &abd);
}

void CMainFrame::OnWindowPosChanged(WINDOWPOS FAR* lpwndpos) 
{
	CFrameWnd::OnWindowPosChanged(lpwndpos);
	
	APPBARDATA abd;
	abd.cbSize = sizeof(APPBARDATA);
	abd.hWnd = GetSafeHwnd();
	SHAppBarMessage(ABM_WINDOWPOSCHANGED, &abd);
}

void CMainFrame::CalcChildren(UINT uEdge)
{
	if (uEdge == ABE_TOP || uEdge == ABE_BOTTOM)
	{
		CRect btnrc;
		m_btnClose.GetClientRect(&btnrc);
		m_nCloseWidth = btnrc.Width();
		btnrc.OffsetRect(GetSystemMetrics(SM_CXSCREEN)-m_nCloseWidth-6, 2);	
		m_btnClose.MoveWindow(btnrc);

		m_btnProperties.GetClientRect(&btnrc);
		m_nCloseWidth = btnrc.Width()*3;
		btnrc.OffsetRect(GetSystemMetrics(SM_CXSCREEN)-m_nCloseWidth-8, 2);	
		m_btnProperties.MoveWindow(btnrc);

		m_btnHelp.GetClientRect(&btnrc);
		m_nCloseWidth = btnrc.Width()*2;
		btnrc.OffsetRect(GetSystemMetrics(SM_CXSCREEN)-m_nCloseWidth-7, 2);	
		m_btnHelp.MoveWindow(btnrc);
	}
}

void CMainFrame::AddMessage(CString str,COLORREF nText,LPCTSTR strFont)
{
	CTickerItem* pItem;

	CreatePtr(pItem);
	pItem->Create(0,2,this);
	pItem->SetMessageFont(120,strFont);
	pItem->SetBackgroundColor(RGB(0,0,0));
	pItem->SetTextColor(nText);
	pItem->AddItemIcon(IDI_STAR,0,0);
	pItem->SetTickerMessage(str);

	m_MsgList.AddTail(pItem);
}

#define TARGET_RESOLUTION 1         // 1-millisecond target resolution

BOOL CMainFrame::InitTimer()
{
	TIMECAPS tc;
	UINT wTimerRes;
	CWnd* pWnd = GetDesktopWindow();
	if (timeGetDevCaps(&tc, sizeof(TIMECAPS)) != TIMERR_NOERROR) 
	{
		return false;
	}

	if(m_bTimerActive) KillPeriodicTimer();
	m_bTimerActive = false;

	wTimerRes = min(max(tc.wPeriodMin, TARGET_RESOLUTION), tc.wPeriodMax);
	timeBeginPeriod(wTimerRes); 

    m_mTimerID = timeSetEvent(
        m_nTimerValue,                    // delay
        wTimerRes,                     // resolution (global variable)
        (LPTIMECALLBACK)PeriodicTimer,               // callback function
        NULL,                  // user data
        TIME_PERIODIC );                // single timer event
    
	if(! m_mTimerID) 
	{
		return false;
	}

	m_bTimerActive = true;
	return true;
}

void CMainFrame::KillPeriodicTimer()
{
	MMRESULT mRes;

	if(!m_bTimerActive) return;

	if(m_mTimerID) 
	{            
		// is timer event pending?
        mRes = timeKillEvent(m_mTimerID);  // cancel the event
		if(mRes==TIMERR_NOERROR) 
		{
//			TRACE("Timer killed\n");
			m_bTimerActive = false;
			m_mTimerID = 0;
		}
//		else TRACE("Timer NOT killed\n");
	}
}

BOOL bEntry=false;
CMainFrame* g_pWnd=NULL;
HWND hWnd;
CWnd pWnd;
bool m_bPNPActive=FALSE;
DWORD dwRet;

void CALLBACK PeriodicTimer(UINT wTimerID,UINT msg,DWORD dwUser,DWORD dw1,DWORD dw2) 
{ 
	CRect rc;
	CRect rcScroll,rcClip,rcUpdate;
	CRgn rgnUpdate;
//	LARGE_INTEGER time;

	if(bEntry) 
	{
		g_pWnd->KillPeriodicTimer();
//		TRACE("Entry\n");
		return;
	}

//	KeQuerySystemTime(&time);

	if(!g_pWnd) return;

	bEntry = true;

	HDC hDC = GetDC(g_pWnd->GetSafeHwnd());
	CDC dc;
	dc.Attach(hDC);
	
	g_pWnd->GetClientRect(rc);
	rcScroll = rc;
	rcClip = rcScroll;

	rcClip.right -= g_pWnd->m_nCloseWidth+5;
	rcClip.left += CONTROLAREA_WIDTH;
	
	if(g_pWnd->m_bDirection) g_pWnd->m_MainDC->ScrollDC(-1,0,&rcScroll,&rcClip,&rgnUpdate,&rcUpdate);
	else g_pWnd->m_MainDC->ScrollDC(1,0,&rcScroll,&rcClip,&rgnUpdate,&rcUpdate);

	if(!g_pWnd->m_bIsScrolling)
	{
		if(!g_pWnd->m_MsgList.IsEmpty())
		{
			if(g_pWnd->m_InfoPos==NULL) 
			{
				g_pWnd->m_InfoPos = g_pWnd->m_MsgList.GetHeadPosition();
				g_pWnd->m_pCurrentItem = (CTickerItem*)g_pWnd->m_MsgList.GetNext(g_pWnd->m_InfoPos);			
			}  
			else
			{
				g_pWnd->m_pCurrentItem = (CTickerItem*)g_pWnd->m_MsgList.GetNext(g_pWnd->m_InfoPos);
			}
			
			g_pWnd->m_bIsScrolling = true;
			
			if(g_pWnd->m_bDirection) g_pWnd->m_nCurrentOffset = 0;
			else g_pWnd->m_nCurrentOffset = g_pWnd->m_pCurrentItem->GetDCWidth();
			
		}
	}
	else
	{
		if(g_pWnd->m_bDirection)
		{
			if(g_pWnd->m_nCurrentOffset<=g_pWnd->m_pCurrentItem->GetDCWidth())
			{
				g_pWnd->m_MainDC->BitBlt(rc.right-(g_pWnd->m_nCloseWidth+6),0,1,rc.Height(), g_pWnd->m_pCurrentItem->GetBackDC(),g_pWnd->m_nCurrentOffset,0, SRCCOPY);
				dc.BitBlt(0,0,rc.Width(),rc.Height(),g_pWnd->m_MainDC,0,0,SRCCOPY);
				g_pWnd->m_nCurrentOffset++;
			}
			else
			{
				g_pWnd->m_nCurrentOffset = 0;
				g_pWnd->m_bIsScrolling = false;
			}
		}
		else
		{
			if(g_pWnd->m_nCurrentOffset>=0)
			{
				g_pWnd->m_MainDC->BitBlt(rc.left+CONTROLAREA_WIDTH,0,1,rc.Height(), g_pWnd->m_pCurrentItem->GetBackDC(),g_pWnd->m_nCurrentOffset,0, SRCCOPY);
				dc.BitBlt(0,0,rc.Width(),rc.Height(),g_pWnd->m_MainDC,0,0,SRCCOPY);
				g_pWnd->m_nCurrentOffset--;
			}
			else
			{
				g_pWnd->m_nCurrentOffset = g_pWnd->m_pCurrentItem->GetDCWidth();
				g_pWnd->m_bIsScrolling = false;
			}
		}
	}

	dc.Detach();
	ReleaseDC(g_pWnd->GetSafeHwnd(),hDC);
	bEntry = false;
} 

void CMainFrame::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CFrameWnd::OnLButtonDown(nFlags, point);
}

void CMainFrame::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CFrameWnd::OnLButtonUp(nFlags, point);
}

void CMainFrame::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CFrameWnd::OnMouseMove(nFlags, point);
}

void CMainFrame::OnScrollRight() 
{
	CRect rc;

	KillPeriodicTimer();

	m_bDirection = false;

	if(m_bDirection) m_nCurrentOffset = 0;
	else m_nCurrentOffset = m_pCurrentItem->GetDCWidth();

	GetClientRect(&rc);
	rc.left += CONTROLAREA_WIDTH;
	m_MainDC->FillSolidRect(&rc,RGB(0,0,0));

	InitTimer();
}

void CMainFrame::OnScrollLeft() 
{
	CRect rc;

	KillPeriodicTimer();

	m_bDirection = true;

	if(m_bDirection) m_nCurrentOffset = 0;
	else m_nCurrentOffset = m_pCurrentItem->GetDCWidth();

	GetClientRect(&rc);
	rc.left += CONTROLAREA_WIDTH;
	m_MainDC->FillSolidRect(&rc,RGB(0,0,0));

	InitTimer();
}

void CMainFrame::OnTopEdge() 
{
	KillPeriodicTimer();
	CalcPosition(m_uEdge = ABE_TOP);
	InitTimer();
}

void CMainFrame::OnBottomEdge() 
{
	KillPeriodicTimer();
	CalcPosition(m_uEdge = ABE_BOTTOM);
	InitTimer();
}

LRESULT CMainFrame::OnDisplayChange(WPARAM wParam,LPARAM lParam)
{
	KillPeriodicTimer();

	CalcPosition(m_uEdge);

	// !!! Need more positioning work here... Re-Create DC's

	InitTimer();

	return 0;
}

void CMainFrame::OnProperties() 
{
	CProperties dlg(this);

	dlg.m_nTimerValue = m_nTimerValue;

	if(dlg.DoModal()==IDOK)
	{
	}
}

void CMainFrame::OnHelp() 
{
	CQHelp dlg;

	if(dlg.DoModal()==IDOK)
	{
	}
}

LRESULT CMainFrame::OnSliderSet(WPARAM wParam, LPARAM lParam)
{
	KillPeriodicTimer();

	m_nTimerValue = (int)wParam;

	InitTimer();
	return 0L;
}

void CMainFrame::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CRect rc;

	GetClientRect(&rc);

	if(!m_bInitialPaint)
	{
		m_MainDC = new CDC();
		if(m_MainDC)
		{
			g_pWnd = this;
			//g_pWnd->m_MainDC = m_MainDC;
			m_MainDC->CreateCompatibleDC(&dc);

			m_MainBitmap = new CBitmap();
			m_MainBitmap->CreateCompatibleBitmap(&dc,rc.Width(),rc.Height());
			m_MainDC->SelectObject(m_MainBitmap);
			m_MainDC->FillSolidRect(&rc,RGB(0,0,0));
			m_bInitialPaint = true;
			InitTimer();
		}
	}
}
