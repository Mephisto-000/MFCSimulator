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
	afx_msg void OnBnClickedButtonInFalse();
	afx_msg void OnBnClickedButtonInTrue();
	afx_msg void OnBnClickedButtonInSin();
	afx_msg void OnBnClickedButtonInCos();

	CEdit m_editShowChoose; 
	CString m_strFunChoose;
	CFont m_fontChooseText;

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
