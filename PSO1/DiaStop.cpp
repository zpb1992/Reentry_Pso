// DiaStop.cpp : implementation file
//

#include "stdafx.h"
#include "PSO1.h"
#include "DiaStop.h"
#include "afxdialogex.h"


// CDiaStop dialog

IMPLEMENT_DYNAMIC(CDiaStop, CDialogEx)

UINT CDiaStop::m_loopMax=500;

CDiaStop::CDiaStop(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDiaStop::IDD, pParent)
{
}

CDiaStop::~CDiaStop()
{
}

void CDiaStop::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_LOOP, m_loopMax);
	DDX_Text(pDX, IDC_LOOP, m_loopMax);
}


BEGIN_MESSAGE_MAP(CDiaStop, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDiaStop::OnBnClickedOk)
END_MESSAGE_MAP()


// CDiaStop message handlers


void CDiaStop::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CDialogEx::OnOK();
}
