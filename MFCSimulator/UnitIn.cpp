#include "pch.h"
#include "UnitIn.h"




UnitIn::UnitIn(CRect rectShowRegion, CRect rectButton) : UnitBase (rectShowRegion, rectButton)
{


}



void UnitIn::SetFuncOrOpera(CString strChoose)
{
	m_strFuncOrOpera = strChoose;
}


// 將要連接 FUN 或 OUT 元件的指標存入陣列
void UnitIn::InsertUnit(UnitBase* ptNewUnit)
{
	
	if (ptNewUnit->m_UnitID == "FUN")
	{
		m_arrPtsNextUnit.push_back(ptNewUnit);
	}
	else if (ptNewUnit->m_UnitID == "OUT")
	{
		m_arrPtsNextUnit.push_back(ptNewUnit);
	}

}


void UnitIn::UpdateDotData(CPoint pointNewLocation)
{
	m_arrConnectPt.push_back(pointNewLocation);
}


void UnitIn::Result(double dRealTimeValue)
{
	if (m_strFuncOrOpera == "sin")
	{
		m_dOutValue = sin(dRealTimeValue);
	}
	else if (m_strFuncOrOpera == "cos")
	{
		m_dOutValue = cos(dRealTimeValue);
	}
	else if (m_strFuncOrOpera == "True")
	{
		m_dOutValue = 1;
	}
	else
	{
		m_dOutValue = 0;
	}
}