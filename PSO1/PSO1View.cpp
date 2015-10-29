
// PSO1View.cpp : implementation of the CPSO1View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "PSO1.h"
#endif

#include "PSO1Doc.h"
#include "PSO1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPSO1View

IMPLEMENT_DYNCREATE(CPSO1View, CView)

BEGIN_MESSAGE_MAP(CPSO1View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CPSO1View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_PICTURE_GAO, &CPSO1View::OnPictrueGao)
	ON_COMMAND(ID_PICTURE_QING, &CPSO1View::OnPictureQing)
	ON_UPDATE_COMMAND_UI(ID_TARGET1, &CPSO1View::OnUpdateTarget1)
	ON_UPDATE_COMMAND_UI(ID_TARGET2, &CPSO1View::OnUpdateTarget2)
	ON_UPDATE_COMMAND_UI(ID_TARGET3, &CPSO1View::OnUpdateTarget3)
	ON_UPDATE_COMMAND_UI(ID_TARGET4, &CPSO1View::OnUpdateTarget4)
	ON_UPDATE_COMMAND_UI(ID_TARGET_M, &CPSO1View::OnUpdateTargetM)
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_PICTURE_JING, &CPSO1View::OnPictureJing)
	ON_COMMAND(ID_PICTURE_WEI, &CPSO1View::OnPictureWei)
	ON_COMMAND(ID_PICTURE_JI, &CPSO1View::OnPictureJi)
	ON_COMMAND(ID_PICTURE_SU, &CPSO1View::OnPictureSu)
	ON_COMMAND(ID_PICTURE_XIANG, &CPSO1View::OnPictureXiang)
	ON_COMMAND(ID_PICTURE_Q, &CPSO1View::OnPictureQ)
	ON_COMMAND(ID_PICTURE_DP, &CPSO1View::OnPictureDp)
	ON_COMMAND(ID_PICTURE_N, &CPSO1View::OnPictureN)
	ON_COMMAND(ID_PICTURE_HV, &CPSO1View::OnPictureHV)
	ON_COMMAND(ID_PICTURE_JW, &CPSO1View::OnPictureJW)
	ON_COMMAND(ID_PAINT_A, &CPSO1View::OnPaintA)
END_MESSAGE_MAP()

// CPSO1View construction/destruction

CPSO1View::CPSO1View()
{
	// TODO: add construction code here
	m_picFlag=0;
	m_reFlag=0;
}

CPSO1View::~CPSO1View()
{
}

BOOL CPSO1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CPSO1View drawing

void CPSO1View::OnDraw(CDC* pDC)
{
	CPSO1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CRect rect;
	GetClientRect(rect);
	// TODO: add draw code for native data here
	//横坐标 right/16 到 right*15/16
	//纵坐标 bottom/9 到 bottom*8/9
	pDC->MoveTo(rect.right/16,rect.bottom*8/9);
	pDC->LineTo(rect.right*15/16,rect.bottom*8/9);
	pDC->MoveTo(rect.right/16,rect.bottom*8/9);
	pDC->LineTo(rect.right/16,rect.bottom/9);

	pDC->Ellipse(rect.right/16-4,rect.bottom*8/9-4,rect.right/16+4,rect.bottom*8/9+4);
	
	pDC->MoveTo(rect.right*15/16-20,rect.bottom*8/9-7);
	pDC->LineTo(rect.right*15/16,rect.bottom*8/9);
	pDC->LineTo(rect.right*15/16-20,rect.bottom*8/9+7);

	pDC->MoveTo(rect.right/16-7,rect.bottom/9+20);
	pDC->LineTo(rect.right/16,rect.bottom/9);
	pDC->LineTo(rect.right/16+7,rect.bottom/9+20);
	
	CString str;
	str.Format("%.3lfs",pDoc->m_startTime/1000);
	pDC->TextOutA(0,0,str);

	DrawDotLine(5);

	if(m_reFlag==1)
	{
		switch(m_picFlag)
		{
		case 1:PostMessage(WM_COMMAND,ID_PICTURE_GAO);
			break;
		case 2:
			PostMessage(WM_COMMAND,ID_PICTURE_JING);
			break;
		case 3:
			PostMessage(WM_COMMAND,ID_PICTURE_WEI);
			break;
		case 4:
			PostMessage(WM_COMMAND,ID_PICTURE_SU);
			break;
		case 5:
			PostMessage(WM_COMMAND,ID_PICTURE_JI);
			break;
		case 6:
			PostMessage(WM_COMMAND,ID_PICTURE_XIANG);
			break;
		case 7:
			PostMessage(WM_COMMAND,ID_PICTURE_QING);
			break;
		case 8:
			PostMessage(WM_COMMAND,ID_PICTURE_Q);
			break;
		case 9:
			PostMessage(WM_COMMAND,ID_PICTURE_DP);
			break;
		case 10:
			PostMessage(WM_COMMAND,ID_PICTURE_N);
			break;
		case 11:
			PostMessage(WM_COMMAND,ID_PICTURE_HV);
			break;
		case 12:
			PostMessage(WM_COMMAND,ID_PICTURE_JW);
			break;
		default:
			;break;
		}
	}
}


// CPSO1View printing


void CPSO1View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CPSO1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPSO1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPSO1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CPSO1View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	//ClientToScreen(&point);
	//OnContextMenu(this, point);
}

void CPSO1View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CPSO1View diagnostics

#ifdef _DEBUG
void CPSO1View::AssertValid() const
{
	CView::AssertValid();
}

void CPSO1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPSO1Doc* CPSO1View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPSO1Doc)));
	return (CPSO1Doc*)m_pDocument;
}
#endif //_DEBUG


// CPSO1View message handlers


void CPSO1View::OnPictrueGao()
{
	m_picFlag=1;
	m_reFlag=0;
	if(GetDocument()->m_bestControl.IsEmpty())
	{
		if(IDOK==MessageBox("点击确定会运行程序来输出图形"))
		{
			GetDocument()->OnStart();
			PostMessage(WM_PAINT);
		}
		return;
	}
	Invalidate();
	OnPaint();
	// TODO: Add your command handler code here
	CPSO1Doc* doc=GetDocument();
	CClientDC dc(this);
	double xmax=doc->m_bestTime,xmin=0;
	double ymax,ymin;
	double* y1,*y2;
	double* x1,*x2;
	UINT n1,n2;
	CRect rect;
	GetClientRect(rect);
	CPoint point(rect.right/16,rect.bottom*8/9);

	n1=doc->m_stateN;

	n2=doc->m_picN;

	y1=new double[n1];
	y2=new double[n2];
	x1=new double[n1];
	x2=new double[n2];
	for(UINT i=0;i<n1;i++)
	{
		y1[i]=doc->m_state1.GetAt(i);
		x1[i]=doc->m_bestTime*i/(n1-1);
	}
	for(UINT i=0;i<n2;i++)
	{
		y2[i]=doc->m_picstate1.GetAt(i);
		x2[i]=doc->m_bestTime*i/(n2-1);		
	}
	MaxMin(y2,n2,ymax,ymin);

	CBrush* old=dc.SelectObject(CBrush::FromHandle((HBRUSH)GetStockObject(BLACK_BRUSH)));
	CPen pen(PS_SOLID,2,RGB(0,0,0));
	CPen* oldpen=dc.SelectObject(&pen);
	CPoint point1(rect.right/16,rect.bottom*8/9);
	double yscale=(rect.bottom*6/9)/(ymax-ymin);
	double xscale=(rect.right*13/16)/(xmax-xmin);
	
	LONG xtemp,ytemp;
	if(doc->m_picOption2)
	{
		xtemp=(LONG)((x2[0]-xmin)*xscale)+point.x;
		ytemp=(LONG)(-(y2[0]-ymin)*yscale)+point.y;
		dc.MoveTo(xtemp,ytemp);
		for(UINT i=1;i<n2;i++)
		{
			xtemp=(LONG)((x2[i]-xmin)*xscale)+point.x;
			ytemp=(LONG)(-(y2[i]-ymin)*yscale)+point.y;
			dc.LineTo(xtemp,ytemp);
		}
	}
	if(doc->m_picOption1)
	{
		for(UINT i=0;i<n1;i++)
		{
			xtemp=(LONG)((x1[i]-xmin)*xscale)+point.x;
			ytemp=(LONG)(-(y1[i]-ymin)*yscale)+point.y;
			dc.Ellipse(xtemp-3,ytemp-3,xtemp+3,ytemp+3);
		}
	}

	//for(UINT i=0;i<n;i++)
	//{
	//	scale=(state1[i]-min)/h;

	//	dc.MoveTo(point1.x,point1.y+3);
	//	dc.LineTo(point1.x,point1.y-6);

	//	//dc.MoveTo(point2.x-3,point2.y);
	//	//dc.LineTo(point2.x+6,point2.y);
	//	
	//	
	//	dc.Ellipse(point1.x-3,int(point1.y-scale*rect.bottom*2/3-3),point1.x+3,int(point1.y-scale*rect.bottom*2/3+3));
	//	
	//	point1.x += rect.right*7/8/xn;	
	//	//point2.y -= rect.bottom*7/9/n;	
	//}
	dc.SelectObject(old);
	dc.SelectObject(oldpen);

	dc.MoveTo(point.x-3,rect.bottom*2/9);
	dc.LineTo(point.x+6,rect.bottom*2/9);
	CString temp;
	temp.Format("%f",(ymax-6378000)/1000);
	TextOut(dc,10,rect.bottom*2/9-10,temp,temp.GetLength()-2);
	temp.Format("%f",(ymin-6378000)/1000);
	TextOut(dc,10,rect.bottom*8/9-10,temp,temp.GetLength()-2);
	temp.Format("高度/km");
	TextOut(dc,20,rect.bottom/9,temp,temp.GetLength());
	temp.Format("时间/s");
	TextOut(dc,rect.right*15/16+10,rect.bottom*8/9+5,temp,temp.GetLength());
	temp.Format("%f",xmax);
	TextOut(dc,rect.right*14/16,rect.bottom*8/9+10,temp,8);
	temp.Format("%f",xmin);
	TextOut(dc,rect.right/16,rect.bottom*8/9+10,temp,8);

	CString str;
	str.Format("最大值:%f,最小值:%f,时间:%f",(ymax-6378000)/1000,(ymin-6378000)/1000,doc->m_bestTime);
	dc.TextOut(rect.right/2-150,rect.bottom/9-40,str,str.GetLength());
	if(doc->m_finalflag1)
	{
		str.Format("终端:%f",(y2[n2-1]-6378000)/1000);
		dc.TextOutA(rect.right/2-150,rect.bottom/9-20,str);
	}
	m_reFlag=1;
	delete(y1);
	delete(y2);
	delete(x1);
	delete(x2);
}


