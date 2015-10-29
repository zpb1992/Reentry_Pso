#pragma once


// CDiaPlane dialog

class CDiaPlane : public CDialogEx
{
	DECLARE_DYNAMIC(CDiaPlane)

public:
	CDiaPlane(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDiaPlane();

// Dialog Data
	enum { IDD = IDD_PLANE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	static double m_m;
	static double m_r;
	static double m_s;
	afx_msg void OnBnClickedOk();
};
