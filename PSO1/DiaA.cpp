// DiaA.cpp : implementation file
//

#include "stdafx.h"
#include "PSO1.h"
#include "DiaA.h"
#include "afxdialogex.h"


// CDiaA dialog

IMPLEMENT_DYNAMIC(CDiaA, CDialogEx)

double CDiaA::m_amax=20;
double CDiaA::m_amaxLD=10;
double CDiaA::m_v1=5000;
double CDiaA::m_v2=3000;

CDiaA::CDiaA(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDiaA::IDD, pParent)
{
}

CDiaA::~CDiaA()
{
}

void CDiaA::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_AAMAX, m_amax);
	DDX_Text(pDX, IDC_AMAXLD, m_amaxLD);
	DDX_Text(pDX, IDC_AV1, m_v1);
	DDX_Text(pDX, IDC_AV2, m_v2);
}


BEGIN_MESSAGE_MAP(CDiaA, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDiaA::OnBnClickedOk)
END_MESSAGE_MAP()


// CDiaA message handlers


void CDiaA::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CDialogEx::OnOK();
}