void CPSO1View::OnPictureQing()
{
	m_picFlag=7;
	m_reFlag=0;
	if(GetDocument()->m_bestControl.IsEmpty())
	{
		if(IDOK==MessageBox("点击确定会运行程序来输出图形"))
		{
			GetDocument()->OnStart();
			PostMessage(WM_PAINT);
		}
		return;
	}
	Invalidate();
	OnPaint();
	// TODO: Add your command handler code here
	CPSO1Doc* doc=GetDocument();
	CClientDC dc(this);
	double xmax=doc->m_bestTime,xmin=0;
	double ymax,ymin;
	double* y1,*y2;
	double* x1,*x2;
	UINT n1,n2;
	CRect rect;
	GetClientRect(rect);
	CPoint point(rect.right/16,rect.bottom*8/9);

	n1=doc->m_d;

	n2=doc->m_picN;

	y1=new double[n1];
	y2=new double[n2];
	x1=new double[n1];
	x2=new double[n2];
	for(UINT i=0;i<n1;i++)
	{
		y1[i]=doc->m_bestControl.GetAt(i);
		x1[i]=doc->m_bestTime*i/(n1-1);
	}
	for(UINT i=0;i<n2;i++)
	{
		y2[i]=doc->m_picControl.GetAt(i);
		x2[i]=doc->m_bestTime*i/(n2-1);		
	}
	MaxMin(y2,n2,ymax,ymin);

	CBrush* old=dc.SelectObject(CBrush::FromHandle((HBRUSH)GetStockObject(BLACK_BRUSH)));
	CPen pen(PS_SOLID,2,RGB(0,0,0));
	CPen* oldpen=dc.SelectObject(&pen);
	CPoint point1(rect.right/16,rect.bottom*8/9);
	double yscale=(rect.bottom*6/9)/(ymax-ymin);
	double xscale=(rect.right*13/16)/(xmax-xmin);
	
	LONG xtemp,ytemp;
	if(doc->m_picOption2)
	{
		xtemp=(LONG)((x2[0]-xmin)*xscale)+point.x;
		ytemp=(LONG)(-(y2[0]-ymin)*yscale)+point.y;
		dc.MoveTo(xtemp,ytemp);
		for(UINT i=1;i<n2;i++)
		{
			xtemp=(LONG)((x2[i]-xmin)*xscale)+point.x;
			ytemp=(LONG)(-(y2[i]-ymin)*yscale)+point.y;
			dc.LineTo(xtemp,ytemp);
		}
	}
	if(doc->m_picOption1)
	{
		for(UINT i=0;i<n1;i++)
		{
			xtemp=(LONG)((x1[i]-xmin)*xscale)+point.x;
			ytemp=(LONG)(-(y1[i]-ymin)*yscale)+point.y;
			dc.Ellipse(xtemp-3,ytemp-3,xtemp+3,ytemp+3);
		}
	}

	//for(UINT i=0;i<n;i++)
	//{
	//	scale=(state1[i]-min)/h;

	//	dc.MoveTo(point1.x,point1.y+3);
	//	dc.LineTo(point1.x,point1.y-6);

	//	//dc.MoveTo(point2.x-3,point2.y);
	//	//dc.LineTo(point2.x+6,point2.y);
	//	
	//	
	//	dc.Ellipse(point1.x-3,int(point1.y-scale*rect.bottom*2/3-3),point1.x+3,int(point1.y-scale*rect.bottom*2/3+3));
	//	
	//	point1.x += rect.right*7/8/xn;	
	//	//point2.y -= rect.bottom*7/9/n;	
	//}
	dc.SelectObject(old);
	dc.SelectObject(oldpen);

	dc.MoveTo(point.x-3,rect.bottom*2/9);
	dc.LineTo(point.x+6,rect.bottom*2/9);
	CString temp;
	temp.Format("%f",ymax*180/3.1416);
	TextOut(dc,10,rect.bottom*2/9-10,temp,temp.GetLength()-2);
	temp.Format("%f",ymin*180/3.1416);
	TextOut(dc,10,rect.bottom*8/9-10,temp,temp.GetLength()-2);
	temp.Format("倾侧角/deg");
	TextOut(dc,20,rect.bottom/9,temp,temp.GetLength());
	temp.Format("时间/s");
	TextOut(dc,rect.right*15/16+10,rect.bottom*8/9+5,temp,temp.GetLength());
	temp.Format("%f",xmax);
	TextOut(dc,rect.right*14/16,rect.bottom*8/9+10,temp,8);
	temp.Format("%f",xmin);
	TextOut(dc,rect.right/16,rect.bottom*8/9+10,temp,8);

	CString str;
	str.Format("最大值:%f,最小值:%f,时间:%f",ymax*180/3.1416,ymin*180/3.1416,doc->m_bestTime);
	dc.TextOut(rect.right/2-150,rect.bottom/9-40,str,str.GetLength());

	m_reFlag=1;
	delete(y1);
	delete(y2);
	delete(x1);
	delete(x2);
}


void CPSO1View::OnUpdateTarget1(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if(GetDocument()->m_targetFlag==1)
	{
		pCmdUI->SetCheck();
	}
}


void CPSO1View::OnUpdateTarget2(CCmdUI *pCmdUI)
{
	// TODO: Add your command handler code here
	if(GetDocument()->m_targetFlag==2)
	{
		pCmdUI->SetCheck();
	}
}


void CPSO1View::OnUpdateTarget3(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if(GetDocument()->m_targetFlag==3)
	{
		pCmdUI->SetCheck();
	}
}


void CPSO1View::OnUpdateTarget4(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if(GetDocument()->m_targetFlag==4)
	{
		pCmdUI->SetCheck();
	}
}


void CPSO1View::OnUpdateTargetM(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if(GetDocument()->m_targetFlag==5)
	{
		pCmdUI->SetCheck();
	}
}


void CPSO1View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	switch(nChar)
	{
	case VK_F5:
		GetDocument()->OnStart();
		PostMessage(WM_PAINT);
		break;
	case '1':
		PostMessage(WM_COMMAND,ID_PICTURE_GAO);
		break;
	case '2':
		PostMessage(WM_COMMAND,ID_PICTURE_JING);
		break;
	case '3':
		PostMessage(WM_COMMAND,ID_PICTURE_WEI);
		break;
	case '4':
		PostMessage(WM_COMMAND,ID_PICTURE_SU);
		break;
	case '5':
		PostMessage(WM_COMMAND,ID_PICTURE_JI);
		break;
	case '6':
		PostMessage(WM_COMMAND,ID_PICTURE_XIANG);
		break;
	case '7':
		PostMessage(WM_COMMAND,ID_PICTURE_QING);
		break;
	case '8':
		PostMessage(WM_COMMAND,ID_PICTURE_Q);
		break;
	case '9':
		PostMessage(WM_COMMAND,ID_PICTURE_DP);
		break;
	case '0':
		PostMessage(WM_COMMAND,ID_PICTURE_N);
		break;
	default:
		;
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}




void CPSO1View::MaxMin(double* state, UINT n, double& max, double& min)
{
	max=state[0];
	min=state[0];
	for(UINT i=1;i<n;i++)
	{
		if(max<state[i])
		{
			max=state[i];
		}
		else if(min>state[i])
		{
			min=state[i];
		}
	}
}


