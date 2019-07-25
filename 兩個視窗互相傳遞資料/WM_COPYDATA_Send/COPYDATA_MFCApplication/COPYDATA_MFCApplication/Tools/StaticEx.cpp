// StaticEx.cpp : implementation file
//

#include "stdafx.h"
#include <windowsx.h>
#include "StaticEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStaticEx

CStaticEx::CStaticEx(): m_uAlign(DT_LEFT), m_bFlash(FALSE), m_uFlashTimeId(1), m_nFlashCount(0)
{
    m_crTextColor = GetSysColor(COLOR_WINDOWTEXT);
    m_BrushBackgroud.CreateSolidBrush(GetSysColor(COLOR_3DFACE));
    m_BrushWnd.CreateSolidBrush(GetSysColor(COLOR_3DFACE));

    memset(&m_lf, 0, sizeof(LOGFONT));
    m_FontUser.CreateFont (-16, 0, 0, 0, NULL, FALSE, FALSE,0,0,0,0,0,0, _T("Courier New"));
    ::GetObject(m_FontUser, sizeof(m_lf), &m_lf);
    m_Font.CreateFontIndirect(&m_lf);
}

CStaticEx::~CStaticEx()
{
}


BEGIN_MESSAGE_MAP(CStaticEx, CStatic)
    //{{AFX_MSG_MAP(CStaticEx)
    ON_WM_PAINT()
    ON_WM_CTLCOLOR_REFLECT()
    ON_WM_TIMER()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStaticEx message handlers

void CStaticEx::PreSubclassWindow() 
{

    CStatic::PreSubclassWindow();

    DWORD dwStyle = GetStyle();
    dwStyle |= WS_CHILD | WS_TABSTOP;
    ModifyStyle(0, dwStyle);
}

void CStaticEx::OnPaint() 
{
    CPaintDC dc(this); // device context for painting
    CRect rtClient;

    INT nSaveDC = dc.SaveDC();

    GetClientRect(&rtClient);

    // set environment
    dc.SetBkMode(TRANSPARENT);
    dc.SelectObject(&m_Font);
    dc.SetTextColor(m_crTextColor);

    if (0 == m_nFlashCount)
    {
        dc.SelectObject(&m_BrushBackgroud);
        dc.FillRect(&rtClient, &m_BrushBackgroud);
    }
    else
    {
        dc.SelectObject(&m_BrushWnd);
        dc.FillRect(&rtClient, &m_BrushWnd);
    }

    CSize sizeText;
    CRect rtOutput;
    sizeText = dc.GetTextExtent(m_strText);
    if (!m_strText.IsEmpty())
    {
        rtOutput.top = (rtClient.Height() - sizeText.cy) / 2;
        rtOutput.bottom = rtOutput.top + sizeText.cy + 1;
        if (rtOutput.top < 0)
        {
            rtOutput.top = 0;
            rtOutput.bottom = rtClient.bottom;
        }
        rtOutput.left = 0;
        rtOutput.right = rtClient.right;
        dc.DrawText(m_strText, &rtOutput, m_uAlign);
    }

    dc.RestoreDC(nSaveDC);
}

HBRUSH CStaticEx::CtlColor(CDC* pDC, UINT nCtlColor) 
{
    HBRUSH hbr = NULL;

    if (CTLCOLOR_STATIC == nCtlColor)
    {
        pDC->SelectObject(&m_Font);
        pDC->SetTextColor(m_crTextColor);
        pDC->SetBkMode(TRANSPARENT);
        hbr = m_BrushBackgroud;
    }
    else
    {
        hbr = m_BrushWnd;
    }
    return hbr;
}

VOID CStaticEx::ReconstructFont()
{
    m_Font.DeleteObject();
    m_Font.CreateFontIndirect(&m_lf);
}

VOID CStaticEx::SetWindowText (LPCTSTR _lpszText, UINT _uAlign, BOOL _bBold, 
    COLORREF _crFr, COLORREF _crBk,
    INT _nSize)
{
    LPTSTR lpszTemp = NULL;
    LPTSTR lpszFind = (LPTSTR)_tcschr(_lpszText, _T('&'));
    LPCTSTR lpszPre = _lpszText;
    size_t nBytes = 0;

    if (NULL != lpszFind)
    {// '&' symbol
        m_strText.Empty();
        lpszTemp = m_strText.GetBuffer((lstrlen(_lpszText) * 2 + 1) * sizeof(TCHAR));
        lpszPre = _lpszText;
        while (NULL != lpszFind)
        {
            nBytes = (lpszFind - lpszPre) * sizeof(TCHAR);
            CopyMemory(lpszTemp, lpszPre, nBytes);

            lpszTemp += (lpszFind - lpszPre);
            lpszTemp[0] = _T('&');
            lpszTemp++;
            lpszTemp[0] = _T('&'); // add '&' symbol
            lpszTemp++;

            lpszFind++;
            lpszPre = lpszFind;
            lpszFind = _tcschr(lpszFind, _T('&'));
        }
        lpszTemp[0] = _T('\0');
        StringCbCat(lpszTemp, (lstrlen(_lpszText) * 2 + 1) * sizeof(TCHAR), lpszPre);

        m_strText.ReleaseBuffer();
    }
    else
    {
        m_strText = _lpszText;
    }

    m_uAlign = _uAlign;
    m_crTextColor = _crFr;
    m_BrushBackgroud.DeleteObject();
    m_BrushBackgroud.CreateSolidBrush(_crBk);

    _nSize *= -1;
    m_lf.lfHeight = _nSize;
    m_lf.lfWeight = _bBold ? FW_BOLD: FW_NORMAL;
    ReconstructFont();	

    RedrawWindow();

    //bro- 20150728
    //CStatic::SetWindowText(_lpszText);
}

