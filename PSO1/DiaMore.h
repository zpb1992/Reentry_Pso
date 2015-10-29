#pragma once


// CDiaMore dialog

class CDiaMore : public CDialogEx
{
	DECLARE_DYNAMIC(CDiaMore)

public:
	CDiaMore(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDiaMore();

// Dialog Data
	enum { IDD = IDD_MORE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	static BOOL m_saFlag;
	static BOOL m_gaFlag;
	static double m_gaHet;
	static double m_saCho;
	afx_msg void OnBnClickedOk();
};