void CPSO1View::OnPictureJing()
{
	m_picFlag=2;
	m_reFlag=0;
	if(GetDocument()->m_bestControl.IsEmpty())
	{
		if(IDOK==MessageBox("点击确定会运行程序来输出图形"))
		{
			GetDocument()->OnStart();
			PostMessage(WM_PAINT);
		}
		return;
	}
	Invalidate();
	OnPaint();
	// TODO: Add your command handler code here
	CPSO1Doc* doc=GetDocument();
	CClientDC dc(this);
	double xmax=doc->m_bestTime,xmin=0;
	double ymax,ymin;
	double* y1,*y2;
	double* x1,*x2;
	UINT n1,n2;
	CRect rect;
	GetClientRect(rect);
	CPoint point(rect.right/16,rect.bottom*8/9);

	n1=doc->m_stateN;

	n2=doc->m_picN;

	y1=new double[n1];
	y2=new double[n2];
	x1=new double[n1];
	x2=new double[n2];
	for(UINT i=0;i<n1;i++)
	{
		y1[i]=doc->m_state2.GetAt(i);
		x1[i]=doc->m_bestTime*i/(n1-1);
	}
	for(UINT i=0;i<n2;i++)
	{
		y2[i]=doc->m_picstate2.GetAt(i);
		x2[i]=doc->m_bestTime*i/(n2-1);		
	}
	MaxMin(y2,n2,ymax,ymin);

	CBrush* old=dc.SelectObject(CBrush::FromHandle((HBRUSH)GetStockObject(BLACK_BRUSH)));
	CPen pen(PS_SOLID,2,RGB(0,0,0));
	CPen* oldpen=dc.SelectObject(&pen);	
	CPoint point1(rect.right/16,rect.bottom*8/9);
	double yscale=(rect.bottom*6/9)/(ymax-ymin);
	double xscale=(rect.right*13/16)/(xmax-xmin);
	
	LONG xtemp,ytemp;
	if(doc->m_picOption2)
	{
		xtemp=(LONG)((x2[0]-xmin)*xscale)+point.x;
		ytemp=(LONG)(-(y2[0]-ymin)*yscale)+point.y;
		dc.MoveTo(xtemp,ytemp);
		for(UINT i=1;i<n2;i++)
		{
			xtemp=(LONG)((x2[i]-xmin)*xscale)+point.x;
			ytemp=(LONG)(-(y2[i]-ymin)*yscale)+point.y;
			dc.LineTo(xtemp,ytemp);
		}
	}
	if(doc->m_picOption1)
	{
		for(UINT i=0;i<n1;i++)
		{
			xtemp=(LONG)((x1[i]-xmin)*xscale)+point.x;
			ytemp=(LONG)(-(y1[i]-ymin)*yscale)+point.y;
			dc.Ellipse(xtemp-3,ytemp-3,xtemp+3,ytemp+3);
		}
	}
	//for(UINT i=0;i<n;i++)
	//{
	//	scale=(state1[i]-min)/h;

	//	dc.MoveTo(point1.x,point1.y+3);
	//	dc.LineTo(point1.x,point1.y-6);

	//	//dc.MoveTo(point2.x-3,point2.y);
	//	//dc.LineTo(point2.x+6,point2.y);
	//	
	//	
	//	dc.Ellipse(point1.x-3,int(point1.y-scale*rect.bottom*2/3-3),point1.x+3,int(point1.y-scale*rect.bottom*2/3+3));
	//	
	//	point1.x += rect.right*7/8/xn;	
	//	//point2.y -= rect.bottom*7/9/n;	
	//}
	dc.SelectObject(old);
	dc.SelectObject(oldpen);

	dc.MoveTo(point.x-3,rect.bottom*2/9);
	dc.LineTo(point.x+6,rect.bottom*2/9);
	CString temp;
	temp.Format("%f",ymax*180/3.1416);
	TextOut(dc,10,rect.bottom*2/9-10,temp,temp.GetLength()-2);
	temp.Format("%f",ymin*180/3.1416);
	TextOut(dc,10,rect.bottom*8/9-10,temp,temp.GetLength()-2);
	temp.Format("经度/deg");
	TextOut(dc,20,rect.bottom/9,temp,temp.GetLength());
	temp.Format("时间/s");
	TextOut(dc,rect.right*15/16+10,rect.bottom*8/9+5,temp,temp.GetLength());
	temp.Format("%f",xmax);
	TextOut(dc,rect.right*14/16,rect.bottom*8/9+10,temp,8);
	temp.Format("%f",xmin);
	TextOut(dc,rect.right/16,rect.bottom*8/9+10,temp,8);

	CString str;
	str.Format("最大值:%f,最小值:%f,时间:%f",ymax*180/3.1416,ymin*180/3.1416,doc->m_bestTime);
	dc.TextOut(rect.right/2-150,rect.bottom/9-40,str,str.GetLength());
	if(doc->m_finalflag1)
	{
		str.Format("终端:%f",y2[n2-1]*180/3.1416);
		dc.TextOutA(rect.right/2-150,rect.bottom/9-20,str);
	}
	m_reFlag=1;
	delete(y1);
	delete(y2);
	delete(x1);
	delete(x2);
}


void CPSO1View::OnPictureWei()
{
	m_picFlag=3;
	m_reFlag=0;
	if(GetDocument()->m_bestControl.IsEmpty())
	{
		if(IDOK==MessageBox("点击确定会运行程序来输出图形"))
		{
			GetDocument()->OnStart();
			PostMessage(WM_PAINT);
		}		
		return;
	}
	Invalidate();
	OnPaint();
	// TODO: Add your command handler code here
	CPSO1Doc* doc=GetDocument();
	CClientDC dc(this);
	double xmax=doc->m_bestTime,xmin=0;
	double ymax,ymin;
	double* y1,*y2;
	double* x1,*x2;
	UINT n1,n2;
	CRect rect;
	GetClientRect(rect);
	CPoint point(rect.right/16,rect.bottom*8/9);

	n1=doc->m_stateN;

	n2=doc->m_picN;

	y1=new double[n1];
	y2=new double[n2];
	x1=new double[n1];
	x2=new double[n2];
	for(UINT i=0;i<n1;i++)
	{
		y1[i]=doc->m_state3.GetAt(i);
		x1[i]=doc->m_bestTime*i/(n1-1);
	}
	for(UINT i=0;i<n2;i++)
	{
		y2[i]=doc->m_picstate3.GetAt(i);
		x2[i]=doc->m_bestTime*i/(n2-1);		
	}
	MaxMin(y2,n2,ymax,ymin);

	CBrush* old=dc.SelectObject(CBrush::FromHandle((HBRUSH)GetStockObject(BLACK_BRUSH)));
	CPen pen(PS_SOLID,2,RGB(0,0,0));
	CPen* oldpen=dc.SelectObject(&pen);
	CPoint point1(rect.right/16,rect.bottom*8/9);
	double yscale=(rect.bottom*6/9)/(ymax-ymin);
	double xscale=(rect.right*13/16)/(xmax-xmin);
	
	LONG xtemp,ytemp;
	if(doc->m_picOption2)
	{
		xtemp=(LONG)((x2[0]-xmin)*xscale)+point.x;
		ytemp=(LONG)(-(y2[0]-ymin)*yscale)+point.y;
		dc.MoveTo(xtemp,ytemp);
		for(UINT i=1;i<n2;i++)
		{
			xtemp=(LONG)((x2[i]-xmin)*xscale)+point.x;
			ytemp=(LONG)(-(y2[i]-ymin)*yscale)+point.y;
			dc.LineTo(xtemp,ytemp);
		}
	}
	if(doc->m_picOption1)
	{
		for(UINT i=0;i<n1;i++)
		{
			xtemp=(LONG)((x1[i]-xmin)*xscale)+point.x;
			ytemp=(LONG)(-(y1[i]-ymin)*yscale)+point.y;
			dc.Ellipse(xtemp-3,ytemp-3,xtemp+3,ytemp+3);
		}
	}
	//for(UINT i=0;i<n;i++)
	//{
	//	scale=(state1[i]-min)/h;

	//	dc.MoveTo(point1.x,point1.y+3);
	//	dc.LineTo(point1.x,point1.y-6);

	//	//dc.MoveTo(point2.x-3,point2.y);
	//	//dc.LineTo(point2.x+6,point2.y);
	//	
	//	
	//	dc.Ellipse(point1.x-3,int(point1.y-scale*rect.bottom*2/3-3),point1.x+3,int(point1.y-scale*rect.bottom*2/3+3));
	//	
	//	point1.x += rect.right*7/8/xn;	
	//	//point2.y -= rect.bottom*7/9/n;	
	//}
	dc.SelectObject(old);
	dc.SelectObject(oldpen);

	dc.MoveTo(point.x-3,rect.bottom*2/9);
	dc.LineTo(point.x+6,rect.bottom*2/9);
	CString temp;
	temp.Format("%f",ymax*180/3.1416);
	TextOut(dc,10,rect.bottom*2/9-10,temp,temp.GetLength()-2);
	temp.Format("%f",ymin*180/3.1416);
	TextOut(dc,10,rect.bottom*8/9-10,temp,temp.GetLength()-2);
	temp.Format("纬度/deg");
	TextOut(dc,20,rect.bottom/9,temp,temp.GetLength());
	temp.Format("时间/s");
	TextOut(dc,rect.right*15/16+10,rect.bottom*8/9+5,temp,temp.GetLength());
	temp.Format("%f",xmax);
	TextOut(dc,rect.right*14/16,rect.bottom*8/9+10,temp,8);
	temp.Format("%f",xmin);
	TextOut(dc,rect.right/16,rect.bottom*8/9+10,temp,8);

	CString str;
	str.Format("最大值:%f,最小值:%f,时间:%f",ymax*180/3.1416,ymin*180/3.1416,doc->m_bestTime);
	dc.TextOut(rect.right/2-150,rect.bottom/9-40,str,str.GetLength());
	if(doc->m_finalflag1)
	{
		str.Format("终端:%f",y2[n2-1]*180/3.1416);
		dc.TextOutA(rect.right/2-150,rect.bottom/9-20,str);
	}
	m_reFlag=1;
	delete(y1);
	delete(y2);
	delete(x1);
	delete(x2);
}


