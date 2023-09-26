// SimulateStartDlg.cpp: 實作檔案
//

#include "pch.h"
#include "MFCSimulator.h"
#include "afxdialogex.h"
#include "SimulateStartDlg.h"


// SimulateStartDlg 對話方塊

IMPLEMENT_DYNAMIC(SimulateStartDlg, CDialogEx)

SimulateStartDlg::SimulateStartDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SIMULATE_START, pParent)
{
	m_fontTimeAndResult.CreatePointFont(200, _T("Arial Black"));
}

SimulateStartDlg::~SimulateStartDlg()
{
}

void SimulateStartDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_TIME, m_staticTimeShow);
	DDX_Control(pDX, IDC_STATIC_RESULT, m_staticResultShow);
}


BEGIN_MESSAGE_MAP(SimulateStartDlg, CDialogEx)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// SimulateStartDlg 訊息處理常式


BOOL SimulateStartDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此加入額外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX 屬性頁應傳回 FALSE
}


HBRUSH SimulateStartDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此變更 DC 的任何屬性


	if ((pWnd->GetDlgCtrlID() == IDC_STATIC_TIME) || (pWnd->GetDlgCtrlID() == IDC_STATIC_RESULT))
	{
		pDC->SetTextColor(RGB(0, 0, 0));
		pDC->SelectObject(&m_fontTimeAndResult);
	}



	// TODO:  如果預設值並非想要的，則傳回不同的筆刷
	return hbr;
}
