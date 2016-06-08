// Reminder.h : main header file for the REMINDER application
//

#if !defined(AFX_REMINDER_H__0C834D84_50B5_11D2_A0D0_AEBED1142A2E__INCLUDED_)
#define AFX_REMINDER_H__0C834D84_50B5_11D2_A0D0_AEBED1142A2E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CReminderApp:
// See Reminder.cpp for the implementation of this class
//

class CReminderApp : public CWinApp
{
public:
	CReminderApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReminderApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CReminderApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REMINDER_H__0C834D84_50B5_11D2_A0D0_AEBED1142A2E__INCLUDED_)