void CPSO1View::OnPictureJi()
{
	m_picFlag=5;
	m_reFlag=0;
	if(GetDocument()->m_bestControl.IsEmpty())
	{
		if(IDOK==MessageBox("点击确定会运行程序来输出图形"))
		{
			GetDocument()->OnStart();
			PostMessage(WM_PAINT);
		}
		return;
	}
	Invalidate();
	OnPaint();
	// TODO: Add your command handler code here
	CPSO1Doc* doc=GetDocument();
	CClientDC dc(this);
	double xmax=doc->m_bestTime,xmin=0;
	double ymax,ymin;
	double* y1,*y2;
	double* x1,*x2;
	UINT n1,n2;
	CRect rect;
	GetClientRect(rect);
	CPoint point(rect.right/16,rect.bottom*8/9);

	n1=doc->m_stateN;

	n2=doc->m_picN;

	y1=new double[n1];
	y2=new double[n2];
	x1=new double[n1];
	x2=new double[n2];
	for(UINT i=0;i<n1;i++)
	{
		y1[i]=doc->m_state5.GetAt(i);
		x1[i]=doc->m_bestTime*i/(n1-1);
	}
	for(UINT i=0;i<n2;i++)
	{
		y2[i]=doc->m_picstate5.GetAt(i);
		x2[i]=doc->m_bestTime*i/(n2-1);		
	}
	MaxMin(y2,n2,ymax,ymin);

	CBrush* old=dc.SelectObject(CBrush::FromHandle((HBRUSH)GetStockObject(BLACK_BRUSH)));
	CPen pen(PS_SOLID,2,RGB(0,0,0));
	CPen* oldpen=dc.SelectObject(&pen);
	
	CPoint point1(rect.right/16,rect.bottom*8/9);
	double yscale=(rect.bottom*6/9)/(ymax-ymin);
	double xscale=(rect.right*13/16)/(xmax-xmin);
	
	LONG xtemp,ytemp;
	if(doc->m_picOption2)
	{
		xtemp=(LONG)((x2[0]-xmin)*xscale)+point.x;
		ytemp=(LONG)(-(y2[0]-ymin)*yscale)+point.y;
		dc.MoveTo(xtemp,ytemp);
		for(UINT i=1;i<n2;i++)
		{
			xtemp=(LONG)((x2[i]-xmin)*xscale)+point.x;
			ytemp=(LONG)(-(y2[i]-ymin)*yscale)+point.y;
			dc.LineTo(xtemp,ytemp);
		}
	}
	if(doc->m_picOption1)
	{
		for(UINT i=0;i<n1;i++)
		{
			xtemp=(LONG)((x1[i]-xmin)*xscale)+point.x;
			ytemp=(LONG)(-(y1[i]-ymin)*yscale)+point.y;
			dc.Ellipse(xtemp-3,ytemp-3,xtemp+3,ytemp+3);
		}
	}
	//for(UINT i=0;i<n;i++)
	//{
	//	scale=(state1[i]-min)/h;

	//	dc.MoveTo(point1.x,point1.y+3);
	//	dc.LineTo(point1.x,point1.y-6);

	//	//dc.MoveTo(point2.x-3,point2.y);
	//	//dc.LineTo(point2.x+6,point2.y);
	//	
	//	
	//	dc.Ellipse(point1.x-3,int(point1.y-scale*rect.bottom*2/3-3),point1.x+3,int(point1.y-scale*rect.bottom*2/3+3));
	//	
	//	point1.x += rect.right*7/8/xn;	
	//	//point2.y -= rect.bottom*7/9/n;	
	//}
	dc.SelectObject(old);
	dc.SelectObject(oldpen);

	dc.MoveTo(point.x-3,rect.bottom*2/9);
	dc.LineTo(point.x+6,rect.bottom*2/9);
	CString temp;
	temp.Format("%f",ymax*180/3.1416);
	TextOut(dc,10,rect.bottom*2/9-10,temp,temp.GetLength()-2);
	temp.Format("%f",ymin*180/3.1416);
	TextOut(dc,10,rect.bottom*8/9-10,temp,temp.GetLength()-2);
	temp.Format("航迹角/deg");
	TextOut(dc,20,rect.bottom/9,temp,temp.GetLength());
	temp.Format("时间/s");
	TextOut(dc,rect.right*15/16+10,rect.bottom*8/9+5,temp,temp.GetLength());
	temp.Format("%f",xmax);
	TextOut(dc,rect.right*14/16,rect.bottom*8/9+10,temp,8);
	temp.Format("%f",xmin);
	TextOut(dc,rect.right/16,rect.bottom*8/9+10,temp,8);

	CString str;
	str.Format("最大值:%f,最小值:%f,时间:%f",ymax*180/3.1416,ymin*180/3.1416,doc->m_bestTime);
	dc.TextOut(rect.right/2-150,rect.bottom/9-40,str,str.GetLength());
	if(doc->m_finalflag1)
	{
		str.Format("终端:%f",y2[n2-1]*180/3.1416);
		dc.TextOutA(rect.right/2-150,rect.bottom/9-20,str);
	}
	m_reFlag=1;
	delete(y1);
	delete(y2);
	delete(x1);
	delete(x2);
}


void CPSO1View::OnPictureSu()
{
	m_picFlag=5;
	m_reFlag=0;
	if(GetDocument()->m_bestControl.IsEmpty())
	{
		if(IDOK==MessageBox("点击确定会运行程序来输出图形"))
		{
			GetDocument()->OnStart();
			PostMessage(WM_PAINT);
		}
		return;
	}
	Invalidate();
	OnPaint();
	// TODO: Add your command handler code here
	CPSO1Doc* doc=GetDocument();
	CClientDC dc(this);
	double xmax=doc->m_bestTime,xmin=0;
	double ymax,ymin;
	double* y1,*y2;
	double* x1,*x2;
	UINT n1,n2;
	CRect rect;
	GetClientRect(rect);
	CPoint point(rect.right/16,rect.bottom*8/9);

	n1=doc->m_stateN;

	n2=doc->m_picN;

	y1=new double[n1];
	y2=new double[n2];
	x1=new double[n1];
	x2=new double[n2];
	for(UINT i=0;i<n1;i++)
	{
		y1[i]=doc->m_state4.GetAt(i);
		x1[i]=doc->m_bestTime*i/(n1-1);
	}
	for(UINT i=0;i<n2;i++)
	{
		y2[i]=doc->m_picstate4.GetAt(i);
		x2[i]=doc->m_bestTime*i/(n2-1);		
	}
	MaxMin(y2,n2,ymax,ymin);

	CBrush* old=dc.SelectObject(CBrush::FromHandle((HBRUSH)GetStockObject(BLACK_BRUSH)));
	CPen pen(PS_SOLID,2,RGB(0,0,0));
	CPen* oldpen=dc.SelectObject(&pen);
	CPoint point1(rect.right/16,rect.bottom*8/9);
	double yscale=(rect.bottom*6/9)/(ymax-ymin);
	double xscale=(rect.right*13/16)/(xmax-xmin);
	
	LONG xtemp,ytemp;
	if(doc->m_picOption2)
	{
		xtemp=(LONG)((x2[0]-xmin)*xscale)+point.x;
		ytemp=(LONG)(-(y2[0]-ymin)*yscale)+point.y;
		dc.MoveTo(xtemp,ytemp);
		for(UINT i=1;i<n2;i++)
		{
			xtemp=(LONG)((x2[i]-xmin)*xscale)+point.x;
			ytemp=(LONG)(-(y2[i]-ymin)*yscale)+point.y;
			dc.LineTo(xtemp,ytemp);
		}
	}
	if(doc->m_picOption1)
	{
		for(UINT i=0;i<n1;i++)
		{
			xtemp=(LONG)((x1[i]-xmin)*xscale)+point.x;
			ytemp=(LONG)(-(y1[i]-ymin)*yscale)+point.y;
			dc.Ellipse(xtemp-3,ytemp-3,xtemp+3,ytemp+3);
		}
	}
	//for(UINT i=0;i<n;i++)
	//{
	//	scale=(state1[i]-min)/h;

	//	dc.MoveTo(point1.x,point1.y+3);
	//	dc.LineTo(point1.x,point1.y-6);

	//	//dc.MoveTo(point2.x-3,point2.y);
	//	//dc.LineTo(point2.x+6,point2.y);
	//	
	//	
	//	dc.Ellipse(point1.x-3,int(point1.y-scale*rect.bottom*2/3-3),point1.x+3,int(point1.y-scale*rect.bottom*2/3+3));
	//	
	//	point1.x += rect.right*7/8/xn;	
	//	//point2.y -= rect.bottom*7/9/n;	
	//}
	dc.SelectObject(old);
	dc.SelectObject(oldpen);

	dc.MoveTo(point.x-3,rect.bottom*2/9);
	dc.LineTo(point.x+6,rect.bottom*2/9);
	CString temp;
	temp.Format("%f",ymax);
	TextOut(dc,10,rect.bottom*2/9-10,temp,temp.GetLength()-2);
	temp.Format("%f",ymin);
	TextOut(dc,10,rect.bottom*8/9-10,temp,temp.GetLength()-2);
	temp.Format("速度/m/s");
	TextOut(dc,20,rect.bottom/9,temp,temp.GetLength());
	temp.Format("时间/s");
	TextOut(dc,rect.right*15/16+10,rect.bottom*8/9+5,temp,temp.GetLength());
	temp.Format("%f",xmax);
	TextOut(dc,rect.right*14/16,rect.bottom*8/9+10,temp,8);
	temp.Format("%f",xmin);
	TextOut(dc,rect.right/16,rect.bottom*8/9+10,temp,8);

	CString str;
	str.Format("最大值:%f,最小值:%f,时间:%f",ymax,ymin,doc->m_bestTime);
	dc.TextOut(rect.right/2-150,rect.bottom/9-40,str,str.GetLength());
	if(doc->m_finalflag1)
	{
		str.Format("终端:%f",y2[n2-1]);
		dc.TextOutA(rect.right/2-150,rect.bottom/9-20,str);
	}
	m_reFlag=1;
	delete(y1);
	delete(y2);
	delete(x1);
	delete(x2);
}


