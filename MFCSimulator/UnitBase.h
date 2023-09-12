#pragma once

#include <vector>

class UnitBase
{

private:
	
	UnitBase* m_ptPreUnit;
	UnitBase* m_ptNextUnit;
	std::vector<UnitBase*> m_arrPtsPreUnit;
	std::vector<UnitBase*> m_arrPtsNextUnit;


public:

	CPoint pointUnitLocation;
	int iUnitHeight;
	int iUnitWidth;

	UnitBase (int iWidthShowRegion, int iHeightShowRegion, int iWidthUnit, int iHeightUnit);

	~UnitBase ();

	// 刪除元件之間的元件
	// unitBaseHeadRef : 頭節點指標
	// del : 標記節點全部刪除的指標
	void DeleteUnit (UnitBase** ptUnitBaseHeadRef, UnitBase* ptDel);

	void InorderTraversal(UnitBase* unitBase);

	// 元件之間插入元件
	void InsertUnit(UnitBase* unitBase, int iNewShowRegW, int iNewShowRegH, int iNewButtonW, int iNewButtonH);


};

