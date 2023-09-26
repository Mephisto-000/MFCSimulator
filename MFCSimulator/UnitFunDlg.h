#pragma once
#include "afxdialogex.h"


// UnitFunDlg 對話方塊

class UnitFunDlg : public CDialogEx
{
	DECLARE_DYNAMIC(UnitFunDlg)

public:
	UnitFunDlg(CWnd* pParent = nullptr);   // 標準建構函式
	virtual ~UnitFunDlg();

// 對話方塊資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_UNIT_FUN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);



	CEdit m_editOperaChoose;
	CString m_strOperaChoose;
	CFont m_fontChooseText;


	afx_msg void OnBnClickedButtonFunPlus();
	afx_msg void OnBnClickedButtonFunMinus();
	afx_msg void OnBnClickedButtonFunMultiply();
	afx_msg void OnBnClickedButtonFunDivision();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
