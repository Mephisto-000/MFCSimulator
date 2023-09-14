#include "pch.h"
#include "UnitFun.h"





void UnitFun::SetFuncOrOpera(CString strChoose)
{
	m_strFuncOrOpera = strChoose;
}


// 將要連接 FUN 或 OUT 元件的指標存入陣列
void UnitFun::InsertUnit(UnitBase* ptNewUnit)
{

	if (ptNewUnit->m_UnitID == "FUN")
	{
		m_arrPtsNextUnit.push_back(ptNewUnit);
	}
	else if (ptNewUnit->m_UnitID = "IN")
	{
		m_arrPtsPreUnit.push_back(ptNewUnit);
	}

}


void UnitFun::UpdateDotData(CPoint pointNewLocation)
{
	m_arrConnectPt.push_back(pointNewLocation);
}


void UnitFun::Result(double dRealTimeValue)
{


}