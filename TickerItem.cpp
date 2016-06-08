// TickerItem.cpp : implementation file
//

#include "stdafx.h"
#include "Reminder.h"
#include "TickerItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTickerItem

CTickerItem::CTickerItem()
{
	m_pBackBits = NULL;
	m_pBackDC = NULL;
	m_pMessageFont = NULL;
}

CTickerItem::~CTickerItem()
{
	m_pBackDC->SelectObject(m_pOldFont);
	DeletePtr(m_pMessageFont);
	DeletePtr(m_pBackBits);
	DeletePtr(m_pBackDC);
}

/////////////////////////////////////////////////////////////////////////////
// CTickerItem message handlers

void CTickerItem::SetTickerMessage(CString & str)
{	
	m_strMessage = str;

	m_SourceRect.left += m_nXOffset + 32;
	m_SourceRect.top += m_nYOffset;

	CSize sz = m_pBackDC->GetTextExtent(str);
	m_SourceRect.right = m_SourceRect.left + sz.cx+4 + 64;

	m_pBackDC->SetTextColor(m_TextColor);
	m_pBackDC->TextOut(m_SourceRect.left,m_SourceRect.top,str);
}

void CTickerItem::SetTickerMessage(LPCTSTR str)
{
	m_strMessage = str;

	m_SourceRect.left += m_nXOffset;
	m_SourceRect.top += m_nYOffset;

	CSize sz = m_pBackDC->GetTextExtent(m_strMessage);
	m_SourceRect.right = m_SourceRect.left + sz.cx+4 + 64;
}

void CTickerItem::SetMessageFont(UINT nPointSize, LPCTSTR strFontName)
{
	CreatePtr(m_pMessageFont);
	m_pMessageFont->CreatePointFont(nPointSize,strFontName);
	m_pOldFont = m_pBackDC->SelectObject(m_pMessageFont);
}

void CTickerItem::Create(int xOffset, int yOffset,CWnd* pWnd)
{
	m_HostWnd = pWnd;
	m_nXOffset = xOffset;
	m_nYOffset = yOffset;

	CreatePtr(m_pBackDC);
	m_pBackDC->CreateCompatibleDC(pWnd->GetDC());

	pWnd->GetClientRect(&m_SourceRect);

	CreatePtr(m_pBackBits);
	m_pBackBits->CreateCompatibleBitmap(pWnd->GetDC(),m_SourceRect.Width(),m_SourceRect.Height());
	m_pBackDC->SelectObject(m_pBackBits);
}

void CTickerItem::SetBackgroundColor(COLORREF mColor)
{
	m_BackgroundColor = mColor;
	m_pBackDC->FillSolidRect(&m_SourceRect,mColor);
}

void CTickerItem::SetTextColor(COLORREF mTextColor)
{
	m_TextColor = mTextColor;
}

void CTickerItem::AddItemIcon(UINT nID, int X, int Y)
{
	m_hIcon = LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(nID));
	m_pBackDC->DrawIcon(0,0,m_hIcon);

}

int CTickerItem::GetDCWidth()
{
	return m_SourceRect.Width();
}

CDC* CTickerItem::GetBackDC()
{
	return m_pBackDC;
}

CString CTickerItem::GetMessage()
{
	return m_strMessage;
}
