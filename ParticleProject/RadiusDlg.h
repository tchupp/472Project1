#pragma once
#include "afxwin.h"


// CRadiusDlg dialog

class CRadiusDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRadiusDlg)

public:
	CRadiusDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CRadiusDlg();

// Dialog Data
	enum { IDD = IDD_RADIUS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	double mBaseRadius;
	int mColor;
	double mBaseVelocityX;
	double mBaseVelocityY;
	double mBaseVelocityZ;
	double mBaseLife;
	double mVelVar;

	afx_msg void OnBnClickedGreenRadio();
	afx_msg void OnBnClickedRedRadio();
	afx_msg void OnBnClickedBlueRadio();
	afx_msg void OnBnClickedYellowRadio();
	afx_msg void OnBnClickedRandomRadio();
	double mLifeVar;
	double mRadVar;

	bool mUseMotionBlur = false;

	
	int mMotionBlur;		// # motion blur frames
	double mParticleNum;
};
