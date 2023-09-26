#pragma once
#include "afxdialogex.h"


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

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
