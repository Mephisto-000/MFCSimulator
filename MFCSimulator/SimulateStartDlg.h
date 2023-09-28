#pragma once
#include "afxdialogex.h"

#include "UnitBase.h"

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


	CStatic m_staticTimeText;
	CStatic m_staticResultText;

	CButton m_buttonStart;
	CButton m_buttonStop;


	double m_dCurTime;
	
	void UpdateSimulate();
	void DrawToBuffer(CDC* pDC);							// 雙緩衝更新區域函數

	double m_dResultValue;

	CList<UnitBase*, UnitBase*> m_listUnitResult;

	UnitBase* m_ptOutUnit;





	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonStop();
};
