
// PSO1View.h : interface of the CPSO1View class
//

#pragma once


class CPSO1View : public CView
{
protected: // create from serialization only
	CPSO1View();
	DECLARE_DYNCREATE(CPSO1View)

// Attributes
public:
	CPSO1Doc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CPSO1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPictrueGao();
	afx_msg void OnPictureQing();

	afx_msg void OnUpdateTarget1(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTarget2(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTarget3(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTarget4(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTargetM(CCmdUI *pCmdUI);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	void MaxMin(double* state, UINT n, double& max, double& min);
	afx_msg void OnPictureJing();
	afx_msg void OnPictureWei();
	afx_msg void OnPictureJi();
	afx_msg void OnPictureSu();
	afx_msg void OnPictureXiang();
private:
	int m_picFlag;
public:
	int m_reFlag;
public:
	afx_msg void OnPictureQ();
	afx_msg void OnPictureDp();
	afx_msg void OnPictureN();
	afx_msg void OnPictureHV();
	afx_msg void OnPictureJW();
	BOOL DrawDotLine(int dot_n);
	BOOL NoflyPaint(void);
	afx_msg void OnPaintA();
};

#ifndef _DEBUG  // debug version in PSO1View.cpp
inline CPSO1Doc* CPSO1View::GetDocument() const
   { return reinterpret_cast<CPSO1Doc*>(m_pDocument); }
#endif

