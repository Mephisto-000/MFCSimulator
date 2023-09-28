// SimulateStartDlg.cpp: 實作檔案
//

#include "pch.h"
#include "MFCSimulator.h"
#include "afxdialogex.h"
#include "SimulateStartDlg.h"

#include "MFCSimulatorDlg.h"


// SimulateStartDlg 對話方塊

IMPLEMENT_DYNAMIC(SimulateStartDlg, CDialogEx)

SimulateStartDlg::SimulateStartDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SIMULATE_START, pParent)
{
	m_fontTimeAndResult.CreatePointFont(200, _T("Arial Black"));

	m_dwStartTime = 0;
	m_nTimerID = 1;
	m_dResultValue = 0.0;

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
	ON_WM_TIMER()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// SimulateStartDlg 訊息處理常式


BOOL SimulateStartDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此加入額外的初始化

	SetTimer(m_nTimerID, 50, nullptr);

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


void SimulateStartDlg::UpdateSimulate()
{


	CString strTimeValue;
	strTimeValue.Format(_T("%.7f"), m_dCurTime);
	m_staticTimeShow.SetWindowText(strTimeValue);

	CMFCSimulatorDlg dlgMain;
	m_dResultValue = dlgMain.SetPostfixResult(m_ptOutUnit, m_dCurTime);

	CString strResult;
	strResult.Format(_T("%.7f"), m_dResultValue);
	m_staticResultShow.SetWindowText(strResult);
}


void SimulateStartDlg::OnTimer(UINT_PTR nIDEvent)
{
	
	DWORD dwRecordTime = timeGetTime();


	if (nIDEvent == m_nTimerID)
	{

		DWORD dwElapsedTime = dwRecordTime - m_dwStartTime;
		double dSeconds = static_cast<double>(dwElapsedTime) / 1000.0;

		m_dCurTime = dSeconds;
		UpdateSimulate();

	}


	CDialogEx::OnTimer(m_nTimerID);
}


void SimulateStartDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此加入您的訊息處理常式程式碼
	// 不要呼叫圖片訊息的 CDialogEx::OnPaint()







}


void SimulateStartDlg::DrawToBuffer(CDC* pDC)
{








}
