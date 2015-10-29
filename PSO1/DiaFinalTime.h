#pragma once


// CDiaFinalTime dialog

class CDiaFinalTime : public CDialogEx
{
	DECLARE_DYNAMIC(CDiaFinalTime)

public:
	CDiaFinalTime(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDiaFinalTime();

// Dialog Data
	enum { IDD = IDD_FINALTIME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
//	double m_t;
//	double m_t0;
//	double m_tf;
	static double m_t;
	static double m_t0;
	static double m_tf;
	static int m_tOption;
	afx_msg void OnBnClickedOk();

};