void CPSO1View::OnPictureXiang()
{
	m_picFlag=6;
	m_reFlag=0;
	if(GetDocument()->m_bestControl.IsEmpty())
	{
		if(IDOK==MessageBox("点击确定会运行程序来输出图形"))
		{
			GetDocument()->OnStart();
			PostMessage(WM_PAINT);
		}
		return;
	}
	Invalidate();
	OnPaint();
	// TODO: Add your command handler code here
	CPSO1Doc* doc=GetDocument();
	CClientDC dc(this);
	double xmax=doc->m_bestTime,xmin=0;
	double ymax,ymin;
	double* y1,*y2;
	double* x1,*x2;
	UINT n1,n2;
	CRect rect;
	GetClientRect(rect);
	CPoint point(rect.right/16,rect.bottom*8/9);

	n1=doc->m_stateN;

	n2=doc->m_picN;

	y1=new double[n1];
	y2=new double[n2];
	x1=new double[n1];
	x2=new double[n2];
	for(UINT i=0;i<n1;i++)
	{
		y1[i]=doc->m_state6.GetAt(i);
		x1[i]=doc->m_bestTime*i/(n1-1);
	}
	for(UINT i=0;i<n2;i++)
	{
		y2[i]=doc->m_picstate6.GetAt(i);
		x2[i]=doc->m_bestTime*i/(n2-1);		
	}
	MaxMin(y2,n2,ymax,ymin);

	CBrush* old=dc.SelectObject(CBrush::FromHandle((HBRUSH)GetStockObject(BLACK_BRUSH)));
	CPen pen(PS_SOLID,2,RGB(0,0,0));
	CPen* oldpen=dc.SelectObject(&pen);
	CPoint point1(rect.right/16,rect.bottom*8/9);
	double yscale=(rect.bottom*6/9)/(ymax-ymin);
	double xscale=(rect.right*13/16)/(xmax-xmin);
	
	LONG xtemp,ytemp;
	if(doc->m_picOption2)
	{
		xtemp=(LONG)((x2[0]-xmin)*xscale)+point.x;
		ytemp=(LONG)(-(y2[0]-ymin)*yscale)+point.y;
		dc.MoveTo(xtemp,ytemp);
		for(UINT i=1;i<n2;i++)
		{
			xtemp=(LONG)((x2[i]-xmin)*xscale)+point.x;
			ytemp=(LONG)(-(y2[i]-ymin)*yscale)+point.y;
			dc.LineTo(xtemp,ytemp);
		}
	}
	if(doc->m_picOption1)
	{
		for(UINT i=0;i<n1;i++)
		{
			xtemp=(LONG)((x1[i]-xmin)*xscale)+point.x;
			ytemp=(LONG)(-(y1[i]-ymin)*yscale)+point.y;
			dc.Ellipse(xtemp-3,ytemp-3,xtemp+3,ytemp+3);
		}
	}
	//for(UINT i=0;i<n;i++)
	//{
	//	scale=(state1[i]-min)/h;

	//	dc.MoveTo(point1.x,point1.y+3);
	//	dc.LineTo(point1.x,point1.y-6);

	//	//dc.MoveTo(point2.x-3,point2.y);
	//	//dc.LineTo(point2.x+6,point2.y);
	//	
	//	
	//	dc.Ellipse(point1.x-3,int(point1.y-scale*rect.bottom*2/3-3),point1.x+3,int(point1.y-scale*rect.bottom*2/3+3));
	//	
	//	point1.x += rect.right*7/8/xn;	
	//	//point2.y -= rect.bottom*7/9/n;	
	//}
	dc.SelectObject(old);
	dc.SelectObject(oldpen);
	dc.MoveTo(point.x-3,rect.bottom*2/9);
	dc.LineTo(point.x+6,rect.bottom*2/9);
	CString temp;
	temp.Format("%f",ymax*180/3.1416);
	TextOut(dc,10,rect.bottom*2/9-10,temp,temp.GetLength()-2);
	temp.Format("%f",ymin*180/3.1416);
	TextOut(dc,10,rect.bottom*8/9-10,temp,temp.GetLength()-2);
	temp.Format("航迹角/deg");
	TextOut(dc,20,rect.bottom/9,temp,temp.GetLength());
	temp.Format("时间/s");
	TextOut(dc,rect.right*15/16+10,rect.bottom*8/9+5,temp,temp.GetLength());
	temp.Format("%f",xmax);
	TextOut(dc,rect.right*14/16,rect.bottom*8/9+10,temp,8);
	temp.Format("%f",xmin);
	TextOut(dc,rect.right/16,rect.bottom*8/9+10,temp,8);

	CString str;
	str.Format("最大值:%f,最小值:%f,时间:%f",ymax*180/3.1416,ymin*180/3.1416,doc->m_bestTime);
	dc.TextOut(rect.right/2-150,rect.bottom/9-40,str,str.GetLength());
	if(doc->m_finalflag1)
	{
		str.Format("终端:%f",y2[n2-1]*180/3.1416);
		dc.TextOutA(rect.right/2-150,rect.bottom/9-20,str);
	}
	m_reFlag=1;
	delete(y1);
	delete(y2);
	delete(x1);
	delete(x2);
}


void CPSO1View::OnPictureQ()
{
	m_picFlag=8;
	m_reFlag=0;
	if(GetDocument()->m_bestControl.IsEmpty())
	{
		if(IDOK==MessageBox("点击确定会运行程序来输出图形"))
		{
			GetDocument()->OnStart();
			PostMessage(WM_PAINT);
		}
		return;
	}
	Invalidate();
	OnPaint();
	// TODO: Add your command handler code here
	CPSO1Doc* doc=GetDocument();
	CClientDC dc(this);
	double xmax=doc->m_bestTime,xmin=0;
	double ymax,ymin;
	double* y1,*y2;
	double* x1,*x2;
	UINT n1,n2;
	CRect rect;
	GetClientRect(rect);
	CPoint point(rect.right/16,rect.bottom*8/9);

	n1=doc->m_stateN;

	n2=doc->m_picN;

	y1=new double[n1];
	y2=new double[n2];
	x1=new double[n1];
	x2=new double[n2];
	for(UINT i=0;i<n1;i++)
	{
		y1[i]=doc->m_Q.GetAt(i);
		x1[i]=doc->m_bestTime*i/(n1-1);
	}
	for(UINT i=0;i<n2;i++)
	{
		y2[i]=doc->m_picQ.GetAt(i);
		x2[i]=doc->m_bestTime*i/(n2-1);		
	}
	MaxMin(y2,n2,ymax,ymin);

	CBrush* old=dc.SelectObject(CBrush::FromHandle((HBRUSH)GetStockObject(BLACK_BRUSH)));
	CPen pen(PS_SOLID,2,RGB(0,0,0));
	CPen* oldpen=dc.SelectObject(&pen);
	CPoint point1(rect.right/16,rect.bottom*8/9);
	double yscale=(rect.bottom*6/9)/(ymax-ymin);
	double xscale=(rect.right*13/16)/(xmax-xmin);
	
	LONG xtemp,ytemp;
	if(doc->m_picOption2)
	{
		xtemp=(LONG)((x2[0]-xmin)*xscale)+point.x;
		ytemp=(LONG)(-(y2[0]-ymin)*yscale)+point.y;
		dc.MoveTo(xtemp,ytemp);
		for(UINT i=1;i<n2;i++)
		{
			xtemp=(LONG)((x2[i]-xmin)*xscale)+point.x;
			ytemp=(LONG)(-(y2[i]-ymin)*yscale)+point.y;
			dc.LineTo(xtemp,ytemp);
		}
	}
	if(doc->m_picOption1)
	{
		for(UINT i=0;i<n1;i++)
		{
			xtemp=(LONG)((x1[i]-xmin)*xscale)+point.x;
			ytemp=(LONG)(-(y1[i]-ymin)*yscale)+point.y;
			dc.Ellipse(xtemp-3,ytemp-3,xtemp+3,ytemp+3);
		}
	}
	//for(UINT i=0;i<n;i++)
	//{
	//	scale=(state1[i]-min)/h;

	//	dc.MoveTo(point1.x,point1.y+3);
	//	dc.LineTo(point1.x,point1.y-6);

	//	//dc.MoveTo(point2.x-3,point2.y);
	//	//dc.LineTo(point2.x+6,point2.y);
	//	
	//	
	//	dc.Ellipse(point1.x-3,int(point1.y-scale*rect.bottom*2/3-3),point1.x+3,int(point1.y-scale*rect.bottom*2/3+3));
	//	
	//	point1.x += rect.right*7/8/xn;	
	//	//point2.y -= rect.bottom*7/9/n;	
	//}
	dc.SelectObject(old);
	dc.SelectObject(oldpen);
	dc.MoveTo(point.x-3,rect.bottom*2/9);
	dc.LineTo(point.x+6,rect.bottom*2/9);
	CString temp;
	temp.Format("%f",ymax);
	TextOut(dc,10,rect.bottom*2/9-10,temp,temp.GetLength()-2);
	temp.Format("%f",ymin);
	TextOut(dc,10,rect.bottom*8/9-10,temp,temp.GetLength()-2);
	temp.Format("热流密度/kW/m2");
	TextOut(dc,20,rect.bottom/9,temp,temp.GetLength());
	temp.Format("时间/s");
	TextOut(dc,rect.right*15/16+10,rect.bottom*8/9+5,temp,temp.GetLength());
	temp.Format("%f",xmax);
	TextOut(dc,rect.right*14/16,rect.bottom*8/9+10,temp,8);
	temp.Format("%f",xmin);
	TextOut(dc,rect.right/16,rect.bottom*8/9+10,temp,8);

	CString str;
	str.Format("最大值:%f,最小值:%f,时间:%f",ymax,ymin,doc->m_bestTime);
	dc.TextOut(rect.right/2-150,rect.bottom/9-40,str,str.GetLength());
	if(doc->m_finalflag1)
	{
		str.Format("终端:%f",y2[n2-1]);
		dc.TextOutA(rect.right/2-150,rect.bottom/9-20,str);
	}
	m_reFlag=1;
	delete(y1);
	delete(y2);
	delete(x1);
	delete(x2);
}


