
// MFCSimulatorDlg.h: 標頭檔
//

#define _USE_MATH_DEFINES
#include "math.h"
#include <vector>
#include <mmsystem.h>                                   // 包含 timeGetTime 函數的標頭
#include "CUnitBase.h"
#include "CUnitLine.h"

#pragma once

// 加入 mmysystem.h 中的 timeGetTime 時需加入以下連接庫
// "winmm.lib" 是 Windows Multimedia API
#pragma comment(lib, "winmm.lib ")


// CMFCSimulatorDlg 對話方塊
class CMFCSimulatorDlg : public CDialogEx
{
// 建構
public:
	CMFCSimulatorDlg(CWnd* pParent = nullptr);	// 標準建構函式
	~CMFCSimulatorDlg();
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
	
	COLORREF m_colorShowRegionBg;												// 顯示區背景初始顏色
	

	HBITMAP m_hBitmapImgBg;														// 顯示區背景圖片


	int m_iInUnitCount;															// 計算元件 IN 個數 
	int m_iListUnitAmount;														// 記錄已生成元件數量
	int m_iListUnitLineAmount;													// 記錄連接線數量
	int m_iOffsetX;																// 拖曳X位移
	int m_iOffsetY;																// 拖曳Y位移


	double TwoPtsDistance(CPoint pointStart, CPoint pointEnd);                           // 計算兩點距離
	double PointToLineDistance(CPoint pointMouse, CPoint pointStart, CPoint pointEnd);   // 計算滑鼠座標點到線段距離


	CList<CUnitBase*, CUnitBase*> m_listUnitPointers;							// 記錄已生成的元件
	CList<CUnitLine*, CUnitLine*> m_listUnitLines;								// 記錄連接線


	CUnitBase* m_ptPreMovingUnit;												// 記錄前一個點選的指標
	CUnitBase* m_ptMovingUnit;													// 記錄正在被滑鼠拖曳的指標，拖曳控件的情況
	CUnitBase* m_ptPreUnit;														// 記錄在連線模式時，連接的起點元件指標
	CUnitBase* m_ptNextUnit;													// 記錄在連線模式時，連接的終點元件指標	
	

	CUnitLine* m_ptMovingLine;													// 記錄正在被滑鼠拖曳的指標，拖曳連接線的情況


	CPoint m_pointMouseInitialPos;												// 記錄滑鼠按下左鍵一開始的位置
	CPoint m_pointMouseStartPos;												// 記錄滑鼠按下左鍵當下位置
	CPoint m_pointMovingMouse;													// 記錄拖曳線當中，還未連接到另一個元件的滑鼠點


	CRect GetUnitRect(CPoint ptLeftTop);										// 經由左上角點定位，得到元件矩形


	BOOL m_bIsDragging;															// 記錄元件是否被拖動
	BOOL m_bIsLineMode;															// 記錄是否開啟連線模式
	BOOL m_bShowRegionBgImgChange;												// 記錄是否更改背景圖片
	BOOL m_bShowRegionBgRGBChange;												// 記錄是否更改背景顏色


	std::vector<CRect> GetConnectRects(CUnitBase* ptUnit);						// 經由左上角點定位，得到元件接點外接矩形


	CStatic m_staticShowRegion;													// 顯示區成員控件
	CStatic m_staticLineState;													// 連線模式的狀態
	CStatic m_staticLineModeText;												// 連線模式狀態左邊的不變的文字


	CButton m_buttonIN;															// 生成元件 IN 按鈕
	CButton m_buttonOUT;														// 生成元件 OUT 按鈕
	CButton m_buttonAND;														// 生成元件 AND 按鈕
	CButton m_buttonOR;															// 生成元件 OR 按鈕
	CButton m_buttonNOT;														// 生成元件 NOT 按鈕
	CButton m_buttonFUN;														// 生成元件 FUN 按鈕
	CButton m_buttonLINE;														// 開啟/關閉連線模式 按鈕
	

	CString GetCurrentDir();													// 取得 MFCSimulatorDlg.cpp 的絕對路徑
	CString m_strInitSettingPath;                                               // 背景設定檔案
	CString m_strFunOrOperChoose;												// 暫時儲存選擇的函式或是四則運算子
	CString m_strShowRegionImgBgPath;											// 顯示區背景圖片路徑


	CFont m_fontLineModeState;													// 自訂 Line Mode 狀態字型
	CFont m_fontLineModeText;													// 自訂 Line Mode 標題字型


	void DrawToBuffer(CDC* pDC);												// 雙緩衝更新區域函數


	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButtonBgImg();										// 調整顯示區背景圖片
	afx_msg void OnBnClickedButtonBgColor();									// 調整顯示區背景顏色
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);						// 按下滑鼠左鍵
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);					// 雙擊滑鼠左鍵
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);						// 拖曳滑鼠
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);						// 放開滑鼠左鍵
	afx_msg void OnBnClickedButtonIn();											// 生成 IN 元件按鈕
	afx_msg void OnBnClickedButtonOut();										// 生成 OUT 元件按鈕
	afx_msg void OnBnClickedButtonAnd();										// 生成 AND 元件按鈕
	afx_msg void OnBnClickedButtonOr();											// 生成 OR 元件按鈕
	afx_msg void OnBnClickedButtonNot();										// 生成 NOT 元件按鈕
	afx_msg void OnBnClickedButtonFun();										// 生成 FUN 元件按鈕
	afx_msg void OnBnClickedButtonLine();										// 開關連線模式按鈕
	afx_msg void OnBnClickedButtonDelete();										// 刪除元件或線段按鈕
	afx_msg void OnBnClickedButtonSimulate();									// 啟動模擬的按鈕
	afx_msg void OnDestroy();                                                   // 關閉視窗
	afx_msg void OnBnClickedButtonSave();                                       // 存檔按鈕
	afx_msg void OnBnClickedButtonOpen();										// 讀檔按鈕

};

