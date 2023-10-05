
// MFCSimulatorDlg.cpp: 實作檔案
//

#include "pch.h"
#include "framework.h"
#include "MFCSimulator.h"
#include "MFCSimulatorDlg.h"
#include "afxdialogex.h"
#include "UnitInDlg.h"
#include "UnitFunDlg.h"
#include "SimulateStartDlg.h"

#include "UnitIN.h"
#include "UnitOUT.h"
#include "UnitAND.h"
#include "UnitOR.h"
#include "UnitNOT.h"
#include "UnitFUN.h"
#include "UnitLine.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BOOL g_bShowRegionBgImgChange = FALSE;                   // 操作視窗是否更換背景圖片狀態

// 對 App About 使用 CAboutDlg 對話方塊

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 對話方塊資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

// 程式碼實作
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()


// CMFCSimulatorDlg 對話方塊


CMFCSimulatorDlg::CMFCSimulatorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCSIMULATOR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_colorShowRegionBg = RGB(255, 255, 255);       // 操作畫面初始為白色
	m_strShowRegionImgBgPath = _T("");              // 背景圖片路徑
	m_bIsDragging = FALSE;                          // 元件是否被拖曳
	m_bIsLineMode = FALSE;                          // 連線模式是否被開啟
	m_iOffsetX = 0;
	m_iOffsetY = 0;
	m_fontLineModeState.CreatePointFont(125, _T("Calibri"));
	m_fontLineModeText.CreatePointFont(125, _T("Calibri"));
	m_iListUnitAmount = 0;
	m_iListUnitLineAmount = 0;
}

CMFCSimulatorDlg::~CMFCSimulatorDlg()
{

	POSITION posiUnit = m_listUnitPointers.GetTailPosition();
	while (posiUnit != nullptr)
	{
		UnitBase* ptUnit = m_listUnitPointers.GetPrev(posiUnit);
		delete ptUnit;
	}
	
	m_listUnitPointers.RemoveAll();


	POSITION posiLineUnit = m_listUnitLines.GetTailPosition();
	while (posiLineUnit != nullptr)
	{
		UnitLine* ptLineUnit = m_listUnitLines.GetPrev(posiLineUnit);
		delete ptLineUnit;
	}

	m_listUnitLines.RemoveAll();

}

void CMFCSimulatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_SHOW_REGION, m_staticShowRegion);
	DDX_Control(pDX, IDC_BUTTON_IN, m_buttonIN);
	DDX_Control(pDX, IDC_BUTTON_OUT, m_buttonOUT);
	DDX_Control(pDX, IDC_BUTTON_AND, m_buttonAND);
	DDX_Control(pDX, IDC_BUTTON_OR, m_buttonOR);
	DDX_Control(pDX, IDC_BUTTON_NOT, m_buttonNOT);
	DDX_Control(pDX, IDC_BUTTON_FUN, m_buttonFUN);
	DDX_Control(pDX, IDC_STATIC_LINE_MODE_STATE, m_staticLineState);
	DDX_Control(pDX, IDC_STATIC_LINE_MODE_TEXT, m_staticLineModeText);
	DDX_Control(pDX, IDC_BUTTON_LINE, m_buttonLINE);
}

BEGIN_MESSAGE_MAP(CMFCSimulatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_BG_IMG, &CMFCSimulatorDlg::OnBnClickedButtonBgImg)
	ON_BN_CLICKED(IDC_BUTTON_BG_COLOR, &CMFCSimulatorDlg::OnBnClickedButtonBgColor)
	ON_BN_CLICKED(IDC_BUTTON_IN, &CMFCSimulatorDlg::OnBnClickedButtonIn)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON_OUT, &CMFCSimulatorDlg::OnBnClickedButtonOut)
	ON_BN_CLICKED(IDC_BUTTON_AND, &CMFCSimulatorDlg::OnBnClickedButtonAnd)
	ON_BN_CLICKED(IDC_BUTTON_OR, &CMFCSimulatorDlg::OnBnClickedButtonOr)
	ON_BN_CLICKED(IDC_BUTTON_NOT, &CMFCSimulatorDlg::OnBnClickedButtonNot)
	ON_BN_CLICKED(IDC_BUTTON_FUN, &CMFCSimulatorDlg::OnBnClickedButtonFun)
	ON_BN_CLICKED(IDC_BUTTON_LINE, &CMFCSimulatorDlg::OnBnClickedButtonLine)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CMFCSimulatorDlg::OnBnClickedButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_SIMULATE, &CMFCSimulatorDlg::OnBnClickedButtonSimulate)

	ON_WM_LBUTTONDBLCLK()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CMFCSimulatorDlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CMFCSimulatorDlg::OnBnClickedButtonOpen)
END_MESSAGE_MAP()


// CMFCSimulatorDlg 訊息處理常式

BOOL CMFCSimulatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 將 [關於...] 功能表加入系統功能表。

	// IDM_ABOUTBOX 必須在系統命令範圍之中。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 設定此對話方塊的圖示。當應用程式的主視窗不是對話方塊時，
	// 框架會自動從事此作業
	SetIcon(m_hIcon, TRUE);			// 設定大圖示
	SetIcon(m_hIcon, FALSE);		// 設定小圖示

	// TODO: 在此加入額外的初始設定

	// 獲取初始操作畫面的位圖路徑
	CString strCurrentPath = GetCurrentDir();
	m_strShowRegionImgBgPath = strCurrentPath + _T("\\res\\test0.bmp");


	return FALSE;  // 傳回 TRUE，除非您對控制項設定焦點
}

void CMFCSimulatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}



// 開啟視窗
BOOL CAboutDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此加入額外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX 屬性頁應傳回 FALSE
}



HBRUSH CMFCSimulatorDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此變更 DC 的任何屬性
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_LINE_MODE_STATE)
	{
		pDC->SetTextColor(RGB(255, 0, 0));
		pDC->SelectObject(&m_fontLineModeState);
	}

	if (pWnd->GetDlgCtrlID() == IDC_STATIC_LINE_MODE_TEXT)
	{
		pDC->SelectObject(&m_fontLineModeText);
	}

	// TODO:  如果預設值並非想要的，則傳回不同的筆刷
	return hbr;
}


////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
// double 四捨五入轉型 int
int RouundDoubleToInt(double dValue)
{
	return static_cast<int>(dValue + 0.5);
}


// 從元件矩形左上角位置來得到元件矩形
CRect CMFCSimulatorDlg::GetUnitRect(CPoint ptLeftTop)
{
	// 元件矩形
	CRect rectUnit;
	
	// 根據 IN 按鍵長寬來設計元件長寬
	m_buttonIN.GetWindowRect(&rectUnit);
	
	int iWidthUnit = rectUnit.Width();
	int iHeightUnit = rectUnit.Height();

	CPoint ptRightButtom(ptLeftTop.x + iWidthUnit, ptLeftTop.y + iHeightUnit);

	return CRect(ptLeftTop, ptRightButtom);
}


// 從元件左上角位置來得到元件連接點外接矩形
std::vector<CRect> CMFCSimulatorDlg::GetConnectRects(UnitBase* ptUnit)
{
	int iUnitW = ptUnit->m_iUnitWidth;
	int iUnitH = ptUnit->m_iUnitHeight;
	int iRadius = ptUnit->m_iConnectPtRadius;
	CPoint pointLocation = ptUnit->m_pointUnitLocation;

	std::vector<CRect> vecConnectPtRects;

	if (ptUnit->m_strUnitID == "IN")
	{	

		// 下方中點位置
		CPoint pointConnect;

		pointConnect.x = pointLocation.x + iUnitW * 0.5;
		pointConnect.y = pointLocation.y + iUnitH;

		CRect rectConnect(CPoint(pointConnect.x - iRadius, pointConnect.y - iRadius),     // Left, Top
						  CPoint(pointConnect.x + iRadius, pointConnect.y + iRadius));    // Right, Bottom

		vecConnectPtRects.push_back(rectConnect);

		return 	vecConnectPtRects;
	}
	else if (ptUnit->m_strUnitID == "OUT")
	{
		// 上方中點位置
		CPoint pointConnect;

		pointConnect.x = pointLocation.x + iUnitW * 0.5;
		pointConnect.y = pointLocation.y + 0;

		CRect rectConnect(CPoint(pointConnect.x - iRadius, pointConnect.y - iRadius),     // Left, Top
						  CPoint(pointConnect.x + iRadius, pointConnect.y + iRadius));    // Right, Bottom

		vecConnectPtRects.push_back(rectConnect);

		return 	vecConnectPtRects;
	}
	else if (ptUnit->m_strUnitID == "NOT")
	{
		// 上方中點位置
		CPoint pointConnect;

		pointConnect.x = pointLocation.x + iUnitW * 0.5;
		pointConnect.y = pointLocation.y + 0;

		CRect rectConnectUp(CPoint(pointConnect.x - iRadius, pointConnect.y - iRadius),     // Left, Top
						    CPoint(pointConnect.x + iRadius, pointConnect.y + iRadius));    // Right, Bottom

		vecConnectPtRects.push_back(rectConnectUp);

		// 下方中點位置

		pointConnect.x = pointLocation.x + iUnitW * 0.5;
		pointConnect.y = pointLocation.y + iUnitH;

		CRect rectConnectDown(CPoint(pointConnect.x - iRadius, pointConnect.y - iRadius),     // Left, Top
							  CPoint(pointConnect.x + iRadius, pointConnect.y + iRadius));    // Right, Bottom

		vecConnectPtRects.push_back(rectConnectDown);

		return vecConnectPtRects;
	}
	else
	{
		// 左上角
		CPoint pointConnectLeftUp;

		pointConnectLeftUp.x = pointLocation.x + 0;
		pointConnectLeftUp.y = pointLocation.y + 0;

		CRect rectConnectLeftUp(CPoint(pointConnectLeftUp.x - iRadius, pointConnectLeftUp.y - iRadius),     // Left, Top
						        CPoint(pointConnectLeftUp.x + iRadius, pointConnectLeftUp.y + iRadius));    // Right, Bottom

		vecConnectPtRects.push_back(rectConnectLeftUp);

		// 右上角
		CPoint pointConnectRightUp;

		pointConnectRightUp.x = pointLocation.x + iUnitW;
		pointConnectRightUp.y = pointLocation.y + 0;

		CRect rectConnectRightUp(CPoint(pointConnectRightUp.x - iRadius, pointConnectRightUp.y - iRadius),     // Left, Top
							     CPoint(pointConnectRightUp.x + iRadius, pointConnectRightUp.y + iRadius));    // Right, Bottom

		vecConnectPtRects.push_back(rectConnectRightUp);

		// 下方中點位置
		CPoint pointConnectDown;

		pointConnectDown.x = pointLocation.x + iUnitW * 0.5;
		pointConnectDown.y = pointLocation.y + iUnitH;

		CRect rectConnectDown(CPoint(pointConnectDown.x - iRadius, pointConnectDown.y - iRadius),     // Left, Top
						      CPoint(pointConnectDown.x + iRadius, pointConnectDown.y + iRadius));    // Right, Bottom

		vecConnectPtRects.push_back(rectConnectDown);

		return vecConnectPtRects;
	}
		


}


