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
	m_fontTimeAndResultText.CreatePointFont(150, _T("Arial Black"));

	m_dwStartTime = 0;
	m_nTimerID = 1;
	m_dResultValue = 0.0;

	m_colorSimShowRegion = RGB(0, 0, 0);

}

SimulateStartDlg::~SimulateStartDlg()
{
}

void SimulateStartDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_TIME, m_staticTimeShow);
	DDX_Control(pDX, IDC_STATIC_RESULT, m_staticResultShow);
	DDX_Control(pDX, IDC_STATIC_TIME_TEXT, m_staticTimeText);
	DDX_Control(pDX, IDC_STATIC_RESULT_TEXT, m_staticResultText);
	DDX_Control(pDX, IDC_BUTTON_START, m_buttonStart);
	DDX_Control(pDX, IDC_BUTTON_STOP, m_buttonStop);
	DDX_Control(pDX, IDC_STATIC_RESULT_SHOW, m_staticResultShowRegion);
}


BEGIN_MESSAGE_MAP(SimulateStartDlg, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_START, &SimulateStartDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &SimulateStartDlg::OnBnClickedButtonStop)
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
		pDC->SetTextColor(RGB(255, 0, 0));
		pDC->SelectObject(&m_fontTimeAndResult);
	}

	if ((pWnd->GetDlgCtrlID() == IDC_STATIC_TIME_TEXT) || (pWnd->GetDlgCtrlID() == IDC_STATIC_RESULT_TEXT))
	{

		pDC->SetTextColor(RGB(0, 0, 0));
		pDC->SelectObject(&m_fontTimeAndResultText);
	}



	// TODO:  如果預設值並非想要的，則傳回不同的筆刷
	return hbr;
}


void SimulateStartDlg::UpdateSimulate()
{


	CString strTimeValue;
	strTimeValue.Format(_T("%.3f"), m_dCurTime);
	m_staticTimeShow.SetWindowText(strTimeValue);

	CMFCSimulatorDlg dlgMain;
	m_dResultValue = dlgMain.SetPostfixResult(m_ptOutUnit, m_dCurTime);

	CString strResult;
	strResult.Format(_T("%.4f"), m_dResultValue);
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
	CPaintDC dc(this);
	// TODO: 在此加入您的訊息處理常式程式碼
	// 不要呼叫圖片訊息的 CDialogEx::OnPaint()

	// 取得操作視窗矩形資訊
	CWnd* pSimShowRegion = GetDlgItem(IDC_STATIC_RESULT_SHOW);
	CRect rectSimShowRegion;

	pSimShowRegion->GetClientRect(&rectSimShowRegion);
	int iWidthSimShowRegion = rectSimShowRegion.Width();
	int iHeightSimShowRegion = rectSimShowRegion.Height();

	CDC* pdcSimShowRegion = pSimShowRegion->GetDC();
	pSimShowRegion->UpdateWindow();

	CDC memDC;
	CBitmap memBitmap;


	// 創建雙緩衝
	memDC.CreateCompatibleDC(pdcSimShowRegion);
	memBitmap.CreateCompatibleBitmap(pdcSimShowRegion, rectSimShowRegion.Width(), rectSimShowRegion.Height());
	CBitmap* pOldMemBitMap = memDC.SelectObject(&memBitmap);

	DrawToBuffer(&memDC);

	pdcSimShowRegion->BitBlt(0, 0, iWidthSimShowRegion, iHeightSimShowRegion, &memDC, 0, 0, SRCCOPY);
	memDC.SelectObject(pOldMemBitMap);
	memBitmap.DeleteObject();
	memDC.DeleteDC();

}


void SimulateStartDlg::DrawGrid(CDC* pDC)
{
	// 取得操作視窗矩形資訊
	CWnd* pSimShowRegion = GetDlgItem(IDC_STATIC_RESULT_SHOW);
	CRect rectSimShowRegion;
	pSimShowRegion->GetClientRect(&rectSimShowRegion);


	// 設置網格線
	CPen penGrid(PS_SOLID, 1, RGB(0, 130, 66));  // 亮綠色網格線
	CPen* pOldPenGrid = pDC->SelectObject(&penGrid);


	// 繪製垂直線
	for (int iVertical = 0; iVertical <= rectSimShowRegion.right; iVertical += 10)
	{	// 每隔 5 像素繪製一條線

		pDC->MoveTo(iVertical, 0);
		pDC->LineTo(iVertical, rectSimShowRegion.bottom);

	}


	// 繪製水平線
	for (int iHorizontal = 0; iHorizontal <= rectSimShowRegion.bottom; iHorizontal += 10)
	{	// 每隔 5 像素繪製一條線

		pDC->MoveTo(0, iHorizontal);
		pDC->LineTo(rectSimShowRegion.right, iHorizontal);

	}

	pDC->SelectObject(pOldPenGrid);

}


void SimulateStartDlg::DrawToBuffer(CDC* pDC)
{

	// 取得操作視窗矩形資訊
	CWnd* pSimShowRegion = GetDlgItem(IDC_STATIC_RESULT_SHOW);
	CRect rectSimShowRegion;

	pSimShowRegion->GetClientRect(&rectSimShowRegion);
	int iWidthSimShowRegion = rectSimShowRegion.Width();
	int iHeightSimShowRegion = rectSimShowRegion.Height();


	CBrush brushSimShowRegion;
	CBrush* pOldBrushSimShowRegion = pDC->SelectObject(&brushSimShowRegion);

	brushSimShowRegion.CreateSolidBrush(m_colorSimShowRegion);
	pDC->Rectangle(rectSimShowRegion);
	pDC->FillRect(&rectSimShowRegion, &brushSimShowRegion);
	pDC->SelectObject(pOldBrushSimShowRegion);

	// 繪製網格
	DrawGrid(pDC);



}



// 模擬開始
void SimulateStartDlg::OnBnClickedButtonStart()
{
	// TODO: 在此加入控制項告知處理常式程式碼





}


// 模擬停止
void SimulateStartDlg::OnBnClickedButtonStop()
{
	// TODO: 在此加入控制項告知處理常式程式碼





}



