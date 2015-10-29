// DiaState.cpp : implementation file
//

#include "stdafx.h"
#include "PSO1.h"
#include "DiaState.h"
#include "afxdialogex.h"


// CDiaState dialog

IMPLEMENT_DYNAMIC(CDiaState, CDialogEx)

UINT CDiaState::m_stateN=40;
double CDiaState::m_initState1=100000.0;
double CDiaState::m_initState2=160.0;
double CDiaState::m_initState3=25.0;
double CDiaState::m_initState4=7200.0;
double CDiaState::m_initState5=-2.0;
double CDiaState::m_initState6=58.0;

CDiaState::CDiaState(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDiaState::IDD, pParent)
{
}

CDiaState::~CDiaState()
{
}

void CDiaState::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_STATE_N, m_stateN);
	DDX_Text(pDX, IDC_STATE_N, m_stateN);
	DDX_Text(pDX, IDC_INITSTATE1, m_initState1);
	DDX_Text(pDX, IDC_INITSTATE2, m_initState2);
	DDX_Text(pDX, IDC_INITSTATE3, m_initState3);
	DDX_Text(pDX, IDC_INITSTATE4, m_initState4);
	DDX_Text(pDX, IDC_INITSTATE5, m_initState5);
	DDX_Text(pDX, IDC_INITSTATE6, m_initState6);
}


BEGIN_MESSAGE_MAP(CDiaState, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDiaState::OnBnClickedOk)
END_MESSAGE_MAP()


// CDiaState message handlers


void CDiaState::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CDialogEx::OnOK();
}
