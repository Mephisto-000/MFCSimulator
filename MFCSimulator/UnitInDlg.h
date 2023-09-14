#pragma once
#include "afxdialogex.h"


// UnitInDlg 對話方塊

class UnitInDlg : public CDialogEx
{
	DECLARE_DYNAMIC(UnitInDlg)

public:
	UnitInDlg(CWnd* pParent = nullptr);   // 標準建構函式
	virtual ~UnitInDlg();

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
};
