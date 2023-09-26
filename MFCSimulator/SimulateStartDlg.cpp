// SimulateStartDlg.cpp: 實作檔案
//

#include "pch.h"
#include "MFCSimulator.h"
#include "afxdialogex.h"
#include "SimulateStartDlg.h"


// SimulateStartDlg 對話方塊

IMPLEMENT_DYNAMIC(SimulateStartDlg, CDialogEx)

SimulateStartDlg::SimulateStartDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

SimulateStartDlg::~SimulateStartDlg()
{
}

void SimulateStartDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(SimulateStartDlg, CDialogEx)
END_MESSAGE_MAP()


// SimulateStartDlg 訊息處理常式


BOOL SimulateStartDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此加入額外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX 屬性頁應傳回 FALSE
}