// 計算兩點距離
double CMFCSimulatorDlg::TwoPtsDistance(CPoint pointStart, CPoint pointEnd)
{
	double dLen = sqrt(pow((pointEnd.x - pointStart.x), 2) + pow((pointEnd.y - pointStart.y), 2));

	return dLen;
}


// 計算滑鼠座標點到線段距離
double CMFCSimulatorDlg::PointToLineDistance(CPoint pointMouse, CPoint pointStart, CPoint pointEnd)
{
	double dLenStartToEnd = TwoPtsDistance(pointStart, pointEnd);

	if (dLenStartToEnd == 0.0)
	{	// 線段長度為 0 的情況	

		return TwoPtsDistance(pointMouse, pointStart);
	}

	// 計算向量 Start -> End 和 Start -> Mouse 內積
	double dDotProduct = ((pointMouse.x - pointStart.x) * (pointEnd.x - pointStart.x) + (pointMouse.y - pointStart.y) * (pointEnd.y - pointStart.y)) / pow(dLenStartToEnd, 2);

	if (dDotProduct < 0.0)
	{	// 滑鼠座標點在點 Start 之前

		return TwoPtsDistance(pointMouse, pointStart);
	}

	if (dDotProduct > 1.0)
	{	// 滑鼠座標點在點 End 之後

		return TwoPtsDistance(pointMouse, pointEnd);
	}
	
	// 計算滑鼠座標點在線段 Start --- End 上的投影點
	CPoint pointProject;
	pointProject.x = pointStart.x + dDotProduct * (pointEnd.x - pointStart.x);
	pointProject.y = pointStart.y + dDotProduct * (pointEnd.y - pointStart.y);

	// 給出滑鼠座標點與其投影點距離
	return TwoPtsDistance(pointMouse, pointProject);
}


// 取得 MFCSimulatorDlg.cpp 的絕對路徑
CString CMFCSimulatorDlg::GetCurrentDir()
{
	
	wchar_t path[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, path);

	return path;
}







////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
// 如果將最小化按鈕加入您的對話方塊，您需要下列的程式碼，
// 以便繪製圖示。對於使用文件/檢視模式的 MFC 應用程式，
// 框架會自動完成此作業。

void CMFCSimulatorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 繪製的裝置內容

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 將圖示置中於用戶端矩形
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 描繪圖示
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{

		CDialogEx::OnPaint();


		// 取得操作視窗矩形資訊
		CWnd* pShowRegion = GetDlgItem(IDC_STATIC_SHOW_REGION);
		CRect rectShowRegion;

		pShowRegion->GetClientRect(&rectShowRegion);
		int iWidthShowRegion = rectShowRegion.Width();
		int iHeightShowRegion = rectShowRegion.Height();

		

		m_hBitmapImgBg = (HBITMAP)::LoadImage(NULL, m_strShowRegionImgBgPath, IMAGE_BITMAP,
			rectShowRegion.Width(), rectShowRegion.Height(), LR_LOADFROMFILE);


		// 取得操作視窗 dc
		//CPaintDC dcShowRegion(pShowRegion);
		CDC* pdcShowRegion = pShowRegion->GetDC();
		pShowRegion->UpdateWindow();

		CDC memDC;
		CBitmap memBitmap;

		if (m_hBitmapImgBg != nullptr)
		{
			memBitmap.Attach(m_hBitmapImgBg);
			BITMAP bmp;
			memBitmap.GetBitmap(&bmp);
		}


		// 創建雙緩衝
		memDC.CreateCompatibleDC(pdcShowRegion);
		CBitmap* pOldMemBitMap = memDC.SelectObject(&memBitmap);


		DrawToBuffer(&memDC);


		pdcShowRegion->BitBlt(0, 0, iWidthShowRegion, iHeightShowRegion, &memDC, 0, 0, SRCCOPY);
		memDC.SelectObject(pOldMemBitMap);
		memBitmap.DeleteObject();
		memDC.DeleteDC();

	}

}


void CMFCSimulatorDlg::DrawToBuffer(CDC* pDC)
{


	CWnd* pShowRegion = GetDlgItem(IDC_STATIC_SHOW_REGION);
	CRect rectShowRegion;

	pShowRegion->GetClientRect(&rectShowRegion);
	int iWidthShowRegion = rectShowRegion.Width();
	int iHeightShowRegion = rectShowRegion.Height();

	CBrush brushShowRegion;
	CBrush* pOldbrushShowRegion = pDC->SelectObject(&brushShowRegion);



	if (g_bShowRegionBgImgChange == FALSE)
	{
		// 操作視窗初始上色
		brushShowRegion.CreateSolidBrush(m_colorShowRegionBg);
		pDC->Rectangle(rectShowRegion);
		pDC->FillRect(&rectShowRegion, &brushShowRegion);
		pDC->SelectObject(pOldbrushShowRegion);
	}




	POSITION posiUnit = m_listUnitPointers.GetTailPosition();

	POSITION posiLineUnit = m_listUnitLines.GetTailPosition();



	CPen penConnectLine(PS_SOLID, 14, RGB(0, 0, 255));
	CPen penMovingLine(PS_DASH, 1, RGB(255, 0, 0));
	CPen penFocusLine(PS_SOLID, 14, RGB(255, 0, 0));

	while (posiLineUnit != nullptr)
	{
		UnitLine* ptLineUnit = m_listUnitLines.GetPrev(posiLineUnit);

		if (ptLineUnit->m_bIsConnect == TRUE)
		{	// 已連接並且未選取的現以藍色實線畫出表示

			CPen* ptOldPenConnectLine = pDC->SelectObject(&penConnectLine);
			pDC->SelectObject(&penConnectLine);
			pDC->MoveTo(ptLineUnit->m_vecPtsPreLeftUnit[0]->m_vecConnectPt[ptLineUnit->m_iConnectPrePtIndex]);
			pDC->LineTo(ptLineUnit->m_vecPtsNextUnit[0]->m_vecConnectPt[ptLineUnit->m_iConnectNextPtIndex]);
			pDC->SelectObject(ptOldPenConnectLine);
		}
		
		if (ptLineUnit->m_bMoveState == TRUE)
		{	// 拖曳中的線以紅色虛線畫出表示

			CPen* ptOldPenMovingLine = pDC->SelectObject(&penMovingLine);
			pDC->SelectObject(&penMovingLine);
			pDC->MoveTo(ptLineUnit->m_vecPtsPreLeftUnit[0]->m_vecConnectPt[ptLineUnit->m_iConnectPrePtIndex]);
			pDC->LineTo(ptLineUnit->m_pointMovingLinePos);
			pDC->SelectObject(ptOldPenMovingLine);
		}

		if (ptLineUnit->m_bFocusState == TRUE)
		{	// 被點選的線以紅色實線畫出表示

			CPen* ptOldPenFocusLine = pDC->SelectObject(&penFocusLine);
			pDC->SelectObject(&penFocusLine);
			pDC->MoveTo(ptLineUnit->m_vecPtsPreLeftUnit[0]->m_vecConnectPt[ptLineUnit->m_iConnectPrePtIndex]);
			pDC->LineTo(ptLineUnit->m_vecPtsNextUnit[0]->m_vecConnectPt[ptLineUnit->m_iConnectNextPtIndex]);
			pDC->SelectObject(ptOldPenFocusLine);
		}
	}






	// 元件矩形顏色
	CBrush brushInRect;
	brushInRect.CreateSolidBrush(RGB(192, 192, 192));  // 灰色

	// 連接點顏色
	CBrush brushConnectPt;
	brushConnectPt.CreateSolidBrush(RGB(255, 140, 0));

	// 點取元件時的邊框顏色
	CPen penFocusRect(PS_SOLID, 8, RGB(255, 0, 0));

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SelectObject(&brushInRect);


	while (posiUnit != nullptr)
	{
		
		UnitBase* ptUnit = m_listUnitPointers.GetPrev(posiUnit);

		std::vector<CRect> vecConnectPtRect = GetConnectRects(ptUnit);

		pDC->SelectObject(&brushConnectPt);

		for (int i = 0; i < vecConnectPtRect.size(); i++)
		{
			pDC->Ellipse(vecConnectPtRect[i]);
		}


		CPoint pointUnitLeftTop = ptUnit->m_pointUnitLocation;

		CRect rectUnit = GetUnitRect(pointUnitLeftTop);

		if (ptUnit->m_bFocusState == TRUE)
		{
			CPen* ptOldPenFocusRect = pDC->SelectObject(&penFocusRect);
			pDC->SelectObject(&penFocusRect);
			pDC->Rectangle(rectUnit);
			pDC->FillRect(&rectUnit, &brushInRect);
			pDC->SetBkMode(TRANSPARENT);
			pDC->TextOut((rectUnit.left + rectUnit.right) * 0.5 - 10, (rectUnit.top + rectUnit.bottom) * 0.5 - 8,
				ptUnit->m_strUnitID);
			pDC->SelectObject(ptOldPenFocusRect);
		}
		else
		{
			pDC->Rectangle(rectUnit);
			pDC->FillRect(&rectUnit, &brushInRect);
			pDC->SetBkMode(TRANSPARENT);
			pDC->TextOut((rectUnit.left + rectUnit.right) * 0.5 - 10, (rectUnit.top + rectUnit.bottom) * 0.5 - 8,
				ptUnit->m_strUnitID);


		}
		
	}
}




