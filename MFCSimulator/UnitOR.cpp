#include "pch.h"
#include "UnitOR.h"


UnitOR::UnitOR(CRect rectShowRegion, CRect rectButton) : UnitBase(rectShowRegion, rectButton)
{
	m_strUnitID = _T("OR");

}


void UnitOR::SetConnectPtAndRect(int iOffsetX, int iOffsetY)
{
	if ((m_vecConnectPt.empty() == TRUE) && (m_vecConnectPtRect.empty() == TRUE))
	{
		// 左上角
		CPoint pointConnectLeftUp;
		pointConnectLeftUp.x = m_pointUnitLocation.x + 0;
		pointConnectLeftUp.y = m_pointUnitLocation.y + 0;

		CRect rectConnectLeftUp(CPoint(pointConnectLeftUp.x - m_iConnectPtRadius, pointConnectLeftUp.y - m_iConnectPtRadius),     // Left, Top
			CPoint(pointConnectLeftUp.x + m_iConnectPtRadius, pointConnectLeftUp.y + m_iConnectPtRadius));    // Right, Bottom

		// 右上角
		CPoint pointConnectRightUp;
		pointConnectRightUp.x = m_pointUnitLocation.x + m_iUnitWidth;
		pointConnectRightUp.y = m_pointUnitLocation.y + 0;

		CRect rectConnectRightUp(CPoint(pointConnectRightUp.x - m_iConnectPtRadius, pointConnectRightUp.y - m_iConnectPtRadius),     // Left, Top
			CPoint(pointConnectRightUp.x + m_iConnectPtRadius, pointConnectRightUp.y + m_iConnectPtRadius));    // Right, Bottom

		// 下方中點位置
		CPoint pointConnectBottom;
		pointConnectBottom.x = m_pointUnitLocation.x + m_iUnitWidth * 0.5;
		pointConnectBottom.y = m_pointUnitLocation.y + m_iUnitHeight;

		CRect rectConnectBottom(CPoint(pointConnectBottom.x - m_iConnectPtRadius, pointConnectBottom.y - m_iConnectPtRadius),     // Left, Top
			CPoint(pointConnectBottom.x + m_iConnectPtRadius, pointConnectBottom.y + m_iConnectPtRadius));    // Right, Bottom

		m_vecConnectPt.push_back(pointConnectLeftUp);
		m_vecConnectPt.push_back(pointConnectRightUp);
		m_vecConnectPt.push_back(pointConnectBottom);

		m_vecConnectPtRect.push_back(rectConnectLeftUp);
		m_vecConnectPtRect.push_back(rectConnectRightUp);
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


void UnitOR::SetFuncOrOpera(CString strChoose)
{

}


// 將要連接 FUN 或 OUT 元件的指標存入陣列
void UnitOR::InsertUnit(UnitBase* ptNewUnit)
{



}


void UnitOR::UpdateDotData(CPoint pointNewLocation)
{

}


void UnitOR::Result(double dRealTimeValue)
{

}

