// SimulateStartDlg.cpp: 實作檔案
//

#include "pch.h"
#include "MFCSimulator.h"
#include "afxdialogex.h"
#include "CSimulateStartDlg.h"
#include "MFCSimulatorDlg.h"


// SimulateStartDlg 對話方塊

IMPLEMENT_DYNAMIC(CSimulateStartDlg, CDialogEx)

CSimulateStartDlg::CSimulateStartDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SIMULATE_START, pParent)
{

	m_fontTimeAndResult.CreatePointFont(200, _T("Arial Black"));
	m_fontTimeAndResultText.CreatePointFont(150, _T("Arial Black"));
	m_dwStartTime = 0;
	m_dCurTime = 0.0;
	m_dSimTime = 0.0;
	m_nTimerID = 1;
	m_dResultValue = 0.0;
	m_colorSimShowRegion = RGB(0, 0, 0);
	m_bIsNAN = FALSE;

}

CSimulateStartDlg::~CSimulateStartDlg()
{
}

void CSimulateStartDlg::DoDataExchange(CDataExchange* pDX)
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


BEGIN_MESSAGE_MAP(CSimulateStartDlg, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_START, &CSimulateStartDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CSimulateStartDlg::OnBnClickedButtonStop)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// SimulateStartDlg 訊息處理常式


BOOL CSimulateStartDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此加入額外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX 屬性頁應傳回 FALSE
}


HBRUSH CSimulateStartDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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



// 計算連線元件的函式結果
// 使用二元樹的後序走訪方法，計算結果數值
//
// Input : 
//			ptUnit :      生成元件的指標
//			dTimeValue :  經過的單位間隔累加時間
//
// Output : 
//			經過每節點的數值
//
// Remark : 
//			當遇到分母為 0 的運算式時，會將數值回傳為 0，當遇到分母小於 1e+10 的情況( example :  sin(0.0) )時，也會將數值回傳為 0 ， 並且更新 m_bIsNAN 為 TRUE ，讓系統發出警告並終止計算。
double CSimulateStartDlg::SetPostfixResult(CUnitBase* ptUnit, double dTimeValue)
{

	// 左子樹傳遞的值
	double dLeftResult = 0.0;

	// 右子樹傳遞的值
	double dRightResult = 0.0;


	if (ptUnit->m_vecPtsPreLeftUnit.size() != 0)
	{	// 檢查儲存左子樹指標的陣列大小，存在的話，更新左子樹傳遞的值

		dLeftResult = SetPostfixResult(ptUnit->m_vecPtsPreLeftUnit[0], dTimeValue);
	}

	if (ptUnit->m_vecPtsPreRightUnit.size() != 0)
	{	// 檢查儲存右子樹指標的陣列大小，存在的話，更新右子樹傳遞的值

		dRightResult = SetPostfixResult(ptUnit->m_vecPtsPreRightUnit[0], dTimeValue);
	}


	// 根據左右子樹指標中記錄的運算元、函式、數值來回傳計算結果
	if (ptUnit->m_strFuncOrOpera == "+")
	{
		return dLeftResult + dRightResult;
	}
	else if (ptUnit->m_strFuncOrOpera == "-")
	{
		return dLeftResult - dRightResult;
	}
	else if (ptUnit->m_strFuncOrOpera == "X")
	{
		return dLeftResult * dRightResult;
	}
	else if (ptUnit->m_strFuncOrOpera == "/")
	{
		if (dRightResult == 0)
		{
			m_bIsNAN = TRUE;
			return 0;
		}
		else if (dRightResult < 1e+10)
		{
			m_bIsNAN = TRUE;
			return 0;
		}
		else
		{
			return dLeftResult / dRightResult;
		}
	}
	else if (ptUnit->m_strFuncOrOpera == "AND")
	{
		return (dLeftResult && dRightResult);
	}
	else if (ptUnit->m_strFuncOrOpera == "OR")
	{
		return (dLeftResult || dRightResult);
	}
	else if (ptUnit->m_strFuncOrOpera == "NOT")
	{
		return !(dLeftResult);
	}
	else if (ptUnit->m_strFuncOrOpera == "sin(t)")
	{
		return sin(dTimeValue);
	}
	else if (ptUnit->m_strFuncOrOpera == "cos(t)")
	{
		return cos(dTimeValue);
	}
	else if (ptUnit->m_strFuncOrOpera == "true")
	{
		return 1.0;
	}
	else if (ptUnit->m_strFuncOrOpera == "false")
	{
		return 0.0;
	}
	else
	{
		return dLeftResult;
	}
}



// 更新數值計算結果
void CSimulateStartDlg::UpdateSimulate()
{
	// 計算連線數值結果
	m_dResultValue = SetPostfixResult(m_ptOutUnit, m_dSimTime);

	// 判斷在計算中是否有分母為 0 的計算情況
	if (m_bIsNAN == FALSE)
	{	// 分母不為 0 

		// 更新畫面中顯示的當下經過時間
		CString strTimeValue;
		strTimeValue.Format(_T("%.3f"), m_dCurTime);
		m_staticTimeShow.SetWindowText(strTimeValue);

		// 更新當下計算的數值結果
		CString strResult;
		strResult.Format(_T("%.4f"), m_dResultValue);
		m_staticResultShow.SetWindowText(strResult);

	}
	else
	{	// 分母為 0 

		// 跳出錯誤警訊
		AfxMessageBox(_T("Error of division by 0 !"));
		// 停止計時
		KillTimer(m_nTimerID);
		// 關閉模擬視窗
		EndDialog(0);

	}
}


