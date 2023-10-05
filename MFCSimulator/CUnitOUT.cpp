#include "pch.h"
#include "CUnitOUT.h"



CUnitOUT::CUnitOUT(CRect rectShowRegion, CRect rectButton) : CUnitBase(rectShowRegion, rectButton)
{
	m_strUnitID = _T("OUT");

	// 初始化連接點位置
	m_pointConnectLeftTop = CPoint(m_iUnitWidth * 0.5, 0);
	m_rectConnectLeftTop.SetRect(m_pointConnectLeftTop.x - m_iConnectPtRadius, m_pointConnectLeftTop.y - m_iConnectPtRadius,
		m_pointConnectLeftTop.x + m_iConnectPtRadius, m_pointConnectLeftTop.y + m_iConnectPtRadius);

}

void CUnitOUT::SetConnectPtAndRect(int iOffsetX, int iOffsetY)
{	// 元件 OUT 只頂部單一連接點

	m_pointConnectLeftTop.Offset(iOffsetX, iOffsetY);
	m_rectConnectLeftTop.OffsetRect(iOffsetX, iOffsetY);


	// 更新繪圖用的 vector
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


// 將要連接 FUN 或 OUT 元件的指標存入陣列
void CUnitOUT::InsertUnit(CUnitBase* ptNewUnit)
{


}


void CUnitOUT::UpdateDotData(CPoint pointNewLocation)
{
	//m_vecConnectPt.push_back(pointNewLocation);
}


void CUnitOUT::Result(double dTimeValue)
{


}