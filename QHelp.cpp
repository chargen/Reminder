// QHelp.cpp : implementation file
//

#include "stdafx.h"
#include "Reminder.h"
#include "QHelp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CQHelp dialog


CQHelp::CQHelp(CWnd* pParent /*=NULL*/)
	: CDialog(CQHelp::IDD, pParent)
{
	//{{AFX_DATA_INIT(CQHelp)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CQHelp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CQHelp)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CQHelp, CDialog)
	//{{AFX_MSG_MAP(CQHelp)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQHelp message handlers
