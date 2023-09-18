#include "pch.h"
#include "UnitAND.h"

UnitAND::UnitAND(CRect rectShowRegion, CRect rectButton) : UnitBase(rectShowRegion, rectButton)
{
	m_strUnitID = _T("AND");


}




void UnitAND::SetFuncOrOpera(CString strChoose)
{

}


// 將要連接 FUN 或 OUT 元件的指標存入陣列
void UnitAND::InsertUnit(UnitBase* ptNewUnit)
{



}


void UnitAND::UpdateDotData(CPoint pointNewLocation)
{

}


void UnitAND::Result(double dRealTimeValue)
{

}