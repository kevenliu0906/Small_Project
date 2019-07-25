
// COPYDATA_MFCApplication.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CCOPYDATA_MFCApplicationApp:
// See COPYDATA_MFCApplication.cpp for the implementation of this class
//

class CCOPYDATA_MFCApplicationApp : public CWinApp
{
public:
	CCOPYDATA_MFCApplicationApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CCOPYDATA_MFCApplicationApp theApp;