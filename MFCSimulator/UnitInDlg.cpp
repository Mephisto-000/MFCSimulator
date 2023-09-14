// UnitInDlg.cpp: 實作檔案
//

#include "pch.h"
#include "MFCSimulator.h"
#include "afxdialogex.h"
#include "UnitInDlg.h"

#include "UnitIn.h"

// UnitInDlg 對話方塊

IMPLEMENT_DYNAMIC(UnitInDlg, CDialogEx)

UnitInDlg::UnitInDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_UNIT_IN, pParent)
{

}

UnitInDlg::~UnitInDlg()
{
}

void UnitInDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_SHOW_CHOOSE, m_editShowChoose);
}


BEGIN_MESSAGE_MAP(UnitInDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_IN_FALSE, &UnitInDlg::OnBnClickedButtonInFalse)
	ON_BN_CLICKED(IDC_BUTTON_IN_TRUE, &UnitInDlg::OnBnClickedButtonInTrue)
	ON_BN_CLICKED(IDC_BUTTON_IN_SIN, &UnitInDlg::OnBnClickedButtonInSin)
	ON_BN_CLICKED(IDC_BUTTON_IN_COS, &UnitInDlg::OnBnClickedButtonInCos)
END_MESSAGE_MAP()


// UnitInDlg 訊息處理常式


BOOL UnitInDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此加入額外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX 屬性頁應傳回 FALSE
}




// False 按鈕
void UnitInDlg::OnBnClickedButtonInFalse()
{
	


}

// True 按鈕
void UnitInDlg::OnBnClickedButtonInTrue()
{
	// TODO: 在此加入控制項告知處理常式程式碼
}

// Sine 函式按鈕
void UnitInDlg::OnBnClickedButtonInSin()
{
	// TODO: 在此加入控制項告知處理常式程式碼
}

// Cosine 函式按鈕
void UnitInDlg::OnBnClickedButtonInCos()
{
	// TODO: 在此加入控制項告知處理常式程式碼
}
