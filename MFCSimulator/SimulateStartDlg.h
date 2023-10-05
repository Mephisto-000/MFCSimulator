#pragma once
#include "afxdialogex.h"

#include "UnitBase.h"
#include <cmath>
#include <deque>


#define _USE_MATH_DEFINES // for C++

// SimulateStartDlg 對話方塊

class SimulateStartDlg : public CDialogEx
{
	DECLARE_DYNAMIC(SimulateStartDlg)

public:
	SimulateStartDlg(CWnd* pParent = nullptr);   // 標準建構函式
	virtual ~SimulateStartDlg();

// 對話方塊資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SIMULATE_START };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();



	CStatic m_staticTimeShow;              // 顯示當下時間
	CStatic m_staticResultShow;            // 顯示當下計算結果
	CFont m_fontTimeAndResult;             // 自訂 時間與結果 狀態字型
	CFont m_fontTimeAndResultText;         // 自訂 時間與結果 標誌字型


	DWORD m_dwStartTime;                   // 計時開始的時間
	UINT_PTR m_nTimerID;                   // 計時器 ID
	double m_dCurTime;
	double m_dSimTime;

	CStatic m_staticTimeText;
	CStatic m_staticResultText;

	CButton m_buttonStart;
	CButton m_buttonStop;
	
	void UpdateSimulate();

	void DrawToBuffer(CDC* pDC);							// 雙緩衝更新區域函數
	void DrawGrid(CDC* pDC);                                // 畫出顯示區背景網格
	void DrawWave(CDC* pDC);                                // 畫出波型

	double m_dResultValue;                                    // 計算結果值
	std::deque<double> m_queueResultValue;                    // 繪圖用計算結果佇列


	UnitBase* m_ptOutUnit;


	COLORREF m_colorSimShowRegion;


	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonStop();

	CStatic m_staticResultShowRegion;

	double SetPostfixResult(UnitBase* ptUnit, double dTimeValue);
	BOOL m_bIsNAN;  // 判斷分母是否為 0 

};
