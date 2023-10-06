#pragma once
#include "afxdialogex.h"

// UnitFunDlg 對話方塊

class CUnitFunDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CUnitFunDlg)

public:
	CUnitFunDlg(CWnd* pParent = nullptr);   // 標準建構函式
	virtual ~CUnitFunDlg();

// 對話方塊資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_UNIT_FUN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();


	CEdit m_editOperaChoose;													// 上方顯示選擇的運算元的控件
	CString m_strOperaChoose;													// 選擇的運算元
	CString m_strOperaFinalChoose;												// 最終確認的運算元
	CFont m_fontChooseText;														// 字型與字型大小調整


	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButtonFunPlus();                                    // 選擇加法運算元按鈕
	afx_msg void OnBnClickedButtonFunMinus();									// 選擇減法運算元按鈕
	afx_msg void OnBnClickedButtonFunMultiply();                                // 選擇乘法運算元按鈕
	afx_msg void OnBnClickedButtonFunDivision();                                // 選擇除法運算元按鈕
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnDestroy();

};

