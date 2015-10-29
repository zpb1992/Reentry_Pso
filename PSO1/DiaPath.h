#pragma once


// CDiaPath dialog

class CDiaPath : public CDialogEx
{
	DECLARE_DYNAMIC(CDiaPath)

public:
	CDiaPath(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDiaPath();

// Dialog Data
	enum { IDD = IDD_PATH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	static double m_dpMax;
	static double m_nMax;
	static double m_qMax;
	static double m_con;
	static int m_egcFlag;

};
