#include "pch.h"
#include "UnitIn.h"




UnitIN::UnitIN(CRect rectShowRegion, CRect rectButton) : UnitBase (rectShowRegion, rectButton)
{
	m_strUnitID = _T("IN");

	m_strFuncOrOpera = _T("");

	// 初始化連接點位置
	m_pointConnectBottom = CPoint(m_iUnitWidth * 0.5, m_iUnitHeight);
	m_rectConnectBottom.SetRect(m_pointConnectBottom.x - m_iConnectPtRadius, m_pointConnectBottom.y - m_iConnectPtRadius,
								m_pointConnectBottom.x + m_iConnectPtRadius, m_pointConnectBottom.y + m_iConnectPtRadius);

}


// 更新連接點的座標
void UnitIN::SetConnectPtAndRect(int iOffsetX, int iOffsetY)
{	// 元件 IN 只底部單一連接點

	
	m_pointConnectBottom.Offset(iOffsetX, iOffsetY);
	m_rectConnectBottom.OffsetRect(iOffsetX, iOffsetY);


	// 更新繪圖用的 vector
	if ((m_vecConnectPt.empty() == TRUE) && (m_vecConnectPtRect.empty() == TRUE))
	{
		CPoint pointConnect;
		pointConnect.x = m_pointUnitLocation.x + m_iUnitWidth * 0.5;
		pointConnect.y = m_pointUnitLocation.y + m_iUnitHeight;
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
void UnitIN::InsertUnit(UnitBase* ptNewUnit)
{
	
	if (ptNewUnit->m_strUnitID == "FUN")
	{
		m_vecPtsNextUnit.push_back(ptNewUnit);
	}
	else if (ptNewUnit->m_strUnitID == "OUT")
	{
		m_vecPtsNextUnit.push_back(ptNewUnit);
	}

}


void UnitIN::UpdateDotData(CPoint pointNewLocation)
{
	

	CPoint pointConnect(m_iUnitWidth * 0.5, m_iUnitHeight);

	//CRect rectConnectPt(CPoint(pointConnect.x - m_iConnectPtRadius, pointConnect.y - m_iConnectPtRadius),
	//	CPoint(pointConnect.x + m_iConnectPtRadius, pointConnect.y + m_iConnectPtRadius));

	//m_vecConnectPt.push_back(pointNewLocation);
}


void UnitIN::Result(double dTimeValue)
{



}