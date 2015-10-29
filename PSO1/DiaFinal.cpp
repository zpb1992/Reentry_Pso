// DiaFinal.cpp : implementation file
//

#include "stdafx.h"
#include "PSO1.h"
#include "DiaFinal.h"
#include "afxdialogex.h"


// CDiaFinal dialog

IMPLEMENT_DYNAMIC(CDiaFinal, CDialogEx)

double CDiaFinal::m_state1=20000.0;
double CDiaFinal::m_state2=232.0;
double CDiaFinal::m_state3=37.0;
double CDiaFinal::m_state4=1000.0;
double CDiaFinal::m_state5=0.0;
double CDiaFinal::m_state6=0.0;

int CDiaFinal::m_final1flag=1;
int CDiaFinal::m_final2flag=1;
int CDiaFinal::m_final3flag=1;
int CDiaFinal::m_final4flag=1;
int CDiaFinal::m_final5flag=0;
int CDiaFinal::m_final6flag=0;

CDiaFinal::CDiaFinal(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDiaFinal::IDD, pParent)
{
}

CDiaFinal::~CDiaFinal()
{
}

void CDiaFinal::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_STATE1, m_state1);
	DDX_Text(pDX, IDC_STATE2, m_state2);
	DDX_Text(pDX, IDC_STATE3, m_state3);
	//  DDX_Text(pDX, IDC_STATE4, m_state4);
	DDX_Text(pDX, IDC_STATE5, m_state5);
	DDX_Text(pDX, IDC_STATE6, m_state6);
	DDX_Text(pDX, IDC_STATE1, m_state1);
	DDV_MinMaxDouble(pDX, m_state1, 0.0, 500000);
	DDX_Text(pDX, IDC_STATE4, m_state4);
	DDV_MinMaxDouble(pDX, m_state4, 0.0, 100000);
	DDX_Check(pDX, IDC_FINAL1, m_final1flag);
	DDX_Check(pDX, IDC_FINAL2, m_final2flag);
	DDX_Check(pDX, IDC_FINAL3, m_final3flag);
	DDX_Check(pDX, IDC_FINAL4, m_final4flag);
	DDX_Check(pDX, IDC_FINAL5, m_final5flag);
	DDX_Check(pDX, IDC_FINAL6, m_final6flag);
}


BEGIN_MESSAGE_MAP(CDiaFinal, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDiaFinal::OnBnClickedOk)
END_MESSAGE_MAP()


// CDiaFinal message handlers


void CDiaFinal::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CDialogEx::OnOK();
}
