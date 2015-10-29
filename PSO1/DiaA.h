#pragma once


// CDiaA dialog

class CDiaA : public CDialogEx
{
	DECLARE_DYNAMIC(CDiaA)

public:
	CDiaA(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDiaA();

// Dialog Data
	enum { IDD = IDD_A };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	static double m_amax;
	static double m_amaxLD;
	static double m_v1;
	static double m_v2;
	afx_msg void OnBnClickedOk();
};
