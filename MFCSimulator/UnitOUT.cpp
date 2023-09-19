#include "pch.h"
#include "UnitOUT.h"



UnitOUT::UnitOUT(CRect rectShowRegion, CRect rectButton) : UnitBase(rectShowRegion, rectButton)
{
	m_strUnitID = _T("OUT");

}

void UnitOUT::SetConnectPtAndRect(int iOffsetX, int iOffsetY)
{
	if ((m_vecConnectPt.empty() == TRUE) && (m_vecConnectPtRect.empty() == TRUE))
	{
		CPoint pointConnect;
		pointConnect.x = m_pointUnitLocation.x + m_iUnitWidth * 0.5;
		pointConnect.y = m_pointUnitLocation.y + 0;
		m_vecConnectPt.push_back(pointConnect);


		CRect rectConnect(CPoint(pointConnect.x - m_iConnectPtRadius, pointConnect.y - m_iConnectPtRadius),     // Left, Top
						  CPoint(pointConnect.x + m_iConnectPtRadius, pointConnect.y + m_iConnectPtRadius));    // Right, Bottom
		m_vecConnectPtRect.push_back(rectConnect);
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
	m_vecConnectPt.push_back(pointNewLocation);
}


void UnitOUT::Result(double dRealTimeValue)
{


}