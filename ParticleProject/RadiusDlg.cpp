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
	, mRadius(0)
{

}

CRadiusDlg::~CRadiusDlg()
{
}

void CRadiusDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_RAD, mRadius);
	DDV_MinMaxDouble(pDX, mRadius, .1, 1.5);
}


BEGIN_MESSAGE_MAP(CRadiusDlg, CDialogEx)
END_MESSAGE_MAP()


// CRadiusDlg message handlers
