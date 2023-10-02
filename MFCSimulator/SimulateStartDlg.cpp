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


// 更新數值計算結果
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




		CWnd* pSimShowRegion = GetDlgItem(IDC_STATIC_RESULT_SHOW);
		CRect rectSimShowRegion;

		pSimShowRegion->GetClientRect(&rectSimShowRegion);

		// 將計算結果儲存於佇列中
		if (m_queueResultValue.size() > rectSimShowRegion.Width())
		{
			m_queueResultValue.pop();
			m_queueResultValue.push(m_dResultValue);
		}
		else
		{
			m_queueResultValue.push(m_dResultValue);
		}
		
		OnPaint();

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
	CPen penGrid(PS_SOLID, 1, RGB(0, 130, 70));  // 亮綠色網格線
	CPen* pOldPenGrid = pDC->SelectObject(&penGrid);


	// 繪製垂直線
	for (int iVertical = 10; iVertical <= rectSimShowRegion.right; iVertical += 10)
	{	// 每隔 10 像素繪製一條線

		pDC->MoveTo(iVertical, 0);
		pDC->LineTo(iVertical, rectSimShowRegion.bottom);

	}


	// 繪製水平線
	for (int iHorizontal = 10; iHorizontal <= rectSimShowRegion.bottom; iHorizontal += 10)
	{	// 每隔 10 像素繪製一條線

		pDC->MoveTo(0, iHorizontal);
		pDC->LineTo(rectSimShowRegion.right, iHorizontal);

	}

	pDC->SelectObject(pOldPenGrid);

}


