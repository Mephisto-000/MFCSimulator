#pragma once
#include "afxdialogex.h"

// UnitInDlg 對話方塊

class CUnitInDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CUnitInDlg)

public:
	CUnitInDlg(CWnd* pParent = nullptr);   // 標準建構函式
	virtual ~CUnitInDlg();

// 對話方塊資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_UNIT_IN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();


	CEdit m_editShowChoose;														// 上方顯示選擇的函式或數值的控件	
	CString m_strFunChoose;													    // 選擇的函數或數值
	CString m_strFunFinalChoose;												// 最終確認的函數值
	CFont m_fontChooseText;														// 字型與字型大小調整


	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButtonInFalse();									// 選擇 false(0) 的按鈕
	afx_msg void OnBnClickedButtonInTrue();										// 選擇 true(1) 的按鈕
	afx_msg void OnBnClickedButtonInSin();										// 選擇 sin(t) 的按鈕
	afx_msg void OnBnClickedButtonInCos();                                      // 選擇 cos(t) 的按鈕
	afx_msg void OnBnClickedOk();												
	afx_msg void OnBnClickedCancel();
	afx_msg void OnDestroy();

};

