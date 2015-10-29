// DiaFinalTime.cpp : implementation file
//

#include "stdafx.h"
#include "PSO1.h"
#include "DiaFinalTime.h"
#include "afxdialogex.h"


// CDiaFinalTime dialog

IMPLEMENT_DYNAMIC(CDiaFinalTime, CDialogEx)

double CDiaFinalTime::m_t=0.0;
double CDiaFinalTime::m_t0=1000.0;
double CDiaFinalTime::m_tf=3000.0;
int CDiaFinalTime::m_tOption=1;

CDiaFinalTime::CDiaFinalTime(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDiaFinalTime::IDD, pParent)
{
}

CDiaFinalTime::~CDiaFinalTime()
{
}

void CDiaFinalTime::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_T, m_t);
	DDX_Text(pDX, IDC_T0, m_t0);
	DDX_Text(pDX, IDC_TF, m_tf);
	DDX_Text(pDX, IDC_T, m_t);
	DDX_Text(pDX, IDC_T0, m_t0);
	DDX_Text(pDX, IDC_TF, m_tf);
	DDX_Radio(pDX, IDC_RADIO1, m_tOption);
}


BEGIN_MESSAGE_MAP(CDiaFinalTime, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDiaFinalTime::OnBnClickedOk)
END_MESSAGE_MAP()


// CDiaFinalTime message handlers


void CDiaFinalTime::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData();

	CDialogEx::OnOK();
}
