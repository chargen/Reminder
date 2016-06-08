#if !defined(AFX_QHELP_H__0D897BE1_57A5_11D2_A0D0_C3692652042E__INCLUDED_)
#define AFX_QHELP_H__0D897BE1_57A5_11D2_A0D0_C3692652042E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// QHelp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CQHelp dialog

class CQHelp : public CDialog
{
// Construction
public:
	CQHelp(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CQHelp)
	enum { IDD = IDD_QHELP };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQHelp)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CQHelp)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QHELP_H__0D897BE1_57A5_11D2_A0D0_C3692652042E__INCLUDED_)
