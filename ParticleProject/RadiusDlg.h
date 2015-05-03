#pragma once


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
	double mRadius;
};
