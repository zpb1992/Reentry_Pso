#pragma once


// CDiaState dialog

class CDiaState : public CDialogEx
{
	DECLARE_DYNAMIC(CDiaState)

public:
	CDiaState(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDiaState();

// Dialog Data
	enum { IDD = IDD_STATE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	
	static UINT m_stateN;
	static double m_initState1;
	static double m_initState2;
	static double m_initState3;
	static double m_initState4;
	static double m_initState5;
	static double m_initState6;
};
