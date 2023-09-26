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
	ON_BN_CLICKED(IDC_BUTTON_FUN_PLUS, &UnitFunDlg::OnBnClickedButtonFunPlus)
	ON_BN_CLICKED(IDC_BUTTON_FUN_MINUS, &UnitFunDlg::OnBnClickedButtonFunMinus)
	ON_BN_CLICKED(IDC_BUTTON_FUN_MULTIPLY, &UnitFunDlg::OnBnClickedButtonFunMultiply)
	ON_BN_CLICKED(IDC_BUTTON_FUN_DIVISION, &UnitFunDlg::OnBnClickedButtonFunDivision)
	ON_BN_CLICKED(IDOK, &UnitFunDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &UnitFunDlg::OnBnClickedCancel)
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



void UnitFunDlg::OnBnClickedButtonFunPlus()
{
	// TODO: 在此加入控制項告知處理常式程式碼
}


void UnitFunDlg::OnBnClickedButtonFunMinus()
{
	// TODO: 在此加入控制項告知處理常式程式碼
}


void UnitFunDlg::OnBnClickedButtonFunMultiply()
{
	// TODO: 在此加入控制項告知處理常式程式碼
}


void UnitFunDlg::OnBnClickedButtonFunDivision()
{
	// TODO: 在此加入控制項告知處理常式程式碼
}


void UnitFunDlg::OnBnClickedOk()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	CDialogEx::OnOK();
}


void UnitFunDlg::OnBnClickedCancel()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	CDialogEx::OnCancel();
}
