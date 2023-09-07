
// MFCSimulatorDlg.cpp: 實作檔案
//

#include "pch.h"
#include "framework.h"
#include "MFCSimulator.h"
#include "MFCSimulatorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BOOL g_bShowRegionBgImgChange = FALSE;

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
	m_strShowRegionImgBgPath = _T("");
	m_bDragging = FALSE;
	m_pDraggedButton = NULL;
}

void CMFCSimulatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_SHOW_REGION, m_staticShowRegion);
	DDX_Control(pDX, IDC_BUTTON_IN, m_buttonIN);
}

BEGIN_MESSAGE_MAP(CMFCSimulatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_BG_IMG, &CMFCSimulatorDlg::OnBnClickedButtonBgImg)
	ON_BN_CLICKED(IDC_BUTTON_BG_COLOR, &CMFCSimulatorDlg::OnBnClickedButtonBgColor)
	ON_BN_CLICKED(IDC_BUTTON_IN, &CMFCSimulatorDlg::OnBnClickedButtonIn)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
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

		// 取得顯示區矩形資訊
		CWnd* pShowRegion = GetDlgItem(IDC_STATIC_SHOW_REGION);
		CRect rectShowRegion;
		pShowRegion->GetClientRect(&rectShowRegion);

		// 取得顯示區 dc
		CPaintDC dcShowRegion(pShowRegion);
		CBrush brushShowRegion;
		CBrush* pOldbrushShowRegion = dcShowRegion.SelectObject(&brushShowRegion);

		// 顯示區初始上色
		brushShowRegion.CreateSolidBrush(m_colorShowRegionBg);
		dcShowRegion.Rectangle(rectShowRegion);
		dcShowRegion.FillRect(&rectShowRegion, &brushShowRegion);
		dcShowRegion.SelectObject(pOldbrushShowRegion);

		if (g_bShowRegionBgImgChange == TRUE)
		{
			m_staticShowRegion.ModifyStyle(NULL, SS_BITMAP);
			m_staticShowRegion.SetBitmap(m_hBitmapImgBg);
			m_staticShowRegion.ShowWindow(SW_SHOW);
		}

		g_bShowRegionBgImgChange = FALSE;
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
	}

	g_bShowRegionBgImgChange = TRUE;

	Invalidate();
	UpdateWindow();
}

// 設定操作視窗背景顏色
void CMFCSimulatorDlg::OnBnClickedButtonBgColor()
{
	// 初始挑選顏色為紅色
	COLORREF colorSelect = RGB(255, 0, 0);

	// 建立顏色挑選視窗
	CColorDialog colorDlg(colorSelect);


	if (IDOK == colorDlg.DoModal())
	{	// 顯示顏色挑選視窗，判斷是否按下確定

		// 得到顏色挑選視窗中挑選的顏色值
		colorSelect = colorDlg.GetColor();

		// 設置背景顏色
		m_colorShowRegionBg = colorSelect;
	}

	// 更新顯示區	
	Invalidate();
	UpdateWindow();
}

// 函數輸入鈕 "IN"
//void CMFCSimulatorDlg::OnBnClickedButtonIn()
//{
//	CButton* pNewButton = new CButton();
//	CString strButtonText = _T("IN");
//
//	/*DWORD dwStyle = WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON;*/
//
//	DWORD dwStyle = WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON;
//
//	CRect rectShowRegion;
//	GetDlgItem(IDC_STATIC_SHOW_REGION)->GetWindowRect(&rectShowRegion);
//	ScreenToClient(&rectShowRegion);
//
//	CRect rectNewInButtons;
//	GetDlgItem(IDC_BUTTON_IN)->GetWindowRect(&rectNewInButtons);
//
//	int iNewInButtonH = rectNewInButtons.Height();
//	int iNewInButtonW = rectNewInButtons.Width();
//
//	int iNewInButtonX = rectShowRegion.left + (rectShowRegion.Width() - iNewInButtonW) * 0.5;
//	int iNewInButtonY = rectShowRegion.top + (rectShowRegion.Height() - iNewInButtonH) * 0.5 + m_iInButtonsCount * 50;
//
//
//	
//
//	pNewButton->Create(strButtonText, dwStyle, CRect(iNewInButtonX, iNewInButtonY, iNewInButtonX + iNewInButtonW, iNewInButtonY +iNewInButtonH)
//		, this, 100 + m_iInButtonsCount);
//
//	m_iInButtonsCount++;
//
//	pNewButton->ShowWindow(SW_SHOW);
//
//}