// 繪製波曲線
void SimulateStartDlg::DrawWave(CDC* pDC)
{
	
	// 取得操作視窗矩形資訊
	CWnd* pSimShowRegion = GetDlgItem(IDC_STATIC_RESULT_SHOW);
	CRect rectSimShowRegion;

	pSimShowRegion->GetClientRect(&rectSimShowRegion);
	int iWidthSimShowRegion = rectSimShowRegion.Width();
	int iHeightSimShowRegion = rectSimShowRegion.Height();


	// 設置 y = 0 的線
	CPen penY0(PS_SOLID, 4, RGB(255, 255, 0));
	CPen* pOldPenY0 = pDC->SelectObject(&penY0);

	int iYOriginal = rectSimShowRegion.CenterPoint().y;

	pDC->MoveTo(0, iYOriginal);
	pDC->LineTo(rectSimShowRegion.right, iYOriginal);
	pDC->SelectObject(pOldPenY0);

	CFont fontY0Text;
	fontY0Text.CreatePointFont(200, _T("Arial"));
	pDC->SelectObject(&fontY0Text);
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(255, 255, 0));
	pDC->TextOut(5, rectSimShowRegion.CenterPoint().y, _T("y=0"));


	// 設置 y = 1 的線
	CPen penY1(PS_SOLID, 4, RGB(0, 200, 255));
	CPen* pOldPenY1 = pDC->SelectObject(&penY1);

	int iY1 = rectSimShowRegion.CenterPoint().y - 100;

	pDC->MoveTo(0, iY1);
	pDC->LineTo(rectSimShowRegion.right, iY1);
	pDC->SelectObject(pOldPenY1);

	CFont fontY1Text;
	fontY1Text.CreatePointFont(200, _T("Arial"));
	pDC->SelectObject(&fontY1Text);
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(0, 200, 255));
	pDC->TextOut(5, rectSimShowRegion.CenterPoint().y - 100, _T("y=1"));


	// 設置 y = -1 的線
	CPen penYNeg1(PS_SOLID, 4, RGB(0, 200, 255));
	CPen* pOldPenYNeg1 = pDC->SelectObject(&penYNeg1);

	int iYNeg1 = rectSimShowRegion.CenterPoint().y + 100;

	pDC->MoveTo(0, iYNeg1);
	pDC->LineTo(rectSimShowRegion.right, iYNeg1);
	pDC->SelectObject(pOldPenYNeg1);

	CFont fontYNeg1Text;
	fontYNeg1Text.CreatePointFont(200, _T("Arial"));
	pDC->SelectObject(&fontYNeg1Text);
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(0, 200, 255));
	pDC->TextOut(5, rectSimShowRegion.CenterPoint().y + 100, _T("y=-1"));


	// 設置 y = 2 的線
	CPen penY2(PS_SOLID, 4, RGB(0, 200, 255));
	CPen* pOldPenY2 = pDC->SelectObject(&penY2);

	int iY2 = rectSimShowRegion.CenterPoint().y - 200;

	pDC->MoveTo(0, iY2);
	pDC->LineTo(rectSimShowRegion.right, iY2);
	pDC->SelectObject(pOldPenY2);

	CFont fontY2Text;
	fontY2Text.CreatePointFont(200, _T("Arial"));
	pDC->SelectObject(&fontY2Text);
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(0, 200, 255));
	pDC->TextOut(5, rectSimShowRegion.CenterPoint().y - 200, _T("y=2"));


	// 設置 y = -2 的線
	CPen penYNeg2(PS_SOLID, 4, RGB(0, 200, 255));
	CPen* pOldPenYNeg2 = pDC->SelectObject(&penYNeg2);

	int iYNeg2 = rectSimShowRegion.CenterPoint().y + 200;

	pDC->MoveTo(0, iYNeg2);
	pDC->LineTo(rectSimShowRegion.right, iYNeg2);
	pDC->SelectObject(pOldPenYNeg2);

	CFont fontYNeg2Text;
	fontYNeg2Text.CreatePointFont(200, _T("Arial"));
	pDC->SelectObject(&fontYNeg2Text);
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(0, 200, 255));
	pDC->TextOut(5, rectSimShowRegion.CenterPoint().y + 200, _T("y=-2"));




	// 設置波線
	CPen penWave(PS_SOLID, 8, RGB(255, 0, 0));
	CPen* pOldPenWave = pDC->SelectObject(&penWave);

	double dXStep = 0.1;								// 每格像素為 0.1 單位
	int iNumberPoints = rectSimShowRegion.Width();      // 一個周期內點的數量與顯示區域的寬對應



	/*std::queue<double> queueCurResult = m_queueResultValue;*/
	m_queueCurValue = m_queueResultValue;

	for (int i = 0; i < m_queueResultValue.size(); i++)
	{

		/*double dX = i * dXStep;*/
		double dY = 1 * m_queueCurValue.front(); 

		// 將波形點映射到屏幕
		int iScreenX = i;  // 一個單位對應 1 個像素
		int iScreenY = rectSimShowRegion.CenterPoint().y - static_cast<int>(dY * 100);

		pDC->MoveTo(CPoint(iScreenX, iScreenY));
		m_queueCurValue.pop();
		
		
		int iScreenX2 = i;									 // 一個單位對應 1 個像素
		int iScreenY2 = rectSimShowRegion.CenterPoint().y - static_cast<int>(dY * 100);
		pDC->LineTo(CPoint(iScreenX2, iScreenY2));

	}



	
	//for (int i = 0; i < iNumberPoints; i++)
	//{

	//	double dX = i * dXStep;
	//	double dY = 1 * m_dResultValue;

	//	// 將波形點映射到屏幕
	//	int iScreenX = i;                   // 一個單位對應一個像素
	//	int iScreenY = rectSimShowRegion.CenterPoint().y - static_cast<int>(dY * 100);
	//	pDC->SetPixel(iScreenX, iScreenY, RGB(255, 0, 0));
	//}

	pDC->SelectObject(pOldPenWave);

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


	DrawWave(pDC);


}




// 模擬開始
void SimulateStartDlg::OnBnClickedButtonStart()
{

	m_dwStartTime = timeGetTime();
	SetTimer(m_nTimerID, 10, nullptr);

}


// 模擬停止
void SimulateStartDlg::OnBnClickedButtonStop()
{
	// TODO: 在此加入控制項告知處理常式程式碼


	int iTotalQueueSize = m_queueResultValue.size();


	KillTimer(m_nTimerID);
	if (m_queueResultValue.empty() != TRUE)
	{
		for (int i = 0; i < iTotalQueueSize; i++)
		{
			m_queueResultValue.pop();
		}

	}

	CRect rectSimShowRegion;
	GetDlgItem(IDC_STATIC_RESULT_SHOW)->GetWindowRect(&rectSimShowRegion);
	GetDlgItem(IDC_STATIC_RESULT_SHOW)->GetParent()->ScreenToClient(rectSimShowRegion);
	InvalidateRect(&rectSimShowRegion, TRUE);
	UpdateWindow();
}