void CPSO1View::OnPictureDp()
{
	m_picFlag=9;
	m_reFlag=0;
	if(GetDocument()->m_bestControl.IsEmpty())
	{
		if(IDOK==MessageBox("点击确定会运行程序来输出图形"))
		{
			GetDocument()->OnStart();
			PostMessage(WM_PAINT);
		}
		return;
	}
	Invalidate();
	OnPaint();
	// TODO: Add your command handler code here
	CPSO1Doc* doc=GetDocument();
	CClientDC dc(this);
	double xmax=doc->m_bestTime,xmin=0;
	double ymax,ymin;
	double* y1,*y2;
	double* x1,*x2;
	UINT n1,n2;
	CRect rect;
	GetClientRect(rect);
	CPoint point(rect.right/16,rect.bottom*8/9);

	n1=doc->m_stateN;

	n2=doc->m_picN;

	y1=new double[n1];
	y2=new double[n2];
	x1=new double[n1];
	x2=new double[n2];
	for(UINT i=0;i<n1;i++)
	{
		y1[i]=doc->m_q.GetAt(i);
		x1[i]=doc->m_bestTime*i/(n1-1);
	}
	for(UINT i=0;i<n2;i++)
	{
		y2[i]=doc->m_picq.GetAt(i);
		x2[i]=doc->m_bestTime*i/(n2-1);		
	}
	MaxMin(y2,n2,ymax,ymin);

	CBrush* old=dc.SelectObject(CBrush::FromHandle((HBRUSH)GetStockObject(BLACK_BRUSH)));
	CPen pen(PS_SOLID,2,RGB(0,0,0));
	CPen* oldpen=dc.SelectObject(&pen);
	
	CPoint point1(rect.right/16,rect.bottom*8/9);
	double yscale=(rect.bottom*6/9)/(ymax-ymin);
	double xscale=(rect.right*13/16)/(xmax-xmin);
	
	LONG xtemp,ytemp;
	if(doc->m_picOption2)
	{
		xtemp=(LONG)((x2[0]-xmin)*xscale)+point.x;
		ytemp=(LONG)(-(y2[0]-ymin)*yscale)+point.y;
		dc.MoveTo(xtemp,ytemp);
		for(UINT i=1;i<n2;i++)
		{
			xtemp=(LONG)((x2[i]-xmin)*xscale)+point.x;
			ytemp=(LONG)(-(y2[i]-ymin)*yscale)+point.y;
			dc.LineTo(xtemp,ytemp);
		}
	}
	if(doc->m_picOption1)
	{
		for(UINT i=0;i<n1;i++)
		{
			xtemp=(LONG)((x1[i]-xmin)*xscale)+point.x;
			ytemp=(LONG)(-(y1[i]-ymin)*yscale)+point.y;
			dc.Ellipse(xtemp-3,ytemp-3,xtemp+3,ytemp+3);
		}
	}
	//for(UINT i=0;i<n;i++)
	//{
	//	scale=(state1[i]-min)/h;

	//	dc.MoveTo(point1.x,point1.y+3);
	//	dc.LineTo(point1.x,point1.y-6);

	//	//dc.MoveTo(point2.x-3,point2.y);
	//	//dc.LineTo(point2.x+6,point2.y);
	//	
	//	
	//	dc.Ellipse(point1.x-3,int(point1.y-scale*rect.bottom*2/3-3),point1.x+3,int(point1.y-scale*rect.bottom*2/3+3));
	//	
	//	point1.x += rect.right*7/8/xn;	
	//	//point2.y -= rect.bottom*7/9/n;	
	//}
	dc.SelectObject(old);
	dc.SelectObject(oldpen);
	dc.MoveTo(point.x-3,rect.bottom*2/9);
	dc.LineTo(point.x+6,rect.bottom*2/9);
	CString temp;
	temp.Format("%f",ymax/1000);
	TextOut(dc,10,rect.bottom*2/9-10,temp,temp.GetLength()-2);
	temp.Format("%f",ymin/1000);
	TextOut(dc,10,rect.bottom*8/9-10,temp,temp.GetLength()-2);
	temp.Format("动压/kPa");
	TextOut(dc,20,rect.bottom/9,temp,temp.GetLength());
	temp.Format("时间/s");
	TextOut(dc,rect.right*15/16+10,rect.bottom*8/9+5,temp,temp.GetLength());
	temp.Format("%f",xmax);
	TextOut(dc,rect.right*14/16,rect.bottom*8/9+10,temp,8);
	temp.Format("%f",xmin);
	TextOut(dc,rect.right/16,rect.bottom*8/9+10,temp,8);

	CString str;
	str.Format("最大值:%f,最小值:%f,时间:%f",ymax/1000,ymin/1000,doc->m_bestTime);
	dc.TextOut(rect.right/2-150,rect.bottom/9-40,str,str.GetLength());
	if(doc->m_finalflag1)
	{
		str.Format("终端:%f",y2[n2-1]/1000);
		dc.TextOutA(rect.right/2-150,rect.bottom/9-20,str);
	}
	m_reFlag=1;
	delete(y1);
	delete(y2);
	delete(x1);
	delete(x2);
}


void CPSO1View::OnPictureN()
{
	m_picFlag=10;
	m_reFlag=0;
	if(GetDocument()->m_bestControl.IsEmpty())
	{
		if(IDOK==MessageBox("点击确定会运行程序来输出图形"))
		{
			GetDocument()->OnStart();
			PostMessage(WM_PAINT);
		}
		return;
	}
	Invalidate();
	OnPaint();
	// TODO: Add your command handler code here
	CPSO1Doc* doc=GetDocument();
	CClientDC dc(this);
	double xmax=doc->m_bestTime,xmin=0;
	double ymax,ymin;
	double* y1,*y2;
	double* x1,*x2;
	UINT n1,n2;
	CRect rect;
	GetClientRect(rect);
	CPoint point(rect.right/16,rect.bottom*8/9);

	n1=doc->m_stateN;

	n2=doc->m_picN;

	y1=new double[n1];
	y2=new double[n2];
	x1=new double[n1];
	x2=new double[n2];
	for(UINT i=0;i<n1;i++)
	{
		y1[i]=doc->m_nLimit.GetAt(i);
		x1[i]=doc->m_bestTime*i/(n1-1);
	}
	for(UINT i=0;i<n2;i++)
	{
		y2[i]=doc->m_picnLimit.GetAt(i);
		x2[i]=doc->m_bestTime*i/(n2-1);		
	}
	MaxMin(y2,n2,ymax,ymin);

	CBrush* old=dc.SelectObject(CBrush::FromHandle((HBRUSH)GetStockObject(BLACK_BRUSH)));
	CPen pen(PS_SOLID,2,RGB(0,0,0));
	CPen* oldpen=dc.SelectObject(&pen);
	CPoint point1(rect.right/16,rect.bottom*8/9);
	double yscale=(rect.bottom*6/9)/(ymax-ymin);
	double xscale=(rect.right*13/16)/(xmax-xmin);
	
	LONG xtemp,ytemp;
	if(doc->m_picOption2)
	{
		xtemp=(LONG)((x2[0]-xmin)*xscale)+point.x;
		ytemp=(LONG)(-(y2[0]-ymin)*yscale)+point.y;
		dc.MoveTo(xtemp,ytemp);
		for(UINT i=1;i<n2;i++)
		{
			xtemp=(LONG)((x2[i]-xmin)*xscale)+point.x;
			ytemp=(LONG)(-(y2[i]-ymin)*yscale)+point.y;
			dc.LineTo(xtemp,ytemp);
		}
	}
	if(doc->m_picOption1)
	{
		for(UINT i=0;i<n1;i++)
		{
			xtemp=(LONG)((x1[i]-xmin)*xscale)+point.x;
			ytemp=(LONG)(-(y1[i]-ymin)*yscale)+point.y;
			dc.Ellipse(xtemp-3,ytemp-3,xtemp+3,ytemp+3);
		}
	}
	//for(UINT i=0;i<n;i++)
	//{
	//	scale=(state1[i]-min)/h;

	//	dc.MoveTo(point1.x,point1.y+3);
	//	dc.LineTo(point1.x,point1.y-6);

	//	//dc.MoveTo(point2.x-3,point2.y);
	//	//dc.LineTo(point2.x+6,point2.y);
	//	
	//	
	//	dc.Ellipse(point1.x-3,int(point1.y-scale*rect.bottom*2/3-3),point1.x+3,int(point1.y-scale*rect.bottom*2/3+3));
	//	
	//	point1.x += rect.right*7/8/xn;	
	//	//point2.y -= rect.bottom*7/9/n;	
	//}
	dc.SelectObject(old);
	dc.SelectObject(oldpen);
	dc.MoveTo(point.x-3,rect.bottom*2/9);
	dc.LineTo(point.x+6,rect.bottom*2/9);
	CString temp;
	temp.Format("%f",ymax);
	TextOut(dc,10,rect.bottom*2/9-10,temp,temp.GetLength()-2);
	temp.Format("%f",ymin);
	TextOut(dc,10,rect.bottom*8/9-10,temp,temp.GetLength()-2);
	temp.Format("过载");
	TextOut(dc,20,rect.bottom/9,temp,temp.GetLength());
	temp.Format("时间/s");
	TextOut(dc,rect.right*15/16+10,rect.bottom*8/9+5,temp,temp.GetLength());
	temp.Format("%f",xmax);
	TextOut(dc,rect.right*14/16,rect.bottom*8/9+10,temp,8);
	temp.Format("%f",xmin);
	TextOut(dc,rect.right/16,rect.bottom*8/9+10,temp,8);

	CString str;
	str.Format("最大值:%f,最小值:%f,时间:%f",ymax,ymin,doc->m_bestTime);
	dc.TextOut(rect.right/2-150,rect.bottom/9-40,str,str.GetLength());
	if(doc->m_finalflag1)
	{
		str.Format("终端:%f",y2[n2-1]);
		dc.TextOutA(rect.right/2-150,rect.bottom/9-20,str);
	}
	m_reFlag=1;
	delete(y1);
	delete(y2);
	delete(x1);
	delete(x2);
}


