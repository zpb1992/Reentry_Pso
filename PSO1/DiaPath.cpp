// DiaPath.cpp : implementation file
//

#include "stdafx.h"
#include "PSO1.h"
#include "DiaPath.h"
#include "afxdialogex.h"


// CDiaPath dialog

IMPLEMENT_DYNAMIC(CDiaPath, CDialogEx)

double CDiaPath::m_dpMax=500000.0;
double CDiaPath::m_nMax=6;
double CDiaPath::m_qMax=1000000.0;
double CDiaPath::m_con=1.0;
int CDiaPath::m_egcFlag=1;
CDiaPath::CDiaPath(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDiaPath::IDD, pParent)
{
}

CDiaPath::~CDiaPath()
{
}

void CDiaPath::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_OVERLOAD, m_n);
	//  DDX_Text(pDX, IDC_DPMAX, m_dpMax);
	//  DDX_Control(pDX, IDC_OVERLOADMAX, m_nMax);
	//  DDX_Text(pDX, IDC_OVERLOADMAX, m_nMax);
	//  DDX_Text(pDX, IDC_QMAX, m_qMax);
	DDX_Text(pDX, IDC_DPMAX, m_dpMax);
	DDX_Text(pDX, IDC_OVERLOADMAX, m_nMax);
	DDX_Text(pDX, IDC_QMAX, m_qMax);
	DDX_Text(pDX, IDC_CON, m_con);
	DDX_Check(pDX, IDC_EGC, m_egcFlag);
}


BEGIN_MESSAGE_MAP(CDiaPath, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDiaPath::OnBnClickedOk)
END_MESSAGE_MAP()


// CDiaPath message handlers


void CDiaPath::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData();

	CDialogEx::OnOK();
}
