#pragma once


// CDiaPicOption dialog

class CDiaPicOption : public CDialogEx
{
	DECLARE_DYNAMIC(CDiaPicOption)

public:
	CDiaPicOption(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDiaPicOption();

// Dialog Data
	enum { IDD = IDD_PICTURE_OPTION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	static UINT m_picN;
	static BOOL m_picOption1;
	static BOOL m_picOption2;
	afx_msg void OnBnClickedPictureOption2();
	static int m_interpFlag;
};