void CPSO1View::OnPictureHV()
{
	m_picFlag=11;
	m_reFlag=0;
	if(GetDocument()->m_bestControl.IsEmpty())
	{
		if(IDOK==MessageBox("点击确定会运行程序来输出图形"))
		{
			GetDocument()->OnStart();
			PostMessage(WM_PAINT);
		}
		return;
	}
	Invalidate();
	OnPaint();
	// TODO: Add your command handler code here
	CPSO1Doc* doc=GetDocument();
	CClientDC dc(this);
	double xmax,xmin;
	double ymax,ymin;
	double* y1,*y2;
	double* x1,*x2;
	UINT n1,n2;
	CRect rect;
	GetClientRect(rect);
	CPoint point(rect.right/16,rect.bottom*8/9);

	n1=doc->m_stateN;

	n2=doc->m_picN;

	y1=new double[n1];
	y2=new double[n2];
	x1=new double[n1];
	x2=new double[n2];
	for(UINT i=0;i<n1;i++)
	{
		y1[i]=doc->m_state1.GetAt(i);
		x1[i]=doc->m_state4.GetAt(i);
	}
	for(UINT i=0;i<n2;i++)
	{
		y2[i]=doc->m_picstate1.GetAt(i);
		x2[i]=doc->m_picstate4.GetAt(i);		
	}
	MaxMin(y2,n2,ymax,ymin);
	MaxMin(x2,n2,xmax,xmin);

	CBrush* old=dc.SelectObject(CBrush::FromHandle((HBRUSH)GetStockObject(BLACK_BRUSH)));
	CPen pen(PS_SOLID,2,RGB(0,0,0));
	CPen* oldpen=dc.SelectObject(&pen);
	CPoint point1(rect.right/16,rect.bottom*8/9);
	double yscale=(rect.bottom*6/9)/(ymax-ymin);
	double xscale=(rect.right*13/16)/(xmax-xmin);
	
	LONG xtemp,ytemp;
	if(doc->m_picOption2)
	{
		xtemp=(LONG)((x2[0]-xmin)*xscale)+point.x;
		ytemp=(LONG)(-(y2[0]-ymin)*yscale)+point.y;
		dc.MoveTo(xtemp,ytemp);
		for(UINT i=1;i<n2;i++)
		{
			xtemp=(LONG)((x2[i]-xmin)*xscale)+point.x;
			ytemp=(LONG)(-(y2[i]-ymin)*yscale)+point.y;
			dc.LineTo(xtemp,ytemp);
		}
	}
	if(doc->m_picOption1)
	{
		for(UINT i=0;i<n1;i++)
		{
			xtemp=(LONG)((x1[i]-xmin)*xscale)+point.x;
			ytemp=(LONG)(-(y1[i]-ymin)*yscale)+point.y;
			dc.Ellipse(xtemp-3,ytemp-3,xtemp+3,ytemp+3);
		}
	}
	//for(UINT i=0;i<n;i++)
	//{
	//	scale=(state1[i]-min)/h;

	//	dc.MoveTo(point1.x,point1.y+3);
	//	dc.LineTo(point1.x,point1.y-6);

	//	//dc.MoveTo(point2.x-3,point2.y);
	//	//dc.LineTo(point2.x+6,point2.y);
	//	
	//	
	//	dc.Ellipse(point1.x-3,int(point1.y-scale*rect.bottom*2/3-3),point1.x+3,int(point1.y-scale*rect.bottom*2/3+3));
	//	
	//	point1.x += rect.right*7/8/xn;	
	//	//point2.y -= rect.bottom*7/9/n;	
	//}
	dc.SelectObject(old);
	dc.SelectObject(oldpen);
	dc.MoveTo(point.x-3,rect.bottom*2/9);
	dc.LineTo(point.x+6,rect.bottom*2/9);
	CString temp;
	temp.Format("%f",(ymax-6378000)/1000);
	TextOut(dc,10,rect.bottom*2/9-10,temp,temp.GetLength()-2);
	temp.Format("%f",(ymin-6378000)/1000);
	TextOut(dc,10,rect.bottom*8/9-10,temp,temp.GetLength()-2);
	temp.Format("高度/km");
	TextOut(dc,20,rect.bottom/9,temp,temp.GetLength());
	temp.Format("速度/m/s");
	TextOut(dc,rect.right*15/16+10,rect.bottom*8/9+5,temp,temp.GetLength());
	temp.Format("%f",xmax);
	TextOut(dc,rect.right*14/16,rect.bottom*8/9+10,temp,8);
	temp.Format("%f",xmin);
	TextOut(dc,rect.right/16,rect.bottom*8/9+10,temp,8);

	m_reFlag=1;
	delete(y1);
	delete(y2);
	delete(x1);
	delete(x2);
}


void CPSO1View::OnPictureJW()
{
	m_picFlag=12;
	m_reFlag=0;
	if(GetDocument()->m_bestControl.IsEmpty())
	{
		if(IDOK==MessageBox("点击确定会运行程序来输出图形"))
		{
			GetDocument()->OnStart();
			PostMessage(WM_PAINT);
		}
		return;
	}
	Invalidate();
	OnPaint();
	//NoflyPaint();
	// TODO: Add your command handler code here
	CPSO1Doc* doc=GetDocument();
	CClientDC dc(this);
	double xmax,xmin;
	double ymax,ymin;
	double* y1,*y2;
	double* x1,*x2;
	UINT n1,n2;
	CRect rect;
	GetClientRect(rect);
	CPoint point(rect.right/16,rect.bottom*8/9);

	n1=doc->m_stateN;

	n2=doc->m_picN;

	y1=new double[n1];
	y2=new double[n2];
	x1=new double[n1];
	x2=new double[n2];
	for(UINT i=0;i<n1;i++)
	{
		y1[i]=doc->m_state3.GetAt(i);
		x1[i]=doc->m_state2.GetAt(i);
	}
	for(UINT i=0;i<n2;i++)
	{
		y2[i]=doc->m_picstate3.GetAt(i);
		x2[i]=doc->m_picstate2.GetAt(i);		
	}
	MaxMin(y2,n2,ymax,ymin);
	MaxMin(x2,n2,xmax,xmin);

	CBrush* old=dc.SelectObject(CBrush::FromHandle((HBRUSH)GetStockObject(BLACK_BRUSH)));
	CPen pen(PS_SOLID,2,RGB(0,0,0));
	CPen* oldpen=dc.SelectObject(&pen);
	CPoint point1(rect.right/16,rect.bottom*8/9);
	double yscale=(rect.bottom*6/9)/(ymax-ymin);
	double xscale=(rect.right*13/16)/(xmax-xmin);
	
	LONG xtemp,ytemp;
	if(doc->m_picOption2)
	{
		xtemp=(LONG)((x2[0]-xmin)*xscale)+point.x;
		ytemp=(LONG)(-(y2[0]-ymin)*yscale)+point.y;
		dc.MoveTo(xtemp,ytemp);
		for(UINT i=1;i<n2;i++)
		{
			xtemp=(LONG)((x2[i]-xmin)*xscale)+point.x;
			ytemp=(LONG)(-(y2[i]-ymin)*yscale)+point.y;
			dc.LineTo(xtemp,ytemp);
		}
	}
	if(doc->m_picOption1)
	{
		for(UINT i=0;i<n1;i++)
		{
			xtemp=(LONG)((x1[i]-xmin)*xscale)+point.x;
			ytemp=(LONG)(-(y1[i]-ymin)*yscale)+point.y;
			dc.Ellipse(xtemp-3,ytemp-3,xtemp+3,ytemp+3);
		}
	}
	//for(UINT i=0;i<n;i++)
	//{
	//	scale=(state1[i]-min)/h;

	//	dc.MoveTo(point1.x,point1.y+3);
	//	dc.LineTo(point1.x,point1.y-6);

	//	//dc.MoveTo(point2.x-3,point2.y);
	//	//dc.LineTo(point2.x+6,point2.y);
	//	
	//	
	//	dc.Ellipse(point1.x-3,int(point1.y-scale*rect.bottom*2/3-3),point1.x+3,int(point1.y-scale*rect.bottom*2/3+3));
	//	
	//	point1.x += rect.right*7/8/xn;	
	//	//point2.y -= rect.bottom*7/9/n;	
	//}
	dc.SelectObject(old);
	dc.SelectObject(oldpen);
	dc.MoveTo(point.x-3,rect.bottom*2/9);
	dc.LineTo(point.x+6,rect.bottom*2/9);
	CString temp;
	temp.Format("%f",ymax*180/3.1416);
	TextOut(dc,10,rect.bottom*2/9-10,temp,temp.GetLength()-2);
	temp.Format("%f",ymin*180/3.1416);
	TextOut(dc,10,rect.bottom*8/9-10,temp,temp.GetLength()-2);
	temp.Format("纬度/deg");
	TextOut(dc,20,rect.bottom/9,temp,temp.GetLength());
	temp.Format("经度/deg");
	TextOut(dc,rect.right*15/16+10,rect.bottom*8/9+5,temp,temp.GetLength());
	temp.Format("%f",xmax*180/3.1416);
	TextOut(dc,rect.right*14/16,rect.bottom*8/9+10,temp,8);
	temp.Format("%f",xmin*180/3.1416);
	TextOut(dc,rect.right/16,rect.bottom*8/9+10,temp,8);

	m_reFlag=1;
	delete(y1);
	delete(y2);
	delete(x1);
	delete(x2);
}


