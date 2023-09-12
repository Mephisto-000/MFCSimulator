#include "pch.h"
#include "UnitBase.h"
#include <cstddef>  // for size_t




// UnitBase �غc�l
UnitBase::UnitBase(int iShowRegW, int iShowRegH, int iButtonWidth, int iButtonHeight)
{
	// ��l�ƫ���
	m_ptPreUnit = nullptr;
	m_ptNextUnit = nullptr;

	// ��l�ƫ��а}�C
	m_arrPtsPreUnit.clear();
	m_arrPtsNextUnit.clear();

	pointUnitLocation = CPoint(iShowRegW * 0.5, iShowRegH * 0.5);
	iUnitWidth = iButtonWidth;
	iUnitHeight = iButtonHeight;

}


// UnitBase �Ѻc�l
UnitBase::~UnitBase()
{
	//UnitBase* ptCurUnit = 
	
	

}


// ���j�R�����а}�C
void UnitBase::DeleteUnit (UnitBase** ptUnitBaseHeadRef, UnitBase* ptDel)
{
	if ((*ptUnitBaseHeadRef == nullptr) || (ptDel == nullptr))
	{
		return;
	}

	if (*ptUnitBaseHeadRef == ptDel)
	{
		*ptUnitBaseHeadRef = ptDel->m_ptNextUnit;
	}

	if (ptDel->m_ptNextUnit != nullptr)
	{
		ptDel->m_ptNextUnit->m_ptPreUnit = ptDel->m_ptPreUnit;
	}

	if (ptDel->m_ptPreUnit != nullptr)
	{
		ptDel->m_ptPreUnit->m_ptNextUnit = ptDel->m_ptNextUnit;
	}

	free(ptDel);
	return;

	//for (UnitBase* unit : unitBase->m_arrPtsNextUnit)
	//{
	//	DeleteUnitTree(unit);
	//}
	//delete unitBase; 
}


void UnitBase::InorderTraversal(UnitBase* unitBase)
{
	if (unitBase == nullptr)
	{
		return;
	}

	//for (size_t i = 0; i < unitBase->m_arrPtsNext.size(); i++)
	//{
	//	InorderTraversal(unitBase->m_arrPtsNext[i]);
	//	
	//	//if (i == unitBase->ptsNext.size() / 2)
	//	//{
	//	//	
	//	//}
	//}

	//if (unitBase->ptsNext.empty())
	//{

	//}
}


void UnitBase::InsertUnit(UnitBase* unitBase, int iNewShowRegW, int iNewShowRegH, int iNewButtonW, int iNewButtonH)
{
	// �t�m�s������
	UnitBase* ptNewUnitBase = new UnitBase(iNewShowRegW, iNewShowRegH, iNewButtonW, iNewButtonH);

	// ��J�s�������T
	ptNewUnitBase->iUnitWidth = iNewButtonW;
	ptNewUnitBase->iUnitHeight = iNewButtonH;
	ptNewUnitBase->pointUnitLocation = CPoint(iNewShowRegW * 0.5, iNewShowRegH * 0.5);

	// �N�s���� Next ���г]���e�@�� Unit �� Next ����
	ptNewUnitBase->m_ptNextUnit = unitBase->m_ptNextUnit;

	// �N�e�@�� Unit �� Next ���г]���s�� Unit
	unitBase->m_ptNextUnit = ptNewUnitBase;

	// �N�e�@�� Unit �]���s Unit �� Pre ����
	ptNewUnitBase->m_ptPreUnit = unitBase;

	// ��s�s Unit �� Next ����
	if (ptNewUnitBase->m_ptNextUnit != nullptr)
	{
		ptNewUnitBase->m_ptNextUnit->m_ptPreUnit = ptNewUnitBase;
	}


	m_arrPtsPreUnit.push_back(ptNewUnitBase->m_ptPreUnit);
	m_arrPtsNextUnit.push_back(ptNewUnitBase->m_ptNextUnit);

}
