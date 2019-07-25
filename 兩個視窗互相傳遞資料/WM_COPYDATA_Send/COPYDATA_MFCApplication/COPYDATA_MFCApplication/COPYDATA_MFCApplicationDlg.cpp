
// COPYDATA_MFCApplicationDlg.cpp : implementation file
//

#include "stdafx.h"
#include "COPYDATA_MFCApplication.h"
#include "COPYDATA_MFCApplicationDlg.h"
#include "afxdialogex.h"
#include "DataDefine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//-------------- global   ----------------------------------------


//----------------------------------------------------------------

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCOPYDATA_MFCApplicationDlg dialog



CCOPYDATA_MFCApplicationDlg::CCOPYDATA_MFCApplicationDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_COPYDATA_MFCAPPLICATION_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCOPYDATA_MFCApplicationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_SEND_DATA, m_Edit_Send_Data);
	DDX_Control(pDX, IDC_STATIC_READ_DATA, m_Static_Read_Data);

}

BEGIN_MESSAGE_MAP(CCOPYDATA_MFCApplicationDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_SEND_DATA, &CCOPYDATA_MFCApplicationDlg::OnBnClickedBtnSendData)
	ON_WM_COPYDATA()
	ON_BN_CLICKED(IDC_BTN_SEND_STRUCT_DATA, &CCOPYDATA_MFCApplicationDlg::OnBnClickedBtnSendStructData)
END_MESSAGE_MAP()


// CCOPYDATA_MFCApplicationDlg message handlers

BOOL CCOPYDATA_MFCApplicationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	SetWindowText(_T("CopyData_Send"));

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCOPYDATA_MFCApplicationDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCOPYDATA_MFCApplicationDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCOPYDATA_MFCApplicationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//-------------------------------------------------------------------------------------------
void CCOPYDATA_MFCApplicationDlg::OnBnClickedBtnSendData()
{
	//------ Initial......
	CString          Data_cstr = _T("");
	COPYDATASTRUCT   cds;
	HWND             OtherWindow_hwnd = NULL;

	//------------------------

	m_Edit_Send_Data.GetWindowText(Data_cstr);

	/////--> For send string to other windows app by sendmessage with copydata
	cds.dwData = 1;
	cds.lpData = Data_cstr.GetBuffer(Data_cstr.GetLength());
	Data_cstr.ReleaseBuffer();
	if (cds.lpData == NULL)
		cds.cbData = 0;
	else
		cds.cbData = (DWORD)(_tcslen(Data_cstr) + 1) * sizeof(TCHAR);

	OtherWindow_hwnd = ::FindWindow(NULL, _T("CopyData_Receive"));
	if (OtherWindow_hwnd != NULL)
	{
		::SendMessage(OtherWindow_hwnd, WM_COPYDATA, (WPARAM)this->m_hWnd, (LPARAM)&cds);
	}
}
//-------------------------------------------------------------------------------------------
BOOL CCOPYDATA_MFCApplicationDlg::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{
	// TODO: Add your message handler code here and/or call default

	return CDialogEx::OnCopyData(pWnd, pCopyDataStruct);
}
//-------------------------------------------------------------------------------------------
void CCOPYDATA_MFCApplicationDlg::OnBnClickedBtnSendStructData()
{
	//------ Initial......
	COPYDATASTRUCT   cds;
	HWND             OtherWindow_hwnd = NULL;
	TAG_COPYDATA     Student_Info;
	CString          tempName_cstr = _T("");
	CString          tempID_cstr = _T("");

	//------------------------

	/////--> for send struct to other windows app
	tempName_cstr = _T("Johnson");
	tempID_cstr = _T("9001-001-20");
	_tcscpy_s(Student_Info.Name, tempName_cstr.GetBuffer());
	_tcscpy_s(Student_Info.ID, tempID_cstr.GetBuffer());
	Student_Info.Math_Score_i = 80;
	if (Student_Info.Math_Score_i >= 60)
	{
		Student_Info.Pass_Exam_fg = true;
	}
	else
		Student_Info.Pass_Exam_fg = false;

	cds.dwData = 10;
	cds.cbData = sizeof(Student_Info);
	cds.lpData = &Student_Info;

	OtherWindow_hwnd = ::FindWindow(NULL, _T("CopyData_Receive"));
	if (OtherWindow_hwnd != NULL)
	{
		::SendMessage(OtherWindow_hwnd, WM_COPYDATA, (WPARAM)this->m_hWnd, (LPARAM)&cds);
	}
}
//-------------------------------------------------------------------------------------------
