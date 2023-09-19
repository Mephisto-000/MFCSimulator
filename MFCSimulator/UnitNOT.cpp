#include "pch.h"
#include "UnitNOT.h"


UnitNOT::UnitNOT(CRect rectShowRegion, CRect rectButton) : UnitBase(rectShowRegion, rectButton)
{
	m_strUnitID = _T("NOT");

}


void UnitNOT::SetConnectPtAndRect()
{
	// 上方中點位置
	CPoint pointConnectTop;
	pointConnectTop.x = m_pointUnitLocation.x + m_iUnitWidth * 0.5;
	pointConnectTop.y = m_pointUnitLocation.y + 0;

	CRect rectConnectTop(CPoint(pointConnectTop.x - m_iConnectPtRadius, pointConnectTop.y - m_iConnectPtRadius),     // Left, Top
						 CPoint(pointConnectTop.x + m_iConnectPtRadius, pointConnectTop.y + m_iConnectPtRadius));    // Right, Bottom

	// 下方中點位置
	CPoint pointConnectBottom;
	pointConnectBottom.x = m_pointUnitLocation.x + m_iUnitWidth * 0.5;
	pointConnectBottom.y = m_pointUnitLocation.y + m_iUnitHeight;

	CRect rectConnectBottom(CPoint(pointConnectBottom.x - m_iConnectPtRadius, pointConnectBottom.y - m_iConnectPtRadius),     // Left, Top
							CPoint(pointConnectBottom.x + m_iConnectPtRadius, pointConnectBottom.y + m_iConnectPtRadius));    // Right, Bottom

	m_vecConnectPt.push_back(pointConnectTop);
	m_vecConnectPt.push_back(pointConnectBottom);

	m_vecConnectPtRect.push_back(rectConnectTop);
	m_vecConnectPtRect.push_back(rectConnectBottom);
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