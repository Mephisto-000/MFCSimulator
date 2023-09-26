// UnitFunDlg.cpp: 實作檔案
//

#include "pch.h"
#include "MFCSimulator.h"
#include "afxdialogex.h"
#include "UnitFunDlg.h"


// UnitFunDlg 對話方塊

IMPLEMENT_DYNAMIC(UnitFunDlg, CDialogEx)

UnitFunDlg::UnitFunDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_UNIT_FUN, pParent)
{

}

UnitFunDlg::~UnitFunDlg()
{
}

void UnitFunDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(UnitFunDlg, CDialogEx)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// UnitFunDlg 訊息處理常式


BOOL UnitFunDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此加入額外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX 屬性頁應傳回 FALSE
}


HBRUSH UnitFunDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此變更 DC 的任何屬性

	// TODO:  如果預設值並非想要的，則傳回不同的筆刷
	return hbr;
}

