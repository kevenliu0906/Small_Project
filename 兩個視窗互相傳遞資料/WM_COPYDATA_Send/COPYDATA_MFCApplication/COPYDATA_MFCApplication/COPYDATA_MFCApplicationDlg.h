
// COPYDATA_MFCApplicationDlg.h : header file
//
#include "Tools\StaticEx.h"

#pragma once


// CCOPYDATA_MFCApplicationDlg dialog
class CCOPYDATA_MFCApplicationDlg : public CDialogEx
{
// Construction
public:
	CCOPYDATA_MFCApplicationDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COPYDATA_MFCAPPLICATION_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CEdit              m_Edit_Send_Data;
	CStaticEx          m_Static_Read_Data;
	afx_msg void OnBnClickedBtnSendData();
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	afx_msg void OnBnClickedBtnSendStructData();
};
