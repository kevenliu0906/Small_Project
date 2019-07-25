#if !defined(AFX_STATICEX_H__B2897C1C_609A_4675_A086_4148A67DE37B__INCLUDED_)
#define AFX_STATICEX_H__B2897C1C_609A_4675_A086_4148A67DE37B__INCLUDED_

#include "strsafe.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StaticEx.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStaticEx window

#define STATIC_RESULT_FONT_SIZE		42
#define STATIC_FONT_SIZE			18

#define STATIC_TEXT_COLOR	RGB(0x00, 0x00, 0xFF)
#define STATIC_BK_COLOR		RGB(0x00, 0xC0, 0x00)
#define STATIC_OBK_COLOR	RGB(0xDF, 0xDF, 0xDF)

#define PASS_BK_COLOR		RGB(0x00, 0xC0, 0x00)
#define PASS_FR_COLOR		RGB(0xFF, 0xFF, 0xFF)
#define FAIL_BK_COLOR		RGB(0xFF, 0x00, 0x00)
#define FAIL_FR_COLOR		RGB(0x00, 0x00, 0xFF)
#define TIP_BK_COLOR		RGB(0x00, 0x00, 0xC0)
#define TIP_FR_COLOR		RGB(0xFF, 0xFF, 0xFF)
#define COLOR_GREEN			RGB(0x00, 0xC0, 0x00)
#define COLOR_BLACK			RGB(0x00, 0x00, 0x00)
#define COLOR_BLUE 			RGB(0x00, 0x00, 0xFF)
#define COLOR_BLUE2			RGB(0x00, 0x00, 0x80)
#define COLOR_BLUE3			RGB(0x00, 0x80, 0xFF)
#define COLOR_YELLOW    	RGB(0xFF, 0xFF, 0x00)
#define COLOR_YELLOW2    	RGB(0xCC, 0xCC, 0x00)
#define COLOR_WHITE  		RGB(0xFF, 0xFF, 0xFF)
#define COLOR_GRAY  		RGB(212, 208, 200)
#define COLOR_TP  		    RGB(100, 89, 73)
//#define COLOR_PURPLE  		RGB(0xAE, 0x00, 0xAE)
#define COLOR_PURPLE  		RGB(0xAA, 0x12, 0xDB)
#define COLOR_PURPLE2  		RGB(0xCE, 0x00, 0xCE)
#define COLOR_MAGENTA 		RGB(0xFF, 0x00, 0xFF)
#define COLOR_RED           FAIL_BK_COLOR

class CStaticEx : public CStatic
{
    // Construction
public:
    CStaticEx();
    virtual ~CStaticEx();

    // Attributes
public:

    // Operations
public:

    // Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CStaticEx)
protected:
    virtual void PreSubclassWindow();
    //}}AFX_VIRTUAL

    // Implementation
public:
    VOID SetWindowTextEx (LPCTSTR _lpszText, UINT _uAlign = DT_CENTER);
    VOID SetWindowText (LPCTSTR _lpszText, UINT _uAlign, BOOL _bBold = TRUE, 
        COLORREF _crFr = TIP_FR_COLOR, COLORREF _crBk = TIP_BK_COLOR,
        INT _nSize = STATIC_FONT_SIZE);

    VOID SetBkColor(COLORREF _crBkColor);
    VOID SetFontName(LPCTSTR _lpszFontName);
    VOID SetFontSize(INT _nSize);
    VOID SetFontItalic(BOOL _bItalic = TRUE);
    VOID SetFontUnderline(BOOL _bUnderline = TRUE);
    VOID SetFontBold(BOOL _bBold = TRUE);
    VOID SetTextColor(COLORREF _crText);

    VOID FlashText(BOOL _bFlash = TRUE);
    // Generated message map functions
protected:
    //{{AFX_MSG(CStaticEx)
    afx_msg void OnPaint();
    afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()

protected:
    VOID ReconstructFont();
    BOOL RedrawWindow (LPCRECT lpRectUpdate = NULL, CRgn* prgnUpdate = NULL, UINT flags = RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);

    CFont	m_Font;
    LOGFONT	m_lf;

    CBrush	m_BrushBackgroud;
    CBrush	m_BrushWnd;

    COLORREF	m_crTextColor;

    BOOL		m_bFlash;
    UINT_PTR	m_uFlashTimeId;
    INT			m_nFlashCount;

    CFont       m_FontUser;

    //bro+ 20151015
    CString		m_strText;
    UINT			m_uAlign;

public:
    void SetTextStyle(LPCTSTR _lpszText, COLORREF _crText, COLORREF _crBk, UINT _uAlign = DT_LEFT, BOOL _bBold = TRUE);
    LPCTSTR CStaticEx::GetWindowTextEx();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATICEX_H__B2897C1C_609A_4675_A086_4148A67DE37B__INCLUDED_)