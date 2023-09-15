#include "pch.h"
#include "UnitIn.h"




UnitIN::UnitIN(CRect rectShowRegion, CRect rectButton) : UnitBase (rectShowRegion, rectButton)
{
	m_strUnitID = _T("IN");

}



void UnitIN::SetFuncOrOpera(CString strChoose)
{
	m_strFuncOrOpera = strChoose;
}


// �N�n�s�� FUN �� OUT ���󪺫��Цs�J�}�C
void UnitIN::InsertUnit(UnitBase* ptNewUnit)
{
	
	if (ptNewUnit->m_strUnitID == "FUN")
	{
		m_arrPtsNextUnit.push_back(ptNewUnit);
	}
	else if (ptNewUnit->m_strUnitID == "OUT")
	{
		m_arrPtsNextUnit.push_back(ptNewUnit);
	}

}


void UnitIN::UpdateDotData(CPoint pointNewLocation)
{
	m_arrConnectPt.push_back(pointNewLocation);
}


void UnitIN::Result(double dRealTimeValue)
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