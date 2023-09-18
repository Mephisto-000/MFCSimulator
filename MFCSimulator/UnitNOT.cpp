#include "pch.h"
#include "UnitNOT.h"


UnitNOT::UnitNOT(CRect rectShowRegion, CRect rectButton) : UnitBase(rectShowRegion, rectButton)
{
	m_strUnitID = _T("NOT");


	CPoint pointConnectTop(m_iUnitWidth * 0.5, 0);
	CPoint pointConnectBottom(m_iUnitWidth * 0.5, m_iUnitHeight);

	CRect rectConnectPtTop(CPoint(pointConnectTop.x - m_iConnectPtRadius, pointConnectTop.y - m_iConnectPtRadius),
		                       CPoint(pointConnectTop.x + m_iConnectPtRadius, pointConnectTop.y + m_iConnectPtRadius));
	CRect rectConnectPtBottom(CPoint(pointConnectBottom.x - m_iConnectPtRadius, pointConnectBottom.y - m_iConnectPtRadius),
							  CPoint(pointConnectBottom.x + m_iConnectPtRadius, pointConnectBottom.y + m_iConnectPtRadius));

	m_arrConnectPtRect.push_back(rectConnectPtTop);
	m_arrConnectPtRect.push_back(rectConnectPtBottom);


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