// 當使用者拖曳最小化視窗時，
// 系統呼叫這個功能取得游標顯示。
HCURSOR CMFCSimulatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// 設定操作視窗背景圖片
void CMFCSimulatorDlg::OnBnClickedButtonBgImg()
{
	// 打開選擇檔案的視窗
	CFileDialog filesDlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST,
		_T("Bitmap Files (*.bmp)|*.bmp||"), this);

	if (IDOK == filesDlg.DoModal())
	{
		m_strShowRegionImgBgPath = filesDlg.GetPathName();

		//// 載入圖片
		CRect rectShowRegion;
		m_staticShowRegion.GetWindowRect(&rectShowRegion);

		m_hBitmapImgBg = (HBITMAP)::LoadImage(NULL, m_strShowRegionImgBgPath, IMAGE_BITMAP,
			rectShowRegion.Width(), rectShowRegion.Height(), LR_LOADFROMFILE);
	
		// 更新操作視窗是否更換背景圖片狀態
		g_bShowRegionBgImgChange = TRUE;


		// 更新操作視窗	
		//Invalidate();
		//UpdateWindow();	
		OnPaint();
	}
}

// 設定操作視窗背景顏色
void CMFCSimulatorDlg::OnBnClickedButtonBgColor()
{
	// 初始挑選顏色為白色
	COLORREF colorSelect = RGB(255, 255, 255);

	// 建立顏色挑選視窗
	CColorDialog colorDlg(colorSelect);


	if (IDOK == colorDlg.DoModal())
	{	// 顯示顏色挑選視窗，判斷是否按下確定

		// 得到顏色挑選視窗中挑選的顏色值
		colorSelect = colorDlg.GetColor();

		// 設置背景顏色
		m_colorShowRegionBg = colorSelect;

		//更新操作視窗是否更換背景圖片狀態
		g_bShowRegionBgImgChange = FALSE;

		// 更新操作視窗	
		Invalidate();
		UpdateWindow();
	}
}









 //函數輸入鈕 "IN"
void CMFCSimulatorDlg::OnBnClickedButtonIn()
{
	// 操作視窗矩形
	CRect rectShowRegion;

	// 元件矩形
	CRect rectUnit;

	// 得到操作視窗矩形
	m_staticShowRegion.GetWindowRect(&rectShowRegion);


	// 操作視窗長、寬
	int iHeightShowRegion = rectShowRegion.Height();
	int iWidthShowRegion = rectShowRegion.Width();

	// 得到元件矩形
	m_buttonIN.GetWindowRect(&rectUnit);

	// 元件矩形長寬
	int iWidthUnit = rectUnit.Width();
	int iHeightUnit = rectUnit.Height();

	// 新建一個新 IN 元件
	UnitIN* ptNewUnitIN = new UnitIN(rectShowRegion, rectUnit);

	// 放進紀錄 Pointer 的串列結構
	m_listUnitPointers.AddTail(ptNewUnitIN);

	// 更新操作視窗	
	Invalidate();
	UpdateWindow();

}


//函數輸入鈕 "OUT"
void CMFCSimulatorDlg::OnBnClickedButtonOut()
{
	// 操作視窗矩形
	CRect rectShowRegion;

	// 元件矩形
	CRect rectUnit;

	// 得到操作視窗矩形
	m_staticShowRegion.GetWindowRect(&rectShowRegion);

	// 操作視窗長、寬
	int iHeightShowRegion = rectShowRegion.Height();
	int iWidthShowRegion = rectShowRegion.Width();

	// 得到元件矩形
	m_buttonOUT.GetWindowRect(&rectUnit);

	// 元件矩形長寬
	int iWidthUnit = rectUnit.Width();
	int iHeightUnit = rectUnit.Height();

	// 新建一個新元件
	UnitOUT* ptNewUnitOUT = new UnitOUT(rectShowRegion, rectUnit);

	// 放進紀錄 Pointer 的串列結構
	m_listUnitPointers.AddTail(ptNewUnitOUT);

	// 更新操作視窗	
	Invalidate();
	UpdateWindow();
}


//函數輸入鈕 "AND"
void CMFCSimulatorDlg::OnBnClickedButtonAnd()
{
	// 操作視窗矩形
	CRect rectShowRegion;

	// 元件矩形
	CRect rectUnit;

	// 得到操作視窗矩形
	m_staticShowRegion.GetWindowRect(&rectShowRegion);

	// 操作視窗長、寬
	int iHeightShowRegion = rectShowRegion.Height();
	int iWidthShowRegion = rectShowRegion.Width();

	// 得到元件矩形
	m_buttonAND.GetWindowRect(&rectUnit);

	// 元件矩形長寬
	int iWidthUnit = rectUnit.Width();
	int iHeightUnit = rectUnit.Height();

	// 新建一個新元件
	UnitAND* ptNewUnitAND = new UnitAND(rectShowRegion, rectUnit);

	// 放進紀錄 Pointer 的串列結構
	m_listUnitPointers.AddTail(ptNewUnitAND);

	// 更新操作視窗	
	Invalidate();
	UpdateWindow();
}


// 函數輸入紐 "OR"
void CMFCSimulatorDlg::OnBnClickedButtonOr()
{
	// 操作視窗矩形
	CRect rectShowRegion;

	// 元件矩形
	CRect rectUnit;

	// 得到操作視窗矩形
	m_staticShowRegion.GetWindowRect(&rectShowRegion);

	// 操作視窗長、寬
	int iHeightShowRegion = rectShowRegion.Height();
	int iWidthShowRegion = rectShowRegion.Width();

	// 得到元件矩形
	m_buttonOR.GetWindowRect(&rectUnit);

	// 元件矩形長寬
	int iWidthUnit = rectUnit.Width();
	int iHeightUnit = rectUnit.Height();

	// 新建一個新元件
	UnitOR* ptNewUnitOR = new UnitOR(rectShowRegion, rectUnit);

	// 放進紀錄 Pointer 的串列結構
	m_listUnitPointers.AddTail(ptNewUnitOR);

	// 更新操作視窗	
	Invalidate();
	UpdateWindow();
}


// 函數輸入紐 "NOT"
void CMFCSimulatorDlg::OnBnClickedButtonNot()
{
	// 操作視窗矩形
	CRect rectShowRegion;

	// 元件矩形
	CRect rectUnit;

	// 得到操作視窗矩形
	m_staticShowRegion.GetWindowRect(&rectShowRegion);

	// 操作視窗長、寬
	int iHeightShowRegion = rectShowRegion.Height();
	int iWidthShowRegion = rectShowRegion.Width();

	// 得到元件矩形
	m_buttonNOT.GetWindowRect(&rectUnit);

	// 元件矩形長寬
	int iWidthUnit = rectUnit.Width();
	int iHeightUnit = rectUnit.Height();

	// 新建一個新元件
	UnitNOT* ptNewUnitNOT = new UnitNOT(rectShowRegion, rectUnit);

	// 放進紀錄 Pointer 的串列結構
	m_listUnitPointers.AddTail(ptNewUnitNOT);

	// 更新操作視窗	
	Invalidate();
	UpdateWindow();
}


// 函數輸入紐 "FUN"
void CMFCSimulatorDlg::OnBnClickedButtonFun()
{
	// 操作視窗矩形
	CRect rectShowRegion;

	// 元件矩形
	CRect rectUnit;

	// 得到操作視窗矩形
	m_staticShowRegion.GetWindowRect(&rectShowRegion);

	// 操作視窗長、寬
	int iHeightShowRegion = rectShowRegion.Height();
	int iWidthShowRegion = rectShowRegion.Width();

	// 得到元件矩形
	m_buttonFUN.GetWindowRect(&rectUnit);

	// 元件矩形長寬
	int iWidthUnit = rectUnit.Width();
	int iHeightUnit = rectUnit.Height();

	// 新建一個新元件
	UnitFUN* ptNewUnitFUN = new UnitFUN(rectShowRegion, rectUnit);

	// 放進紀錄 Pointer 的串列結構
	m_listUnitPointers.AddTail(ptNewUnitFUN);

	// 更新操作視窗	
	Invalidate();
	UpdateWindow(); 
}


// 開啟連線模式
void CMFCSimulatorDlg::OnBnClickedButtonLine()
{

	if (m_bIsLineMode == FALSE)
	{
		m_bIsLineMode = TRUE;

		m_staticLineState.SetWindowText(_T("Line"));


		CButton* ptButtonIN = (CButton*)GetDlgItem(IDC_BUTTON_IN);
		ptButtonIN->EnableWindow(FALSE);
		CButton* ptButtonOUT = (CButton*)GetDlgItem(IDC_BUTTON_OUT);
		ptButtonOUT->EnableWindow(FALSE);
		CButton* ptButtonAND = (CButton*)GetDlgItem(IDC_BUTTON_AND);
		ptButtonAND->EnableWindow(FALSE);
		CButton* ptButtonOR = (CButton*)GetDlgItem(IDC_BUTTON_OR);
		ptButtonOR->EnableWindow(FALSE);
		CButton* ptButtonNOT = (CButton*)GetDlgItem(IDC_BUTTON_NOT);
		ptButtonNOT->EnableWindow(FALSE);
		CButton* ptButtonFUN = (CButton*)GetDlgItem(IDC_BUTTON_FUN);
		ptButtonFUN->EnableWindow(FALSE);
		CButton* ptButtonSIM = (CButton*)GetDlgItem(IDC_BUTTON_SIMULATE);
		ptButtonSIM->EnableWindow(FALSE);
		CButton* ptButtonDEL = (CButton*)GetDlgItem(IDC_BUTTON_DELETE);
		ptButtonDEL->EnableWindow(FALSE);
		CButton* ptButtonSAVE = (CButton*)GetDlgItem(IDC_BUTTON_SAVE);
		ptButtonSAVE->EnableWindow(FALSE);
		CButton* ptButtonOPEN = (CButton*)GetDlgItem(IDC_BUTTON_OPEN);
		ptButtonOPEN->EnableWindow(FALSE);


	}
	else
	{
		m_bIsLineMode = FALSE;

		m_staticLineState.SetWindowText(_T("Normal"));

		CButton* ptButtonIN = (CButton*)GetDlgItem(IDC_BUTTON_IN);
		ptButtonIN->EnableWindow(TRUE);
		CButton* ptButtonOUT = (CButton*)GetDlgItem(IDC_BUTTON_OUT);
		ptButtonOUT->EnableWindow(TRUE);
		CButton* ptButtonAND = (CButton*)GetDlgItem(IDC_BUTTON_AND);
		ptButtonAND->EnableWindow(TRUE);
		CButton* ptButtonOR = (CButton*)GetDlgItem(IDC_BUTTON_OR);
		ptButtonOR->EnableWindow(TRUE);
		CButton* ptButtonNOT = (CButton*)GetDlgItem(IDC_BUTTON_NOT);
		ptButtonNOT->EnableWindow(TRUE);
		CButton* ptButtonFUN = (CButton*)GetDlgItem(IDC_BUTTON_FUN);
		ptButtonFUN->EnableWindow(TRUE);
		CButton* ptButtonSIM = (CButton*)GetDlgItem(IDC_BUTTON_SIMULATE);
		ptButtonSIM->EnableWindow(TRUE);
		CButton* ptButtonDEL = (CButton*)GetDlgItem(IDC_BUTTON_DELETE);
		ptButtonDEL->EnableWindow(TRUE);
		CButton* ptButtonSAVE = (CButton*)GetDlgItem(IDC_BUTTON_SAVE);
		ptButtonSAVE->EnableWindow(TRUE);
		CButton* ptButtonOPEN = (CButton*)GetDlgItem(IDC_BUTTON_OPEN);
		ptButtonOPEN->EnableWindow(TRUE);
	}

}


