// DiaPlane.cpp : implementation file
//

#include "stdafx.h"
#include "PSO1.h"
#include "DiaPlane.h"
#include "afxdialogex.h"


// CDiaPlane dialog

IMPLEMENT_DYNAMIC(CDiaPlane, CDialogEx)

double CDiaPlane::m_m=907.2;
double CDiaPlane::m_r=0.1;
double CDiaPlane::m_s=0.4839;

CDiaPlane::CDiaPlane(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDiaPlane::IDD, pParent)
{

}

CDiaPlane::~CDiaPlane()
{
}

void CDiaPlane::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_M, m_m);
	DDX_Text(pDX, IDC_R, m_r);
	DDX_Text(pDX, IDC_S, m_s);
}


BEGIN_MESSAGE_MAP(CDiaPlane, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDiaPlane::OnBnClickedOk)
END_MESSAGE_MAP()


// CDiaPlane message handlers


void CDiaPlane::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CDialogEx::OnOK();
}
