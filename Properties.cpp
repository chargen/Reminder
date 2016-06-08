// Properties.cpp : implementation file
//

#include "stdafx.h"
#include "Reminder.h"
#include "Properties.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProperties dialog


CProperties::CProperties(CWnd* pParent /*=NULL*/)
	: CDialog(CProperties::IDD, pParent)
{
	m_pParent = pParent;
	//{{AFX_DATA_INIT(CProperties)
	//}}AFX_DATA_INIT
}


void CProperties::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProperties)
	DDX_Control(pDX, IDC_NOWLIST, m_ctlNowList);
	DDX_Control(pDX, IDC_SPEEDGROUP, m_ctlSpeedGroup);
	DDX_Control(pDX, IDC_SLIDER1, m_ctlSlider);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProperties, CDialog)
	//{{AFX_MSG_MAP(CProperties)
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProperties message handlers

void CProperties::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CString str;

	if(nPos>0)
	{
		str.Format("Scrolling Speed: %dms  ",nPos);
		m_ctlSpeedGroup.SetWindowText(str);
		m_pParent->PostMessage(WM_USER+2,nPos,0);
	}
	
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

BOOL CProperties::OnInitDialog() 
{
	CDC* pDC;
	CTickerItem* pItem;
	CString str;
	CSize sz;
	int nMaxX=0;

	CDialog::OnInitDialog();

	pDC = m_ctlNowList.GetDC();

	m_ctlSlider.SetPos(m_nTimerValue);
	m_ctlSlider.SetRange(3,50,TRUE);

	str.Format("Scrolling Speed: %dms  ",m_nTimerValue);
	m_ctlSpeedGroup.SetWindowText(str);

	CMainFrame* pWnd = (CMainFrame*)AfxGetMainWnd();

	POSITION pos;

	pos = pWnd->m_MsgList.GetHeadPosition();
	
	pItem = (CTickerItem*)pWnd->m_MsgList.GetNext(pos);

	while(pos)
	{
		str = pItem->GetMessage();
		
		sz = pDC->GetTextExtent(str);	
		if(sz.cx>nMaxX) nMaxX = sz.cx;

		m_ctlNowList.AddString(pItem->GetMessage());
		pItem = (CTickerItem*)pWnd->m_MsgList.GetNext(pos);
	}

	m_ctlNowList.SetHorizontalExtent(nMaxX-50);

	m_ctlNowList.ReleaseDC(pDC);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
