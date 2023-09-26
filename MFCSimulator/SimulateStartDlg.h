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
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();


	





};
