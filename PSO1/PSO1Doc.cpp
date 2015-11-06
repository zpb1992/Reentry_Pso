
// PSO1Doc.cpp : implementation of the CPSO1Doc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "PSO1.h"
#endif

#include "PSO1Doc.h"
#include "PSO1View.h"
#include "DiaControl.h"
#include "DiaFinal.h"
#include "DiaFinalTime.h"
#include "DiaPath.h"
#include "DiaStop.h"
#include "DiaState.h"
#include "DiaTargetM.h"
#include "DiaA.h"
#include "DiaPlane.h"
#include "DiaPicOption.h"
#include "DiaMore.h"
#include "DiaLimitsWeight.h"
#include<cmath>

#include <propkey.h>

#include <fstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CPSO1Doc

IMPLEMENT_DYNCREATE(CPSO1Doc, CDocument)

BEGIN_MESSAGE_MAP(CPSO1Doc, CDocument)
	ON_COMMAND(ID_PSO_CONTROL, &CPSO1Doc::OnPsoControl)
	ON_COMMAND(ID_CONSTRAINT_PATH, &CPSO1Doc::OnConstraintPath)
	ON_COMMAND(ID_PSO_STOP, &CPSO1Doc::OnPsoStop)
	ON_COMMAND(ID_START, &CPSO1Doc::OnStart)
	ON_COMMAND(ID_FINALTIME, &CPSO1Doc::OnFinaltime)
	ON_COMMAND(ID_PSO_STATE, &CPSO1Doc::OnPsoState)
	ON_COMMAND(ID_CONSTRAINT_FINAL, &CPSO1Doc::OnConstraintFinal)
	ON_COMMAND(ID_STOP, &CPSO1Doc::OnStop)
	ON_COMMAND(ID_TARGET1, &CPSO1Doc::OnTarget1)
	ON_COMMAND(ID_TARGET2, &CPSO1Doc::OnTarget2)
	ON_COMMAND(ID_TARGET3, &CPSO1Doc::OnTarget3)
	ON_COMMAND(ID_TARGET4, &CPSO1Doc::OnTarget4)
	ON_COMMAND(ID_TARGET_M, &CPSO1Doc::OnTargetM)
	ON_COMMAND(ID_PSO_A, &CPSO1Doc::OnPsoA)
	ON_COMMAND(ID_PSO_PLANE, &CPSO1Doc::OnPsoPlane)
	ON_COMMAND(ID_PICTURE_OPTION, &CPSO1Doc::OnPictureOption)
	ON_COMMAND(ID_PSO_MORE, &CPSO1Doc::OnPsoMore)
	ON_COMMAND(ID_FILE_REMOVE, &CPSO1Doc::OnFileRemove)
	ON_COMMAND(ID_WEIGHT, &CPSO1Doc::OnWeight)
END_MESSAGE_MAP()


// CPSO1Doc construction/destruction

CPSO1Doc::CPSO1Doc():pi(3.1416),R0(6378000),g0(9.80665),uE(3.986e14),wE((2*pi)/(24*3600)),Vc(7900),den0(1.2258),H(7254.26188),v_sound(295.188)
{
	// TODO: add one-time construction code here
	m_startTime=0;
	m_gaFlag=FALSE;
	m_saFlag=FALSE;
	m_gaHet=0.04;
	m_saCho=0.1;
	//PSO 控制变量
	m_d=20;
	m_n=50;
	m_scope[0]=-80*pi/180;
	m_scope[1]=80*pi/180;
	m_scope_a[0]=10*pi/180;
	m_scope_a[1]=20*pi/180;
	m_randFlag=0;
	//时间约束
	m_tScope[0]=1000.0;
	m_tScope[1]=3000.0;
	//路径约束 最大值
	m_Qmax=1000000;
	m_qmax=500000;
	m_nmax=6;
	m_conlimit=1*pi/180;
	m_egcFlag=1;
	//迭代次数
	m_loopMax=500;
	m_stepCount=0;
	// 全局 最优值
	//m_bestControl=NULL;
	// 攻角
	m_v1=5000;
	m_v2=3000;
	m_amax=20;
	m_amaxLD=10;
	//飞行器参数
	m_m=907.2;
	m_r=0.1;
	m_s=0.4839;
	//
	m_picOption1=TRUE;
	m_picOption2=TRUE;
	m_picN=1000;
	m_interpFlag=1;

	m_stateN=40;
	m_state1.Add(R0+CDiaState::m_initState1);
	m_state2.Add(160.0*pi/180);
	m_state3.Add(25.0*pi/180);
	m_state4.Add(CDiaState::m_initState4);
	m_state5.Add(-2.0*pi/180);
	m_state6.Add(58.0*pi/180);

	m_finalflag1=1;
	m_finalflag2=1;
	m_finalflag3=1;
	m_finalflag4=1;
	m_finalflag5=0;
	m_finalflag6=0;
	m_finalState1=R0+20000;
	m_finalState2=232.0*pi/180;
	m_finalState3=37.0*pi/180;
	m_finalState4=1000.0;
	m_finalState5=0.0;
	m_finalState6=0.0;

	m_bestAdapt=0;
	m_bestTime=0;

	m_targetFlag =3;

	m_target1=10;
	m_target2=1;
	m_target3=10000;
	m_target4=100000000;

	// 初始化权重
	Initial();
}

CPSO1Doc::~CPSO1Doc()
{
}

BOOL CPSO1Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CPSO1Doc serialization

