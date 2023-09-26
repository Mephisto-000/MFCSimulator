// UnitInDlg.cpp: 實作檔案
//

#include "pch.h"
#include "MFCSimulator.h"
#include "afxdialogex.h"
#include "UnitInDlg.h"

#include "UnitIn.h"
#include "MFCSimulatorDlg.h"

// UnitInDlg 對話方塊

IMPLEMENT_DYNAMIC(UnitInDlg, CDialogEx)

UnitInDlg::UnitInDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_UNIT_IN, pParent)
{
	m_strFunChoose = _T("請選擇輸入");
	m_fontChooseText.CreatePointFont(100, _T("Calibri"));
}

UnitInDlg::~UnitInDlg()
{
}

void UnitInDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_SHOW_CHOOSE, m_editShowChoose);
	DDX_Text(pDX, IDC_EDIT_SHOW_CHOOSE, m_strFunChoose);
}


BEGIN_MESSAGE_MAP(UnitInDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_IN_FALSE, &UnitInDlg::OnBnClickedButtonInFalse)
	ON_BN_CLICKED(IDC_BUTTON_IN_TRUE, &UnitInDlg::OnBnClickedButtonInTrue)
	ON_BN_CLICKED(IDC_BUTTON_IN_SIN, &UnitInDlg::OnBnClickedButtonInSin)
	ON_BN_CLICKED(IDC_BUTTON_IN_COS, &UnitInDlg::OnBnClickedButtonInCos)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDOK, &UnitInDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &UnitInDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// UnitInDlg 訊息處理常式


BOOL UnitInDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此加入額外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX 屬性頁應傳回 FALSE
}




HBRUSH UnitInDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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



// Sine 函式按鈕
void UnitInDlg::OnBnClickedButtonInSin()
{
	
	// 更新選擇的函式值
	m_strFunChoose = _T("sin(t)");
	UpdateData(FALSE);

}


// Cosine 函式按鈕
void UnitInDlg::OnBnClickedButtonInCos()
{

	m_strFunChoose = _T("cos(t)");
	UpdateData(FALSE);

}


// True 按鈕
void UnitInDlg::OnBnClickedButtonInTrue()
{

	m_strFunChoose = _T("true");
	UpdateData(FALSE);

}


// False 按鈕
void UnitInDlg::OnBnClickedButtonInFalse()
{

	m_strFunChoose = _T("false");
	UpdateData(FALSE);

}



void UnitInDlg::OnBnClickedOk()
{
	// TODO: 在此加入控制項告知處理常式程式碼

	// 將選擇的函式傳入父視窗
	CMFCSimulatorDlg* parentDlg = (CMFCSimulatorDlg*)GetParent();
	parentDlg->m_strFunOrOperChoose = m_strFunChoose;


	CDialogEx::OnOK();
}


void UnitInDlg::OnBnClickedCancel()
{
	// TODO: 在此加入控制項告知處理常式程式碼




	CDialogEx::OnCancel();
}
