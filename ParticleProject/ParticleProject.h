// ParticleProject.h : main header file for the ParticleProject application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols
// CParticleProjectApp:
// See ParticleProject.cpp for the implementation of this class
//

class CParticleProjectApp : public CWinAppEx
{
public:
	CParticleProjectApp();


	// Overrides
public:
	virtual BOOL InitInstance() override;
	virtual int ExitInstance() override;

	// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CParticleProjectApp theApp;