VOID CStaticEx::SetWindowTextEx(LPCTSTR _lpszText, UINT _uAlign)
{
    LPTSTR lpszTemp = NULL;
    LPTSTR lpszFind = (LPTSTR)_tcschr(_lpszText, _T('&'));
    LPCTSTR lpszPre = _lpszText;
    size_t nBytes = 0;

    if (NULL != lpszFind)
    {// '&' symbol
        m_strText.Empty();
        lpszTemp = m_strText.GetBuffer((lstrlen(_lpszText) * 2 + 1) * sizeof(TCHAR));
        lpszPre = _lpszText;
        while (NULL != lpszFind)
        {
            nBytes = (lpszFind - lpszPre) * sizeof(TCHAR);
            CopyMemory(lpszTemp, lpszPre, nBytes);

            lpszTemp += (lpszFind - lpszPre);
            lpszTemp[0] = _T('&');
            lpszTemp++;
            lpszTemp[0] = _T('&'); // add '&' symbol
            lpszTemp++;

            lpszFind++;
            lpszPre = lpszFind;
            lpszFind = _tcschr(lpszFind, _T('&'));
        }
        lpszTemp[0] = _T('\0');
        StringCbCat(lpszTemp, (lstrlen(_lpszText) * 2 + 1) * sizeof(TCHAR), lpszPre);

        m_strText.ReleaseBuffer();
    }
    else
    {
        m_strText = _lpszText;
    }
    m_uAlign = _uAlign;
    RedrawWindow();

    //bro- 20150728
    //CStatic::SetWindowText(_lpszText);
}

//bro+ 20151015
LPCTSTR CStaticEx::GetWindowTextEx()
{
    return m_strText;
}

VOID CStaticEx::SetTextColor(COLORREF _crText)
{
    m_crTextColor = _crText;

    RedrawWindow();
}

VOID CStaticEx::SetBkColor(COLORREF _crBkColor)
{
    m_BrushBackgroud.DeleteObject();
    m_BrushBackgroud.CreateSolidBrush(_crBkColor);

    RedrawWindow();
}

VOID CStaticEx::SetFontBold(BOOL _bBold)
{
    m_lf.lfWeight = _bBold ? FW_BOLD: FW_NORMAL;
    ReconstructFont();
    RedrawWindow();
}

VOID CStaticEx::SetFontUnderline(BOOL _bUnderline)
{
    m_lf.lfUnderline = (BYTE)_bUnderline;
    ReconstructFont();
    RedrawWindow();
}

VOID CStaticEx::SetFontItalic(BOOL _bItalic)
{
    m_lf.lfItalic = (BYTE)_bItalic;
    ReconstructFont();
    RedrawWindow();
}

VOID CStaticEx::SetFontSize(INT _nSize)
{
    _nSize *= -1;
    m_lf.lfHeight = _nSize;
    ReconstructFont();
    RedrawWindow();
}

VOID CStaticEx::SetFontName(LPCTSTR _lpszFontName)
{
    StringCbCopy(m_lf.lfFaceName, sizeof(TCHAR) * LF_FACESIZE, _lpszFontName);
    ReconstructFont();
    RedrawWindow();
}


VOID CStaticEx::FlashText(BOOL _bFlash)
{
    m_bFlash = _bFlash;
    if (m_bFlash)
    {
        SetTimer(m_uFlashTimeId, 600, NULL);
    }
    else
    {
        //::KillTimer(GetSafeHwnd(), m_uFlashTimeId);
        KillTimer(m_uFlashTimeId);
        m_nFlashCount = 0;
    }
    RedrawWindow();
}

void CStaticEx::OnTimer(UINT nIDEvent) 
{
    CStatic::OnTimer(nIDEvent);
    m_nFlashCount++;
    m_nFlashCount %= 2;

    RedrawWindow();
}

BOOL CStaticEx::RedrawWindow (LPCRECT lpRectUpdate , CRgn* prgnUpdate, UINT flags)
{
    BOOL bRedraw = FALSE;
    if (NULL != m_hWnd)
    {
        CStatic::RedrawWindow(lpRectUpdate, prgnUpdate, flags);
    }

    return bRedraw;
}

void CStaticEx::SetTextStyle(LPCTSTR _lpszText, COLORREF _crText, COLORREF _crBk, UINT _uAlign, BOOL _bBold)
{
    SetWindowTextEx(_lpszText);
    m_uAlign = _uAlign;
    SetTextColor(_crText);
    SetBkColor(_crBk);
    SetFontBold(_bBold);
}