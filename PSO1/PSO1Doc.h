
// PSO1Doc.h : interface of the CPSO1Doc class
//


#pragma once
#include "afxtempl.h"


class CPSO1Doc : public CDocument
{
public:
	const double pi;
	const double R0;
	const double g0;
	const double uE;
	const double wE;
	const double Vc;
	const double den0;
	const double H;
	const double v_sound;
// 初始化 勿忘。。。。。。。。。。。。。。。
public:
	double m_startTime;
	BOOL m_saFlag;
	BOOL m_gaFlag;
	double m_gaHet;
	double m_saCho;
	//PSO 控制变量
	UINT m_d;
	UINT m_n;
	double m_scope[2];
	double m_scope_a[2];
	int m_randFlag;
	//时间约束
	double m_tScope[2];
	//路径约束 最大值
	double m_Qmax;
	double m_qmax;
	double m_nmax;
	double m_conlimit;
	int m_egcFlag;
	//迭代次数
	UINT m_loopMax;
	UINT m_stepCount;
	//攻角 
	double m_v1;
	double m_v2;
	double m_amax;
	double m_amaxLD;
	//飞行器参数
	double m_m;
	double m_s;
	double m_r;
	// 终端约束
	double m_finalState1;
	double m_finalState2;
	double m_finalState3;
	double m_finalState4;
	double m_finalState5;
	double m_finalState6;
	int m_finalflag1;
	int m_finalflag2;
	int m_finalflag3;
	int m_finalflag4;
	int m_finalflag5;
	int m_finalflag6;
	// 优化目标比例
	double m_target1;
	double m_target2;
	double m_target3;
	double m_target4;
	//画图
	BOOL m_picOption1;
	BOOL m_picOption2;
	UINT m_picN;
	int m_interpFlag;
	// 全局 最优值
	CArray<double,double> m_bestControl;
	CArray<double,double> m_picControl;
	CArray<double,double> m_bestControl_a;
	CArray<double,double> m_picControl_a;

	UINT m_stateN;
	CArray<double,double> m_state1;
	CArray<double,double> m_state2;
	CArray<double,double> m_state3;
	CArray<double,double> m_state4;
	CArray<double,double> m_state5;
	CArray<double,double> m_state6;

	CArray<double,double> m_picstate1;
	CArray<double,double> m_picstate2;
	CArray<double,double> m_picstate3;
	CArray<double,double> m_picstate4;
	CArray<double,double> m_picstate5;
	CArray<double,double> m_picstate6;

	CArray<double,double> m_Q;
	CArray<double,double> m_q;
	CArray<double,double> m_nLimit;

	CArray<double,double> m_picQ;
	CArray<double,double> m_picq;
	CArray<double,double> m_picnLimit;

	double m_bestAdapt;
	double m_bestTime;
	
	

protected: // create from serialization only
	CPSO1Doc();
	DECLARE_DYNCREATE(CPSO1Doc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CPSO1Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
private:
	afx_msg void OnPsoControl();
	afx_msg void OnConstraintPath();
	afx_msg void OnPsoStop();
public:
	afx_msg void OnStart();
private:
	void PsoProcess();
	void InitSwarm(double** ParSwarm, double** ParSwarmV,double** OptSwarm, double* AdaptSwarm, double* TimeSwarm, double* TimeSwarmV, double* BestPar, double* OptTime, double* BestTime, double** State);
	double AdaptFunc(double* contr, double finalTime, double** State);
	double Max(double* arry, UINT& n);
	void StepFunc(double** ParSwarm, double** ParSwarmV, double* TimeSwarm, double* TimeSwarmV, double** OptSwarm, double* BestPar, double* AdaptSwarm, double* OptTime, double* BestTime, double** State);
private:
	afx_msg void OnFinaltime();
	afx_msg void OnPsoState();
private:
	void LGKT(double* contr, double finalTime, double** State);
private:
	void PathLimits(double** State, double& Q, double& q, double& n, double& sumQ);
	void PathLimits(double** State, double* con,double& Q, double& q, double& n, double& sumQ);
	afx_msg void OnConstraintFinal();
private:
	void HeapDel(double** ParSwarm, double** ParSwarmV, double** OptSwarm, double* AdaptSwarm, double* TimeSwarm, double* TimeSwarmV, double* OptTime, double* BestTime, double* BestPar, double** State);
	void DiffFunc(double contr,double* k, double state1, double state2, double state3, double state4, double state5, double state6);
	void DiffFunc(double contr,double contr_a,double* k, double state1, double state2, double state3, double state4, double state5, double state6);
private:
	afx_msg void OnStop();
	afx_msg void OnTarget1();
public:
	UINT m_targetFlag;
	afx_msg void OnTarget2();
	afx_msg void OnTarget3();
	afx_msg void OnTarget4();
	afx_msg void OnTargetM();
	void DelData();
	double Interp1(double* y, double xi);
private:
	double AFunc(double V);
public:
	afx_msg void OnPsoA();
	afx_msg void OnPsoPlane();
//public:
	//CArray<double,double> operator =(CArray<double,double> arr);
	double FinalLimits(double** state);
	double TargetFunc(double** state, double finaltime, double* con);
	void PathLimitPic(double** state, double* pathQ, double* pathq, double* pathn);
	void PathLimitPic(double** state,double* con, double* pathQ, double* pathq, double* pathn);
	double ConLimit(double* con, double time);
	double EGCLimit(double** state,double time);
	double EGCLimit(double** state,double* contr,double time);
	afx_msg void OnPictureOption();
	void PathLimitPicLine(double** picstate, double* picQ, double* picq, double* picn);
	void PathLimitPicLine(double** picstate,double* con, double* picQ, double* picq, double* picn);
	void UpdatePar(double* TimePar, double* TimeParV, double* OptTime, double* Par, double* ParV, double* OptPar);
	afx_msg void OnPsoMore();
	// 插值函数
	void Lagrange(double* x, double* y, UINT n, double* result);
	void Spline3(double* x, double* y, UINT n, double* result);
	double NoflyFunc(double** State);
	BOOL ClCdFunc(double a, double v,double* Cl,double* Cd);
	BOOL Interp1_ab(double* y, double xi, double& a , double& b);
	afx_msg void OnFileRemove();

public:
	// 归一化的适应度计算
	void NormalizationForLimit(double *adapt,
		double **finalState,double *overLoad,double *pressure,double *heatDen,double *heat,double *conA,double *conB,double *track,double *dTrack);
	afx_msg void OnWeight();
	void Initial();  // 初始化权重
	double MaxEx(double *array,int n);
public:
	double m_wS1;
	double m_wS2;
	double m_wS3;
	double m_wS4;
	double m_wS5;
	double m_wS6;

	double m_wOver;
	double m_wPressure;
	double m_wHeatDen;
	double m_wHeat;
	double m_wConA;
	double m_wConB;
	double m_wTrack;
	double m_wDTrack;

	double m_wTime;

};
