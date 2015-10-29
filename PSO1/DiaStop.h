#pragma once


// CDiaStop dialog

class CDiaStop : public CDialogEx
{
	DECLARE_DYNAMIC(CDiaStop)

public:
	CDiaStop(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDiaStop();

// Dialog Data
	enum { IDD = IDD_STOP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
//	UINT m_loopMax;
	static UINT m_loopMax;
};
