#include "pch.h"
#include "UnitBase.h"
#include <cstddef>  // for size_t




// UnitBase 建構子
UnitBase::UnitBase(int iShowRegW, int iShowRegH, int iButtonWidth, int iButtonHeight)
{
	// 初始化指標
	m_ptPreUnit = nullptr;
	m_ptNextUnit = nullptr;

	// 初始化指標陣列
	m_arrPtsPreUnit.clear();
	m_arrPtsNextUnit.clear();

	pointUnitLocation = CPoint(iShowRegW * 0.5, iShowRegH * 0.5);
	iUnitWidth = iButtonWidth;
	iUnitHeight = iButtonHeight;

}


// UnitBase 解構子
UnitBase::~UnitBase()
{
	//UnitBase* ptCurUnit = 
	
	

}


// 遞迴刪除指標陣列
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
	// 配置新的元件
	UnitBase* ptNewUnitBase = new UnitBase(iNewShowRegW, iNewShowRegH, iNewButtonW, iNewButtonH);

	// 放入新的元件資訊
	ptNewUnitBase->iUnitWidth = iNewButtonW;
	ptNewUnitBase->iUnitHeight = iNewButtonH;
	ptNewUnitBase->pointUnitLocation = CPoint(iNewShowRegW * 0.5, iNewShowRegH * 0.5);

	// 將新元件的 Next 指標設為前一個 Unit 的 Next 指標
	ptNewUnitBase->m_ptNextUnit = unitBase->m_ptNextUnit;

	// 將前一個 Unit 的 Next 指標設為新的 Unit
	unitBase->m_ptNextUnit = ptNewUnitBase;

	// 將前一個 Unit 設為新 Unit 的 Pre 指標
	ptNewUnitBase->m_ptPreUnit = unitBase;

	// 更新新 Unit 的 Next 指標
	if (ptNewUnitBase->m_ptNextUnit != nullptr)
	{
		ptNewUnitBase->m_ptNextUnit->m_ptPreUnit = ptNewUnitBase;
	}


	m_arrPtsPreUnit.push_back(ptNewUnitBase->m_ptPreUnit);
	m_arrPtsNextUnit.push_back(ptNewUnitBase->m_ptNextUnit);

}
