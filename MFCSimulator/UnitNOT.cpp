#include "pch.h"
#include "UnitNOT.h"


UnitNOT::UnitNOT(CRect rectShowRegion, CRect rectButton) : UnitBase(rectShowRegion, rectButton)
{
	m_strUnitID = _T("NOT");

	m_strFuncOrOpera = _T("NOT");


	// 初始化連接點位置
	// 頂部 : 
	m_pointConnectLeftTop = CPoint(m_iUnitWidth * 0.5, 0);
	m_rectConnectLeftTop.SetRect(m_pointConnectLeftTop.x - m_iConnectPtRadius, m_pointConnectLeftTop.y - m_iConnectPtRadius,
								 m_pointConnectLeftTop.x + m_iConnectPtRadius, m_pointConnectLeftTop.y + m_iConnectPtRadius);

	// 底部 : 
	m_pointConnectBottom = CPoint(m_iUnitWidth * 0.5, m_iUnitHeight);
	m_rectConnectBottom.SetRect(m_pointConnectBottom.x - m_iConnectPtRadius, m_pointConnectBottom.y - m_iConnectPtRadius,
								m_pointConnectBottom.x + m_iConnectPtRadius, m_pointConnectBottom.y + m_iConnectPtRadius);


}


void UnitNOT::SetConnectPtAndRect(int iOffsetX, int iOffsetY)
{	// 元件 NOT 只頂部單一連接點和底部單一連接點

	m_pointConnectLeftTop.Offset(iOffsetX, iOffsetY);
	m_rectConnectLeftTop.OffsetRect(iOffsetX, iOffsetY);


	m_pointConnectBottom.Offset(iOffsetX, iOffsetY);
	m_rectConnectBottom.OffsetRect(iOffsetX, iOffsetY);



	// 更新繪圖用的 vector
	if ((m_vecConnectPt.empty() == TRUE) && (m_vecConnectPtRect.empty() == TRUE))
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
void UnitNOT::InsertUnit(UnitBase* ptNewUnit)
{



}


void UnitNOT::UpdateDotData(CPoint pointNewLocation)
{

}


void UnitNOT::Result(double dTimeValue)
{

}