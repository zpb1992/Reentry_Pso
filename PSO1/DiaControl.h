#pragma once


// CDiaControl dialog

class CDiaControl : public CDialogEx
{
	DECLARE_DYNAMIC(CDiaControl)

public:
	CDiaControl(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDiaControl();

// Dialog Data
	enum { IDD = IDD_CONTROL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	static UINT m_d;
	static UINT m_n;
	static double m_maxScope;
	static double m_minScope;
	static int m_randFlag;

	afx_msg void OnBnClickedOk();

};
