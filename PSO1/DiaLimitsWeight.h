#pragma once


// CDiaLimitsWeight �Ի���

class CDiaLimitsWeight : public CDialogEx
{
	DECLARE_DYNAMIC(CDiaLimitsWeight)

public:
	CDiaLimitsWeight(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDiaLimitsWeight();

// �Ի�������
	enum { IDD = IDD_WEIGHT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	double m_conA;
	double m_conB;
	double m_dTrack;
	double m_gao;
	double m_hangJi;
	double m_hangXiang;
	double m_heat;
	double m_heatDen;
	double m_jing;
	double m_overLoad;
	double m_pressure;
	double m_su;
	double m_track;
	double m_wei;
	double m_time;
};
