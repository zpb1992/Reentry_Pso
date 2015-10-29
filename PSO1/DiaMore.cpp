// DiaMore.cpp : implementation file
//

#include "stdafx.h"
#include "PSO1.h"
#include "DiaMore.h"
#include "afxdialogex.h"


// CDiaMore dialog

IMPLEMENT_DYNAMIC(CDiaMore, CDialogEx)

BOOL CDiaMore::m_saFlag=FALSE;
BOOL CDiaMore::m_gaFlag=FALSE;
double CDiaMore::m_gaHet=0.04;
double CDiaMore::m_saCho=0.1;
CDiaMore::CDiaMore(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDiaMore::IDD, pParent)
{

}

CDiaMore::~CDiaMore()
{
}

void CDiaMore::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_SA, m_saFlag);
	DDX_Check(pDX, IDC_GA, m_gaFlag);
	DDX_Text(pDX, IDC_GAEDIT, m_gaHet);
	DDX_Text(pDX, IDC_SAEDIT, m_saCho);
}


BEGIN_MESSAGE_MAP(CDiaMore, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDiaMore::OnBnClickedOk)
END_MESSAGE_MAP()


// CDiaMore message handlers


void CDiaMore::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	CDialogEx::OnOK();
}