LRESULT CALLBACK CMFCSimulatorDlg::ButtonSubclassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
	switch (uMsg)
	{
	case WM_LBUTTONDOWN:
	{
		// 得到 CMFCSimulatorDlg 的實例
		CMFCSimulatorDlg* pDlg = (CMFCSimulatorDlg*)CWnd::FromHandle(::GetParent(hWnd));

		if (pDlg)
		{
			// 調用 OnLButtonDown 函數處理拖曳邏輯
			CPoint point(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			pDlg->OnLButtonDown(MK_LBUTTON, point);
		}

		break;
	}
	}

	// Always call the original window procedure afterwards.
	return DefSubclassProc(hWnd, uMsg, wParam, lParam);
}



void CMFCSimulatorDlg::OnBnClickedButtonIn()
{
	CButton* pNewButton = new CButton();
	CString strButtonText = _T("IN");

	DWORD dwStyle = WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON;

	CRect rectShowRegion;
	GetDlgItem(IDC_STATIC_SHOW_REGION)->GetWindowRect(&rectShowRegion);
	ScreenToClient(&rectShowRegion);

	CRect rectNewInButtons;
	GetDlgItem(IDC_BUTTON_IN)->GetWindowRect(&rectNewInButtons);

	int iNewInButtonH = rectNewInButtons.Height();
	int iNewInButtonW = rectNewInButtons.Width();

	int iNewInButtonX = rectShowRegion.left + (rectShowRegion.Width() - iNewInButtonW) * 0.5;
	int iNewInButtonY = rectShowRegion.top + (rectShowRegion.Height() - iNewInButtonH) * 0.5 + m_iInButtonsCount * 50;

	pNewButton->Create(strButtonText, dwStyle, CRect(iNewInButtonX, iNewInButtonY, iNewInButtonX + iNewInButtonW, iNewInButtonY + iNewInButtonH)
		, this, 100 + m_iInButtonsCount);

	m_iInButtonsCount++;

	pNewButton->ShowWindow(SW_SHOW);


	SetWindowSubclass(pNewButton->m_hWnd, ButtonSubclassProc, 0, 0);

}




//void CMFCSimulatorDlg::OnLButtonDown(UINT nFlags, CPoint point)
//{
//	CWnd* pWnd = ChildWindowFromPoint(point);
//
//	if (pWnd && pWnd->IsKindOf(RUNTIME_CLASS(CButton)))
//	{
//		m_bDragging = TRUE;
//		m_pDragButton = dynamic_cast<CButton*>(pWnd);
//		m_ptLastMousePos = point;
//
//		SetCapture();
//	}
//
//	CDialogEx::OnLButtonDown(nFlags, point);
//}
//
//
//void CMFCSimulatorDlg::OnLButtonUp(UINT nFlags, CPoint point)
//{
//	
//	if (m_bDragging == TRUE)
//	{
//		ReleaseCapture();
//
//		m_bDragging = FALSE;
//
//		m_pDragButton = nullptr;
//	}
//
//	CDialogEx::OnLButtonUp(nFlags, point);
//}
//
//
//void CMFCSimulatorDlg::OnMouseMove(UINT nFlags, CPoint point)
//{
//	
//	if (m_bDragging && m_pDragButton)
//	{
//		CRect rectButton;
//		m_pDragButton->GetWindowRect(&rectButton);
//		ScreenToClient(&rectButton);
//
//		int iButtonX = point.x - m_ptLastMousePos.x;
//		int iButtonY = point.y - m_ptLastMousePos.y;
//
//		rectButton.OffsetRect(iButtonX, iButtonY);
//		m_pDragButton->MoveWindow(rectButton);
//
//
//		m_ptLastMousePos = point;
//	}
//
//	CDialogEx::OnMouseMove(nFlags, point);
//}



void CMFCSimulatorDlg::OnLButtonDown(UINT nFlags, CPoint point)
{

	//AfxMessageBox(_T("Clicked"));

	CWnd* pWnd = ChildWindowFromPoint(point);
	/*if (pWnd && pWnd != this && pWnd->IsKindOf(RUNTIME_CLASS(CButton)))*/
	if (pWnd && pWnd != this)
	{
		m_pDraggedButton = dynamic_cast<CButton*>(pWnd);
		if (m_pDraggedButton)
		{
			m_bDragging = TRUE;
			m_ptLastMousePos = point;
			SetCapture();
		}
	}
}

void CMFCSimulatorDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_bDragging)
	{
		m_bDragging = FALSE;
		m_pDraggedButton = NULL;
		ReleaseCapture();
	}
}

void CMFCSimulatorDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_bDragging && (nFlags & MK_LBUTTON))
	{
		CRect rcNew;
		m_pDraggedButton->GetWindowRect(&rcNew);
		ScreenToClient(&rcNew);
		CPoint ptDiff = point - m_ptLastMousePos;
		rcNew.OffsetRect(ptDiff);
		m_pDraggedButton->MoveWindow(&rcNew);
		m_ptLastMousePos = point;
	}
}
