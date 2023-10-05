#pragma once
#include "afxdialogex.h"
#include "CUnitBase.h"
#include <cmath>
#include <deque>

#define _USE_MATH_DEFINES // for C++

// SimulateStartDlg 對話方塊

class CSimulateStartDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSimulateStartDlg)

public:
	CSimulateStartDlg(CWnd* pParent = nullptr);   // 標準建構函式
	virtual ~CSimulateStartDlg();

// 對話方塊資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SIMULATE_START };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();


	CStatic m_staticTimeShow;													// 顯示當下時間
	CStatic m_staticResultShow;													// 顯示當下計算結果
	CStatic m_staticTimeText;													// 顯示當下時間的標題
	CStatic m_staticResultText;													// 顯示當下結果的標題
	CStatic m_staticResultShowRegion;											// 模擬繪圖的區域


	CFont m_fontTimeAndResult;													// 自訂 時間與結果 狀態字型
	CFont m_fontTimeAndResultText;												// 自訂 時間與結果 標誌字型


	DWORD m_dwStartTime;														// 計時開始的時間
	
	
	UINT_PTR m_nTimerID;														// 計時器 ID
	
	
	// 時間說明 : 
	// 當經過每單位系統時間間隔後，累加模擬函數的自變數時間，
	// 避免畫面因系統時間造成畫面有段點的錯誤。
	// 例 : 
	//		每經過 0.01 秒 系統時間，則累加自變數時間 PI / 100 。
	double m_dCurTime;															// 當下時間
	double m_dSimTime;															// 模擬函數的自變數時間
	double m_dResultValue;														// 記錄計算結果的值
	double SetPostfixResult(CUnitBase* ptUnit, double dTimeValue);              // 計算連線元件的函式結果


	CButton m_buttonStart;														// 開始模擬的按鈕
	CButton m_buttonStop;														// 停止模擬的按鈕
	

	void UpdateSimulate();														// 依單位間隔時間更新模擬的值
	void DrawToBuffer(CDC* pDC);												// 雙緩衝更新區域函數
	void DrawGrid(CDC* pDC);													// 畫出顯示區背景網格
	void DrawWave(CDC* pDC);													// 畫出模擬的波型


	std::deque<double> m_queueResultValue;										// 儲存計算結果的佇列


	CUnitBase* m_ptOutUnit;														// 記錄選取的 OUT 指標


	COLORREF m_colorSimShowRegion;												// 模擬區背景顏色


	BOOL m_bIsNAN;																// 判斷計算的函示中，是否有分母為 0 的情況 


	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnTimer(UINT_PTR nIDEvent);									// 單位間隔時間發生的事件 
	afx_msg void OnPaint();														// 繪圖
	afx_msg void OnBnClickedButtonStart();										// 開始模擬的按鈕
	afx_msg void OnBnClickedButtonStop();										//停止模擬的按鈕
	afx_msg void OnDestroy();													// 關閉視窗

};

