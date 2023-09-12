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

	// �R�����󤧶�������
	// unitBaseHeadRef : �Y�`�I����
	// del : �аO�`�I�����R��������
	void DeleteUnit (UnitBase** ptUnitBaseHeadRef, UnitBase* ptDel);

	void InorderTraversal(UnitBase* unitBase);

	// ���󤧶����J����
	void InsertUnit(UnitBase* unitBase, int iNewShowRegW, int iNewShowRegH, int iNewButtonW, int iNewButtonH);


};

