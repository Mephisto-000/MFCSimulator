// UnitInDlg.cpp: 實作檔案
//

#include "pch.h"
#include "MFCSimulator.h"
#include "afxdialogex.h"
#include "CUnitInDlg.h"
#include "CUnitIn.h"
#include "MFCSimulatorDlg.h"

// UnitInDlg 對話方塊

IMPLEMENT_DYNAMIC(CUnitInDlg, CDialogEx)

CUnitInDlg::CUnitInDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_UNIT_IN, pParent)
{
	m_strFunChoose = _T("true");
	m_fontChooseText.CreatePointFont(100, _T("Calibri"));
}


CUnitInDlg::~CUnitInDlg()
{
}


void CUnitInDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_SHOW_CHOOSE, m_editShowChoose);
	DDX_Text(pDX, IDC_EDIT_SHOW_CHOOSE, m_strFunChoose);
}


BEGIN_MESSAGE_MAP(CUnitInDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_IN_FALSE, &CUnitInDlg::OnBnClickedButtonInFalse)
	ON_BN_CLICKED(IDC_BUTTON_IN_TRUE, &CUnitInDlg::OnBnClickedButtonInTrue)
	ON_BN_CLICKED(IDC_BUTTON_IN_SIN, &CUnitInDlg::OnBnClickedButtonInSin)
	ON_BN_CLICKED(IDC_BUTTON_IN_COS, &CUnitInDlg::OnBnClickedButtonInCos)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDOK, &CUnitInDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CUnitInDlg::OnBnClickedCancel)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// UnitInDlg 訊息處理常式


BOOL CUnitInDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此加入額外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX 屬性頁應傳回 FALSE
}


HBRUSH CUnitInDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此變更 DC 的任何屬性

	if (pWnd->GetDlgCtrlID() == IDC_EDIT_SHOW_CHOOSE)
	{
		pDC->SetTextColor(RGB(0, 0, 0));
		pDC->SelectObject(&m_fontChooseText);
	}

	// TODO:  如果預設值並非想要的，則傳回不同的筆刷
	return hbr;
}


// 選擇 sin(t) 函式按鈕
void CUnitInDlg::OnBnClickedButtonInSin()
{
	
	// 更新選擇的函式值
	m_strFunChoose = _T("sin(t)");
	UpdateData(FALSE);

}


// 選擇 cos(t) 函式按鈕
void CUnitInDlg::OnBnClickedButtonInCos()
{

	m_strFunChoose = _T("cos(t)");
	UpdateData(FALSE);

}


// 選擇 true(1) 按鈕
void CUnitInDlg::OnBnClickedButtonInTrue()
{

	m_strFunChoose = _T("true");
	UpdateData(FALSE);

}


// False 按鈕
void CUnitInDlg::OnBnClickedButtonInFalse()
{

	m_strFunChoose = _T("false");
	UpdateData(FALSE);

}


// 確認選擇的函式或是數值
void CUnitInDlg::OnBnClickedOk()
{

	// 將選擇的函式傳入父視窗
	CMFCSimulatorDlg* parentDlg = (CMFCSimulatorDlg*)GetParent();
	parentDlg->m_strFunOrOperChoose = m_strFunChoose;
	
	CDialogEx::OnOK();

}


// 取消選擇運算元，使用預設的 true(1) 數值
void CUnitInDlg::OnBnClickedCancel()
{

	// 將預設的函式傳入父視窗
	CMFCSimulatorDlg* parentDlg = (CMFCSimulatorDlg*)GetParent();
	parentDlg->m_strFunOrOperChoose = m_strFunChoose;

	CDialogEx::OnCancel();

}


// 沒有按下確認按鈕，直接關閉視窗的話，用預設的 true(1) 數值
void CUnitInDlg::OnDestroy()
{
	
	CDialogEx::OnDestroy();

	// 將預設的函式傳入父視窗
	CMFCSimulatorDlg* parentDlg = (CMFCSimulatorDlg*)GetParent();
	parentDlg->m_strFunOrOperChoose = m_strFunChoose;

}

