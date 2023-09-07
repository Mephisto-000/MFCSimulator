
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
	int m_iInButtonsCount;

	afx_msg void OnBnClickedButtonBgImg();                    // 調整顯示區背景圖片
	afx_msg void OnBnClickedButtonBgColor();				  // 調整顯示區背景顏色
	afx_msg void OnBnClickedButtonIn();                       // 

	CStatic m_staticShowRegion;								  //
	CButton m_buttonIN;										  //

	
	BOOL m_bDragging;
	CPoint m_ptLastMousePos;
	/*CButton* m_pDragButton;*/

	CButton* m_pDraggedButton;
	

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);


	static LRESULT CALLBACK ButtonSubclassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);
};
