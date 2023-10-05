#pragma once

#include "math.h"
#include <vector>



class CUnitBase
{

																												  
public:			

	// 元件連接資料
	std::vector<CUnitBase*> m_vecPtsPreLeftUnit;						// 指向前一個左邊分支元件的指標陣列，或是只有單一指向前一個分支元件的指標陣列
	std::vector<CUnitBase*>  m_vecPtsPreRightUnit;						// 指向前一個右邊分支元件的指標陣列	
	std::vector<CUnitBase*> m_vecPtsNextUnit;							// 指向下一個元件的指標陣列


	// 元件資料
	CPoint m_pointUnitLocation;											// 元件位置，元件矩形左上角的點
	int m_iUnitHeight;													// 元件長
	int m_iUnitWidth;													// 元件寬
	CString m_strUnitID;												// 元件類型
	BOOL m_bMoveState;													// 確認是否被拖曳
	BOOL m_bFocusState;													// 確認是否被點取
	int m_iUnitSaveNum;													// 記錄元件生成順序序號
	

	// 輸出處理
	CString m_strFuncOrOpera;											// 記錄選擇的函數或是運算元
	double m_dOutValue;													// 輸出的數值


	// 連接點資料 
	// 用於分辨左右支點 : 
	CPoint m_pointConnectLeftTop;										// 左上角連接點或頂部中間連接點
	CPoint m_pointConnectRightTop;										// 右上角連接點
	CPoint m_pointConnectBottom;										// 底部連接點

	CRect m_rectConnectLeftTop;											// 左上連接點矩形或頂部中間連接點矩形
	CRect m_rectConnectRightTop;										// 右上連接點矩形
	CRect m_rectConnectBottom;											// 底部連接點矩形

	int m_iConnectPtRadius;												// 連接點半徑
	BOOL m_bConnectPoint;												// 確認是否被連接


	// 用於繪圖 : 
	std::vector<CPoint> m_vecConnectPt;									// 儲存連接點點資訊
	std::vector<CRect> m_vecConnectPtRect;								// 儲存連接點外切矩形資訊
	int m_iConnectPtAmount;												// 儲存的線段連接點數量
	int m_iConnectPtRectAmount;											// 儲存的線段連接點矩形數量
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// 建構子
	CUnitBase (CRect rectShowRegion, CRect rectButton);


	// 解構子
	~CUnitBase ();


	// 根據元件類型和拖曳後的位移，更新連接點與其外切矩形的位置
	virtual void SetConnectPtAndRect (int iOffsetX, int iOffsetY) {};


};