BOOL CPSO1View::DrawDotLine(int dot_n)
{
	CClientDC dc(this);
	CRect rect;
	CPen pen(PS_DASH,1,RGB(0,0,0));
	CPen* old=dc.SelectObject(&pen);
	GetClientRect(&rect);
	for(int i=0;i<dot_n;i++)
	{
		dc.MoveTo(rect.right/16,rect.bottom*2/9+rect.bottom*6/9*i/dot_n);
		dc.LineTo(rect.right*14/16,rect.bottom*2/9+rect.bottom*6/9*i/dot_n);
	}
	dc.SelectObject(old);
	return TRUE;
}


BOOL CPSO1View::NoflyPaint(void)
{
	CPSO1Doc* doc=GetDocument();
	CClientDC dc(this);
	double xmax,xmin;
	double ymax,ymin;
	double* y1,*y2;
	double* x1,*x2;
	UINT n1,n2;
	CRect rect;
	GetClientRect(rect);
	CPoint point(rect.right/16,rect.bottom*8/9);

	n1=doc->m_stateN;

	n2=doc->m_picN;

	y1=new double[n1];
	y2=new double[n2];
	x1=new double[n1];
	x2=new double[n2];
	for(UINT i=0;i<n1;i++)
	{
		y1[i]=doc->m_state3.GetAt(i);
		x1[i]=doc->m_state2.GetAt(i);
	}
	for(UINT i=0;i<n2;i++)
	{
		y2[i]=doc->m_picstate3.GetAt(i);
		x2[i]=doc->m_picstate2.GetAt(i);		
	}
	MaxMin(y2,n2,ymax,ymin);
	MaxMin(x2,n2,xmax,xmin);

	int p_x,p_y;
	p_x=int(rect.right/16+(200*3.1416/180-xmin)/(xmax-xmin)*(rect.right*13/16));
	p_y=int(rect.bottom*8/9-(35*3.1416/180-ymin)/(ymax-ymin)*(rect.bottom*6/9));

	int minor;
	int lon;
	minor=int(5*3.1416/180/(ymax-ymin)*(rect.bottom*6/9));
	lon=int(5*3.1416/180/(xmax-xmin)*(rect.right*13/16));

	dc.Ellipse(p_x-lon,p_y-minor,p_x+lon,p_y+minor);


	return TRUE;
}


void CPSO1View::OnPaintA()
{
	// TODO: Add your command handler code here
	m_reFlag=0;
	if(GetDocument()->m_bestControl.IsEmpty())
	{
		if(IDOK==MessageBox("点击确定会运行程序来输出图形"))
		{
			GetDocument()->OnStart();
			PostMessage(WM_PAINT);
		}
		return;
	}
	Invalidate();
	OnPaint();
	// TODO: Add your command handler code here
	CPSO1Doc* doc=GetDocument();
	CClientDC dc(this);
	double xmax=doc->m_bestTime,xmin=0;
	double ymax,ymin;
	double* y1,*y2;
	double* x1,*x2;
	UINT n1,n2;
	CRect rect;
	GetClientRect(rect);
	CPoint point(rect.right/16,rect.bottom*8/9);

	n1=doc->m_d;

	n2=doc->m_picN;

	y1=new double[n1];
	y2=new double[n2];
	x1=new double[n1];
	x2=new double[n2];
	for(UINT i=0;i<n1;i++)
	{
		y1[i]=doc->m_bestControl_a.GetAt(i);
		x1[i]=doc->m_bestTime*i/(n1-1);
	}
	for(UINT i=0;i<n2;i++)
	{
		y2[i]=doc->m_picControl_a.GetAt(i);
		x2[i]=doc->m_bestTime*i/(n2-1);		
	}
	MaxMin(y2,n2,ymax,ymin);

	CBrush* old=dc.SelectObject(CBrush::FromHandle((HBRUSH)GetStockObject(BLACK_BRUSH)));
	CPen pen(PS_SOLID,2,RGB(0,0,0));
	CPen* oldpen=dc.SelectObject(&pen);
	CPoint point1(rect.right/16,rect.bottom*8/9);
	double yscale=(rect.bottom*6/9)/(ymax-ymin);
	double xscale=(rect.right*13/16)/(xmax-xmin);
	
	LONG xtemp,ytemp;
	if(doc->m_picOption2)
	{
		xtemp=(LONG)((x2[0]-xmin)*xscale)+point.x;
		ytemp=(LONG)(-(y2[0]-ymin)*yscale)+point.y;
		dc.MoveTo(xtemp,ytemp);
		for(UINT i=1;i<n2;i++)
		{
			xtemp=(LONG)((x2[i]-xmin)*xscale)+point.x;
			ytemp=(LONG)(-(y2[i]-ymin)*yscale)+point.y;
			dc.LineTo(xtemp,ytemp);
		}
	}
	if(doc->m_picOption1)
	{
		for(UINT i=0;i<n1;i++)
		{
			xtemp=(LONG)((x1[i]-xmin)*xscale)+point.x;
			ytemp=(LONG)(-(y1[i]-ymin)*yscale)+point.y;
			dc.Ellipse(xtemp-3,ytemp-3,xtemp+3,ytemp+3);
		}
	}

	//for(UINT i=0;i<n;i++)
	//{
	//	scale=(state1[i]-min)/h;

	//	dc.MoveTo(point1.x,point1.y+3);
	//	dc.LineTo(point1.x,point1.y-6);

	//	//dc.MoveTo(point2.x-3,point2.y);
	//	//dc.LineTo(point2.x+6,point2.y);
	//	
	//	
	//	dc.Ellipse(point1.x-3,int(point1.y-scale*rect.bottom*2/3-3),point1.x+3,int(point1.y-scale*rect.bottom*2/3+3));
	//	
	//	point1.x += rect.right*7/8/xn;	
	//	//point2.y -= rect.bottom*7/9/n;	
	//}
	dc.SelectObject(old);
	dc.SelectObject(oldpen);

	dc.MoveTo(point.x-3,rect.bottom*2/9);
	dc.LineTo(point.x+6,rect.bottom*2/9);
	CString temp;
	temp.Format("%f",ymax*180/3.1416);
	TextOut(dc,10,rect.bottom*2/9-10,temp,temp.GetLength()-2);
	temp.Format("%f",ymin*180/3.1416);
	TextOut(dc,10,rect.bottom*8/9-10,temp,temp.GetLength()-2);
	temp.Format("攻角/deg");
	TextOut(dc,20,rect.bottom/9,temp,temp.GetLength());
	temp.Format("时间/s");
	TextOut(dc,rect.right*15/16+10,rect.bottom*8/9+5,temp,temp.GetLength());
	temp.Format("%f",xmax);
	TextOut(dc,rect.right*14/16,rect.bottom*8/9+10,temp,8);
	temp.Format("%f",xmin);
	TextOut(dc,rect.right/16,rect.bottom*8/9+10,temp,8);

	CString str;
	str.Format("最大值:%f,最小值:%f,时间:%f",ymax*180/3.1416,ymin*180/3.1416,doc->m_bestTime);
	dc.TextOut(rect.right/2-150,rect.bottom/9-40,str,str.GetLength());

	m_reFlag=1;
	delete(y1);
	delete(y2);
	delete(x1);
	delete(x2);
}
