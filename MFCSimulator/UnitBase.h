#pragma once

#include "math.h"
#include <vector>

class UnitBase
{

protected:
	
	std::vector<UnitBase*> m_arrPtsPreUnit;               // 指向前一個元件的指標陣列
	std::vector<UnitBase*> m_arrPtsNextUnit;              // 指向下一個元件的指標陣列
														  
														  
public:													  
	
	// 元件資料
	CPoint m_pointUnitLocation;                           // 元件位置，元件矩形左上角的點
	int m_iUnitHeight;                                    // 元件長
	int m_iUnitWidth;                                     // 元件寬
	CString m_strUnitID;                                     // 元件類型
	BOOL m_bMoveState;                                    // 確認是否被拖曳
	
	// 輸出處理
	CString m_strFuncOrOpera;							  // 紀錄選擇的函數或是運算元
	double m_dOutValue;                                   // 輸出的數值

	// 線段資料
	std::vector<CPoint> m_arrConnectPt;				      // 線段連接點位置
	BOOL m_bConnectPoint;                                 // 確認是否被連接
	



	// 建構子
	UnitBase (CRect rectShowRegion, CRect rectButton);


	// 解構子
	~UnitBase ();


	// 設置選擇的函數或是四則運算元
	virtual void SetFuncOrOpera(CString strChoose) = 0;


	// 更新連接的元件
	virtual void InsertUnit(UnitBase* ptNewUnit) = 0;

	
	// 根據拖曳位置更新線段點資料
	virtual void UpdateDotData(CPoint pointNewLocation) = 0;


	// 輸出元件的結果
	virtual void Result(double dRealTimeValue) = 0;
};

