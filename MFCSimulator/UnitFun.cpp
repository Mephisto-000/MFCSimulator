#include "pch.h"
#include "UnitFUN.h"


UnitFUN::UnitFUN(CRect rectShowRegion, CRect rectButton) : UnitBase(rectShowRegion, rectButton)
{
	m_strUnitID = _T("FUN");

}


void UnitFUN::SetFuncOrOpera(CString strChoose)
{
	m_strFuncOrOpera = strChoose;
}


// 將要連接 FUN 或 OUT 元件的指標存入陣列
void UnitFUN::InsertUnit(UnitBase* ptNewUnit)
{

	if (ptNewUnit->m_strUnitID == "FUN")
	{
		m_arrPtsNextUnit.push_back(ptNewUnit);
	}
	else if (ptNewUnit->m_strUnitID = "IN")
	{
		m_arrPtsPreUnit.push_back(ptNewUnit);
	}

}


void UnitFUN::UpdateDotData(CPoint pointNewLocation)
{
	m_arrConnectPt.push_back(pointNewLocation);
}


void UnitFUN::Result(double dRealTimeValue)
{


}