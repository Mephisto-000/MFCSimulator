// UnitFunDlg.cpp: 實作檔案
//

#include "pch.h"
#include "MFCSimulator.h"
#include "afxdialogex.h"
#include "CUnitFunDlg.h"
#include "MFCSimulatorDlg.h"

// UnitFunDlg 對話方塊

IMPLEMENT_DYNAMIC(CUnitFunDlg, CDialogEx)

CUnitFunDlg::CUnitFunDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_UNIT_FUN, pParent)
{
	m_strOperaChoose = _T("+");
	m_strOperaFinalChoose = _T("+");
	m_fontChooseText.CreatePointFont(90, _T("Calibri"));
}

CUnitFunDlg::~CUnitFunDlg()
{
}

void CUnitFunDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_OPERA_CHOOSE, m_editOperaChoose);
	DDX_Text(pDX, IDC_EDIT_OPERA_CHOOSE, m_strOperaChoose);
}


BEGIN_MESSAGE_MAP(CUnitFunDlg, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_FUN_PLUS, &CUnitFunDlg::OnBnClickedButtonFunPlus)
	ON_BN_CLICKED(IDC_BUTTON_FUN_MINUS, &CUnitFunDlg::OnBnClickedButtonFunMinus)
	ON_BN_CLICKED(IDC_BUTTON_FUN_MULTIPLY, &CUnitFunDlg::OnBnClickedButtonFunMultiply)
	ON_BN_CLICKED(IDC_BUTTON_FUN_DIVISION, &CUnitFunDlg::OnBnClickedButtonFunDivision)
	ON_BN_CLICKED(IDOK, &CUnitFunDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CUnitFunDlg::OnBnClickedCancel)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// UnitFunDlg 訊息處理常式


BOOL CUnitFunDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此加入額外的初始化

	m_strOperaFinalChoose = m_strOperaChoose;

	m_editOperaChoose.SetWindowText(m_strOperaChoose);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX 屬性頁應傳回 FALSE
}


HBRUSH CUnitFunDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此變更 DC 的任何屬性

	if (pWnd->GetDlgCtrlID() == IDC_EDIT_OPERA_CHOOSE)
	{
		pDC->SetTextColor(RGB(0, 0, 0));
		pDC->SelectObject(&m_fontChooseText);
	}

	// TODO:  如果預設值並非想要的，則傳回不同的筆刷
	return hbr;
}


// 選擇加法運算元按鈕
void CUnitFunDlg::OnBnClickedButtonFunPlus()
{

	// 更新選擇的函式值
	m_strOperaChoose = _T("+");
	UpdateData(FALSE);

}


// 選擇減法運算元按鈕
void CUnitFunDlg::OnBnClickedButtonFunMinus()
{

	// 更新選擇的函式值
	m_strOperaChoose = _T("-");
	UpdateData(FALSE);

}


// 選擇乘法運算元按鈕
void CUnitFunDlg::OnBnClickedButtonFunMultiply()
{

	// 更新選擇的函式值
	m_strOperaChoose = _T("X");
	UpdateData(FALSE);

}


// 選擇除法運算元按鈕
void CUnitFunDlg::OnBnClickedButtonFunDivision()
{

	// 更新選擇的函式值
	m_strOperaChoose = _T("/");
	UpdateData(FALSE);

}


// 確認選擇的運算元
void CUnitFunDlg::OnBnClickedOk()
{

	m_strOperaFinalChoose = m_strOperaChoose;

	// 將選擇的函式傳入父視窗
	CMFCSimulatorDlg* parentDlg = (CMFCSimulatorDlg*)GetParent();
	parentDlg->m_strFunOrOperChoose = m_strOperaFinalChoose;

	CDialogEx::OnOK();

}

// 取消選擇運算元，使用預設的加法運算元
void CUnitFunDlg::OnBnClickedCancel()
{

	// 將預設的函式傳入父視窗
	CMFCSimulatorDlg* parentDlg = (CMFCSimulatorDlg*)GetParent();
	parentDlg->m_strFunOrOperChoose = m_strOperaFinalChoose;

	CDialogEx::OnCancel();
}


// 沒有按下確認按鈕，直接關閉視窗的話，用預設的加法運算元
void CUnitFunDlg::OnDestroy()
{

	CDialogEx::OnDestroy();

	// 將預設的函式傳入父視窗
	CMFCSimulatorDlg* parentDlg = (CMFCSimulatorDlg*)GetParent();
	parentDlg->m_strFunOrOperChoose = m_strOperaFinalChoose;

}

