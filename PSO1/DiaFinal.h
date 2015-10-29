#pragma once


// CDiaFinal dialog

class CDiaFinal : public CDialogEx
{
	DECLARE_DYNAMIC(CDiaFinal)

public:
	CDiaFinal(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDiaFinal();

// Dialog Data
	enum { IDD = IDD_FINAL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();

	static double m_state1;
	static double m_state2;
	static double m_state3;
	static double m_state4;
	static double m_state5;
	static double m_state6;

	static int m_final1flag;
	static int m_final2flag;
	static int m_final3flag;
	static int m_final4flag;
	static int m_final5flag;
	static int m_final6flag;

};
