// DiaControl.cpp : implementation file
//

#include "stdafx.h"
#include "PSO1.h"
#include "DiaControl.h"
#include "afxdialogex.h"


// CDiaControl dialog

IMPLEMENT_DYNAMIC(CDiaControl, CDialogEx)

UINT CDiaControl::m_d=20;
UINT CDiaControl::m_n=50;
double CDiaControl::m_maxScope=80;
double CDiaControl::m_minScope=-80;
int CDiaControl::m_randFlag=0;

CDiaControl::CDiaControl(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDiaControl::IDD, pParent)
{
}

CDiaControl::~CDiaControl()
{
}

void CDiaControl::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_N, m_n);
	//  D//  DX_Control(p//  DX, I//  DC_N, m_ad);
	DDX_Text(pDX, IDC_D, m_n);
	DDX_Text(pDX, IDC_D, m_d);
	DDX_Text(pDX, IDC_N, m_n);
	DDX_Text(pDX, IDC_MAXSCOPE, m_maxScope);
	DDX_Text(pDX, IDC_MINSCOPE, m_minScope);
	DDX_Text(pDX, IDC_D, m_d);
	DDX_Text(pDX, IDC_N, m_n);
	DDX_Radio(pDX, IDC_RAND, m_randFlag);
}


BEGIN_MESSAGE_MAP(CDiaControl, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDiaControl::OnBnClickedOk)
END_MESSAGE_MAP()


// CDiaControl message handlers


void CDiaControl::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CDialogEx::OnOK();
}
