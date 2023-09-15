
// MFCSimulatorDlg.h: 標頭檔
//

#include "math.h"

#pragma once

#include "UnitBase.h"

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
	
	COLORREF m_colorShowRegionBg;							// 顯示區背景初始顏色
	CString m_strShowRegionImgBgPath;						// 顯示區背景圖片路徑
	HBITMAP m_hBitmapImgBg;									// 顯示區背景圖片

	int m_iInUnitCount;									    // 計算元件 IN 個數 
	CList<CRect, CRect&> m_listInUnit;                      // 記錄生成的 IN 元件
	CList<CRect, CRect&> m_listInUnitBg;					// 記錄生成的 IN 元件背景矩形

	CList<CRect, CRect&> m_listOutUnit;
	CList<CRect, CRect&> m_listOutUnitBg;


	CList<UnitBase*, UnitBase*> m_listUnitPointers;         // 紀錄已生成的元件
	UnitBase* m_ptMovingUnit;                                // 紀錄正在被滑鼠拖曳的指標


	//CPoint m_pointInUnitStartPos;						    // IN 元件被拖動的起始點
	//CPoint m_pointOutUnitStartPos;                        // OUT 元件被拖動的起始點

	CPoint m_pointMouseStartPos;                            // 紀錄滑鼠按下左鍵當下位置 


	BOOL m_bIsDragging;                                     // 記錄元件是否被拖動


	afx_msg void OnBnClickedButtonBgImg();					// 調整顯示區背景圖片
	afx_msg void OnBnClickedButtonBgColor();				// 調整顯示區背景顏色


	CRect GetUnitRect(CPoint ptLeftTop);                    // 經由左上角點定位，得到元件矩形

	CStatic m_staticShowRegion;								// 顯示區成員控件

	CButton m_buttonIN;										// 輸入函數元件 IN 
	CButton m_buttonOUT;
	CButton m_buttonAND;
	CButton m_buttonOR;
	CButton m_buttonNOT;
	CButton m_buttonFUN;
	
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);



	void DrawToBuffer(CDC* pDC);							// 雙緩衝更新區域函數

	
	void UnitInWindow();                                    // 開啟函數選擇視窗


	afx_msg void OnBnClickedButtonIn();						// 新增 IN 元件按鈕
	afx_msg void OnBnClickedButtonOut();                    // 新增 OUT 元件按鈕
	afx_msg void OnBnClickedButtonAnd();                    // 新增 AND 元件按鈕
	afx_msg void OnBnClickedButtonOr();                     // 新增 OR 元件按鈕
	afx_msg void OnBnClickedButtonNot();                    // 新增 NOT 元件按鈕
	afx_msg void OnBnClickedButtonFun();                    // 新增 FUN 元件按鈕
	afx_msg void OnBnClickedButtonLine();                   // 新增連線模式按鈕

};
