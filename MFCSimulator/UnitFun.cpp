#include "pch.h"
#include "UnitFun.h"





void UnitFun::SetFuncOrOpera(CString strChoose)
{
	m_strFuncOrOpera = strChoose;
}


// �N�n�s�� FUN �� OUT ���󪺫��Цs�J�}�C
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