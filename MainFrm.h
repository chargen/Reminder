// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__0C834D88_50B5_11D2_A0D0_AEBED1142A2E__INCLUDED_)
#define AFX_MAINFRM_H__0C834D88_50B5_11D2_A0D0_AEBED1142A2E__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "TickerItem.h"
#include "mmsystem.h"
#include "properties.h"
#include "qhelp.h"

#define WM_ACCESSBAR (WM_USER+1)
#define WM_SLIDERSET (WM_USER+2)
#define BUTTON_WIDTH	75
#define BUTTON_HEIGHT 18
#define DEF_BAR_WIDTH (BUTTON_WIDTH + 10)
#define DEF_BAR_HEIGHT (BUTTON_HEIGHT + 10)

#define CONTROLAREA_WIDTH 83

void CALLBACK PeriodicTimer(UINT wTimerID,UINT msg,DWORD dwUser,DWORD dw1,DWORD dw2);

class CMainFrame : public CFrameWnd
{
public: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)
	void CalcChildren(UINT uEdge);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	void KillPeriodicTimer();
	BOOL InitTimer();
	void AddMessage(CString str,COLORREF nText,LPCTSTR strFont);
	void CalcPosition(UINT uEdge);
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg void OnScrollRight();
	afx_msg void OnScrollLeft();
	afx_msg void OnTopEdge();
	afx_msg void OnBottomEdge();
	afx_msg void OnProperties();
	afx_msg void OnHelp();
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnWindowPosChanged(WINDOWPOS FAR* lpwndpos);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg LRESULT OnDisplayChange(WPARAM wParam,LPARAM lParam);
	//}}AFX_MSG
	afx_msg LRESULT OnAccessBar(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnSliderSet(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()

public:
	int m_nTimerValue;
	int m_nCloseWidth;
	BOOL m_bTimerActive;
	BOOL m_bDirection;
	MMRESULT m_mTimerID;
	BOOL m_bInitialPaint;
	CBitmap* m_MainBitmap;
	CDC* m_MainDC;
	POSITION m_InfoPos;
	int m_nCurrentOffset;
	CTickerItem* m_pCurrentItem;
	BOOL m_bIsScrolling;
	CPtrList m_MsgList;
	CBitmapButton m_btnClose;
	CBitmapButton m_btnScrollLeft;
	CBitmapButton m_btnScrollRight;
	CBitmapButton m_btnEdgeTop;
	CBitmapButton m_btnEdgeBottom;
	CBitmapButton m_btnProperties;
	CBitmapButton m_btnHelp;
	UINT m_uEdge;
	afx_msg void OnPaint();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__0C834D88_50B5_11D2_A0D0_AEBED1142A2E__INCLUDED_)
