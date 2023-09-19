#include "pch.h"
#include "UnitNOT.h"


UnitNOT::UnitNOT(CRect rectShowRegion, CRect rectButton) : UnitBase(rectShowRegion, rectButton)
{
	m_strUnitID = _T("NOT");

}


void UnitNOT::SetConnectPtAndRect(int iOffsetX, int iOffsetY)
{
	if ((m_vecConnectPt.empty() == TRUE) && (m_vecConnectPtRect.empty() == TRUE))
	{
		// �W�褤�I��m
		CPoint pointConnectTop;
		pointConnectTop.x = m_pointUnitLocation.x + m_iUnitWidth * 0.5;
		pointConnectTop.y = m_pointUnitLocation.y + 0;

		CRect rectConnectTop(CPoint(pointConnectTop.x - m_iConnectPtRadius, pointConnectTop.y - m_iConnectPtRadius),     // Left, Top
							 CPoint(pointConnectTop.x + m_iConnectPtRadius, pointConnectTop.y + m_iConnectPtRadius));    // Right, Bottom

		// �U�褤�I��m
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
	else
	{
		m_vecConnectPtRect.clear();

		for (int i = 0; i < m_vecConnectPt.size(); i++)
		{
			m_vecConnectPt[i].Offset(iOffsetX, iOffsetY);

			CRect rectConnect(CPoint(m_vecConnectPt[i].x - m_iConnectPtRadius, m_vecConnectPt[i].y - m_iConnectPtRadius),     // Left, Top
							  CPoint(m_vecConnectPt[i].x + m_iConnectPtRadius, m_vecConnectPt[i].y + m_iConnectPtRadius));    // Right, Bottom

			m_vecConnectPtRect.push_back(rectConnect);
		}
	}
}


void UnitNOT::SetFuncOrOpera(CString strChoose)
{

}


// �N�n�s�� FUN �� OUT ���󪺫��Цs�J�}�C
void UnitNOT::InsertUnit(UnitBase* ptNewUnit)
{



}


void UnitNOT::UpdateDotData(CPoint pointNewLocation)
{

}


void UnitNOT::Result(double dRealTimeValue)
{

}