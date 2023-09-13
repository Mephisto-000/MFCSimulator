// UnitInDlg.cpp: 實作檔案
//

#include "pch.h"
#include "MFCSimulator.h"
#include "afxdialogex.h"
#include "UnitInDlg.h"


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
}


BEGIN_MESSAGE_MAP(UnitInDlg, CDialogEx)
END_MESSAGE_MAP()


// UnitInDlg 訊息處理常式


BOOL UnitInDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此加入額外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX 屬性頁應傳回 FALSE
}
