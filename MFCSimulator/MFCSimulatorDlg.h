
// MFCSimulatorDlg.h: 標頭檔
//

#pragma once


// CMFCSimulatorDlg 對話方塊
class CMFCSimulatorDlg : public CDialogEx
{
// 建構
public:
	CMFCSimulatorDlg(CWnd* pParent = nullptr);	// 標準建構函式

// 對話方塊資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCSIMULATOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支援


// 程式碼實作
protected:
	HICON m_hIcon;

	// 產生的訊息對應函式
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	
	COLORREF m_colorShowRegionBg;			                  // 顯示區背景初始顏色
	CString m_strShowRegionImgBgPath;						  // 顯示區背景圖片路徑
	HBITMAP m_hBitmapImgBg;

	afx_msg void OnBnClickedButtonBgImg();                    // 調整顯示區背景圖片
	afx_msg void OnBnClickedButtonBgColor();				  // 調整顯示區背景顏色
	
	CStatic m_staticShowRegion;
};
