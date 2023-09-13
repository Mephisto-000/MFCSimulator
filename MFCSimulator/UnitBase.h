#pragma once

#include <vector>

class UnitBase
{

protected:
	
	std::vector<UnitBase*> m_arrPtsPreUnit;               // 指向前一個元件的指標陣列
	std::vector<UnitBase*> m_arrPtsNextUnit;              // 指向下一個元件的指標陣列
														  
	CString m_UnitID;                                     // 確認是哪一種元件
														  
public:													  
														  
	CPoint pointUnitLocation;                             // 元件位置
	std::vector<CPoint> m_pointLineLocation;              // 線段連接點位置
	BOOL m_bConnectPoint;                                 // 確認是否被連接
	int m_iUnitHeight;                                    // 元件長
	int m_iUnitWidth;                                     // 元件寬
	double m_dOutValue;                                   // 輸出的數值
	




	// 建構子
	UnitBase (UnitBase* ptPreUnit, CString strUnitID, CRect rectShowRegion, CRect rectButton);

	// 解構子
	~UnitBase ();



	// 元件之間插入元件
	void InsertUnit(UnitBase* ptPreUnit, CString strUnitID, CRect rectButton);



	//// 記錄線段資料
	//void InsertLineData();

	//// 記錄線段點資料
	//void InsertDotData();
};

