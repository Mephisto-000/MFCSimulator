#include "pch.h"
#include "UnitIn.h"




UnitIn::UnitIn(CRect rectShowRegion, CRect rectButton) : UnitBase (rectShowRegion, rectButton)
{


}



void UnitIn::SetFuncOrOpera(CString strChoose)
{
	m_strFuncOrOpera = strChoose;
}


// �N�n�s�� FUN �� OUT ���󪺫��Цs�J�}�C
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