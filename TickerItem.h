#if !defined(AFX_TICKERITEM_H__02A96CA1_5307_11D2_A0D0_CDBF8D23E02D__INCLUDED_)
#define AFX_TICKERITEM_H__02A96CA1_5307_11D2_A0D0_CDBF8D23E02D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// TickerItem.h : header file
//

#include "shared.h"

/////////////////////////////////////////////////////////////////////////////
// CTickerItem window

class CTickerItem : public CObject
{
// Construction
public:
	CTickerItem();
	virtual ~CTickerItem();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTickerItem)
	//}}AFX_VIRTUAL

// Implementation
public:
	CString GetMessage();
	CDC* GetBackDC();
	int GetDCWidth();
	void AddItemIcon(UINT nID,int X, int Y);
	void SetTextColor(COLORREF mTextColor);
	void SetBackgroundColor(COLORREF mColor);
	void Create(int xOffset,int yOffset,CWnd* pWnd);
	void SetMessageFont(UINT nPointSize,LPCTSTR strFontName);
	void SetTickerMessage(LPCTSTR str);
	void SetTickerMessage(CString& str);

protected:
	HICON m_hIcon;
	COLORREF m_BackgroundColor;
	COLORREF m_TextColor;
	CWnd* m_HostWnd;
	CFont* m_pMessageFont;
	CFont* m_pOldFont;
	int m_nXOffset;
	int m_nYOffset;
	CRect m_SourceRect;
	CDC* m_pBackDC;
	CBitmap* m_pBackBits;
	CString m_strMessage;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TICKERITEM_H__02A96CA1_5307_11D2_A0D0_CDBF8D23E02D__INCLUDED_)
