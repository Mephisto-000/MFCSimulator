
// MFCSimulatorDlg.h: 標頭檔
//

#include "math.h"
#include <vector>

#pragma once

#include "UnitBase.h"
#include "UnitLine.h"

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



	CList<UnitBase*, UnitBase*> m_listUnitPointers;         // 紀錄已生成的元件
	CList<UnitLine*, UnitLine*> m_listUnitLines;            // 紀錄連接線

	UnitBase* m_ptPreMovingUnit;							// 紀錄前一個點選的指標
	UnitBase* m_ptMovingUnit;                               // 紀錄正在被滑鼠拖曳的指標，拖曳控件的情況
	UnitLine* m_ptMovingLine;								// 紀錄正在被滑鼠拖曳的指標，拖曳連接線的情況

	// 連線狀態中，元件指標連接用:
	UnitBase* m_ptPreUnit;                                  // 紀錄連接的起點元件指標
	UnitBase* m_ptNextUnit;									// 紀錄連接的終點元件指標


	double TwoPtsDistance(CPoint pointStart, CPoint pointEnd);                           // 計算兩點距離
	double PointToLineDistance(CPoint pointMouse, CPoint pointStart, CPoint pointEnd);   // 計算滑鼠座標點到線段距離


	int m_iOffsetX;                                         // 拖曳X位移
	int m_iOffsetY;											// 拖曳Y位移


	CPoint m_pointMouseStartPos;                            // 紀錄滑鼠按下左鍵當下位置
	CPoint m_pointMovingMouse;                              // 紀錄拖曳線當中，還未連接到另一個元件的滑鼠點


	BOOL m_bIsDragging;                                     // 記錄元件是否被拖動
	BOOL m_bIsLineMode;                                     // 紀錄是否開啟連線模式


	afx_msg void OnBnClickedButtonBgImg();					// 調整顯示區背景圖片
	afx_msg void OnBnClickedButtonBgColor();				// 調整顯示區背景顏色


	CRect GetUnitRect(CPoint ptLeftTop);                    // 經由左上角點定位，得到元件矩形
	
	std::vector<CRect> GetConnectRects(UnitBase* ptUnit);   // 經由左上角點定位，得到元件接點外接矩形

	void DrawConnectLine(UnitBase* ptUnit, CDC* pDC);       // 根據前後連接的指標畫出連接線段

	CStatic m_staticShowRegion;								// 顯示區成員控件
	CStatic m_staticLineState;                              // 連線模式的狀態
	CStatic m_staticLineModeText;

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
	afx_msg void OnBnClickedButtonLine();                   // 開關連線模式按鈕
	afx_msg void OnBnClickedButtonDelete();                 // 刪除元件或線段按鈕



	CString GetCurrentDir();                                // 取得 MFCSimulatorDlg.cpp 的絕對路徑

	CFont m_fontLineModeState;                              // 自定 Line Mode 狀態字型
	CFont m_fontLineModeText;								// 自定 Line Mode 標題字型

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

};