// 刪除元件或線段
void CMFCSimulatorDlg::OnBnClickedButtonDelete()
{

	POSITION posiUnit = m_listUnitPointers.GetTailPosition();
	while ((posiUnit != nullptr) && (m_bIsLineMode != TRUE))
	{	// 遍歷所有元件

		POSITION posiCur = posiUnit;
		UnitBase* ptCurUnit = m_listUnitPointers.GetPrev(posiUnit);

		if (ptCurUnit->m_bFocusState == TRUE)
		{	// 確認元件是否為被選取狀態




			if (ptCurUnit->m_vecPtsPreLeftUnit.empty() != TRUE)
			{	// 確認指向前一個元件的指標陣列是否為空
				// 若不為空，則開始清除前一個元件指向被選取元件的指標

				for (int i = 0; i < ptCurUnit->m_vecPtsPreLeftUnit.size(); i++)
				{	// 遍歷指標陣列，找出指向被選取元件的指標

					// 前一個元件指向下一個元件的指標陣列
					std::vector<UnitBase*>vecPreToCur = ptCurUnit->m_vecPtsPreLeftUnit[i]->m_vecPtsNextUnit;

					// 記錄被選取的元件指標位於指標陣列中的位置
					int iCurPtIndex;

					for (int j = 0; j < vecPreToCur.size(); j++)
					{	// 遍歷"前一個元件指向下一個元件的指標陣列"

						if (vecPreToCur[j] == ptCurUnit)
						{	// 確認是否為被選取的指標

							// 記錄位置
							iCurPtIndex = j;

							// 刪除前一個元件指向被選取元件的指標
							ptCurUnit->m_vecPtsPreLeftUnit[i]->m_vecPtsNextUnit.erase(ptCurUnit->m_vecPtsPreLeftUnit[i]->m_vecPtsNextUnit.begin() + iCurPtIndex);

							break;
						}
					}
				}
			}




			if (ptCurUnit->m_vecPtsPreRightUnit.empty() != TRUE)
			{	// 確認指向前一個元件的指標陣列是否為空
				// 若不為空，則開始清除前一個元件指向被選取元件的指標

				for (int i = 0; i < ptCurUnit->m_vecPtsPreRightUnit.size(); i++)
				{	// 遍歷指標陣列，找出指向被選取元件的指標

					// 前一個元件指向下一個元件的指標陣列
					std::vector<UnitBase*>vecPreToCur = ptCurUnit->m_vecPtsPreRightUnit[i]->m_vecPtsNextUnit;

					// 記錄被選取的元件指標位於指標陣列中的位置
					int iCurPtIndex;

					for (int j = 0; j < vecPreToCur.size(); j++)
					{	// 遍歷"前一個元件指向下一個元件的指標陣列"

						if (vecPreToCur[j] == ptCurUnit)
						{	// 確認是否為被選取的指標

							// 記錄位置
							iCurPtIndex = j;

							// 刪除前一個元件指向被選取元件的指標
							ptCurUnit->m_vecPtsPreRightUnit[i]->m_vecPtsNextUnit.erase(ptCurUnit->m_vecPtsPreRightUnit[i]->m_vecPtsNextUnit.begin() + iCurPtIndex);

							break;
						}
					}
				}
			}


			if (ptCurUnit->m_vecPtsNextUnit.empty() != TRUE)
			{	// 確認指向後一個元件的指標陣列是否為空
				// 若不為空，則開始清除後一個元件指向被選取元件的指標

				for (int i = 0; i < ptCurUnit->m_vecPtsNextUnit.size(); i++)
				{	// 遍歷指標陣列，找出指向被選取元件的指標

					// 後一個元件指向前一個元件的指標陣列
					std::vector<UnitBase*>vecNextLeftToCur = ptCurUnit->m_vecPtsNextUnit[i]->m_vecPtsPreLeftUnit;
					std::vector<UnitBase*>vecNextRightToCur = ptCurUnit->m_vecPtsNextUnit[i]->m_vecPtsPreRightUnit;

					// 記錄被選取的元件指標位於指標陣列中的位置
					int iCurPtIndex;


					if (vecNextLeftToCur.empty() != TRUE)
					{
						for (int j = 0; j < vecNextLeftToCur.size(); j++)
						{	// 遍歷"後一個元件指向下一個元件的指標陣列"

							if (vecNextLeftToCur[j] == ptCurUnit)
							{	// 確認是否為被選取的指標

								// 記錄位置
								iCurPtIndex = j;

								// 刪除後一個元件指向被選取元件的指標
								ptCurUnit->m_vecPtsNextUnit[i]->m_vecPtsPreLeftUnit.erase(ptCurUnit->m_vecPtsNextUnit[i]->m_vecPtsPreLeftUnit.begin() + iCurPtIndex);

								break;
							}
						}
					}


					if (vecNextRightToCur.empty() != TRUE)
					{
						for (int j = 0; j < vecNextRightToCur.size(); j++)
						{	// 遍歷"後一個元件指向下一個元件的指標陣列"

							if (vecNextRightToCur[j] == ptCurUnit)
							{	// 確認是否為被選取的指標

								// 記錄位置
								iCurPtIndex = j;

								// 刪除後一個元件指向被選取元件的指標
								ptCurUnit->m_vecPtsNextUnit[i]->m_vecPtsPreRightUnit.erase(ptCurUnit->m_vecPtsNextUnit[i]->m_vecPtsPreRightUnit.begin() + iCurPtIndex);

								break;
							}
						}
					}
				}
			}

			// TODO : 把線段刪乾淨
			// 清除連接的線
			POSITION posiLineUnit = m_listUnitLines.GetTailPosition();
			while (posiLineUnit != nullptr)
			{
				POSITION posiLineCur = posiLineUnit;
				UnitLine* ptUnitLine = m_listUnitLines.GetPrev(posiLineUnit);

				// 指向前一個線段連接元件的指標陣列
				std::vector<UnitBase*> vecPreToLine = ptUnitLine->m_vecPtsPreLeftUnit;

				// 指向後一個線段連接元件的指標陣列
				std::vector<UnitBase*> vecNextToLine = ptUnitLine->m_vecPtsNextUnit;


				for (int i = 0; i < vecPreToLine.size(); i++)
				{	// 遍歷指標陣列

					if (vecPreToLine[i] == ptCurUnit)
					{	// 確認是否為被選取的元件，並刪除此元件的指標

						m_listUnitLines.RemoveAt(posiLineCur);
					}
				}

				for (int i = 0; i < vecNextToLine.size(); i++)
				{	// 遍歷指標陣列

					if (vecNextToLine[i] == ptCurUnit)
					{	// 確認是否為被選取的元件，並刪除此元件的指標

						m_listUnitLines.RemoveAt(posiLineCur);
					}
				}
			}

			// 清除在記錄已創建元件的 CList 中被選取的元件
			m_listUnitPointers.RemoveAt(posiCur);

			delete ptCurUnit;
		}
	}



	POSITION posiLineUnit = m_listUnitLines.GetTailPosition();
	while ((posiLineUnit != nullptr) && (m_bIsLineMode != TRUE))
	{

		POSITION posiLineCur = posiLineUnit;
		UnitBase* ptCurLineUnit = m_listUnitLines.GetPrev(posiLineUnit);

		if (ptCurLineUnit->m_bFocusState == TRUE)
		{	// 確認是否為被選取的線段

			// 線段起點連接的元件指標 
			UnitBase* ptPreUnit = ptCurLineUnit->m_vecPtsPreLeftUnit[0];

			// 線段終點連接的元件指標
			UnitBase* ptNextUnit = ptCurLineUnit->m_vecPtsNextUnit[0];

			// 取得線段起點連接的元件指向下一個元件的指標陣列 
			std::vector<UnitBase*> vecPreUnitToLine = ptPreUnit->m_vecPtsNextUnit;

			for (int i = 0; i < vecPreUnitToLine.size(); i++)
			{
				if (vecPreUnitToLine[i] == ptNextUnit)
				{	// 確認是否為連接的下一個元件

					// 刪除連接的元件指標
					ptPreUnit->m_vecPtsNextUnit.erase(ptPreUnit->m_vecPtsNextUnit.begin() + i);
				}
			}

			// 取得線段終點連接的元件指向前一個元件的指標陣列 
			std::vector<UnitBase*> vecNextLeftUnitToLine = ptNextUnit->m_vecPtsPreLeftUnit;
			std::vector<UnitBase*> vecNextRightUnitToLine = ptNextUnit->m_vecPtsPreRightUnit;


			for (int i = 0; i < vecNextLeftUnitToLine.size(); i++)
			{
				if (vecNextLeftUnitToLine[i] == ptPreUnit)
				{	// 確認是否為連接的前一個元件

					// 刪除連接的元件指標
					ptNextUnit->m_vecPtsPreLeftUnit.erase(ptNextUnit->m_vecPtsPreLeftUnit.begin() + i);
				}
			}


			for (int i = 0; i < vecNextRightUnitToLine.size(); i++)
			{
				if (vecNextRightUnitToLine[i] == ptPreUnit)
				{	// 確認是否為連接的前一個元件

					// 刪除連接的元件指標
					ptNextUnit->m_vecPtsPreRightUnit.erase(ptNextUnit->m_vecPtsPreRightUnit.begin() + i);
				}
			}

			// 刪除被選取的線段
			m_listUnitLines.RemoveAt(posiLineCur);

			delete ptCurLineUnit;
		}
	}

	OnPaint();
}




void CMFCSimulatorDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// 得到操作視窗矩形資訊
	CRect rectShowRegion;
	GetDlgItem(IDC_STATIC_SHOW_REGION)->GetWindowRect(&rectShowRegion);

	// 操作視窗長、寬
	int iHeightShowRegion = rectShowRegion.Height();
	int iWidthShowRegion = rectShowRegion.Width();

	// 主視窗座標轉換為操作視窗的座標
	ScreenToClient(&rectShowRegion);

	// 滑鼠座標點轉換為操作視窗內的座標點
	point.x = point.x - rectShowRegion.left;
	point.y = point.y - rectShowRegion.top;

	// 擷取滑鼠位置
	SetCapture();

	// 得到內含已創建元件的指針的 CList ，並取得 CList 的位置指針
	POSITION posiUnit = m_listUnitPointers.GetHeadPosition();

	while (posiUnit != nullptr)
	{	// 走訪 CList 內的所有元素

		UnitBase* ptUnit = m_listUnitPointers.GetNext(posiUnit);

		// 得到元件的矩形
		CRect rectUnit = GetUnitRect(ptUnit->m_pointUnitLocation);

		if (rectUnit.PtInRect(point) && (m_bIsLineMode == FALSE))
		{	// 確認滑鼠是否點取元件
			
			// 更新被拖曳元件的狀態
			ptUnit->m_bMoveState = TRUE;

			
			// 點取元件時，滑鼠產生十字的圖案
			SetCursor(LoadCursor(NULL, IDC_SIZEALL));

			// 開啟拖曳的狀態
			m_bIsDragging = TRUE;

			// 更新滑鼠點擊時的位置
			m_pointMouseStartPos = point;

			// 暫時紀錄移動中的元件指標
			m_ptMovingUnit = ptUnit;

			break;
		}



		// 更新元件連接點與其外切矩形位置
		ptUnit->SetConnectPtAndRect(m_iOffsetX, m_iOffsetY);

		// 得到儲存連接點外切矩形的陣列
		std::vector<CRect> vecConnectPtRects = ptUnit->m_vecConnectPtRect;
		
		CRect rectLeftTopCheck = ptUnit->m_rectConnectLeftTop;
		CRect rectRightTopCheck = ptUnit->m_rectConnectRightTop;
		CRect rectBottomCheck = ptUnit->m_rectConnectBottom;


		for (int i = 0; i < vecConnectPtRects.size(); i++)
		{	// 遍歷元件所有的連接點外切矩形

			if (m_bIsLineMode == TRUE)
			{
				if (vecConnectPtRects[i].PtInRect(point))
				{	// 滑鼠點到外切矩形內的範圍，並且開啟連線模式

					// 點取元件時，滑鼠產生十字的圖案
					SetCursor(LoadCursor(NULL, IDC_SIZEALL));

					// 開啟拖曳的狀態
					m_bIsDragging = TRUE;

					// 新增連線線段物件
					UnitLine* ptNewUnitLine = new UnitLine(rectShowRegion, rectUnit);

					// 更新線段狀態，設為正在拖曳中
					ptNewUnitLine->m_bMoveState = TRUE;

					// 紀錄連線的連接點編號
					ptNewUnitLine->m_iConnectPrePtIndex = i;

					// 
					ptNewUnitLine->m_pointMovingLinePos = ptUnit->m_vecConnectPt[i];

					// 暫時紀錄移動中的線段指標
					m_ptMovingLine = ptNewUnitLine;

					// 紀錄連線起點的元件指標
					m_ptPreUnit = ptUnit;

					// 紀錄連線起點的元件
					ptNewUnitLine->m_vecPtsPreLeftUnit.push_back(ptUnit);

					// 放進紀錄 Line Pointer 的串列結構
					m_listUnitLines.AddTail(ptNewUnitLine);

					// 更新按下滑鼠左鍵當下位置
					m_pointMouseStartPos = point;

					m_pointMouseInitialPos = point;

					break;
				}
			}
		}
	}	


	////////////////////////////////////////////////////////
	// 點選元件的功能
	POSITION posiUnitCheck = m_listUnitPointers.GetTailPosition();
	while ((posiUnitCheck != nullptr) && (m_bIsLineMode == FALSE))
	{
		UnitBase* ptUnit = m_listUnitPointers.GetPrev(posiUnitCheck);

		// 得到元件的矩形
		CRect rectUnit = GetUnitRect(ptUnit->m_pointUnitLocation);

		ptUnit->m_bFocusState = FALSE;
		if (rectUnit.PtInRect(point) && (m_bIsLineMode == FALSE))
		{	// 確認滑鼠是否點取元件

			ptUnit->m_bFocusState = TRUE;

		}
	}


	// 點選線段的功能
	POSITION posiLineUnitCheck = m_listUnitLines.GetTailPosition();
	while ((posiLineUnitCheck != nullptr) && (m_bIsLineMode == FALSE))
	{
		POSITION posiCur = posiLineUnitCheck;
		UnitLine* ptLineUnit = m_listUnitLines.GetPrev(posiLineUnitCheck);

		ptLineUnit->m_bFocusState = FALSE;

		CPoint pointLineStart = ptLineUnit->m_vecPtsPreLeftUnit[0]->m_vecConnectPt[ptLineUnit->m_iConnectPrePtIndex];
		CPoint pointLineEnd = ptLineUnit->m_vecPtsNextUnit[0]->m_vecConnectPt[ptLineUnit->m_iConnectNextPtIndex];

		double dMouseToLineDistance = PointToLineDistance(point, pointLineStart, pointLineEnd);

		if (dMouseToLineDistance <= 7)
		{
			ptLineUnit->m_bFocusState = TRUE;
		}
	}
	////////////////////////////////////////////////////////


	OnPaint();

	CDialogEx::OnLButtonDown(nFlags, point);
}




// 點擊滑鼠左鍵兩下
void CMFCSimulatorDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// 得到操作視窗矩形資訊
	CRect rectShowRegion;
	GetDlgItem(IDC_STATIC_SHOW_REGION)->GetWindowRect(&rectShowRegion);

	// 操作視窗長、寬
	int iHeightShowRegion = rectShowRegion.Height();
	int iWidthShowRegion = rectShowRegion.Width();

	// 主視窗座標轉換為操作視窗的座標
	ScreenToClient(&rectShowRegion);

	// 滑鼠座標點轉換為操作視窗內的座標點
	point.x = point.x - rectShowRegion.left;
	point.y = point.y - rectShowRegion.top;


	// 得到內含已創建元件的指針的 CList ，並取得 CList 的位置指針
	POSITION posiUnit = m_listUnitPointers.GetHeadPosition();

	while (posiUnit != nullptr)
	{	// 走訪 CList 內的所有元素

		UnitBase* ptUnit = m_listUnitPointers.GetNext(posiUnit);

		// 得到元件的矩形
		CRect rectUnit = GetUnitRect(ptUnit->m_pointUnitLocation);


		if (rectUnit.PtInRect(point) && (m_bIsLineMode == FALSE))
		{	// 確認滑鼠是否點取元件

			if (ptUnit->m_strUnitID == "IN")
			{

				UnitInDlg dlgUnitInChoose;
				dlgUnitInChoose.DoModal();
				

				// 將從子視窗選擇的函式更新到元件內
				ptUnit->m_strFuncOrOpera = m_strFunOrOperChoose;

			}
			else if (ptUnit->m_strUnitID == "FUN")
			{

				UnitFunDlg dlgUnitFun;
				dlgUnitFun.DoModal();

				// 將從子視窗選擇的函式更新到元件內
				ptUnit->m_strFuncOrOpera = m_strFunOrOperChoose;

			}

			break;
		}

	}

	CDialogEx::OnLButtonDblClk(nFlags, point);
}





void CMFCSimulatorDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// 得到操作視窗矩形資訊
	CRect rectShowRegion;
	GetDlgItem(IDC_STATIC_SHOW_REGION)->GetWindowRect(&rectShowRegion);

	// 主視窗座標轉換為操作視窗的座標
	ScreenToClient(&rectShowRegion);

	// 滑鼠座標點轉換為操作視窗內的座標點
	point.x = point.x - rectShowRegion.left;
	point.y = point.y - rectShowRegion.top;
	
	if (m_bIsDragging == TRUE)
	{	// 當開始拖曳時，計算拖曳的距離，改變矩形位置

		//計算並暫存拖曳元件或是線段的位移
		m_iOffsetX = point.x - m_pointMouseStartPos.x;
		m_iOffsetY = point.y - m_pointMouseStartPos.y;

		if (m_bIsLineMode == FALSE)
		{	// 連線模式關閉的時候

			CPoint pointOffsetCheck = m_ptMovingUnit->m_pointUnitLocation;
			pointOffsetCheck.Offset(m_iOffsetX, m_iOffsetY);

			if ((pointOffsetCheck.x >= 0) && (pointOffsetCheck.y >= 0))
			{ // 確認元件位置不會高於畫面邊界和超出左邊畫面邊界

				if ((pointOffsetCheck.x + m_ptMovingUnit->m_iUnitWidth <= rectShowRegion.Width()) && (pointOffsetCheck.y + m_ptMovingUnit->m_iUnitHeight <= rectShowRegion.Height()))
				{	// 確認元件位置不會低於畫面邊界和超出右邊畫面邊界

					// 更新元件的位置
					m_ptMovingUnit->m_pointUnitLocation.Offset(m_iOffsetX, m_iOffsetY);

					// 更新元件連接點與其外切矩形的位置
					m_ptMovingUnit->SetConnectPtAndRect(m_iOffsetX, m_iOffsetY);
				}
			}
			// 更新滑鼠左鍵當下位置
			m_pointMouseStartPos = point; 

		}
		else
		{	// 連線模式開啟的時候
			
			// 更新線段終點的位置
			m_ptMovingLine->m_pointMovingLinePos.Offset(m_iOffsetX, m_iOffsetY);

			// 更新拖曳移動中的滑鼠點位置
			m_pointMovingMouse = point;

			// 初始化按下滑鼠左鍵時的位置
			m_pointMouseStartPos = point;

		}

		OnPaint();
	}

	CDialogEx::OnMouseMove(nFlags, point);
}



void CMFCSimulatorDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// 得到操作視窗矩形資訊
	CRect rectShowRegion;
	GetDlgItem(IDC_STATIC_SHOW_REGION)->GetWindowRect(&rectShowRegion);

	// 主視窗座標轉換為操作視窗的座標
	ScreenToClient(&rectShowRegion);

	// 滑鼠座標點轉換為操作視窗內的座標點
	point.x = point.x - rectShowRegion.left;
	point.y = point.y - rectShowRegion.top;




	if (m_bIsDragging)
	{   // 當放開滑鼠時，釋放滑鼠位置

		// 更新拖曳狀態
		m_bIsDragging = FALSE;

		// 得到內含已創建元件的指針的 CList ，並取得 CList 的位置指針
		POSITION posiUnit = m_listUnitPointers.GetTailPosition();

		// 得到內含已創建線段的指針的 CList ，並取得 CList 的位置指針
		POSITION posiLineUnit = m_listUnitLines.GetTailPosition();


		while (posiUnit != nullptr)
		{	// 走訪 CList 內的所有元件

			UnitBase* ptUnit = m_listUnitPointers.GetPrev(posiUnit);

			// 得到連接點外切矩形
			std::vector<CRect> rectConnectPts = ptUnit->m_vecConnectPtRect;




			if ((ptUnit->m_bMoveState == TRUE) && (m_bIsLineMode == FALSE))
			{	// 更新元件移動的狀態

				ptUnit->m_bMoveState = FALSE;

				break;
			}

			if (m_bIsLineMode == TRUE)
			{	// 開啟連線模式後

				for (int i = 0; i < rectConnectPts.size(); i++)
				{	// 遍歷已儲存元件的連接點外切矩形

					if (rectConnectPts[i].PtInRect(point))
					{	// 當拖曳的後釋放滑鼠左鍵時，在外切矩形內

						UnitLine* ptLineUnit = m_listUnitLines.GetPrev(posiLineUnit);

						// 更新線段拖曳狀態
						ptLineUnit->m_bMoveState = FALSE;

						// 紀錄線段連接點終點所連到的矩形編號
						ptLineUnit->m_iConnectNextPtIndex = i;

						// 紀錄連線終點的元件
						m_ptNextUnit = ptUnit;


						// 不合理連線警告
						if ((m_ptPreUnit->m_strUnitID == "IN") && (m_ptNextUnit->m_strUnitID == "IN"))
						{
							AfxMessageBox(_T("連線錯誤"));
							break;
						}
						else if ((m_ptPreUnit->m_strUnitID == "OUT") && (m_ptNextUnit->m_strUnitID == "OUT"))
						{
							AfxMessageBox(_T("連線錯誤"));
							break;
						}

						if ((m_ptPreUnit->m_strUnitID == "FUN") && (m_ptNextUnit->m_strUnitID == "FUN"))
						{
							if (((m_ptNextUnit->m_rectConnectLeftTop.PtInRect(point)) || (m_ptNextUnit->m_rectConnectRightTop.PtInRect(point))) &&
								(m_ptPreUnit->m_rectConnectLeftTop.PtInRect(m_pointMouseInitialPos)))
							{
								AfxMessageBox(_T("連線錯誤"));
								break;
							}
							else if (((m_ptNextUnit->m_rectConnectLeftTop.PtInRect(point)) || (m_ptNextUnit->m_rectConnectRightTop.PtInRect(point))) &&
								(m_ptPreUnit->m_rectConnectRightTop.PtInRect(m_pointMouseInitialPos)))
							{
								AfxMessageBox(_T("連線錯誤"));
								break;
							}
							else if ((m_ptPreUnit->m_rectConnectBottom.PtInRect(m_pointMouseInitialPos)) && (m_ptNextUnit->m_rectConnectBottom.PtInRect(point)))
							{
								AfxMessageBox(_T("連線錯誤"));
								break;
							}
						}


						if ((m_ptPreUnit->m_strUnitID == "AND") && (m_ptNextUnit->m_strUnitID == "AND"))
						{
							if (((m_ptNextUnit->m_rectConnectLeftTop.PtInRect(point)) || (m_ptNextUnit->m_rectConnectRightTop.PtInRect(point))) &&
								(m_ptPreUnit->m_rectConnectLeftTop.PtInRect(m_pointMouseInitialPos)))
							{
								AfxMessageBox(_T("連線錯誤"));
								break;
							}
							else if (((m_ptNextUnit->m_rectConnectLeftTop.PtInRect(point)) || (m_ptNextUnit->m_rectConnectRightTop.PtInRect(point))) &&
								(m_ptPreUnit->m_rectConnectRightTop.PtInRect(m_pointMouseInitialPos)))
							{
								AfxMessageBox(_T("連線錯誤"));
								break;
							}
							else if ((m_ptPreUnit->m_rectConnectBottom.PtInRect(m_pointMouseInitialPos)) && (m_ptNextUnit->m_rectConnectBottom.PtInRect(point)))
							{
								AfxMessageBox(_T("連線錯誤"));
								break;
							}
						}



						if ((m_ptPreUnit->m_strUnitID == "OR") && (m_ptNextUnit->m_strUnitID == "OR"))
						{
							if (((m_ptNextUnit->m_rectConnectLeftTop.PtInRect(point)) || (m_ptNextUnit->m_rectConnectRightTop.PtInRect(point))) &&
								(m_ptPreUnit->m_rectConnectLeftTop.PtInRect(m_pointMouseInitialPos)))
							{
								AfxMessageBox(_T("連線錯誤"));
								break;
							}
							else if (((m_ptNextUnit->m_rectConnectLeftTop.PtInRect(point)) || (m_ptNextUnit->m_rectConnectRightTop.PtInRect(point))) &&
								(m_ptPreUnit->m_rectConnectRightTop.PtInRect(m_pointMouseInitialPos)))
							{
								AfxMessageBox(_T("連線錯誤"));
								break;
							}
							else if ((m_ptPreUnit->m_rectConnectBottom.PtInRect(m_pointMouseInitialPos)) && (m_ptNextUnit->m_rectConnectBottom.PtInRect(point)))
							{
								AfxMessageBox(_T("連線錯誤"));
								break;
							}
						}



						if ((m_ptPreUnit->m_strUnitID == "NOT") && (m_ptNextUnit->m_strUnitID == "NOT") && (m_ptPreUnit->m_rectConnectLeftTop.PtInRect(m_pointMouseInitialPos)))
						{
							if (m_ptNextUnit->m_rectConnectLeftTop.PtInRect(point))
							{
								AfxMessageBox(_T("連線錯誤"));
								break;
							}
						}
						else if ((m_ptPreUnit->m_strUnitID == "NOT") && (m_ptNextUnit->m_strUnitID == "NOT") && (m_ptPreUnit->m_rectConnectBottom.PtInRect(m_pointMouseInitialPos)))
						{
							if (m_ptNextUnit->m_rectConnectBottom.PtInRect(point))
							{
								AfxMessageBox(_T("連線錯誤"));
								break;
							}
						}


						if ((m_ptPreUnit->m_rectConnectLeftTop.PtInRect(m_pointMouseInitialPos)) &&
							((m_ptNextUnit->m_rectConnectLeftTop.PtInRect(point)) || m_ptNextUnit->m_rectConnectRightTop.PtInRect(point)))
						{
							AfxMessageBox(_T("連線錯誤"));
							break;
						}
						else if ((m_ptPreUnit->m_rectConnectRightTop.PtInRect(m_pointMouseInitialPos)) &&
							    ((m_ptNextUnit->m_rectConnectLeftTop.PtInRect(point)) || m_ptNextUnit->m_rectConnectRightTop.PtInRect(point)))
						{
							AfxMessageBox(_T("連線錯誤"));
							break;
						}



						// 兩連接元件紀錄彼此的指標
			           // 考慮放的位置
						if (m_ptPreUnit->m_rectConnectLeftTop.PtInRect(m_pointMouseInitialPos))
						{
							m_ptPreUnit->m_vecPtsPreLeftUnit.push_back(ptUnit);
						}
						else if (m_ptPreUnit->m_rectConnectRightTop.PtInRect(m_pointMouseInitialPos))
						{
							m_ptPreUnit->m_vecPtsPreRightUnit.push_back(ptUnit);
						}
						else if (m_ptPreUnit->m_rectConnectBottom.PtInRect(m_pointMouseInitialPos))
						{
							m_ptPreUnit->m_vecPtsNextUnit.push_back(ptUnit);
						}


						if (ptUnit->m_rectConnectLeftTop.PtInRect(point))
						{
							m_ptNextUnit->m_vecPtsPreLeftUnit.push_back(m_ptPreUnit);
						}
						else if (ptUnit->m_rectConnectRightTop.PtInRect(point))
						{
							m_ptNextUnit->m_vecPtsPreRightUnit.push_back(m_ptPreUnit);
						}
						else if (ptUnit->m_rectConnectBottom.PtInRect(point))
						{
							m_ptNextUnit->m_vecPtsNextUnit.push_back(m_ptPreUnit);
						}

						// 紀錄連接的元件指標
						ptLineUnit->m_vecPtsNextUnit.push_back(ptUnit);

						// 更新線段的連接狀態
						ptLineUnit->m_bIsConnect = TRUE;

						break;
					}
				}
			}
		}
	}


	////////////////////////////////////////////////////////
	// 即時清除畫面中沒有連接的線段
	POSITION posiLineUnitCheck = m_listUnitLines.GetTailPosition();
	while (posiLineUnitCheck != nullptr)
	{
		POSITION posiCur = posiLineUnitCheck;
		UnitLine* ptLineUnit = m_listUnitLines.GetPrev(posiLineUnitCheck);
		
		if (ptLineUnit->m_bIsConnect == FALSE)
		{
			m_listUnitLines.RemoveAt(posiCur);

			break;
		}
	}
	OnPaint();
	////////////////////////////////////////////////////////


	// 位移歸零
	m_iOffsetX = 0;
	m_iOffsetY = 0;

	// 釋放滑鼠擷取
	ReleaseCapture();

	CDialogEx::OnLButtonUp(nFlags, point);
}



// 開始模擬
void CMFCSimulatorDlg::OnBnClickedButtonSimulate()
{

	m_bIsLineMode = FALSE;

	BOOL bIsChooseOUT = FALSE;

	m_staticLineState.SetWindowText(_T("Simulation"));


	UnitBase* ptUnitResultOut = NULL;
	POSITION posiUnit = m_listUnitPointers.GetTailPosition();
	while (posiUnit != nullptr)
	{
		UnitBase* ptUnit = m_listUnitPointers.GetPrev(posiUnit);

		if ((ptUnit->m_strUnitID == "OUT") && (ptUnit->m_bFocusState == TRUE))
		{
			ptUnitResultOut = ptUnit;
			bIsChooseOUT = TRUE;
		}
	}

	if (bIsChooseOUT == TRUE)
	{
		SimulateStartDlg dlgResult;
		dlgResult.m_ptOutUnit = ptUnitResultOut;
		dlgResult.DoModal();
	}
	else
	{
		AfxMessageBox(_T("Please choose and click an OUT unit."));
	}

	m_staticLineState.SetWindowText(_T("Normal"));

}




