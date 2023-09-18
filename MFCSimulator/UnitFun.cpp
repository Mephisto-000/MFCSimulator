#include "pch.h"
#include "UnitFUN.h"


UnitFUN::UnitFUN(CRect rectShowRegion, CRect rectButton) : UnitBase(rectShowRegion, rectButton)
{
	m_strUnitID = _T("FUN");

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