#include "pch.h"
#include "UnitAND.h"

UnitAND::UnitAND(CRect rectShowRegion, CRect rectButton) : UnitBase(rectShowRegion, rectButton)
{
	m_strUnitID = _T("AND");


	CPoint pointConnectTopLeft(0, 0);
	CPoint pointConnectTopRight(m_iUnitWidth, 0);
	CPoint pointConnectBottom(m_iUnitWidth * 0.5, m_iUnitHeight);

	CRect rectConnectPtTopLeft(CPoint(pointConnectTopLeft.x - m_iConnectPtRadius, pointConnectTopLeft.y - m_iConnectPtRadius),
							   CPoint(pointConnectTopLeft.x + m_iConnectPtRadius, pointConnectTopLeft.y + m_iConnectPtRadius));
	CRect rectConnectPtTopRight(CPoint(pointConnectTopRight.x - m_iConnectPtRadius, pointConnectTopRight.y - m_iConnectPtRadius),
								CPoint(pointConnectTopRight.x + m_iConnectPtRadius, pointConnectTopRight.y + m_iConnectPtRadius));
	CRect rectConnectPtBottom(CPoint(pointConnectBottom.x - m_iConnectPtRadius, pointConnectBottom.y - m_iConnectPtRadius),
							  CPoint(pointConnectBottom.x + m_iConnectPtRadius, pointConnectBottom.y + m_iConnectPtRadius));



	m_arrConnectPtRect.push_back(rectConnectPtTopLeft);
	m_arrConnectPtRect.push_back(rectConnectPtTopRight);
	m_arrConnectPtRect.push_back(rectConnectPtBottom);


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