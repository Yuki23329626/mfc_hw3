
// 403410016沈濃翔.h : main header file for the 403410016沈濃翔 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMy403410016沈濃翔App:
// See 403410016沈濃翔.cpp for the implementation of this class
//

class CMy403410016沈濃翔App : public CWinApp
{
public:
	CMy403410016沈濃翔App();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	UINT  m_nAppLook;
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy403410016沈濃翔App theApp;
