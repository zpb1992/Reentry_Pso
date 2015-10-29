// DiaTargetM.cpp : implementation file
//

#include "stdafx.h"
#include "PSO1.h"
#include "DiaTargetM.h"
#include "afxdialogex.h"


// CDiaTargetM dialog

IMPLEMENT_DYNAMIC(CDiaTargetM, CDialogEx)

double CDiaTargetM::m_target1=10;
double CDiaTargetM::m_target2=1;
double CDiaTargetM::m_target3=10000;
double CDiaTargetM::m_target4=100000000;

CDiaTargetM::CDiaTargetM(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDiaTargetM::IDD, pParent)
{
}

CDiaTargetM::~CDiaTargetM()
{
}

void CDiaTargetM::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_TARGET1, m_target1);
	DDX_Text(pDX, IDC_TARGET2, m_target2);
	DDX_Text(pDX, IDC_TARGET3, m_target3);
	DDX_Text(pDX, IDC_TARGET4, m_target4);
}


BEGIN_MESSAGE_MAP(CDiaTargetM, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDiaTargetM::OnBnClickedOk)
END_MESSAGE_MAP()


// CDiaTargetM message handlers


void CDiaTargetM::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CDialogEx::OnOK();
}
