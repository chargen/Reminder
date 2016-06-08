// Reminder.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Reminder.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReminderApp

BEGIN_MESSAGE_MAP(CReminderApp, CWinApp)
	//{{AFX_MSG_MAP(CReminderApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReminderApp construction

CReminderApp::CReminderApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CReminderApp object

CReminderApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CReminderApp initialization

BOOL CReminderApp::InitInstance()
{
	AfxEnableControlContainer();

//	Enable3dControls();			// Call this when using MFC in a shared DLL

	CMainFrame* pMainWnd = new CMainFrame();
	if(pMainWnd==NULL) return false;

	m_pMainWnd = pMainWnd;

	if(!pMainWnd->Create(NULL,_T(""),WS_POPUP|WS_DLGFRAME|WS_CLIPCHILDREN,
		CFrameWnd::rectDefault,NULL,NULL,WS_EX_TOOLWINDOW)) return false;

	pMainWnd->ShowWindow(SW_SHOW);

	return TRUE;
}



