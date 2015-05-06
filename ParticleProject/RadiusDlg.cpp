// RadiusDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ParticleProject.h"
#include "RadiusDlg.h"
#include "afxdialogex.h"


// CRadiusDlg dialog

IMPLEMENT_DYNAMIC(CRadiusDlg, CDialogEx)

CRadiusDlg::CRadiusDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRadiusDlg::IDD, pParent)
	, mBaseRadius(0)
	, mBaseVelocityX(0)
	, mBaseVelocityY(0)
	, mBaseVelocityZ(0)
	, mBaseLife(0)
	, mVelVar(0)
	, mLifeVar(0)
	, mRadVar(0)
{

}

CRadiusDlg::~CRadiusDlg()
{
}

void CRadiusDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_RAD, mBaseRadius);
	DDV_MinMaxDouble(pDX, mBaseRadius, .1, 1.5);
	DDX_Text(pDX, IDC_BASE_VELX_EDIT, mBaseVelocityX);
	DDV_MinMaxDouble(pDX, mBaseVelocityX, 5.0, 30.0);
	DDX_Text(pDX, IDC_BASE_VELY_EDIT, mBaseVelocityY);
	DDV_MinMaxDouble(pDX, mBaseVelocityY, 5.0, 30.0);
	DDX_Text(pDX, IDC_BASE_VELZ_EDIT, mBaseVelocityZ);
	DDV_MinMaxDouble(pDX, mBaseVelocityZ, 5.0, 30.0);
	DDX_Text(pDX, IDC_LIFE_EDIT, mBaseLife);
	DDV_MinMaxDouble(pDX, mBaseLife, 1.0, 10.0);
	DDX_Text(pDX, IDC_VEL_VAR_EDIT, mVelVar);
	DDV_MinMaxDouble(pDX, mVelVar, 0, .5);
	DDX_Text(pDX, IDC_LIFE_VAR_EDIT, mLifeVar);
	DDV_MinMaxDouble(pDX, mLifeVar, 0, .5);
	DDX_Text(pDX, IDC_RAD_VAR_EDIT, mRadVar);
	DDV_MinMaxDouble(pDX, mRadVar, 0, .5);
}


BEGIN_MESSAGE_MAP(CRadiusDlg, CDialogEx)
	ON_BN_CLICKED(IDC_GREEN_RADIO, &CRadiusDlg::OnBnClickedGreenRadio)
	ON_BN_CLICKED(IDC_RED_RADIO, &CRadiusDlg::OnBnClickedRedRadio)
	ON_BN_CLICKED(IDC_BLUE_RADIO, &CRadiusDlg::OnBnClickedBlueRadio)
	ON_BN_CLICKED(IDC_YELLOW_RADIO, &CRadiusDlg::OnBnClickedYellowRadio)
	ON_BN_CLICKED(IDC_RANDOM_RADIO, &CRadiusDlg::OnBnClickedRandomRadio)
END_MESSAGE_MAP()


// CRadiusDlg message handlers


void CRadiusDlg::OnBnClickedGreenRadio()
{
	mColor = 1;
}


void CRadiusDlg::OnBnClickedRedRadio()
{
	mColor = 2;
}


void CRadiusDlg::OnBnClickedBlueRadio()
{
	mColor = 3;
}


void CRadiusDlg::OnBnClickedYellowRadio()
{
	mColor = 4;
}


void CRadiusDlg::OnBnClickedRandomRadio()
{
	mColor = -1;
}
