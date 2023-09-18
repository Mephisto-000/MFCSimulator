#include "pch.h"
#include "UnitIn.h"




UnitIN::UnitIN(CRect rectShowRegion, CRect rectButton) : UnitBase (rectShowRegion, rectButton)
{
	m_strUnitID = _T("IN");


	CPoint pointConnect(m_iUnitWidth * 0.5, m_iUnitHeight);

	CRect rectConnectPt(CPoint(pointConnect.x - m_iConnectPtRadius, pointConnect.y - m_iConnectPtRadius),
		CPoint(pointConnect.x + m_iConnectPtRadius, pointConnect.y + m_iConnectPtRadius));

	m_arrConnectPtRect.push_back(rectConnectPt);

}



void UnitIN::SetFuncOrOpera(CString strChoose)
{
	m_strFuncOrOpera = strChoose;
}


// 將要連接 FUN 或 OUT 元件的指標存入陣列
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
	

	CPoint pointConnect(m_iUnitWidth * 0.5, m_iUnitHeight);

	//CRect rectConnectPt(CPoint(pointConnect.x - m_iConnectPtRadius, pointConnect.y - m_iConnectPtRadius),
	//	CPoint(pointConnect.x + m_iConnectPtRadius, pointConnect.y + m_iConnectPtRadius));

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