// DiaPicOption.cpp : implementation file
//

#include "stdafx.h"
#include "PSO1.h"
#include "DiaPicOption.h"
#include "afxdialogex.h"


// CDiaPicOption dialog

IMPLEMENT_DYNAMIC(CDiaPicOption, CDialogEx)

BOOL CDiaPicOption::m_picOption1=TRUE;
BOOL CDiaPicOption::m_picOption2=TRUE;
UINT CDiaPicOption::m_picN=1000;
int CDiaPicOption::m_interpFlag=1;

CDiaPicOption::CDiaPicOption(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDiaPicOption::IDD, pParent)
{
}

CDiaPicOption::~CDiaPicOption()
{
}

void CDiaPicOption::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PICTURE_N, m_picN);
	DDX_Check(pDX, IDC_PICTURE_OPTION1, m_picOption1);
	DDX_Check(pDX, IDC_PICTURE_OPTION2, m_picOption2);
	DDX_Radio(pDX, IDC_REAL, m_interpFlag);
}


BEGIN_MESSAGE_MAP(CDiaPicOption, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDiaPicOption::OnBnClickedOk)
	ON_BN_CLICKED(IDC_PICTURE_OPTION2, &CDiaPicOption::OnBnClickedPictureOption2)
END_MESSAGE_MAP()


// CDiaPicOption message handlers


void CDiaPicOption::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CDialogEx::OnOK();
}


void CDiaPicOption::OnBnClickedPictureOption2()
{
	// TODO: Add your control notification handler code here
	CWnd* pwnd=GetDlgItem(IDC_PICTURE_N);
	if(pwnd->IsWindowVisible())
	{
		GetDlgItem(IDC_STATICUSE)->ShowWindow(FALSE);
		pwnd->ShowWindow(FALSE);
	}
	else 
	{
		GetDlgItem(IDC_STATICUSE)->ShowWindow(TRUE);
		pwnd->ShowWindow(TRUE);
	}
}