// 單位間隔時間發生的事件 
void CSimulateStartDlg::OnTimer(UINT_PTR nIDEvent)
{
	
	DWORD dwRecordTime = timeGetTime();


	if (nIDEvent == m_nTimerID)
	{
		if (m_bIsNAN == FALSE)
		{
			DWORD dwElapsedTime = dwRecordTime - m_dwStartTime;
			double dSeconds = static_cast<double>(dwElapsedTime) / 1000.0;

			m_dCurTime = dSeconds;


			// 時間說明 : 
			// 當經過每單位系統時間間隔後，累加模擬函數的自變數時間，
			// 避免畫面因系統時間造成畫面有段點的錯誤。
			// 這裡假設 : 
			//		每經過 0.01 秒 系統時間，則累加自變數時間 2*PI / 2500 。
			if (m_dSimTime >= 2*M_PI)
			{
				m_dSimTime = 0.0;
				m_dSimTime += (2*M_PI) / 250;
			}
			else 
			{
				m_dSimTime += (2*M_PI) / 250;
			}
		
			// 更新計算結果
			UpdateSimulate();


			CWnd* pSimShowRegion = GetDlgItem(IDC_STATIC_RESULT_SHOW);
			CRect rectSimShowRegion;

			pSimShowRegion->GetClientRect(&rectSimShowRegion);

			// 將計算結果儲存於佇列中
			if (m_queueResultValue.size() > rectSimShowRegion.Width())
			{	// 檢查佇列長度是否超過模擬畫面寬度
				// 要是超過，就將舊資料刪除

				m_queueResultValue.pop_front();
				m_queueResultValue.push_back(m_dResultValue);
			}
			else
			{
				m_queueResultValue.push_back(m_dResultValue);
			}

			OnPaint();
		}
	}


	CDialogEx::OnTimer(m_nTimerID);

}


void CSimulateStartDlg::OnPaint()
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


// 繪製模擬畫面中的網格線
void CSimulateStartDlg::DrawGrid(CDC* pDC)
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


// 繪製模擬的波型線
void CSimulateStartDlg::DrawWave(CDC* pDC)
{
	
	// 取得操作視窗矩形資訊
	CWnd* pSimShowRegion = GetDlgItem(IDC_STATIC_RESULT_SHOW);
	CRect rectSimShowRegion;

	pSimShowRegion->GetClientRect(&rectSimShowRegion);
	int iWidthSimShowRegion = rectSimShowRegion.Width();
	int iHeightSimShowRegion = rectSimShowRegion.Height();

	////////////////////////////////////////////////////////////////////////////
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

	////////////////////////////////////////////////////////////////////////////
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

	////////////////////////////////////////////////////////////////////////////
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

	////////////////////////////////////////////////////////////////////////////
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

	////////////////////////////////////////////////////////////////////////////
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

	////////////////////////////////////////////////////////////////////////////
	// 設置波線
	CPen penWave(PS_SOLID, 8, RGB(255, 0, 0));
	CPen* pOldPenWave = pDC->SelectObject(&penWave);

	double dXStep = 0.1;								// 每格像素為 0.1 單位
	int iNumberPoints = rectSimShowRegion.Width();      // 一個周期內點的數量與顯示區域的寬對應


	for (int i = 1; i < m_queueResultValue.size(); i++)
	{	// 將儲存於佇列中的所有舊的波型資料繪出
		
		// 畫線的前一個點
		double dY = 1 * m_queueResultValue[i-1];

		// 將波形點映射到屏幕
		// 調整實際自變數與應變數值在螢幕中像素點的大小對應
		int iScreenX = i-1;  
		int iScreenY = rectSimShowRegion.CenterPoint().y - static_cast<int>(dY * 100 + 0.5);
		pDC->MoveTo(CPoint(iScreenX, iScreenY));

		// 畫線的後一個點
		double dY2 = 1 * m_queueResultValue[i];

		// 將波形點映射到屏幕
		// 調整實際自變數與應變數值在螢幕中像素點的大小對應
		int iScreenX2 = i;									 
		int iScreenY2 = rectSimShowRegion.CenterPoint().y - static_cast<int>(dY2 * 100 + 0.5);
		pDC->LineTo(CPoint(iScreenX2, iScreenY2));

	}

	pDC->SelectObject(pOldPenWave);

}


// 雙緩衝繪圖
void CSimulateStartDlg::DrawToBuffer(CDC* pDC)
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

	// 繪製背景網格
	DrawGrid(pDC);

	// 繪製模擬波型
	DrawWave(pDC);

}


// 開始模擬的按鈕
void CSimulateStartDlg::OnBnClickedButtonStart()
{
	// 記錄開始時間
	m_dwStartTime = timeGetTime();

	// 每 0.01 秒更新模擬資料
	SetTimer(m_nTimerID, 10, nullptr);

}


// 停止模擬的按鈕
void CSimulateStartDlg::OnBnClickedButtonStop()
{

	if (m_bIsNAN == TRUE)
	{	// 重新初始化分母是否為 0 的判斷 

		m_bIsNAN = FALSE;
	}

	// 重新初始化模擬函數的自變數時間
	m_dSimTime = 0.0;

	// 停止 Timer
	KillTimer(m_nTimerID);

	// 取得停止時的佇列長度
	int iTotalQueueSize = m_queueResultValue.size();

	// 清空佇列
	if (m_queueResultValue.empty() != TRUE)
	{
		for (int i = 0; i < iTotalQueueSize; i++)
		{
			m_queueResultValue.pop_front();
		}
	}

	CRect rectSimShowRegion;
	GetDlgItem(IDC_STATIC_RESULT_SHOW)->GetWindowRect(&rectSimShowRegion);
	GetDlgItem(IDC_STATIC_RESULT_SHOW)->GetParent()->ScreenToClient(rectSimShowRegion);
	InvalidateRect(&rectSimShowRegion, TRUE);
	UpdateWindow();
}


// 退出視窗
void CSimulateStartDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
}