void CPSO1Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar<<m_amax<<m_amaxLD<<m_bestAdapt<<m_bestTime<<m_conlimit<<m_d<<m_egcFlag<<m_finalflag1
			<<m_finalflag2<<m_finalflag3<<m_finalflag4<<m_finalflag5<<m_finalflag6<<m_finalState1
			<<m_finalState2<<m_finalState3<<m_finalState4<<m_finalState5<<m_finalState6<<m_gaFlag<<m_gaHet<<m_interpFlag<<m_loopMax
			<<m_m<<m_n<<m_nmax<<m_picOption1<<m_picOption2<<m_picN<<m_Qmax<<m_qmax<<m_r<<m_randFlag<<m_s<<m_scope[0]<<m_scope[1]<<m_startTime
			<<m_saCho<<m_saFlag<<m_stateN<<m_stepCount<<m_target1<<m_target2<<m_target3<<m_target4<<m_targetFlag
			<<m_tScope[0]<<m_tScope[1]<<m_v1<<m_v2;
		for(UINT i=0;i<m_d;i++)
		{
			ar<<m_bestControl.GetAt(i);
		}
		for(UINT i=0;i<m_stateN;i++)
		{
			ar<<m_state1.GetAt(i)<<m_state2.GetAt(i)<<m_state3.GetAt(i)<<m_state4.GetAt(i)
				<<m_state5.GetAt(i)<<m_state6.GetAt(i)<<m_Q.GetAt(i)<<m_q.GetAt(i)<<m_nLimit.GetAt(i);
		}
		for(UINT i=0;i<m_picN;i++)
		{
			ar<<m_picControl.GetAt(i)<<m_picstate1.GetAt(i)<<m_picstate2.GetAt(i)<<m_picstate3.GetAt(i)<<m_picstate4.GetAt(i)
				<<m_picstate5.GetAt(i)<<m_picstate6.GetAt(i)<<m_picQ.GetAt(i)<<m_picq.GetAt(i)
				<<m_picnLimit.GetAt(i);
		}
	}
	else
	{
		DelData();
		// TODO: add storing code here
		ar>>m_amax>>m_amaxLD>>m_bestAdapt>>m_bestTime>>m_conlimit>>m_d>>m_egcFlag>>m_finalflag1
			>>m_finalflag2>>m_finalflag3>>m_finalflag4>>m_finalflag5>>m_finalflag6>>m_finalState1
			>>m_finalState2>>m_finalState3>>m_finalState4>>m_finalState5>>m_finalState6>>m_gaFlag>>m_gaHet>>m_interpFlag>>m_loopMax
			>>m_m>>m_n>>m_nmax>>m_picOption1>>m_picOption2>>m_picN>>m_Qmax>>m_qmax>>m_r>>m_randFlag>>m_s>>m_scope[0]>>m_scope[1]>>m_startTime
			>>m_saCho>>m_saFlag>>m_stateN>>m_stepCount>>m_target1>>m_target2>>m_target3>>m_target4>>m_targetFlag
			>>m_tScope[0]>>m_tScope[1]>>m_v1>>m_v2;

		double temp;
		for(UINT i=0;i<m_d;i++)
		{
			ar>>temp;
			m_bestControl.Add(temp);
		}
		double temp0,temp1,temp2,temp3,temp4,temp5,temp6,temp7,temp8,temp9;
		m_state1.RemoveAll();
		m_state2.RemoveAll();
		m_state3.RemoveAll();
		m_state4.RemoveAll();
		m_state5.RemoveAll();
		m_state6.RemoveAll();
		for(UINT i=0;i<m_stateN;i++)
		{
			ar>>temp1>>temp2>>temp3>>temp4>>temp5>>temp6>>temp7>>temp8>>temp9;
			m_state1.Add(temp1);
			m_state2.Add(temp2);
			m_state3.Add(temp3);
			m_state4.Add(temp4);
			m_state5.Add(temp5);
			m_state6.Add(temp6);
			m_Q.Add(temp7);
			m_q.Add(temp8);
			m_nLimit.Add(temp9);
		}
		for(UINT i=0;i<m_picN;i++)
		{
			ar>>temp0>>temp1>>temp2>>temp3>>temp4>>temp5>>temp6>>temp7>>temp8>>temp9;
			m_picControl.Add(temp0);
			m_picstate1.Add(temp1);
			m_picstate2.Add(temp2);
			m_picstate3.Add(temp3);
			m_picstate4.Add(temp4);
			m_picstate5.Add(temp5);
			m_picstate6.Add(temp6);
			m_picQ.Add(temp7);
			m_picq.Add(temp8);
			m_picnLimit.Add(temp9);
		}

	CDiaControl::m_d=m_d;
	CDiaControl::m_maxScope=m_scope[1];
	CDiaControl::m_minScope=m_scope[0];
	CDiaControl::m_n=m_n;

	CDiaFinal::m_state1=m_finalState1;
	CDiaFinal::m_state2=m_finalState2;
	CDiaFinal::m_state3=m_finalState3;
	CDiaFinal::m_state4=m_finalState4;
	CDiaFinal::m_state5=m_finalState5;
	CDiaFinal::m_state6=m_finalState6;
	CDiaFinal::m_final1flag=m_finalflag1;
	CDiaFinal::m_final2flag=m_finalflag2;
	CDiaFinal::m_final3flag=m_finalflag3;
	CDiaFinal::m_final4flag=m_finalflag4;
	CDiaFinal::m_final5flag=m_finalflag5;
	CDiaFinal::m_final6flag=m_finalflag6;

	CDiaFinalTime::m_t=0.0;
	CDiaFinalTime::m_t0=m_tScope[0];
	CDiaFinalTime::m_tf=m_tScope[1];

	CDiaPath::m_dpMax=m_qmax; 
	CDiaPath::m_nMax=m_nmax; //???
	CDiaPath::m_qMax=m_nmax; //???一样的？
	CDiaPath::m_con=m_conlimit;
	CDiaPath::m_egcFlag=m_egcFlag;

	CDiaState::m_stateN=m_stateN;
	CDiaState::m_initState1=m_state1.GetAt(0);
	CDiaState::m_initState2=m_state2.GetAt(0);
	CDiaState::m_initState3=m_state3.GetAt(0);
	CDiaState::m_initState4=m_state4.GetAt(0);
	CDiaState::m_initState5=m_state5.GetAt(0);
	CDiaState::m_initState6=m_state6.GetAt(0);

	CDiaStop::m_loopMax=m_loopMax;

	CDiaA::m_amax=m_amax;
	CDiaA::m_amaxLD=m_amaxLD;
	CDiaA::m_v1=m_v1;
	CDiaA::m_v2=m_v2;

	CDiaPlane::m_m=m_m;
	CDiaPlane::m_s=m_s;
	CDiaPlane::m_r=m_r;

	CDiaTargetM::m_target1=m_target1;
	CDiaTargetM::m_target2=m_target2;
	CDiaTargetM::m_target3=m_target3;
	CDiaTargetM::m_target4=m_target4;

	CDiaPicOption::m_picOption1=m_picOption1;
	CDiaPicOption::m_picOption2=m_picOption2;
	CDiaPicOption::m_picN=m_picN;
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CPSO1Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CPSO1Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CPSO1Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CPSO1Doc diagnostics

#ifdef _DEBUG
void CPSO1Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPSO1Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CPSO1Doc commands


void CPSO1Doc::OnPsoControl()
{
	// TODO: Add your command handler code here
	CDiaControl diaCon;
	if(IDOK==diaCon.DoModal())
	{
		m_d=diaCon.m_d;
		m_n=diaCon.m_n;
		m_scope[0]=diaCon.m_minScope*pi/180;
		m_scope[1]=diaCon.m_maxScope*pi/180;
		m_randFlag=diaCon.m_randFlag;
	}
}


void CPSO1Doc::OnConstraintPath()
{
	// TODO: Add your command handler code here
	CDiaPath diaPath;
	if(IDOK==diaPath.DoModal())
	{
		m_Qmax=diaPath.m_qMax;
		m_qmax=diaPath.m_dpMax;
		m_nmax=diaPath.m_nMax;
		m_conlimit=diaPath.m_con*pi/180;
		m_egcFlag=diaPath.m_egcFlag;
	}
}


void CPSO1Doc::OnPsoStop()
{
	// TODO: Add your command handler code here
	CDiaStop diaStop;
	if(IDOK==diaStop.DoModal())
	{
		m_loopMax=diaStop.m_loopMax;
	}
}


void CPSO1Doc::OnStart()
{
	// TODO: Add your command handler code here
	double t1=GetTickCount();
	// 把上次运行的结果删除
	DelData();

	PsoProcess();
	//把数据传递到View类 方便画图
	// 不用了，这样清楚点(别骗自己了 清楚个屁)
	
	double t2=GetTickCount();
	m_startTime=t2-t1;

	// 清空图形  显示时间
	POSITION pos=GetFirstViewPosition();
	CPSO1View* v=(CPSO1View*)GetNextView(pos);
	v->m_reFlag=0;
	v->Invalidate();
	v->SendMessage(WM_PAINT);
	v->m_reFlag=1;
}


void CPSO1Doc::PsoProcess()
{
	//最后记得delete  防止内存泄露。。。。。。。。。。
	//粒子位置 速度 每个粒子最优适应度
	double** parSwarm=new double* [m_n];  //粒子位置
	double** parSwarmV=new double* [m_n];// 速度
	double** optSwarm=new double* [m_n];// 最优位置
	double* adaptSwarm=new double [m_n];// 最优适应度
	double* timeSwarm=new double[m_n];// 时间位置
	double* timeSwarmV=new double[m_n];
	double* optTime=new double[m_n];

	double* bestTime=new double;
	double* bestPar=new double[2*m_d];// 全局最优位置
	// 状态变量
	double** State=new double* [6];

	srand((int)time(0));

	//初始化种群
	InitSwarm(parSwarm,parSwarmV,optSwarm,adaptSwarm,timeSwarm,timeSwarmV,bestPar,optTime,bestTime,State);
	

	//迭代
	while(m_stepCount<=m_loopMax)
	{
		m_stepCount++;
		StepFunc(parSwarm,parSwarmV,timeSwarm,timeSwarmV,optSwarm,bestPar,adaptSwarm,optTime,bestTime,State);
	}
	// 最后把值赋给成员变量 
	// 控制变量 位置 bestPar
	// 状态变量  
	// 时间 bestTime
	// 只有倾侧角
	for(UINT i=0;i<m_d;i++)
	{
		m_bestControl.Add(bestPar[i]);
		m_bestControl_a.Add(bestPar[m_d+i]);
	}
	m_bestTime=*bestTime;
	// 节点图
	double* pathQ=new double[m_stateN];
	double* pathq=new double[m_stateN];
	double* pathn=new double[m_stateN];
	LGKT(bestPar,*bestTime,State);
	
	//AdaptFunc(bestPar,*bestTime,State);
	
	for(UINT i=1;i<m_stateN;i++)
	{
		m_state1.Add(State[0][i]);
		m_state2.Add(State[1][i]);
		m_state3.Add(State[2][i]);
		m_state4.Add(State[3][i]);
		m_state5.Add(State[4][i]);
		m_state6.Add(State[5][i]);
	}
	PathLimitPic(State,bestPar,pathQ,pathq,pathn);
	for(UINT i=0;i<m_stateN;i++)
	{
		m_Q.Add(pathQ[i]);
		m_nLimit.Add(pathn[i]);
		m_q.Add(pathq[i]);

	}


	// 曲线图
	double* piccon=new double[m_picN];
	double* piccon_a=new double[m_picN];
	double** picState=new double* [6];
	double* picQ=new double[m_picN];
	double* picq=new double[m_picN];
	double* picn=new double[m_picN];
	for(UINT i=0;i<6;i++)
	{
		picState[i]=new double [m_picN];
	}
		
	//三次样条曲线 插值
	//控制变量 必须用这个
	double* time=new double[m_d];
	double h=*bestTime/(m_d-1);
	time[0]=0;
	for(UINT i=1;i<m_d;i++)
	{
		time[i]=time[0]+h*i;
	}
	Spline3(time,bestPar,m_d,piccon);
	Spline3(time,bestPar+m_d,m_d,piccon_a);
	for(UINT i=0;i<m_picN;i++)
	{
		m_picControl.Add(piccon[i]);
		m_picControl_a.Add(piccon_a[i]);
	}
	delete(time);
	// 控制变量求出

	double* stateTime=new double[m_stateN];
	stateTime[0]=0;
	for(UINT i=1;i<m_stateN;i++)
	{
		stateTime[i]=stateTime[0]+h*i;
	}
	if(0==m_interpFlag)
	{
		picState[0][0]=m_state1.GetAt(0);
		picState[1][0]=m_state2.GetAt(0);
		picState[2][0]=m_state3.GetAt(0);
		picState[3][0]=m_state4.GetAt(0);
		picState[4][0]=m_state5.GetAt(0);
		picState[5][0]=m_state6.GetAt(0);
		int temp=m_stateN;
		m_stateN=m_picN;
		LGKT(bestPar,*bestTime,picState);
		for(UINT i=0;i<m_stateN;i++)
		{
			m_picstate1.Add(picState[0][i]);
			m_picstate2.Add(picState[1][i]);
			m_picstate3.Add(picState[2][i]);
			m_picstate4.Add(picState[3][i]);
			m_picstate5.Add(picState[4][i]);
			m_picstate6.Add(picState[5][i]);
		}
		m_stateN=temp;
		PathLimitPicLine(picState,bestPar,picQ,picq,picn);
	}
	else if(1==m_interpFlag)
	{
		for(UINT i=0;i<6;i++)
		{
			Spline3(stateTime,State[i],m_stateN,picState[i]);
		}
		Spline3(stateTime,pathQ,m_stateN,picQ);
		Spline3(stateTime,pathq,m_stateN,picq);
		Spline3(stateTime,pathn,m_stateN,picn);
		for(UINT i=0;i<m_picN;i++)
		{
			m_picstate1.Add(picState[0][i]);
			m_picstate2.Add(picState[1][i]);
			m_picstate3.Add(picState[2][i]);
			m_picstate4.Add(picState[3][i]);
			m_picstate5.Add(picState[4][i]);
			m_picstate6.Add(picState[5][i]);

			m_picQ.Add(picQ[i]);
			m_picq.Add(picq[i]);
			m_picnLimit.Add(picn[i]);
		}
	}
	else if(2==m_interpFlag)
	{
		for(UINT i=0;i<6;i++)
		{
			Lagrange(stateTime,State[i],m_stateN,picState[i]);
		}
		Lagrange(stateTime,pathQ,m_stateN,picQ);
		Lagrange(stateTime,pathq,m_stateN,picq);
		Lagrange(stateTime,pathn,m_stateN,picn);
		for(UINT i=0;i<m_picN;i++)
		{
			m_picstate1.Add(picState[0][i]);
			m_picstate2.Add(picState[1][i]);
			m_picstate3.Add(picState[2][i]);
			m_picstate4.Add(picState[3][i]);
			m_picstate5.Add(picState[4][i]);
			m_picstate6.Add(picState[5][i]);

			m_picQ.Add(picQ[i]);
			m_picq.Add(picq[i]);
			m_picnLimit.Add(picn[i]);
		}
	}


	// 拉格朗日插值 拟合曲线
	// test
	/*double x[3]={-10,0,10};
	double y[3]={101,1,101};
	double* result=new double[m_picN];
	Lagrange(x,y,3,result);*/
	//
	/*double* time=new double[m_d];
	double h=*bestTime/(m_d-1);
	time[0]=0;
	for(UINT i=1;i<m_d;i++)
	{
		time[i]=time[i-1]+h;
	}
	Lagrange(time,bestPar,m_d,piccon);
	for(UINT i=0;i<m_picN;i++)
	{
		m_picControl.Add(piccon[i]);
	}
	delete(time);
	delete(piccon);
	for(UINT i=0;i<6;i++)
	{
		delete(picState[i]);
	}
	delete(picState);*/
	//LAGRANGE 龙格现象严重


	delete []stateTime;
	delete []piccon;
	delete []piccon_a;
	for(UINT i=0;i<6;i++)
	{
		delete []picState[i];
	}
	delete []picState;
	delete []pathQ;
	delete []pathq;
	delete []pathn;
	delete []picQ;
	delete []picq;
	delete []picn;

	
	
	//  Test  最优控制的相应量测试
	double test1=AdaptFunc(bestPar,*bestTime,State);
	double test2=AdaptFunc(bestPar,*bestTime,State);

	CFile file("data.txt",CFile::modeCreate|CFile::modeWrite|CFile::modeNoTruncate);
	file.SeekToEnd();
	char a[100];
	double* data_t=new double[m_stateN];

	sprintf_s(a,100,"控制变量对应时间： ");
	file.Write(a,strlen(a));
	for(UINT i=0;i<m_d;i++)
	{
		data_t[i]=*bestTime*i/(m_d-1);
		sprintf_s(a,100,"%f ",data_t[i]);
		file.Write(a,strlen(a));
	}
	a[0]=13;
	a[1]=10;
	file.Write(a,2);

	// 控制变量
	sprintf_s(a,100,"倾侧角： ");
	file.Write(a,strlen(a));
	for(UINT i=0;i<m_d;i++)
	{
		sprintf_s(a,100,"%f ",bestPar[i]);
		file.Write(a,strlen(a));
	}
	a[0]=13;
	a[1]=10;
	file.Write(a,2);
	sprintf_s(a,100,"攻角： ");
	file.Write(a,strlen(a));
	for(UINT i=m_d;i<2*m_d;i++)
	{
		sprintf_s(a,100,"%f ",bestPar[i]);
		file.Write(a,strlen(a));
	}
	a[0]=13;
	a[1]=10;
	file.Write(a,2);

	sprintf_s(a,100,"状态变量对应时间： ");
	file.Write(a,strlen(a));
	for(UINT i=0;i<m_stateN;i++)
	{
		data_t[i]=*bestTime*i/(m_stateN-1);
		sprintf_s(a,100,"%f ",data_t[i]);
		file.Write(a,strlen(a));
	}
	a[0]=13;
	a[1]=10;
	file.Write(a,2);

	for(UINT j=0;j<6;j++)
	{
		switch(j)
		{
		case 0:
			sprintf_s(a,100,"高度： ");
			file.Write(a,strlen(a));
			break;
		case 1:
			sprintf_s(a,100,"经度： ");
			file.Write(a,strlen(a));
			break;
		case 2:
			sprintf_s(a,100,"纬度： ");
			file.Write(a,strlen(a));
			break;
		case 3:
			sprintf_s(a,100,"速度： ");
			file.Write(a,strlen(a));
			break;
		case 4:
			sprintf_s(a,100,"航迹角： ");
			file.Write(a,strlen(a));
			break;
		case 5:
			sprintf_s(a,100,"航向角： ");
			file.Write(a,strlen(a));
			break;
		}
		for(UINT i=0;i<m_stateN;i++)
		{
			sprintf_s(a,100,"%f ",State[j][i]);
			//file.Write(a,strlen(a));
			file.Write(a,strlen(a));
		}
		a[0]=13;
		a[1]=10;
		file.Write(a,2);
	}

	sprintf_s(a,100,"热流密度： ");
	file.Write(a,strlen(a));
	for(UINT i=0;i<m_stateN;i++)
	{

		sprintf_s(a,100,"%f ",m_Q.GetAt(i));
		file.Write(a,strlen(a));
	}
	a[0]=13;
	a[1]=10;
	file.Write(a,2);

	sprintf_s(a,100,"动压： ");
	file.Write(a,strlen(a));
	for(UINT i=0;i<m_stateN;i++)
	{
		sprintf_s(a,100,"%f ",m_q.GetAt(i));
		file.Write(a,strlen(a));
	}
	a[0]=13;
	a[1]=10;
	file.Write(a,2);

	sprintf_s(a,100,"过载： ");
	file.Write(a,strlen(a));
	for(UINT i=0;i<m_stateN;i++)
	{
		sprintf_s(a,100,"%f ",m_nLimit.GetAt(i));
		file.Write(a,strlen(a));
	}
	a[0]=13;
	a[1]=10;
	file.Write(a,2);
	//sprintf_s(a,100,"%f",test1);
	a[0]=13;
	a[1]=10;
	file.Write(a,2);
	file.Close();
	
	delete(data_t);
	// delete 堆上分配的内存
	HeapDel(parSwarm,parSwarmV,optSwarm,adaptSwarm,timeSwarm,timeSwarmV,optTime,bestTime,bestPar,State);

}


void CPSO1Doc::InitSwarm(double** ParSwarm,double** ParSwarmV, double** OptSwarm, double* AdaptSwarm, double* TimeSwarm, double* TimeSwarmV, double* BestPar, double* OptTime, double* BestTime, double** State)
{
	for(UINT i=0;i<6;i++)
	{
		State[i]=new double [m_stateN];
	}
	State[0][0]=m_state1.GetAt(0);
	State[1][0]=m_state2.GetAt(0);
	State[2][0]=m_state3.GetAt(0);
	State[3][0]=m_state4.GetAt(0);
	State[4][0]=m_state5.GetAt(0);
	State[5][0]=m_state6.GetAt(0);
	UINT index=m_n;
	if(0==m_randFlag)
	{
		for(UINT i=0;i<m_n;i++)
		{
			// 倾侧角 攻角
			ParSwarm[i]=new double [2*m_d];
			ParSwarmV[i]=new double [2*m_d];
			OptSwarm[i]=new double [2*m_d];

			//时间
			TimeSwarm[i]=((double)rand()/RAND_MAX)*(m_tScope[1]-m_tScope[0])+m_tScope[0];
			TimeSwarmV[i]=((double)rand()/RAND_MAX)*(m_tScope[1]-m_tScope[0])*pow(-1.0,rand()%2);
			OptTime[i]=TimeSwarm[i];
			for(UINT j=0;j<m_d;j++)
			{
				ParSwarm[i][j]=((double)rand()/RAND_MAX)*(m_scope[1]-m_scope[0])+m_scope[0];
				ParSwarmV[i][j]=((double)rand()/RAND_MAX)*(m_scope[1]-m_scope[0])*pow(-1.0,rand()%2);
				OptSwarm[i][j]=ParSwarm[i][j];

				ParSwarm[i][m_d+j]=((double)rand()/RAND_MAX)*(m_scope_a[1]-m_scope_a[0])+m_scope_a[0];
				ParSwarmV[i][m_d+j]=((double)rand()/RAND_MAX)*(m_scope_a[1]-m_scope_a[0])*pow(-1.0,rand()%2);
				OptSwarm[i][m_d+j]=ParSwarm[i][m_d+j];
			}

			AdaptSwarm[i]=AdaptFunc(ParSwarm[i],TimeSwarm[i],State);			//每个粒子的最优位置的适应度
		
			// 判断AdaptSwarm[i]是否是NaN
			while(AdaptSwarm[i]!=AdaptSwarm[i])
			{
				TimeSwarm[i]=((double)rand()/RAND_MAX)*(m_tScope[1]-m_tScope[0])+m_tScope[0];
				TimeSwarmV[i]=((double)rand()/RAND_MAX)*(m_tScope[1]-m_tScope[0])*pow(-1.0,rand()%2);
				OptTime[i]=TimeSwarm[i];
				for(UINT j=0;j<m_d;j++)
				{
					ParSwarm[i][j]=((double)rand()/RAND_MAX)*(m_scope[1]-m_scope[0])+m_scope[0];
					ParSwarmV[i][j]=((double)rand()/RAND_MAX)*(m_scope[1]-m_scope[0])*pow(-1.0,rand()%2);
					OptSwarm[i][j]=ParSwarm[i][j];

					ParSwarm[i][m_d+j]=((double)rand()/RAND_MAX)*(m_scope_a[1]-m_scope_a[0])+m_scope_a[0];
					ParSwarmV[i][m_d+j]=((double)rand()/RAND_MAX)*(m_scope_a[1]-m_scope_a[0])*pow(-1.0,rand()%2);
					OptSwarm[i][m_d+j]=ParSwarm[i][m_d+j];
				}

				AdaptSwarm[i]=AdaptFunc(ParSwarm[i],TimeSwarm[i],State);	
			}
		}
	}
	else if(1==m_randFlag)
	{
		srand((int)time(0));
		double* lrandPar=new double [m_d];
		double* lrandParV=new double [m_d];
		double lrandTime=(double)rand()/RAND_MAX;
		double lrandTimeV=(double)rand()/RAND_MAX;
		for(UINT i=0;i<m_d;i++)
		{
			lrandPar[i]=(double)rand()/RAND_MAX;
			lrandParV[i]=(double)rand()/RAND_MAX;
		}
		for(UINT i=0;i<m_n;i++)
		{
			ParSwarm[i]=new double [m_d];
			ParSwarmV[i]=new double [m_d];
			OptSwarm[i]=new double [m_d];
			lrandTime=4.0*lrandTime*(1-lrandTime);
			lrandTimeV=4.0*lrandTimeV*(1-lrandTimeV);
			TimeSwarm[i]=(lrandTime)*(m_tScope[1]-m_tScope[0])+m_tScope[0];
			TimeSwarmV[i]=(lrandTimeV)*(m_tScope[1]-m_tScope[0])*pow(-1.0,rand()%2);
			OptTime[i]=TimeSwarm[i];
			for(UINT j=0;j<m_d;j++)
			{
				lrandPar[j]=4.0*lrandPar[j]*(1-lrandPar[j]);
				lrandParV[j]=4.0*lrandParV[j]*(1-lrandParV[j]);
				ParSwarm[i][j]=(lrandPar[j])*(m_scope[1]-m_scope[0])+m_scope[0];
				ParSwarmV[i][j]=(lrandPar[j])*(m_scope[1]-m_scope[0])*pow(-1.0,rand()%2);
				OptSwarm[i][j]=ParSwarm[i][j];
			}
			AdaptSwarm[i]=AdaptFunc(ParSwarm[i],TimeSwarm[i],State);			//每个粒子的最优位置的适应度
		
			// 判断AdaptSwarm[i]是否是NaN
			while(AdaptSwarm[i]!=AdaptSwarm[i])
			{
				lrandTime=4.0*lrandTime*(1-lrandTime);
				lrandTimeV=4.0*lrandTimeV*(1-lrandTimeV);
				TimeSwarm[i]=(lrandTime)*(m_tScope[1]-m_tScope[0])+m_tScope[0];
				TimeSwarmV[i]=(lrandTimeV)*(m_tScope[1]-m_tScope[0])*pow(-1.0,rand()%2);
				OptTime[i]=TimeSwarm[i];
				for(UINT j=0;j<m_d;j++)
				{
					lrandPar[j]=4.0*lrandPar[j]*(1-lrandPar[j]);
					lrandParV[j]=4.0*lrandParV[j]*(1-lrandParV[j]);
					ParSwarm[i][j]=(lrandPar[j])*(m_scope[1]-m_scope[0])+m_scope[0];
					ParSwarmV[i][j]=(lrandPar[j])*(m_scope[1]-m_scope[0])*pow(-1.0,rand()%2);
					OptSwarm[i][j]=ParSwarm[i][j];
				}
				AdaptSwarm[i]=AdaptFunc(ParSwarm[i],TimeSwarm[i],State);	
			}
		}
		delete(lrandPar);
		delete(lrandParV);
	}
	m_bestAdapt=Max(AdaptSwarm,index);
	for(UINT i=0;i<2*m_d;i++)
	{
		BestPar[i]=ParSwarm[index][i];
	}
	*BestTime=TimeSwarm[index];
}


double CPSO1Doc::AdaptFunc(double* contr, double finalTime, double** State)
{
	//四阶龙格库塔法 求出状态变量 LGKT
	LGKT(contr,finalTime,State);
	//由状态变量 求Q q n  
	double Q;
	double q;
	double n;
	double sumQ=0;  // 还要乘以时间间隔才是正确数值

	double finallimit;		// 终端
	double pathlimit;		//路径
	//double conlimit;		//控制变量
	double egclimit;		//拟平衡

	double adapt=0;
	// 路径约束
	PathLimits(State,contr,Q,q,n,sumQ);// 求出的sumQ只是节点处的Q相加得到的 还要乘以节点间隔时间
	sumQ = sumQ*finalTime/(double)(m_stateN-1);
	pathlimit=exp(Q-m_Qmax)+exp(q-m_qmax)+exp(10*(n-m_nmax));
	adapt -= pathlimit;

	// 终端约束 
	finallimit=FinalLimits(State);
	adapt -= finallimit;

	// 控制变量变化约束  (自己加的 试试)
	//conlimit=ConLimit(contr,finalTime);
	//adapt -= conlimit;

	// 平衡滑翔约束 (感觉对航向角 航迹角的变化会有帮助)
	// (航向角) 航迹角变化量最小
	if(m_egcFlag==1)
	{
		egclimit=EGCLimit(State,contr,finalTime);
		adapt -= egclimit;
	}
	// 禁飞点约束
	//adapt -= NoflyFunc(State);
	////求适应度 根据选项  给PathLimits添加参数 sumQ if（m_targetFlag==1） 计算sumQ
	//double adapt=0;
	//// 约束  罚函
	//adapt -=finallimit;   //*800  跟路径约束的权值
	//adapt -=pathlimit;
	//adapt -=conlimit;
	//adapt -=egclimit;

	// 优化目标
	// 单目标优化会比多目标优化相应权值高十倍
	if(m_targetFlag==5)
	{
		//adapt -= m_target1*sumQ/1000000;
		adapt -= m_target1*sumQ/1000000;
	}
	else if(m_targetFlag==1)
	{
		//adapt -= 100*sumQ/1000000;
		adapt -= 100*sumQ/1000000;

	}
	if(m_targetFlag!=1)
	{
		//adapt += TargetFunc(State,finalTime,contr)/1000000;
		adapt += TargetFunc(State,finalTime,contr)/1000000;
	}
	
	return adapt;
}

// n 输入数组的元素个数   输出最大的数下标
double CPSO1Doc::Max(double* arry, UINT& n)
{
	UINT m=0;
	double max=arry[0];
	for(UINT i=1;i<n;i++)
	{
		if(max<arry[i])
		{
			max=arry[i];
			m=i;
		}
	}
	n=m;
	return max;
}


void CPSO1Doc::StepFunc(double** ParSwarm, double** ParSwarmV, double* TimeSwarm, double* TimeSwarmV, double** OptSwarm, double* BestPar, double* AdaptSwarm, double* OptTime, double* BestTime, double** State)
{
	// 速度更新系数
	// 可以作为成员变量 建立对话框进行自定义输入
	// 线性递减权值策略 w=(wini-wend)(T-t)/T+wend
	//取wini=0.9  wend=0.4
	double w=0.9-0.5*(double)m_stepCount/m_loopMax;
	double c1=2.0;
	double c2=2.0;
	double SubTract1;
	double SubTract2;
	double tSubTract1;
	double tSubTract2;
	double SubTract1_a;
	double SubTract2_a;
	//位置更新系数
	double a=0.729;
	// 速度的最大值和最小值  maxV   -maxV
	double maxV=(m_scope[1]-m_scope[0]);
	double maxTV=(m_tScope[1]-m_tScope[0]);
	double maxV_a=(m_scope_a[1]-m_scope_a[0]);
	//临时的适应度
	//double adapt;

	// 保存每次与约束有关的计算结果
	double **finalState=new double *[6];
	for(int i=0;i<6;i++)
	{
		finalState[i]=new double [m_n];
	}
	double *overLoad=new double [m_n];
	double *pressure=new double[m_n];
	double *heatDensity=new double[m_n];
	double *heat=new double[m_n];
	double *dControlA=new double[m_n];
	double *dControlB=new double[m_n];
	double *angleTrack=new double[m_n];
	double *dAngleTrack=new double[m_n];

	// 归一化问题 
	// 本次循环只是将所有与约束有关的量全部存储 并不能计算适应度
	for(UINT i=0;i<m_n;i++)
	{
		for(UINT j=0;j<m_d;j++)
		{
			// 更新速度
			// 倾侧角
			SubTract1=OptSwarm[i][j]-ParSwarm[i][j];
			SubTract2=BestPar[j]-ParSwarm[i][j];
			ParSwarmV[i][j]=w*ParSwarmV[i][j]+c1*(double)rand()/RAND_MAX*SubTract1+c2*(double)rand()/RAND_MAX*SubTract2;
			if(ParSwarmV[i][j]>maxV)
			{
				ParSwarmV[i][j]=maxV;
			}
			else if(ParSwarmV[i][j]<-maxV)
			{
				ParSwarmV[i][j]=-maxV;
			}
			//攻角
			SubTract1_a=OptSwarm[i][m_d+j]-ParSwarm[i][m_d+j];
			SubTract2_a=BestPar[m_d+j]-ParSwarm[i][m_d+j];
			ParSwarmV[i][m_d+j]=w*ParSwarmV[i][m_d+j]+c1*(double)rand()/RAND_MAX*SubTract1_a+c2*(double)rand()/RAND_MAX*SubTract2_a;
			if(ParSwarmV[i][m_d+j]>maxV_a)
			{
				ParSwarmV[i][m_d+j]=maxV_a;
			}
			else if(ParSwarmV[i][m_d+j]<-maxV_a)
			{
				ParSwarmV[i][m_d+j]=-maxV_a;
			}

			//更新位置
			ParSwarm[i][j]=ParSwarm[i][j]+a*ParSwarmV[i][j];
			if(ParSwarm[i][j]>m_scope[1])
			{
				ParSwarm[i][j]=m_scope[1];
			}
			else if(ParSwarm[i][j]<m_scope[0])
			{
				ParSwarm[i][j]=m_scope[0];
			}

			ParSwarm[i][m_d+j]=ParSwarm[i][m_d+j]+a*ParSwarmV[i][m_d+j];
			if(ParSwarm[i][m_d+j]>m_scope_a[1])
			{
				ParSwarm[i][m_d+j]=m_scope_a[1];
			}
			else if(ParSwarm[i][m_d+j]<m_scope_a[0])
			{
				ParSwarm[i][m_d+j]=m_scope_a[0];
			}
		}
		//更新时间
		tSubTract1=OptTime[i]-TimeSwarm[i];
		tSubTract2=*BestTime-TimeSwarm[i];
		TimeSwarmV[i]=w*TimeSwarmV[i]+c1*(double)rand()/RAND_MAX*tSubTract1+c2*rand()/RAND_MAX*tSubTract2;
		if(TimeSwarmV[i]>maxTV)
		{
			TimeSwarmV[i]=maxTV;
		}
		else if(TimeSwarmV[i]<-maxTV)
		{
			TimeSwarmV[i]=-maxTV;
		}
		TimeSwarm[i]=TimeSwarm[i]+a*TimeSwarmV[i];
		if(TimeSwarm[i]>m_tScope[1])
		{
			TimeSwarm[i]=m_tScope[1];
		}
		else if(TimeSwarm[i]<m_tScope[0])
		{
			TimeSwarm[i]=m_tScope[0];
		}

		
		LGKT(ParSwarm[i],TimeSwarm[i],State);

		/*     让所有的值都趋于0就行了   */
		// 等式约束
		if(m_finalflag1)
			finalState[0][i]=std::abs(State[0][m_d-1]-m_finalState1);
		if(m_finalflag2)
			finalState[1][i]=std::abs(State[1][m_d-1]-m_finalState2);
		if(m_finalflag3)
			finalState[2][i]=std::abs(State[2][m_d-1]-m_finalState3);
		if(m_finalflag5)
			finalState[4][i]=std::abs(State[4][m_d-1]-m_finalState5);
		if(m_finalflag6)
			finalState[5][i]=std::abs(State[5][m_d-1]-m_finalState6);
		// 等式约束
		if(m_finalflag4)
			finalState[3][i]=std::abs(State[3][m_d-1]-m_finalState4);


		double sumQ=0;
		double Q,q,n;
		PathLimits(State,ParSwarm[i],Q,q,n,sumQ);
		sumQ = sumQ*TimeSwarm[i]/(double)(m_stateN-1);
		overLoad[i]=n;
		pressure[i]=q;
		heatDensity[i]=Q;
		heat[i]=sumQ;

		double conA=0,conB=0;
		for(int cn=1;cn<m_d;cn++)
		{
			// 控制变量 变化率
			conB += std::abs(ParSwarm[i][cn]-ParSwarm[i][cn-1]);
			conA += std::abs(ParSwarm[i][cn+m_d]-ParSwarm[i][cn+m_d-1]);
		}
		dControlA[i]=conA*TimeSwarm[i]/(double)(m_d-1);
		dControlB[i]=conB*TimeSwarm[i]/(double)(m_d-1);

		double track=0,dTrack=0;
		for(int sd=1;sd<m_stateN;sd++)
		{
			track+=std::abs(State[4][sd]);

			double g=R0*R0*g0/(State[0][i]*State[0][i]);
			double den=den0*exp(-(State[0][i]-R0)/H);
			double a=Interp1(ParSwarm[i]+m_d,(double)sd/(m_stateN-1));
			double Cl,Cd;
			ClCdFunc(a,State[3][i],&Cl,&Cd);
			double L=den*State[3][i]*State[3][i]*m_s*Cl/2;
			dTrack += std::abs((State[3][i]*State[3][i]/State[0][i]-g)+L/m_m);
			//dTrack+=std::abs(State[4][sd]-State[4][sd-1]);			
		}
		angleTrack[i]=track;
		dAngleTrack[i]=dTrack;

		double *tempAdaptLimits=new double[m_n];
		memset(tempAdaptLimits,0,m_n*sizeof(double));

		delete []tempAdaptLimits;
		/*
		//更新适应度
		adapt=AdaptFunc(ParSwarm[i],TimeSwarm[i],State);

		// NAN 怎么办？？？？？？？？？？
		//AdaptSwarm  初始化检查
		if(AdaptSwarm[i]<adapt)
		{
			AdaptSwarm[i]=adapt;
			for(UINT j=0;j<2*m_d;j++)
			{
				OptSwarm[i][j]=ParSwarm[i][j];
			}
			OptTime[i]=TimeSwarm[i];
			//全局最优
			if(m_bestAdapt<adapt)
			{
				m_bestAdapt=adapt;
				for(UINT j=0;j<2*m_d;j++)
				{
					BestPar[j]=ParSwarm[i][j];
				}
				*BestTime=TimeSwarm[i];

				//  达到最优之后 重新随机粒子
				UpdatePar(&TimeSwarm[i],&TimeSwarmV[i],&OptTime[i],ParSwarm[i],ParSwarmV[i],OptSwarm[i]);
				AdaptSwarm[i]=AdaptFunc(ParSwarm[i],TimeSwarm[i],State);	
				// 判断AdaptSwarm[i]是否是NaN
				while(AdaptSwarm[i]!=AdaptSwarm[i])
				{
					UpdatePar(&TimeSwarm[i],&TimeSwarmV[i],&OptTime[i],ParSwarm[i],ParSwarmV[i],OptSwarm[i]);
					AdaptSwarm[i]=AdaptFunc(ParSwarm[i],TimeSwarm[i],State);
				}
			}
		}

		// 模拟退火思想 一定概率接受适应度低的解
		if(m_saFlag)
		{
			if(AdaptSwarm[i]>adapt)
			{
				if((double)rand()/RAND_MAX<m_saCho)
				{
					AdaptSwarm[i]=adapt;
					for(UINT j=0;j<m_d;j++)
					{
						OptSwarm[i][j]=ParSwarm[i][j];
					}
					OptTime[i]=TimeSwarm[i];
				}
			}
		}
		// 选择 交叉 变异  脱离局部解
		// 选择被淘汰的个体  与适应度无关 粒子群算法会接近最优值 所以这里不相关没问题吧？
		// 被淘汰之后重新随机一个粒子

		// 两个粒子进行交叉
		// 随机一个粒子变异
		if(m_gaFlag)
		{
			if((double)rand()/RAND_MAX<0.05&&(double)rand()/RAND_MAX<(m_bestAdapt-adapt)/abs(adapt))
			{
				UpdatePar(&TimeSwarm[i],&TimeSwarmV[i],&OptTime[i],ParSwarm[i],ParSwarmV[i],OptSwarm[i]);
				adapt=AdaptFunc(ParSwarm[i],TimeSwarm[i],State);
				// 判断AdaptSwarm[i]是否是NaN
				while(AdaptSwarm[i]!=AdaptSwarm[i])
				{
					UpdatePar(&TimeSwarm[i],&TimeSwarmV[i],&OptTime[i],ParSwarm[i],ParSwarmV[i],OptSwarm[i]);
					adapt=AdaptFunc(ParSwarm[i],TimeSwarm[i],State);
				}
			}
			//else if(i>0&&(double)rand()/RAND_MAX < 0.1)
			//{
			//	int index=rand()%m_d;
			//	for(UINT j=0;j<m_d;j++)
			//	{
			//		double temp;
			//		double para;
			//		para=(double)rand()/RAND_MAX;
			//		temp=ParSwarm[i][j];
			//		ParSwarm[i][j]=para*ParSwarm[i][j]+(1-para)*ParSwarm[index][j];
			//	}
			//	double para=(double)rand()/RAND_MAX;

			//	TimeSwarm[i]=para*TimeSwarm[i]+(1-para)*TimeSwarm[index];

			//	adapt=AdaptFunc(ParSwarm[i],TimeSwarm[i],State);
			//}
			if((double)rand()/RAND_MAX<m_gaHet)
			{
				for(UINT j=0;j<m_d;j++)
				{
					double para=(double)rand()/RAND_MAX;
					ParSwarm[i][j]=ParSwarm[i][j]+pow(-1.0,rand())*para/10;
					if(ParSwarm[i][j]>m_scope[1])
					{
						ParSwarm[i][j]=m_scope[1];
					}
					ParSwarm[i][j]=ParSwarm[i][j]<m_scope[0]?m_scope[0]:ParSwarm[i][j];
				}
				double para=(double)rand()/RAND_MAX;
				TimeSwarm[i]=TimeSwarm[i]+0.1*para*m_tScope[1];

				adapt=AdaptFunc(ParSwarm[i],TimeSwarm[i],State);
			}

			// 之后的最优值选取
			if(AdaptSwarm[i]<adapt)
			{
				AdaptSwarm[i]=adapt;
				for(UINT j=0;j<2*m_d;j++)
				{
					OptSwarm[i][j]=ParSwarm[i][j];
				}
				OptTime[i]=TimeSwarm[i];
				//全局最优
				if(m_bestAdapt<adapt)
				{
					m_bestAdapt=adapt;
					for(UINT j=0;j<2*m_d;j++)
					{
						BestPar[j]=ParSwarm[i][j];
					}
					*BestTime=TimeSwarm[i];
				}
			}
		}*/   // 在内更新adapt
	}

	// 计算适应度 计算出的是个矩阵
	double *adapt=new double [m_n]; // 本次循环计算出的所有粒子的适应度

	delete []adapt;


	for(int i=0;i<6;i++)
	{
		delete []finalState[i];
	}
	delete []finalState;
	delete []overLoad;
	delete []pressure;
	delete []heatDensity;
	delete []heat;
	delete []dControlA;
	delete []dControlB;
	delete []angleTrack;
	delete []dAngleTrack;
}


void CPSO1Doc::OnFinaltime()
{
	// TODO: Add your command handler code here
	CDiaFinalTime diaFTime;
	if(IDOK==diaFTime.DoModal())
	{
		if(diaFTime.m_tOption==0)
		{
			m_tScope[0]=diaFTime.m_t;
			m_tScope[1]=diaFTime.m_t;
		}
		else if(diaFTime.m_tOption==1)
		{
			m_tScope[0]=diaFTime.m_t0;
			m_tScope[1]=diaFTime.m_tf;
		}
	}
}


void CPSO1Doc::OnPsoState()
{
	// TODO: Add your command handler code here
	CDiaState diaState;
	if(IDOK==diaState.DoModal())
	{
		m_stateN=diaState.m_stateN;
		m_state1.Add(diaState.m_initState1+R0);
		m_state2.Add(diaState.m_initState2*pi/180);
		m_state3.Add(diaState.m_initState3*pi/180);
		m_state4.Add(diaState.m_initState4);
		m_state5.Add(diaState.m_initState5*pi/180);
		m_state6.Add(diaState.m_initState6*pi/180);

	}
}

// State 输出 状态变量
void CPSO1Doc::LGKT(double* contr, double finalTime, double** State)
{
	// 初值
	double t=finalTime/(m_stateN-1); //间隔时间
	

	double k1[6],k2[6],k3[6],k4[6];  // 六维的数组 保存六个斜率
	double u1,u2,u3,u4;   //对应state点上的控制变量
	double a1,a2,a3,a4;

	//因为 m_n 跟m_stateN 不同

	double h=1/((double)m_stateN-1);

	//求一个点的微分
	for(UINT i=0;i<m_stateN-1;i++)
	{
		//u1=Interp1(contr,(double)i/(m_stateN-1));
		Interp1_ab(contr,(double)i*h,a1,u1);
		DiffFunc(u1,a1,k1,State[0][i],State[1][i],State[2][i],State[3][i],State[4][i],State[5][i]);
		//u2=Interp1(contr,(double)i/(m_stateN-1)+h/2);
		Interp1_ab(contr,(double)i*h+h/2,a2,u2);
		DiffFunc(u2,a2,k2,State[0][i]+k1[0]*t/2,State[1][i]+k1[1]*t/2,State[2][i]+k1[2]*t/2,State[3][i]+k1[3]*t/2,State[4][i]+k1[4]*t/2,State[5][i]+k1[5]*t/2);
		//u3=Interp1(contr,(double)i/(m_stateN-1)+h/2);
		Interp1_ab(contr,(double)i*h+h/2,a3,u3);
		DiffFunc(u2,a2,k3,State[0][i]+k2[0]*t/2,State[1][i]+k2[1]*t/2,State[2][i]+k2[2]*t/2,State[3][i]+k2[3]*t/2,State[4][i]+k2[4]*t/2,State[5][i]+k2[5]*t/2);
		//u4=Interp1(contr,(double)i/(m_stateN-1)+h);
		Interp1_ab(contr,(double)i*h+h,a4,u4);
		DiffFunc(u4,a4,k4,State[0][i]+k3[0]*t,State[1][i]+k3[1]*t,State[2][i]+k3[2]*t,State[3][i]+k3[3]*t,State[4][i]+k3[4]*t,State[5][i]+k3[5]*t);

		for(UINT j=0;j<6;j++)
		{
			State[j][i+1]=State[j][i]+t*(k1[j]+2*k2[j]+2*k3[j]+k4[j])/6;
		}
	}
}


void CPSO1Doc::PathLimits(double** State, double& Q, double& q, double& n, double& sumQ)
{
	// 先求第一个点 最大值的第一个数
	double g=R0*R0*g0/(State[0][0]*State[0][0]);
	double a;
	a=AFunc(State[3][0]);
    double Cl,Cd;
    ClCdFunc(a,State[3][0],&Cl,&Cd);
	double den=den0*exp(-(State[0][0]-R0)/H);
	double C1=11030;
	double tempQ;
	double tempq;
	double tempn;

	sumQ=0;

	Q=C1/pow(m_r,0.5)*pow(den/den0,0.5)*pow(State[3][0]/Vc,3.15);
	q=den*State[3][0]*State[3][0]/2;
	n=q*pow((Cl*Cl+Cd*Cd),0.5)*m_s/(m_m*g);
	//Q q n 为整个路径的最大值
	if(m_targetFlag==1||m_targetFlag==5)
	{
		for(UINT i=1;i<m_stateN;i++)
		{
			g=R0*R0*g0/(State[0][i]*State[0][i]);
			a=AFunc(State[3][i]);
	
			ClCdFunc(a,State[3][i],&Cl,&Cd);

			den=den0*exp(-(State[0][i]-R0)/H);
			tempQ=C1/pow(m_r,0.5)*pow(den/den0,0.5)*pow((State[3][i]/Vc),3.15);
			tempq=den*State[3][i]*State[3][i]/2;
			tempn=tempq*pow(Cl*Cl+Cd*Cd,0.5)*m_s/(m_m*g);
			if(Q<tempQ)
			{	Q=tempQ;}
			if(q<tempq)
			{	q=tempq;}
			if(n<tempn)
			{	n=tempn;}
			sumQ += Q;
		}
	}
	else
	{
		for(UINT i=1;i<m_stateN;i++)
		{
			g=R0*R0*g0/(State[0][i]*State[0][i]);
			a=AFunc(State[3][i]);

		    ClCdFunc(a,State[3][0],&Cl,&Cd);
			den=den0*exp(-(State[0][i]-R0)/H);
			tempQ=C1/pow(m_r,0.5)*pow(den/den0,0.5)*pow(State[3][i]/Vc,3.15);
			tempq=den*State[3][i]*State[3][i]/2;
			tempn=tempq*pow(Cl*Cl+Cd*Cd,0.5)*m_s/(m_m*g);
			if(Q<tempQ)
			{	Q=tempQ;}
			if(q<tempq)
			{	q=tempq;}
			if(n<tempn)
			{	n=tempn;}
		}
	}
}
// 可以的话可以加入终端约束  FinalLimits

void CPSO1Doc::PathLimits(double** State,double*con, double& Q, double& q, double& n, double& sumQ)
{
	// 先求第一个点 最大值的第一个数
	double g=R0*R0*g0/(State[0][0]*State[0][0]);
	double a;
	a=con[m_d];
    double Cl,Cd;
    ClCdFunc(a,State[3][0],&Cl,&Cd);
	double den=den0*exp(-(State[0][0]-R0)/H);
	double C1=11030;
	double tempQ;
	double tempq;
	double tempn;

	Q=C1/pow(m_r,0.5)*pow(den/den0,0.5)*pow(State[3][0]/Vc,3.15);
	q=den*State[3][0]*State[3][0]/2;
	n=q*pow((Cl*Cl+Cd*Cd),0.5)*m_s/(m_m*g);

	sumQ=0;
	//Q q n 为整个路径的最大值
	if(m_targetFlag==1||m_targetFlag==5)
	{
		for(UINT i=1;i<m_stateN;i++)
		{
			g=R0*R0*g0/(State[0][i]*State[0][i]);
			//Interp1_ab(con,(double)i/(m_stateN-1),a,b);
			a=Interp1(con+m_d,(double)i/(m_stateN-1));

			ClCdFunc(a,State[3][i],&Cl,&Cd);

			den=den0*exp(-(State[0][i]-R0)/H);
			tempQ=C1/pow(m_r,0.5)*pow(den/den0,0.5)*pow((State[3][i]/Vc),3.15);
			tempq=den*State[3][i]*State[3][i]/2;
			tempn=tempq*pow(Cl*Cl+Cd*Cd,0.5)*m_s/(m_m*g);
			if(Q<tempQ)
			{	Q=tempQ;}
			if(q<tempq)
			{	q=tempq;}
			if(n<tempn)
			{	n=tempn;}
			sumQ += Q;
		}
	}
	else
	{
		for(UINT i=1;i<m_stateN;i++)
		{
			g=R0*R0*g0/(State[0][i]*State[0][i]);
			//Interp1_ab(con,(double)i/(m_stateN-1),a,b);
			a=Interp1(con+m_d,(double)i/(m_stateN-1));

		    ClCdFunc(a,State[3][0],&Cl,&Cd);
			den=den0*exp(-(State[0][i]-R0)/H);
			tempQ=C1/pow(m_r,0.5)*pow(den/den0,0.5)*pow(State[3][i]/Vc,3.15);
			tempq=den*State[3][i]*State[3][i]/2;
			tempn=tempq*pow(Cl*Cl+Cd*Cd,0.5)*m_s/(m_m*g);
			if(Q<tempQ)
			{	Q=tempQ;}
			if(q<tempq)
			{	q=tempq;}
			if(n<tempn)
			{	n=tempn;}
		}
	}
}

void CPSO1Doc::OnConstraintFinal()
{
	// TODO: Add your command handler code here
	CDiaFinal diaFinal;
	if(IDOK==diaFinal.DoModal())
	{
		//  再建一个保存终端 
		m_finalflag1=diaFinal.m_final1flag;
		m_finalflag2=diaFinal.m_final2flag;
		m_finalflag3=diaFinal.m_final3flag;
		m_finalflag4=diaFinal.m_final4flag;
		m_finalflag5=diaFinal.m_final5flag;
		m_finalflag6=diaFinal.m_final6flag;
		m_finalState1=diaFinal.m_state1+R0;
		m_finalState2=diaFinal.m_state2*pi/180;
		m_finalState3=diaFinal.m_state3*pi/180;
		m_finalState4=diaFinal.m_state4;
		m_finalState5=diaFinal.m_state5*pi/180;
		m_finalState6=diaFinal.m_state6*pi/180;
	}
}


void CPSO1Doc::HeapDel(double** ParSwarm, double** ParSwarmV, double** OptSwarm, double* AdaptSwarm, double* TimeSwarm, double* TimeSwarmV, double* OptTime, double* BestTime, double* BestPar, double** STate)
{
	for(UINT i=0;i<m_n;i++)
	{
		delete(ParSwarm[i]);
		delete(ParSwarmV[i]);
		delete(OptSwarm[i]);
	}
	delete(ParSwarm);
	delete(ParSwarmV);
	delete(OptSwarm);
	delete(AdaptSwarm);
	delete(TimeSwarm);
	delete(TimeSwarmV);
	delete(OptTime);
	delete(BestTime);
	delete(BestPar);
	for(UINT i=0;i<6;i++)
	{
		delete(STate[i]);
	}
	delete(STate);

}


void CPSO1Doc::DiffFunc(double contr,double*k, double state1, double state2, double state3, double state4, double state5, double state6)
{
	double s5=sin(state5);
	double c5=cos(state5);
	double s6=sin(state6);
	double c6=cos(state6);
	double s3=sin(state3);
	double c3=cos(state3);
	
	double Cl,Cd;
	double D;
	double L;
	double g;
	double den;
	double a;

	a=AFunc(state4);

    ClCdFunc(a,state4,&Cl,&Cd);

	den=den0*exp(-(state1-R0)/H);
	L=den*state4*state4*m_s*Cl/2;
	D=den*state4*state4*m_s*Cd/2;
	g=R0*R0*g0/(state1*state1);

	//量纲方程  所有量都为量纲量
	k[0]=state4*s5;
	k[1]=state4*c5*s6/(state1*c3);
	k[2]=state4*c5*c6/state1;
	k[3]=-D/m_m-g*s5+wE*wE*state1*c3*(s5*c3-c5*s3*c6);
	k[4]=(L*cos(contr)/m_m+(state4*state4/state1-g)*c5+2*wE*state4*c3*s6+wE*wE*state1*c3*(c5*c3+s5*s3*c6))/state4;
	k[5]=(L*sin(contr)/(m_m*c5)+state4*state4/state1*c5*s6*tan(state3)-2*wE*state4*(c3*tan(state5)*c6-s3)+wE*wE*state1/c5*s3*c3*s6)/state4;
	

}

// 不使用最优攻角模型
void CPSO1Doc::DiffFunc(double contr,double contr_a,double*k, double state1, double state2, double state3, double state4, double state5, double state6)
{
	double s5=sin(state5);
	double c5=cos(state5);
	double s6=sin(state6);
	double c6=cos(state6);
	double s3=sin(state3);
	double c3=cos(state3);
	
	double Cl,Cd;
	double D;
	double L;
	double g;
	double den;
	//double a;

	//a=AFunc(state4);

    ClCdFunc(contr_a,state4,&Cl,&Cd);

	den=den0*exp(-(state1-R0)/H);
	L=den*state4*state4*m_s*Cl/2;
	D=den*state4*state4*m_s*Cd/2;
	g=R0*R0*g0/(state1*state1);

	//量纲方程  所有量都为量纲量
	k[0]=state4*s5;
	k[1]=state4*c5*s6/(state1*c3);
	k[2]=state4*c5*c6/state1;
	k[3]=-D/m_m-g*s5+wE*wE*state1*c3*(s5*c3-c5*s3*c6);
	k[4]=(L*cos(contr)/m_m+(state4*state4/state1-g)*c5+2*wE*state4*c3*s6+wE*wE*state1*c3*(c5*c3+s5*s3*c6))/state4;
	k[5]=(L*sin(contr)/(m_m*c5)+state4*state4/state1*c5*s6*tan(state3)-2*wE*state4*(c3*tan(state5)*c6-s3)+wE*wE*state1/c5*s3*c3*s6)/state4;
	

}


void CPSO1Doc::OnStop()
{
	// TODO: Add your command handler code here
	//  清空doc类成员变量数据
	m_saFlag=FALSE;
	m_gaFlag=FALSE;
	m_gaHet=0.04;
	//PSO 控制变量
	m_d=20;
	m_n=50;
	m_scope[0]=-80*pi/180;
	m_scope[1]=80*pi/180;
	m_randFlag=0;
	//时间约束
	m_tScope[0]=1000.0;
	m_tScope[1]=3000.0;
	//路径约束 最大值
	m_Qmax=1000000;
	m_qmax=500000;
	m_nmax=6;
	m_conlimit=1*pi/180;
	m_egcFlag=1;
	//迭代次数
	m_loopMax=500;
	m_stepCount=0;
	// 攻角
	m_v1=5000;
	m_v2=3000;
	m_amax=20;
	m_amaxLD=10;
	//飞行器参数
	m_m=907.2;
	m_r=0.1;
	m_s=0.4839;
	//
	m_picOption1=TRUE;
	m_picOption2=TRUE;
	m_picN=1000;
	m_interpFlag=1;
	// 全局 最优值
	m_bestControl.RemoveAll();

	m_stateN=40;

	m_state1.RemoveAll();
	m_state2.RemoveAll();
	m_state3.RemoveAll();
	m_state4.RemoveAll();
	m_state5.RemoveAll();
	m_state6.RemoveAll();

	m_picstate1.RemoveAll();
	m_picstate2.RemoveAll();
	m_picstate3.RemoveAll();
	m_picstate4.RemoveAll();
	m_picstate5.RemoveAll();
	m_picstate6.RemoveAll();

	m_Q.RemoveAll();
	m_q.RemoveAll();
	m_nLimit.RemoveAll();

	m_picQ.RemoveAll();
	m_picq.RemoveAll();
	m_picnLimit.RemoveAll();

	m_state1.Add(R0+100000);
	m_state2.Add(160.0*pi/180);
	m_state3.Add(25.0*pi/180);
	m_state4.Add(7200.0);
	m_state5.Add(-2.0*pi/180);
	m_state6.Add(58.0*pi/180);

	m_finalflag1=1;
	m_finalflag2=1;
	m_finalflag3=1;
	m_finalflag4=1;
	m_finalflag5=0;
	m_finalflag6=0;
	m_finalState1=R0+20000;
	m_finalState2=232.0*pi/180;
	m_finalState3=37.0*pi/180;
	m_finalState4=1000.0;
	m_finalState5=0.0;
	m_finalState6=0.0;

	m_bestAdapt=0;
	m_bestTime=0;

	m_target1=10;
	m_target2=1;
	m_target3=10000;
	m_target4=100000000;


	// 菜单数据清空
	CDiaControl::m_d=20;
	CDiaControl::m_maxScope=80;
	CDiaControl::m_minScope=-80;
	CDiaControl::m_n=50;
	CDiaControl::m_randFlag=0;

	CDiaMore::m_saFlag=FALSE;
	CDiaMore::m_gaFlag=FALSE;
	CDiaMore::m_gaHet=0.04;
	CDiaMore::m_saCho=0.1;

	CDiaFinal::m_state1=20000.0;
	CDiaFinal::m_state2=232.0;
	CDiaFinal::m_state3=37.0;
	CDiaFinal::m_state4=1000.0;
	CDiaFinal::m_state5=0.0;
	CDiaFinal::m_state6=0.0;
	CDiaFinal::m_final1flag=1;
	CDiaFinal::m_final2flag=1;
	CDiaFinal::m_final3flag=1;
	CDiaFinal::m_final4flag=1;
	CDiaFinal::m_final5flag=0;
	CDiaFinal::m_final6flag=0;

	CDiaFinalTime::m_t=0.0;
	CDiaFinalTime::m_t0=1000.0;
	CDiaFinalTime::m_tf=3000.0;

	CDiaPath::m_dpMax=50000.0;
	CDiaPath::m_nMax=6.0;
	CDiaPath::m_qMax=1000000.0;
	CDiaPath::m_con=1.0;
	CDiaPath::m_egcFlag=1;

	CDiaState::m_stateN=40;
	CDiaState::m_initState1=100000.0;
	CDiaState::m_initState2=160.0;
	CDiaState::m_initState3=25.0;
	CDiaState::m_initState4=7200.0;
	CDiaState::m_initState5=-2.0;
	CDiaState::m_initState6=58.0;

	CDiaStop::m_loopMax=500;

	CDiaA::m_amax=20;
	CDiaA::m_amaxLD=10;
	CDiaA::m_v1=5000;
	CDiaA::m_v2=3000;

	CDiaPlane::m_m=907.2;
	CDiaPlane::m_s=0.4839;
	CDiaPlane::m_r=0.1;

	CDiaTargetM::m_target1=10;
	CDiaTargetM::m_target2=1;
	CDiaTargetM::m_target3=10000;
	CDiaTargetM::m_target4=100000000;

	m_targetFlag=3;

	CDiaPicOption::m_picOption1=TRUE;
	CDiaPicOption::m_picOption2=TRUE;
	CDiaPicOption::m_picN=1000;
	CDiaPicOption::m_interpFlag=1;
	// 清空图形
	POSITION pos=GetFirstViewPosition();
	CPSO1View* v=(CPSO1View*)GetNextView(pos);
	v->m_reFlag=0;
	v->Invalidate();
	v->SendMessage(WM_PAINT);
	v->m_reFlag=1;
}


void CPSO1Doc::OnTarget1()
{
	// TODO: Add your command handler code here
	m_targetFlag=1;
	m_egcFlag=1;
	CDiaPath::m_egcFlag=1;
}


void CPSO1Doc::OnTarget2()
{
	// TODO: Add your command handler code here
	m_targetFlag=2;
	m_egcFlag=0;
	CDiaPath::m_egcFlag=0;
}


void CPSO1Doc::OnTarget3()
{
	// TODO: Add your command handler code here
	m_targetFlag=3;
	m_egcFlag=1;
	CDiaPath::m_egcFlag=1;
}


void CPSO1Doc::OnTarget4()
{
	// TODO: Add your command handler code here
	m_targetFlag=4;
	m_egcFlag=1;
	CDiaPath::m_egcFlag=1;
}


void CPSO1Doc::OnTargetM()
{
	// TODO: Add your command handler code here
	CDiaTargetM diaTar;
	m_egcFlag=1;
	CDiaPath::m_egcFlag=1;
	if(IDOK==diaTar.DoModal())
	{
		m_targetFlag=5;
		//能做完再说
	}
}


void CPSO1Doc::DelData()
{
	m_stepCount=0;
	m_bestAdapt=0;
	m_bestTime=0;
	m_bestControl.RemoveAll();
	m_picControl.RemoveAll();
	double temp1=m_state1.GetAt(0);
	double temp2=m_state2.GetAt(0);
	double temp3=m_state3.GetAt(0);
	double temp4=m_state4.GetAt(0);
	double temp5=m_state5.GetAt(0);
	double temp6=m_state6.GetAt(0);

	m_state1.RemoveAll();
	m_state2.RemoveAll();
	m_state3.RemoveAll();
	m_state4.RemoveAll();
	m_state5.RemoveAll();
	m_state6.RemoveAll();

	m_Q.RemoveAll();
	m_q.RemoveAll();
	m_nLimit.RemoveAll();

	m_picstate1.RemoveAll();
	m_picstate2.RemoveAll();
	m_picstate3.RemoveAll();
	m_picstate4.RemoveAll();
	m_picstate5.RemoveAll();
	m_picstate6.RemoveAll();

	m_picQ.RemoveAll();
	m_picq.RemoveAll();
	m_picnLimit.RemoveAll();

	m_state1.Add(temp1);
	m_state2.Add(temp2);
	m_state3.Add(temp3);
	m_state4.Add(temp4);
	m_state5.Add(temp5);
	m_state6.Add(temp6);


}


double CPSO1Doc::Interp1(double* y, double xi)
{
	double result;
	for(UINT j=0;j<m_d;j++)
	{
		if(xi>=(double)j/(m_d-1)&&xi<=(double)(j+1)/(m_d-1))
		{
			result=-(y[j+1]-y[j])*(m_d-1)*((double)(j+1)/(m_d-1)-xi)+y[j+1];
			return result;
		}
	}
	return 0;
}


double CPSO1Doc::AFunc(double V)
{
	if(V>=m_v1)
	{
		return m_amax/180*pi;
	}
	else if(V<m_v1&&V>m_v2)
	{
		return ((m_amaxLD-m_amax)/(m_v2-m_v1)*(V-m_v1)+m_amax)/180*pi;
	}
	else
	{
		return m_amaxLD/180*pi;
	}
}


void CPSO1Doc::OnPsoA()
{
	// TODO: Add your command handler code here
	CDiaA diaA;
	if(IDOK==diaA.DoModal())
	{
		m_amax=diaA.m_amax;
		m_amaxLD=diaA.m_amaxLD;
		m_v1=diaA.m_v1;
		m_v2=diaA.m_v2;
	}
}


void CPSO1Doc::OnPsoPlane()
{
	// TODO: Add your command handler code here
	CDiaPlane diaPlane;
	if(IDOK==diaPlane.DoModal())
	{
		m_m=diaPlane.m_m;
		m_r=diaPlane.m_r;
		m_s=diaPlane.m_s;
	}
}

//CArray<double,double> CPSO1Doc::operator = (CArray<double,double> arr)
//{
//	CArray<double,double> result;
//	for(int i=0;i<arr.GetSize();i++)
//	{
//		result.Add(arr.GetAt(i));
//	}
//	return result;
//}

double CPSO1Doc::FinalLimits(double** state)
{
	// 角度约束乘以10  以免跟速度高度比 过小
	// 权值可能不合适  1/10000 40000 400000 1/100 400000 40000  已放弃
	//  一弧度 -》 R0m
	double result=0;
	if(m_finalflag1)
	{
		result += (state[0][m_stateN-1]-m_finalState1)*(state[0][m_stateN-1]-m_finalState1)/100/100;
		//result += exp((state[0][m_stateN-1]-m_finalState1)*(state[0][m_stateN-1]-m_finalState1)/1000/1000);
	}
	if(m_finalflag2)
	{
		//result += exp(abs(state[1][m_stateN-1]-m_finalState2)*6000000/5000);
		result += (state[1][m_stateN-1]-m_finalState2)*6000000/10000*(state[1][m_stateN-1]-m_finalState2)*6000000/10000;
		//result += exp((state[1][m_stateN-1]-m_finalState2)*6000000/10000*(state[1][m_stateN-1]-m_finalState2)*6000000/10000);
	}
	if(m_finalflag3)
	{
		//result += exp(abs(state[2][m_stateN-1]-m_finalState3)*6000000/5000);
		result += (state[2][m_stateN-1]-m_finalState3)*6000000/10000*(state[2][m_stateN-1]-m_finalState3)*6000000/10000;
		//result += exp((state[2][m_stateN-1]-m_finalState3)*6000000/10000*(state[2][m_stateN-1]-m_finalState3)*6000000/10000);
	}
	if(m_finalflag4)
	{
		//result += exp(abs(state[3][m_stateN-1]-m_finalState4)/100);
		result += (state[3][m_stateN-1]-m_finalState4)/8*(state[3][m_stateN-1]-m_finalState4)/8;
		//result += exp(state[3][m_stateN-1]-m_finalState4)/100*(state[3][m_stateN-1]-m_finalState4)/100;
	}
	if(m_finalflag5)
	{
		result += (state[4][m_stateN-1]-m_finalState5)*6000000/10000*(state[4][m_stateN-1]-m_finalState5)*6000000/10000;
		//result += exp(abs(state[4][m_stateN-1]-m_finalState5)*6000000/10000);
	}
	if(m_finalflag6)
	{
		result += ((state[5][m_stateN-1]-m_finalState6)*6000000/10000)*((state[5][m_stateN-1]-m_finalState6)*6000000/10000);
		//result += exp(abs(state[5][m_stateN-1]-m_finalState6)*6000000/10000);
	}

	return result;
}


double CPSO1Doc::TargetFunc(double** state, double finaltime, double* con)
{
	double s=0;
	double t=0;
	double c=0;
	double result;
	if(m_targetFlag==2||m_targetFlag==5)
	{
		for(UINT i=0;i<m_stateN;i++)
		{
			s += state[3][i]*cos(state[4][i])*finaltime/(m_stateN-1);
		}
	}
	if(m_targetFlag==3||m_targetFlag==5)
	{
		// 10 后加
		t += 5*finaltime;
	}
	if(m_targetFlag==4||m_targetFlag==5)
	{
		for(UINT i=1;i<m_d;i++)
		{
			c += abs(con[i]-con[i-1])/(finaltime/(m_d-1))+abs(con[m_d+i]-con[m_d+i-1])/(finaltime/(m_d-1)); //每秒变化
		}
	}
	switch(m_targetFlag)
	{
	case 2:
		result = 10*s;
		break;
	case 3:
		result = -100000*t;
		break;
	case 4:
		result = -1e9*c;
		break;
	case 5:
		result =m_target2*s-m_target3*t-m_target4*c;
		break;
	}
	return result;
}


void CPSO1Doc::PathLimitPic(double** state, double* pathQ, double* pathq, double* pathn)
{
	double Q;
	double q;
	double n;
	double g;
	double a;
	double Cl;
	double Cd;
	double den;
	double C1=11030;
	for(UINT i=0;i<m_stateN;i++)
	{
		g=R0*R0*g0/(state[0][i]*state[0][i]);
		a=AFunc(state[3][i]);
	
		ClCdFunc(a,state[3][i],&Cl,&Cd);
		
		den=den0*exp(-(state[0][i]-R0)/H);
		Q=C1/pow(m_r,0.5)*pow(den/den0,0.5)*pow((state[3][i]/Vc),3.15);
		q=den*state[3][i]*state[3][i]/2;
		n=q*pow(Cl*Cl+Cd*Cd,0.5)*m_s/(m_m*g);

		pathQ[i]=Q;
		pathq[i]=q;
		pathn[i]=n;
	}
}

void CPSO1Doc::PathLimitPic(double** state,double* con, double* pathQ, double* pathq, double* pathn)
{
	double Q;
	double q;
	double n;
	double g;
	double a;
	double Cl;
	double Cd;
	double den;
	double C1=11030;
	for(UINT i=0;i<m_stateN;i++)
	{
		g=R0*R0*g0/(state[0][i]*state[0][i]);

		//Interp1_ab(con,(double)i/(m_stateN-1),a,b);
		a=Interp1(con+m_d,(double)i/(m_stateN-1));

		ClCdFunc(a,state[3][i],&Cl,&Cd);
		
		den=den0*exp(-(state[0][i]-R0)/H);
		Q=C1/pow(m_r,0.5)*pow(den/den0,0.5)*pow((state[3][i]/Vc),3.15);
		q=den*state[3][i]*state[3][i]/2;
		n=q*pow(Cl*Cl+Cd*Cd,0.5)*m_s/(m_m*g);
		
		pathQ[i]=Q;
		pathq[i]=q;
		pathn[i]=n;
	}
}


double CPSO1Doc::ConLimit(double* con,double time)
{
	double t=time/(double)(m_d-1);
	double maxb=abs(con[1]-con[0]);
	double maxa=abs(con[m_d+1]-con[m_d]);
	double deg=m_conlimit*7/10;  //对曲线平滑做适当补偿
	double temp=0,temp_a=0;
	double limit=0;
	for(UINT i=2;i<m_d;i++)
	{
		temp=abs(con[i]-con[i-1]);
		if(maxb<temp)
		{
			maxb=temp;
		}
		temp_a=abs(con[m_d+i]-con[m_d+i-1]);
		if(maxa<temp_a)
		{
			maxa=temp_a;
		}
	}
	limit=exp((maxb-deg*t)*10)+exp((maxa-pi/180*t)*10);
	return limit;
}


double CPSO1Doc::EGCLimit(double** state, double time)
{
	double a;
	double Cl,Cd;
	double result=0;
	double L;
	double den;
	double g;
	for(UINT i=0;i<m_stateN;i++)
	{
		g=R0*R0*g0/(state[0][i]*state[0][i]);
		den=den0*exp(-(state[0][i]-R0)/H);
		a=AFunc(state[3][i]);

	    ClCdFunc(a,state[3][i],&Cl,&Cd);

		L=den*state[3][i]*state[3][i]*m_s*Cl/2;
		//result += exp(((state[3][i]*state[3][i]/state[0][i]-g)+L/m_m));

		result += 4*((state[3][i]*state[3][i]/state[0][i]-g)+L/m_m)*((state[3][i]*state[3][i]/state[0][i]-g)+L/m_m);
		result += (state[4][i]*state[4][i]);
		//result += exp(((state[3][i]*state[3][i]/state[0][i]-g)+L/m_m)/30);
	}

	//double result=0;
	//double t=time/(double)(m_stateN-1);
	//double limit=0;
	//double deg1=0.01*pi/180;
	//double deg2=0.1*pi/180;
	//double state5=abs(state[4][1]-state[4][0]);
	//double state6=abs(state[5][1]-state[5][0]);
	//double tempstate5;
	//double tempstate6;
	//for(UINT i=2;i<m_stateN;i++)
	//{
	//	/*tempstate5=abs(state[4][i]-state[4][i-1]);
	//	tempstate6=abs(state[5][i]-state[5][i-1]);
	//	if(state5<tempstate5)
	//	{
	//		state5=tempstate5;
	//	}
	//	if(state6<tempstate6)
	//	{
	//		state6=tempstate6;
	//	}*/
	//}
	//result=exp((state5-deg1*t)*10)+exp((state6-deg2*t)*10);
	return result;
}

double CPSO1Doc::EGCLimit(double** state,double* contr,double time)
{
	double a;
	double Cl,Cd;
	double result=0;
	double L;
	double den;
	double g;
	for(UINT i=0;i<m_stateN;i++)
	{
		//求攻角时效率不高
		g=R0*R0*g0/(state[0][i]*state[0][i]);
		den=den0*exp(-(state[0][i]-R0)/H);
		//Interp1_ab(contr,(double)i/(m_stateN-1),a,b);
		a=Interp1(contr+m_d,(double)i/(m_stateN-1));

	    ClCdFunc(a,state[3][i],&Cl,&Cd);

		L=den*state[3][i]*state[3][i]*m_s*Cl/2;
		//result += exp(((state[3][i]*state[3][i]/state[0][i]-g)+L/m_m));

		// 这个策略比较好，轨迹不会skip 也不会突然降低
		result += ((state[3][i]*state[3][i]/state[0][i]-g)+L/m_m)*((state[3][i]*state[3][i]/state[0][i]-g)+L/m_m);
		result += (state[4][i]*state[4][i]);

		//result += exp(((state[3][i]*state[3][i]/state[0][i]-g)+L/m_m)/30);
		
		//result += ((state[3][i]*state[3][i]/state[0][i]-g)+L/m_m);
	}

	//double result=0;
	//double t=time/(double)(m_stateN-1);
	//double limit=0;
	//double deg1=0.01*pi/180;
	//double deg2=0.1*pi/180;
	//double state5=abs(state[4][1]-state[4][0]);
	//double state6=abs(state[5][1]-state[5][0]);
	//double tempstate5;
	//double tempstate6;
	//for(UINT i=2;i<m_stateN;i++)
	//{
	//	/*tempstate5=abs(state[4][i]-state[4][i-1]);
	//	tempstate6=abs(state[5][i]-state[5][i-1]);
	//	if(state5<tempstate5)
	//	{
	//		state5=tempstate5;
	//	}
	//	if(state6<tempstate6)
	//	{
	//		state6=tempstate6;
	//	}*/
	//}
	//result=exp((state5-deg1*t)*10)+exp((state6-deg2*t)*10);
	return result;
}


void CPSO1Doc::OnPictureOption()
{
	// TODO: Add your command handler code here
	CDiaPicOption diaPic;
	if(IDOK==diaPic.DoModal())
	{
		m_picOption1=diaPic.m_picOption1;
		m_picOption2=diaPic.m_picOption2;
		m_picN=diaPic.m_picN;
		m_interpFlag=diaPic.m_interpFlag;
	}
}


void CPSO1Doc::PathLimitPicLine(double** picstate, double* picQ, double* picq, double* picn)
{
	double Q;
	double q;
	double n;
	double g;
	double a;
	double Cl;
	double Cd;
	double den;
	double C1=11030;
	for(UINT i=0;i<m_picN;i++)
	{
		g=R0*R0*g0/(picstate[0][i]*picstate[0][i]);
		a=AFunc(picstate[3][i]);
		

	    ClCdFunc(a,picstate[3][i],&Cl,&Cd);
		den=den0*exp(-(picstate[0][i]-R0)/H);
		Q=C1/pow(m_r,0.5)*pow(den/den0,0.5)*pow((picstate[3][i]/Vc),3.15);
		q=den*picstate[3][i]*picstate[3][i]/2;
		n=q*pow(Cl*Cl+Cd*Cd,0.5)*m_s/(m_m*g);

		picQ[i]=Q;
		picq[i]=q;
		picn[i]=n;
	}
}

void CPSO1Doc::PathLimitPicLine(double** picstate,double*con, double* picQ, double* picq, double* picn)
{
	double Q;
	double q;
	double n;
	double g;
	double a;
	double Cl;
	double Cd;
	double den;
	double C1=11030;
	for(UINT i=0;i<m_picN;i++)
	{
		g=R0*R0*g0/(picstate[0][i]*picstate[0][i]);
		
		//Interp1_ab(con,(double)i/(m_picN-1),a,b);
		a=Interp1(con+m_d,(double)i/(m_picN-1));

	    ClCdFunc(a,picstate[3][i],&Cl,&Cd);
		den=den0*exp(-(picstate[0][i]-R0)/H);
		Q=C1/pow(m_r,0.5)*pow(den/den0,0.5)*pow((picstate[3][i]/Vc),3.15);
		q=den*picstate[3][i]*picstate[3][i]/2;
		n=q*pow(Cl*Cl+Cd*Cd,0.5)*m_s/(m_m*g);

		picQ[i]=Q;
		picq[i]=q;
		picn[i]=n;
	}
}


void CPSO1Doc::UpdatePar(double* TimePar, double* TimeParV, double* OptTime, double* Par, double* ParV, double* OptPar)
{
	*TimePar=((double)rand()/RAND_MAX)*(m_tScope[1]-m_tScope[0])+m_tScope[0];
	*TimeParV=((double)rand()/RAND_MAX)*(m_tScope[1]-m_tScope[0])*pow(-1.0,rand()%2);
	*OptTime=*TimePar;
	for(UINT j=0;j<m_d;j++)
	{
		Par[j]=((double)rand()/RAND_MAX)*(m_scope[1]-m_scope[0])+m_scope[0];
		ParV[j]=((double)rand()/RAND_MAX)*(m_scope[1]-m_scope[0])*pow(-1.0,rand()%2);
		OptPar[j]=Par[j];

		Par[m_d+j]=((double)rand()/RAND_MAX)*(m_scope_a[1]-m_scope_a[0])+m_scope_a[0];
		ParV[m_d+j]=((double)rand()/RAND_MAX)*(m_scope_a[1]-m_scope_a[0])*pow(-1.0,rand()%2);
		OptPar[m_d+j]=Par[m_d+j];
	}
}


void CPSO1Doc::OnPsoMore()
{
	// TODO: Add your command handler code here
	CDiaMore diaM;
	if(IDOK==diaM.DoModal())
	{
		m_saFlag=diaM.m_saFlag;
		m_gaFlag=diaM.m_gaFlag;
		m_gaHet=diaM.m_gaHet;
		m_saCho=diaM.m_saCho;
	}
}


void CPSO1Doc::Lagrange(double* x, double* y, UINT n, double* result)
{
	// 时间设置成向量 作为x传入
	double element=0;
	double h=(x[n-1]-x[0])/(m_picN-1);  // 画图点的距离
	double xresult;
	double yresult;
	double xtemp;
	for(UINT index=0;index<m_picN;index++)
	{
		xresult=x[0]+h*index;
		yresult=0;
		for(UINT i=0;i<n;i++)
		{
			xtemp=1;
			for(UINT j=0;j<n;j++)
			{
				if(i!=j)
				{
					xtemp *= (xresult-x[j])/(x[i]-x[j]);
				}
			}
			yresult += y[i]*xtemp;
		}
		result[index]=yresult;
	}
}


void CPSO1Doc::Spline3(double* x, double* y, UINT n, double* result)
{
	//n xy的维数  result维数m_picN
	// 时间设置成向量 作为x传入
	// 间隔时间固定 所以h不变 简单些  ac为定值
	// 自然边界条件
	n=n-1; // 数组最大元素下标变为 n
	double h=(x[n]-x[0])/n;  // 画图点的距离
	double xh=(x[n]-x[0]);

	double a=0.5;
	double b=2;
	double c=0.5;
	double* d=new double[n-1];
	double* m=new double[n+1];
	double* v=new double[n-1];
	double* u=new double[n-1];
	m[0]=0;
	m[n]=0;  // 自由边界约束
	d[0]=6/(2*h)*((y[2]-y[1]-y[1]+y[0])/h);
	v[0]=c/b;
	u[0]=d[0]/b;
	for(UINT i=1;i<n-1;i++)
	{
		d[i]=6/(2*h)*((y[i+2]-y[i+1]-y[i+1]+y[i])/h);
		v[i]=c/(b-v[i-1]*a);
		u[i]=(d[i]-u[i-1]*a)/(b-v[i-1]*a);
	}
	for(UINT i=n-1;i>0;i--)
	{
		m[i]=u[i-1]-v[i-1]*m[i+1];
	}

	double xi;
	for(UINT i=0;i<m_picN;i++)
	{
		xi=x[0]+i*xh/(m_picN-1);
		for(UINT j=0;j<n;j++)
		{
			if(xi>=x[j]&&xi<=x[j+1])
			{
				result[i]=pow(x[j+1]-xi,3)*m[j]/(6*h)+pow(xi-x[j],3)*m[j+1]/(6*h)+(y[j]-(m[j]*h*h)/6)*(x[j+1]-xi)/h+(y[j+1]-m[j+1]*h*h/6)*(xi-x[j])/h;
				break;
			}
		}
	}

	delete(d);
	delete(m);
	delete(v);
	delete(u);
}


double CPSO1Doc::NoflyFunc(double** State)
{
	double limit=0;
	double j=200*pi/180;
	double w=35*pi/180;
	for(UINT i=0;i<m_stateN;i++)
	{
		if((State[1][i]-j)<5&&State[2][i]-w<5)
		{
			limit += 10000;
		}
	}
	return limit;
}


BOOL CPSO1Doc::ClCdFunc(double a, double v,double* Cl,double* Cd)
{
	*Cl=2.9451*a+0.2949*exp(-0.00033943*v/v_sound)-0.2355;
	*Cd=2.3795*a*a+0.3983*exp(-0.0010794*v/v_sound)+0.0234;
	return TRUE;
}


BOOL CPSO1Doc::Interp1_ab(double* y, double xi, double& a , double& b)
{
	for(UINT j=0;j<m_d-1;j++)
	{
		if(xi>=(double)j/(m_d-1)&&xi<=(double)(j+1)/(m_d-1))
		{
			b=-(y[j+1]-y[j])*(m_d-1)*((double)(j+1)/(m_d-1)-xi)+y[j+1];
			a=-(y[m_d+j+1]-y[m_d+j])*(m_d-1)*((double)(j+1)/(m_d-1)-xi)+y[m_d+j+1];
		}
	}
	return TRUE;
}


void CPSO1Doc::OnFileRemove()
{
	// TODO: Add your command handler code here
	CFile::Remove("data.txt");
}

void CPSO1Doc::NormalizationForLimit(double *adaptLimits,double **finalState,double *overLoad,double *pressure,double *heatDen,double *heat,double *conA,double *conB,double *track,double *dTrack)
{
	double fitFinalState[6];
	if(m_finalflag1)
		fitFinalState[0]=Max(finalState[0],m_n);
	if(m_finalflag2)
		fitFinalState[1]=Max(finalState[1],m_n);
	if(m_finalflag3)
		fitFinalState[2]=Max(finalState[2],m_n);
	if(m_finalflag5)
		fitFinalState[4]=Max(finalState[4],m_n);
	if(m_finalflag6)
		fitFinalState[5]=Max(finalState[5],m_n);
	// 等式约束
	if(m_finalflag4)
		fitFinalState[3]=Max(finalState[3],m_n);

	double maxOverLoad=Max(overLoad,m_n);
	double maxPressure=Max(pressure,m_n);
	double maxHeatDen=Max(heatDen,m_n);
	double maxHeat=Max(heat,m_n);
	double maxConA=Max(conA,m_n);
	double maxConB=Max(conB,m_n);
	double maxTrack=Max(track,m_n);
	double maxDTrack=Max(dTrack,m_n);

	for(int i=0;i<m_n;i++)
	{
		// 权值 * 对应部分/最大值
	}
	

}


void CPSO1Doc::OnWeight()
{
	// TODO: 在此添加命令处理程序代码
	CDiaLimitsWeight diaWeight;
	diaWeight.m_conA=m_wConA;
	diaWeight.m_conB=m_wConB;
	diaWeight.m_dTrack=m_wDTrack;
	diaWeight.m_gao=m_wS1;
	diaWeight.m_hangJi=m_wS5;
	diaWeight.m_hangXiang=m_wS6;
	diaWeight.m_heat=m_wHeat;
	diaWeight.m_heatDen=m_wHeatDen;
	diaWeight.m_jing=m_wS2;
	diaWeight.m_overLoad=m_wOver;
	diaWeight.m_pressure=m_wPressure;
	diaWeight.m_su=m_wS4;
	diaWeight.m_track=m_wTrack;
	diaWeight.m_wei=m_wS3;
	//diaWeight.UpdateData(FALSE);
	if(diaWeight.DoModal()==IDOK)
	{
		m_wConA=diaWeight.m_conA;
		m_wConB=diaWeight.m_conB;
		m_wDTrack=diaWeight.m_dTrack;
		m_wS1=diaWeight.m_gao;
		m_wS5=diaWeight.m_hangJi;
		m_wS6=diaWeight.m_hangXiang;
		m_wHeat=diaWeight.m_heat;
		m_wHeatDen=diaWeight.m_heatDen;
		m_wS2=diaWeight.m_jing;
		m_wOver=diaWeight.m_overLoad;
		m_wPressure=diaWeight.m_pressure;
		m_wS4=diaWeight.m_su;
		m_wTrack=diaWeight.m_track;
		m_wS3=diaWeight.m_wei;
		
		std::ofstream file("LimitsWeight.txt");
		file<<"gaodu "<<m_wS1
			<<"jingdu "<<m_wS2
			<<"weidu "<<m_wS3
			<<"sudu "<<m_wS4
			<<"hangjijiao "<<m_wS5
			<<"hangxiangjiao "<<m_wS6
			<<"guozai "<<m_wOver
			<<"dongya "<<m_wPressure
			<<"reliu "<<m_wHeatDen
			<<"zongreliang "<<m_wHeat
			<<"gongjiaobianhualv "<<m_wConA
			<<"qingcejiaobianhualv "<<m_wConB
			<<"track "<<m_wTrack
			<<"trackbianhualv "<<m_wDTrack;
	}

}

void CPSO1Doc::Initial()
{
	std::ifstream file("LimitsWeight.txt");
	char tempName[100];
	memset(tempName,0,sizeof(tempName));

	while(file>>tempName)
	{
		if(strcmp(tempName,"gaodu")==0)
		{
			file>>m_wS1;
			continue;
		}
		else if(strcmp(tempName,"jingdu")==0)
		{
			file>>m_wS2;
			continue;
		}
		else if(strcmp(tempName,"weidu")==0)
		{
			file>>m_wS3;
			continue;
		}
		else if(strcmp(tempName,"sudu")==0)
		{
			file>>m_wS4;
			continue;
		}
		else if(strcmp(tempName,"hangjijiao")==0)
		{
			file>>m_wS5;
			continue;
		}
		else if(strcmp(tempName,"hangxiangjiao")==0)
		{
			file>>m_wS6;
			continue;
		}
		else if(strcmp(tempName,"guozai")==0)
		{
			file>>m_wOver;
			continue;
		}
		else if(strcmp(tempName,"dongya")==0)
		{
			file>>m_wPressure;
			continue;
		}
		else if(strcmp(tempName,"reliu")==0)
		{
			file>>m_wHeatDen;
			continue;
		}
		else if(strcmp(tempName,"zongreliang")==0)
		{
			file>>m_wHeat;
			continue;
		}
		else if(strcmp(tempName,"gongjiaobianhualv")==0)
		{
			file>>m_wConA;
			continue;
		}
		else if(strcmp(tempName,"qingcejiaobianhualv")==0)
		{
			file>>m_wConB;
			continue;
		}
		else if(strcmp(tempName,"track")==0)
		{
			file>>m_wTrack;
			continue;
		}
		else if(strcmp(tempName,"trackbianhualv")==0)
		{
			file>>m_wDTrack;
			continue;
		}
	}


}
