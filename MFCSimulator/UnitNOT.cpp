#include "pch.h"
#include "UnitNOT.h"


UnitNOT::UnitNOT(CRect rectShowRegion, CRect rectButton) : UnitBase(rectShowRegion, rectButton)
{
	m_strUnitID = _T("NOT");

}


void UnitNOT::SetFuncOrOpera(CString strChoose)
{

}


// 將要連接 FUN 或 OUT 元件的指標存入陣列
void UnitNOT::InsertUnit(UnitBase* ptNewUnit)
{



}


void UnitNOT::UpdateDotData(CPoint pointNewLocation)
{

}


void UnitNOT::Result(double dRealTimeValue)
{

}