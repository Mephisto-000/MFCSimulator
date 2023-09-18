#include "pch.h"
#include "UnitOUT.h"



UnitOUT::UnitOUT(CRect rectShowRegion, CRect rectButton) : UnitBase(rectShowRegion, rectButton)
{
	m_strUnitID = _T("OUT");


	CPoint pointConnect(m_iUnitWidth * 0.5, 0);

	CRect rectConnectPt(CPoint(pointConnect.x - m_iConnectPtRadius, pointConnect.y - m_iConnectPtRadius),
		CPoint(pointConnect.x + m_iConnectPtRadius, pointConnect.y + m_iConnectPtRadius));

	m_arrConnectPtRect.push_back(rectConnectPt);
}


void UnitOUT::SetFuncOrOpera(CString strChoose)
{
	m_strFuncOrOpera = strChoose;
}


// 將要連接 FUN 或 OUT 元件的指標存入陣列
void UnitOUT::InsertUnit(UnitBase* ptNewUnit)
{


}


void UnitOUT::UpdateDotData(CPoint pointNewLocation)
{
	m_arrConnectPt.push_back(pointNewLocation);
}


void UnitOUT::Result(double dRealTimeValue)
{


}