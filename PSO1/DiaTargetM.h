#pragma once


// CDiaTargetM dialog

class CDiaTargetM : public CDialogEx
{
	DECLARE_DYNAMIC(CDiaTargetM)

public:
	CDiaTargetM(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDiaTargetM();

// Dialog Data
	enum { IDD = IDD_TARGET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	static double m_target1;
	static double m_target2;
	static double m_target3;
	static double m_target4;
	afx_msg void OnBnClickedOk();
};
