// DiaLimitsWeight.cpp : 实现文件
//

#include "stdafx.h"
#include "PSO1.h"
#include "DiaLimitsWeight.h"
#include "afxdialogex.h"


// CDiaLimitsWeight 对话框

IMPLEMENT_DYNAMIC(CDiaLimitsWeight, CDialogEx)

CDiaLimitsWeight::CDiaLimitsWeight(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDiaLimitsWeight::IDD, pParent)
{

	m_conA = 0.0;
	m_conB = 0.0;
	m_dTrack = 0.0;
	m_gao = 0.0;
	m_hangJi = 0.0;
	m_hangXiang = 0.0;
	m_heat = 0.0;
	m_heatDen = 0.0;
	m_jing = 0.0;
	m_overLoad = 0.0;
	m_pressure = 0.0;
	m_su = 0.0;
	m_track = 0.0;
	m_wei = 0.0;
}

CDiaLimitsWeight::~CDiaLimitsWeight()
{
}

void CDiaLimitsWeight::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_DCONA, m_conA);
	DDX_Text(pDX, IDC_DCONB, m_conB);
	DDX_Text(pDX, IDC_DTRACK, m_dTrack);
	DDX_Text(pDX, IDC_GAO, m_gao);
	DDX_Text(pDX, IDC_HANGJI, m_hangJi);
	DDX_Text(pDX, IDC_HANGXIANG, m_hangXiang);
	DDX_Text(pDX, IDC_HEAT, m_heat);
	DDX_Text(pDX, IDC_HEATDEN, m_heatDen);
	DDX_Text(pDX, IDC_JING, m_jing);
	DDX_Text(pDX, IDC_OVERLOAD, m_overLoad);
	DDX_Text(pDX, IDC_PRESSURE, m_pressure);
	DDX_Text(pDX, IDC_SU, m_su);
	DDX_Text(pDX, IDC_TRACK, m_track);
	DDX_Text(pDX, IDC_WEI, m_wei);
}


BEGIN_MESSAGE_MAP(CDiaLimitsWeight, CDialogEx)
END_MESSAGE_MAP()


// CDiaLimitsWeight 消息处理程序