void CMFCSimulatorDlg::OnDestroy()
{


	CDialogEx::OnDestroy();

	// TODO: 在此加入您的訊息處理常式程式碼
}




// 存檔
void CMFCSimulatorDlg::OnBnClickedButtonSave()
{


	int iNum = 0; // 紀錄元件建立順序
	POSITION posiAllUnit = m_listUnitPointers.GetHeadPosition();
	while (posiAllUnit != nullptr)
	{
		UnitBase* ptUnit = m_listUnitPointers.GetNext(posiAllUnit);
		ptUnit->m_iUnitSaveNum = iNum;

		iNum++;
	}

	

	CString strSaveFilePath;
	CFileDialog dlgSaveFile(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("All Files(*.ini)|*.ini|所有文件(*.*)|*.*|"), NULL);

	
	if (dlgSaveFile.DoModal() == IDOK)
	{

		strSaveFilePath = dlgSaveFile.GetPathName();

		// 刪除之前的檔案並重新寫入
		DeleteFile(strSaveFilePath);

		POSITION posiUnit = m_listUnitPointers.GetHeadPosition();
		while (posiUnit != nullptr)
		{
			UnitBase* ptUnit = m_listUnitPointers.GetNext(posiUnit);
			
			CString strSaveNum;
			strSaveNum.Format(_T("%d"), ptUnit->m_iUnitSaveNum);
			
			// 元件種類
			WritePrivateProfileString(strSaveNum, _T("ID"), ptUnit->m_strUnitID, strSaveFilePath);

			// 元件定義的函數或是算元
			WritePrivateProfileString(strSaveNum, _T("FunOrOpera"), ptUnit->m_strFuncOrOpera, strSaveFilePath);

			
			// 元件矩形左上角位置
			CString strLocaX;  // X 座標 
			strLocaX.Format(_T("%d"), ptUnit->m_pointUnitLocation.x);
			CString strLocaY;  // Y 座標 
			strLocaY.Format(_T("%d"), ptUnit->m_pointUnitLocation.y);

			WritePrivateProfileString(strSaveNum, _T("LocationX"), strLocaX, strSaveFilePath);
			WritePrivateProfileString(strSaveNum, _T("LocationY"), strLocaY, strSaveFilePath);

			// 元件連接編號(左上、右上、下方)

			if (ptUnit->m_vecPtsPreLeftUnit.empty() != TRUE)
			{
				CString strLeftTop;
				strLeftTop.Format(_T("%d"), ptUnit->m_vecPtsPreLeftUnit[0]->m_iUnitSaveNum);
				WritePrivateProfileString(strSaveNum, _T("LeftTopConnect"), strLeftTop, strSaveFilePath);
			}
			else
			{
				WritePrivateProfileString(strSaveNum, _T("LeftTopConnect"), _T(""), strSaveFilePath);
			}

			if (ptUnit->m_vecPtsPreRightUnit.empty() != TRUE)
			{
				CString strRightTop;
				strRightTop.Format(_T("%d"), ptUnit->m_vecPtsPreRightUnit[0]->m_iUnitSaveNum);
				WritePrivateProfileString(strSaveNum, _T("RightTopConnect"), strRightTop, strSaveFilePath);
			}
			else
			{
				WritePrivateProfileString(strSaveNum, _T("RightTopConnect"), _T(""), strSaveFilePath);
			}

			CString strNext;
			if (ptUnit->m_vecPtsNextUnit.size() > 1)
			{
				CString strNextNum;
				for (int i = 0; i < ptUnit->m_vecPtsNextUnit.size(); i++)
				{
					strNextNum.Format(_T("%d"), i);
					strNext.Format(_T("%d"), ptUnit->m_vecPtsNextUnit[i]->m_iUnitSaveNum);
					WritePrivateProfileString(strSaveNum, _T("NextConnect") + strNextNum, strNext, strSaveFilePath);
				}
			}
			else if (ptUnit->m_vecPtsNextUnit.size() == 1)
			{
				strNext.Format(_T("%d"), ptUnit->m_vecPtsNextUnit[0]->m_iUnitSaveNum);
				WritePrivateProfileString(strSaveNum, _T("NextConnect"), strNext, strSaveFilePath);
			}
			else
			{
				WritePrivateProfileString(strSaveNum, _T("NextConnect"), _T(""), strSaveFilePath);
			}
			
		}

		int iLineNum = 0;
		POSITION posiLineUnit = m_listUnitLines.GetHeadPosition();
		while (posiLineUnit != nullptr)
		{
			UnitLine* ptLineUnit = m_listUnitLines.GetNext(posiLineUnit);

			// 線段編號
			CString strLineNum;
			strLineNum.Format(_T("%d"), iLineNum);
			strLineNum = _T("Line") + strLineNum;

			// 線段起點元件的生成編號
			int iLineStartUnitNum = ptLineUnit->m_vecPtsPreLeftUnit[0]->m_iUnitSaveNum;
			CString strLineStart;
			strLineStart.Format(_T("%d"), iLineStartUnitNum);
			WritePrivateProfileString(strLineNum, _T("LineStartUnit"), strLineStart, strSaveFilePath);

			// 線段終點元件的生成編號
			int iLineEndUnitNum = ptLineUnit->m_vecPtsNextUnit[0]->m_iUnitSaveNum;
			CString strLineEnd;
			strLineEnd.Format(_T("%d"), iLineEndUnitNum);
			WritePrivateProfileString(strLineNum, _T("LineEndUnit"), strLineEnd, strSaveFilePath);

			// 線段繪圖連接點起點編號
			int iConnectPrePtIndex = ptLineUnit->m_iConnectPrePtIndex;
			CString strConnectPrePtIndex;
			strConnectPrePtIndex.Format(_T("%d"), iConnectPrePtIndex);
			WritePrivateProfileString(strLineNum, _T("LineStartIndex"), strConnectPrePtIndex, strSaveFilePath);

			// 線段繪圖連接點終點編號
			int iConnectNextPtIndex = ptLineUnit->m_iConnectNextPtIndex;
			CString strConnectNextPtIndex;
			strConnectNextPtIndex.Format(_T("%d"), iConnectNextPtIndex);
			WritePrivateProfileString(strLineNum, _T("LineEndIndex"), strConnectNextPtIndex, strSaveFilePath);


			iLineNum++;

		}

		// 紀錄生成元件個數
		CString strUnitTotalNum;
		int iUnitTotalNum = m_listUnitPointers.GetSize();
		strUnitTotalNum.Format(_T("%d"), iUnitTotalNum);
		WritePrivateProfileString(_T("TotalNum"), _T("Units"), strUnitTotalNum, strSaveFilePath);

		CString strUnitLineTotalNum;
		int iUnitLineTotalNum = m_listUnitLines.GetSize();
		strUnitLineTotalNum.Format(_T("%d"), iUnitLineTotalNum);
		WritePrivateProfileString(_T("TotalNum"), _T("Lines"), strUnitLineTotalNum, strSaveFilePath);



		// 儲存背景資訊
		// 是否更改背景圖片
		CString strIsChangeBG = (g_bShowRegionBgImgChange ? _T("TRUE") : _T("FALSE"));
		WritePrivateProfileString(_T("BackgroundInfo"), _T("IsChange"), strIsChangeBG, strSaveFilePath);
		WritePrivateProfileString(_T("BackgroundInfo"), _T("BackgroundPath"), m_strShowRegionImgBgPath, strSaveFilePath);

		// 背景顏色
		CString strColorR;
		CString strColorG;
		CString strColorB;
		strColorR.Format(_T("%d"), GetRValue(m_colorShowRegionBg));
		strColorG.Format(_T("%d"), GetGValue(m_colorShowRegionBg));
		strColorB.Format(_T("%d"), GetBValue(m_colorShowRegionBg));
		WritePrivateProfileString(_T("BackgroundInfo"), _T("BackgroundColorR"), strColorR, strSaveFilePath);
		WritePrivateProfileString(_T("BackgroundInfo"), _T("BackgroundColorG"), strColorG, strSaveFilePath);
		WritePrivateProfileString(_T("BackgroundInfo"), _T("BackgroundColorB"), strColorB, strSaveFilePath);



		AfxMessageBox(_T("Saved Successfully"));
	}
	else
	{
		AfxMessageBox(_T("Cancel"));
	}
	

}


