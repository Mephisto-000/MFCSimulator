
// MFCSimulatorDlg.cpp: 實作檔案
//

#include "pch.h"
#include "framework.h"
#include "MFCSimulator.h"
#include "MFCSimulatorDlg.h"
#include "afxdialogex.h"
#include "UnitInDlg.h"

#include "UnitIN.h"
#include "UnitOUT.h"
#include "UnitAND.h"
#include "UnitOR.h"
#include "UnitNOT.h"
#include "UnitFUN.h"


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
END_MESSAGE_MAP()


// CMFCSimulatorDlg 對話方塊


CMFCSimulatorDlg::CMFCSimulatorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCSIMULATOR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_colorShowRegionBg = RGB(255, 255, 255);
	m_strShowRegionImgBgPath = _T("test1.bmp");
	m_bIsDragging = FALSE;
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



	return TRUE;  // 傳回 TRUE，除非您對控制項設定焦點
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

		//if (m_hBitmapImgBg != nullptr)
		//{
		//	memBitmap.Attach(m_hBitmapImgBg);
		//	BITMAP bmp;
		//	memBitmap.GetBitmap(&bmp);
		//}



		memDC.CreateCompatibleDC(pdcShowRegion);
		memBitmap.CreateCompatibleBitmap(pdcShowRegion, iWidthShowRegion, iHeightShowRegion);

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


	// TODO : 雙緩衝圖片被洗掉問題
	// 判斷是否更改操作視窗背景圖片，有的話就更新背景並顯示出來
	if (g_bShowRegionBgImgChange == TRUE)
	{
		//m_staticShowRegion.ModifyStyle(1, SS_BITMAP);
		//m_staticShowRegion.SetBitmap(m_hBitmapImgBg);
		//m_staticShowRegion.ShowWindow(SW_SHOW);


		m_staticShowRegion.ModifyStyle(1, SS_BITMAP);
		m_staticShowRegion.SetBitmap(m_hBitmapImgBg);
		m_staticShowRegion.ShowWindow(SW_SHOW);

	}
	



	// 元件矩形顏色 : 
	CBrush brushInRect;
	brushInRect.CreateSolidBrush(RGB(192, 192, 192));  // 灰色

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->SelectObject(&brushInRect);


	POSITION posiUnit = m_listUnitPointers.GetHeadPosition();

	while (posiUnit != nullptr)
	{

		UnitBase* ptUnit = m_listUnitPointers.GetNext(posiUnit);

		CPoint pointUnitLeftTop = ptUnit->m_pointUnitLocation;
		
		CRect rectUnit = GetUnitRect(pointUnitLeftTop);

		pDC->Rectangle(rectUnit);
		pDC->FillRect(&rectUnit, &brushInRect);
		pDC->SetBkMode(TRANSPARENT);
		pDC->TextOut((rectUnit.left + rectUnit.right) * 0.5 - 8, (rectUnit.top + rectUnit.bottom) * 0.5 - 8, 
			ptUnit->m_strUnitID);
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
		Invalidate();
		UpdateWindow();	
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
	m_listUnitPointers.AddHead(ptNewUnitIN);

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
	m_listUnitPointers.AddHead(ptNewUnitOUT);

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
	m_listUnitPointers.AddHead(ptNewUnitAND);

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
	m_listUnitPointers.AddHead(ptNewUnitOR);

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
	m_listUnitPointers.AddHead(ptNewUnitNOT);

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
	m_listUnitPointers.AddHead(ptNewUnitFUN);

	// 更新操作視窗	
	Invalidate();
	UpdateWindow(); 
}


// 開啟連線模式
void CMFCSimulatorDlg::OnBnClickedButtonLine()
{
	// TODO: 在此加入控制項告知處理常式程式碼
}


void CMFCSimulatorDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// 得到操作視窗矩形資訊
	CRect rectShowRegion;
	GetDlgItem(IDC_STATIC_SHOW_REGION)->GetWindowRect(&rectShowRegion);

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
		
		if (rectUnit.PtInRect(point))
		{	// 確認滑鼠是否點取元件

			// 更新被拖曳元件的狀態
			ptUnit->m_bMoveState = TRUE;
			
			// 點取元件時，滑鼠產生十字的圖案
			SetCursor(LoadCursor(NULL, IDC_SIZEALL));

			// 開啟拖曳的狀態
			m_bIsDragging = TRUE;

			// 更新滑鼠位置
			m_pointMouseStartPos = point;

			m_ptMovingUnit = ptUnit;

			break;
		}
	}	

	CDialogEx::OnLButtonDown(nFlags, point);
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

		//
		int iOffsetX = point.x - m_pointMouseStartPos.x;
		int iOffsetY = point.y - m_pointMouseStartPos.y;



		m_ptMovingUnit->m_pointUnitLocation.Offset(iOffsetX, iOffsetY);

		m_pointMouseStartPos = point;

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
	
		point = NULL;

		m_bIsDragging = FALSE;

		// 得到內含已創建元件的指針的 CList ，並取得 CList 的位置指針
		POSITION posiUnit = m_listUnitPointers.GetHeadPosition();

		while (posiUnit != nullptr)
		{	// 走訪 CList 內的所有元素

			UnitBase* ptUnit = m_listUnitPointers.GetNext(posiUnit);

			// 得到元件的矩形
			CRect rectUnit = GetUnitRect(ptUnit->m_pointUnitLocation);

			if (ptUnit->m_bMoveState = TRUE)
			{
				ptUnit->m_bMoveState = FALSE;

				break;
			}

		}

		// 釋放滑鼠擷取
		ReleaseCapture();

	}

	CDialogEx::OnLButtonUp(nFlags, point);
}
















// 開啟視窗
BOOL CAboutDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此加入額外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX 屬性頁應傳回 FALSE
}