// 讀檔
void CMFCSimulatorDlg::OnBnClickedButtonOpen()
{
	

	CString strLoadFilePath;
	CFileDialog dlgLoadFile(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("All Files(*.ini)|*.ini|所有文件(*.*)|*.*|"), NULL);

	if (dlgLoadFile.DoModal() == IDOK)
	{
		
		// 清空之前所記取的元件以及線段
		m_listUnitPointers.RemoveAll();
		m_listUnitLines.RemoveAll();

		// 操作視窗矩形
		CRect rectShowRegion;

		// 元件矩形
		CRect rectUnit;

		// 得到操作視窗矩形
		m_staticShowRegion.GetWindowRect(&rectShowRegion);


		// 操作視窗長、寬
		int iHeightShowRegion = rectShowRegion.Height();
		int iWidthShowRegion = rectShowRegion.Width();




		strLoadFilePath = dlgLoadFile.GetPathName();
		
		int iUnitTotalNum = GetPrivateProfileInt(_T("TotalNum"), _T("Units"), -1, strLoadFilePath);
		
		int iLineUnitTotalNNum = GetPrivateProfileInt(_T("TotalNum"), _T("Lines"), -1, strLoadFilePath);


		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		for (int i = 0; i < iUnitTotalNum; i++)
		{
			CString strNum;
			 
			CString strBuff;
			
			strNum.Format(_T("%d"), i);
			GetPrivateProfileString(strNum, _T("ID"), _T("NULL"), strBuff.GetBuffer(MAX_PATH), MAX_PATH, strLoadFilePath);
			strBuff.ReleaseBuffer();
			// 判斷元件種類
			CString strFlag = strBuff.GetBuffer(0);

			// 元件位置
			int iLOcationX = GetPrivateProfileInt(strNum, _T("LocationX"), -1, strLoadFilePath);
			int iLOcationY = GetPrivateProfileInt(strNum, _T("LocationY"), -1, strLoadFilePath);

			// 元件函數或是運算元種類
			GetPrivateProfileString(strNum, _T("FunOrOpera"), _T(""), strBuff.GetBuffer(MAX_PATH), MAX_PATH, strLoadFilePath);
			strBuff.ReleaseBuffer();
			CString strFunOrOpera = strBuff.GetBuffer(0);
			


			if (strFlag == _T("IN"))
			{
				// 得到元件矩形
				m_buttonIN.GetWindowRect(&rectUnit);

				// 元件矩形長寬
				int iWidthUnit = rectUnit.Width();
				int iHeightUnit = rectUnit.Height();

				// 新建一個新 IN 元件
				UnitIN* ptNewUnitIN = new UnitIN(rectShowRegion, rectUnit);

				ptNewUnitIN->m_pointUnitLocation = CPoint(iLOcationX, iLOcationY);

				ptNewUnitIN->SetConnectPtAndRect(iLOcationX, iLOcationY);

				ptNewUnitIN->m_iUnitSaveNum = i;

				ptNewUnitIN->m_strFuncOrOpera = strFunOrOpera;


				// 放進紀錄 Pointer 的串列結構
				m_listUnitPointers.AddTail(ptNewUnitIN);
			}
			else if (strFlag == _T("OUT"))
			{
				// 得到元件矩形
				m_buttonOUT.GetWindowRect(&rectUnit);

				// 元件矩形長寬
				int iWidthUnit = rectUnit.Width();
				int iHeightUnit = rectUnit.Height();

				// 新建一個新元件
				UnitOUT* ptNewUnitOUT = new UnitOUT(rectShowRegion, rectUnit);


				ptNewUnitOUT->m_pointUnitLocation = CPoint(iLOcationX, iLOcationY);

				ptNewUnitOUT->SetConnectPtAndRect(iLOcationX, iLOcationY);

				ptNewUnitOUT->m_iUnitSaveNum = i;

				ptNewUnitOUT->m_strFuncOrOpera = strFunOrOpera;

				// 放進紀錄 Pointer 的串列結構
				m_listUnitPointers.AddTail(ptNewUnitOUT);
			}
			else if (strFlag == _T("AND"))
			{

				// 得到元件矩形
				m_buttonAND.GetWindowRect(&rectUnit);

				// 元件矩形長寬
				int iWidthUnit = rectUnit.Width();
				int iHeightUnit = rectUnit.Height();

				// 新建一個新元件
				UnitAND* ptNewUnitAND = new UnitAND(rectShowRegion, rectUnit);

				ptNewUnitAND->m_pointUnitLocation = CPoint(iLOcationX, iLOcationY);

				ptNewUnitAND->SetConnectPtAndRect(iLOcationX, iLOcationY);

				ptNewUnitAND->m_iUnitSaveNum = i;

				ptNewUnitAND->m_strFuncOrOpera = strFunOrOpera;

				// 放進紀錄 Pointer 的串列結構
				m_listUnitPointers.AddTail(ptNewUnitAND);

			}
			else if (strFlag == _T("OR"))
			{
				// 得到元件矩形
				m_buttonOR.GetWindowRect(&rectUnit);

				// 元件矩形長寬
				int iWidthUnit = rectUnit.Width();
				int iHeightUnit = rectUnit.Height();

				// 新建一個新元件
				UnitOR* ptNewUnitOR = new UnitOR(rectShowRegion, rectUnit);

				ptNewUnitOR->m_pointUnitLocation = CPoint(iLOcationX, iLOcationY);

				ptNewUnitOR->SetConnectPtAndRect(iLOcationX, iLOcationY);

				ptNewUnitOR->m_iUnitSaveNum = i;

				ptNewUnitOR->m_strFuncOrOpera = strFunOrOpera;

				// 放進紀錄 Pointer 的串列結構
				m_listUnitPointers.AddTail(ptNewUnitOR);

			}
			else if (strFlag == _T("NOT"))
			{

				// 得到元件矩形
				m_buttonNOT.GetWindowRect(&rectUnit);

				// 元件矩形長寬
				int iWidthUnit = rectUnit.Width();
				int iHeightUnit = rectUnit.Height();

				// 新建一個新元件
				UnitNOT* ptNewUnitNOT = new UnitNOT(rectShowRegion, rectUnit);

				ptNewUnitNOT->m_pointUnitLocation = CPoint(iLOcationX, iLOcationY);

				ptNewUnitNOT->SetConnectPtAndRect(iLOcationX, iLOcationY);

				ptNewUnitNOT->m_iUnitSaveNum = i;

				ptNewUnitNOT->m_strFuncOrOpera = strFunOrOpera;

				// 放進紀錄 Pointer 的串列結構
				m_listUnitPointers.AddTail(ptNewUnitNOT);

			}
			else if (strFlag == _T("FUN"))
			{
				
				// 得到元件矩形
				m_buttonFUN.GetWindowRect(&rectUnit);

				// 元件矩形長寬
				int iWidthUnit = rectUnit.Width();
				int iHeightUnit = rectUnit.Height();

				// 新建一個新元件
				UnitFUN* ptNewUnitFUN = new UnitFUN(rectShowRegion, rectUnit);

				ptNewUnitFUN->m_pointUnitLocation = CPoint(iLOcationX, iLOcationY);

				ptNewUnitFUN->SetConnectPtAndRect(iLOcationX, iLOcationY);

				ptNewUnitFUN->m_iUnitSaveNum = i;

				ptNewUnitFUN->m_strFuncOrOpera = strFunOrOpera;

				// 放進紀錄 Pointer 的串列結構
				m_listUnitPointers.AddTail(ptNewUnitFUN);

			}
		}


		// 處理指標連接

		for (int i = 0; i < iUnitTotalNum; i++)
		{

			CString strNum;

			CString strBuff;

			strNum.Format(_T("%d"), i);

			// 元件連接的指標
			// 左上 : 
			int iLeftTopPt = GetPrivateProfileInt(strNum, _T("LeftTopConnect"), -1, strLoadFilePath);
			// 右上 : 
			int iRightTopPt = GetPrivateProfileInt(strNum, _T("RightTopConnect"), -1, strLoadFilePath);
			// 下方 : 
			int iNextPt = GetPrivateProfileInt(strNum, _T("NextConnect"), -1, strLoadFilePath);

			POSITION posiUnit = m_listUnitPointers.GetHeadPosition();
			while (posiUnit != nullptr)
			{
				UnitBase* ptUnit = m_listUnitPointers.GetNext(posiUnit);
				if (ptUnit->m_iUnitSaveNum == i)
				{
					POSITION posiConnect = m_listUnitPointers.GetHeadPosition();
					while (posiConnect != nullptr)
					{
						UnitBase* ptConnectUnit = m_listUnitPointers.GetNext(posiConnect);
						if (ptConnectUnit->m_iUnitSaveNum == iLeftTopPt)
						{
							ptUnit->m_vecPtsPreLeftUnit.push_back(ptConnectUnit);
						}
						else if (ptConnectUnit->m_iUnitSaveNum == iRightTopPt)
						{
							ptUnit->m_vecPtsPreRightUnit.push_back(ptConnectUnit);
						}
						else if (ptConnectUnit->m_iUnitSaveNum == iNextPt)
						{
							ptUnit->m_vecPtsNextUnit.push_back(ptConnectUnit);
						}

					}
				}


			}
		}
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		for (int i = 0; i < iLineUnitTotalNNum; i++)
		{
			CString strLineNum;

			CString strBuff;

			strLineNum.Format(_T("%d"), i);
			strLineNum = _T("Line") + strLineNum;


			// 連線起點
			int iStartUnit = GetPrivateProfileInt(strLineNum, _T("LineStartUnit"), -1, strLoadFilePath);
			// 連線終點
			int iEndUnit = GetPrivateProfileInt(strLineNum, _T("LineEndUnit"), -1, strLoadFilePath);
			// 連線繪圖起點序號
			int iStartIndex = GetPrivateProfileInt(strLineNum, _T("LineStartIndex"), -1, strLoadFilePath);
			// 連線繪圖終點序號
			int iEndIndex = GetPrivateProfileInt(strLineNum, _T("LineEndIndex"), -1, strLoadFilePath);


			// 新增連線線段物件
			UnitLine* ptNewUnitLine = new UnitLine(rectShowRegion, rectUnit);

			POSITION posiUnit = m_listUnitPointers.GetHeadPosition();
			while (posiUnit != nullptr)
			{
				UnitBase* ptUnit = m_listUnitPointers.GetNext(posiUnit);

				// 存取起點的元件指標
				if (ptUnit->m_iUnitSaveNum == iStartUnit)
				{
					ptNewUnitLine->m_vecPtsPreLeftUnit.push_back(ptUnit);
				}
				else if (ptUnit->m_iUnitSaveNum == iEndUnit)
				{
					ptNewUnitLine->m_vecPtsNextUnit.push_back(ptUnit);
				}
			}
			
			ptNewUnitLine->m_iConnectPrePtIndex = iStartIndex;
			ptNewUnitLine->m_iConnectNextPtIndex = iEndIndex;

			ptNewUnitLine->m_bIsConnect = TRUE;

			m_listUnitLines.AddTail(ptNewUnitLine);

		}

		
		// 讀取背景資訊
		// 是否更改背景圖片
		CString strBuff;
		GetPrivateProfileString(_T("BackgroundInfo"), _T("IsChange"), _T("NULL"), strBuff.GetBuffer(MAX_PATH), MAX_PATH, strLoadFilePath);
		strBuff.ReleaseBuffer();
		CString strIsChaneBG = strBuff.GetBuffer(0);
		BOOL bIsChangeBG = (strIsChaneBG.CompareNoCase(_T("TRUE")) == 0);
		g_bShowRegionBgImgChange = bIsChangeBG;

		// 讀取背景圖片位址
		GetPrivateProfileString(_T("BackgroundInfo"), _T("BackgroundPath"), _T("NULL"), strBuff.GetBuffer(MAX_PATH), MAX_PATH, strLoadFilePath);
		strBuff.ReleaseBuffer();
		CString strPathBG = strBuff.GetBuffer(0);
		if (strPathBG != _T("NULL"))
		{
			m_strShowRegionImgBgPath = strPathBG;
		}

		// 讀取背景顏色設置
		int iColorR = GetPrivateProfileInt(_T("BackgroundInfo"), _T("BackgroundColorR"), -1, strLoadFilePath);
		int iColorG = GetPrivateProfileInt(_T("BackgroundInfo"), _T("BackgroundColorG"), -1, strLoadFilePath);
		int iColorB = GetPrivateProfileInt(_T("BackgroundInfo"), _T("BackgroundColorB"), -1, strLoadFilePath);

		m_colorShowRegionBg = RGB(iColorR, iColorG, iColorB);


		// 更新操作視窗	
		Invalidate();
		UpdateWindow();

	}
	else
	{

		AfxMessageBox(_T("Cancel"));
	}
}
