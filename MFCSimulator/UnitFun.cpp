#include "pch.h"
#include "UnitFUN.h"


UnitFUN::UnitFUN(CRect rectShowRegion, CRect rectButton) : UnitBase(rectShowRegion, rectButton)
{
	m_strUnitID = _T("FUN");

	// ��l�Ƴs���I��m
	m_pointConnectLeftTop = CPoint(0, 0);
	m_pointConnectRightTop = CPoint(m_iUnitWidth, 0);
	m_pointConnectBottom = CPoint(m_iUnitWidth * 0.5, m_iUnitHeight);

	m_rectConnectLeftTop.SetRect(m_pointConnectLeftTop.x - m_iConnectPtRadius, m_pointConnectLeftTop.y - m_iConnectPtRadius,
								 m_pointConnectLeftTop.x + m_iConnectPtRadius, m_pointConnectLeftTop.y + m_iConnectPtRadius);
	m_rectConnectRightTop.SetRect(m_pointConnectRightTop.x - m_iConnectPtRadius, m_pointConnectRightTop.y - m_iConnectPtRadius,
								  m_pointConnectRightTop.x + m_iConnectPtRadius, m_pointConnectRightTop.y + m_iConnectPtRadius);
	m_rectConnectBottom.SetRect(m_pointConnectBottom.x - m_iConnectPtRadius, m_pointConnectBottom.y - m_iConnectPtRadius,
								m_pointConnectBottom.x + m_iConnectPtRadius, m_pointConnectBottom.y + m_iConnectPtRadius);

}

void UnitFUN::SetConnectPtAndRect(int iOffsetX, int iOffsetY)
{

	m_pointConnectLeftTop.Offset(iOffsetX, iOffsetY);
	m_pointConnectRightTop.Offset(iOffsetX, iOffsetY);
	m_pointConnectBottom.Offset(iOffsetX, iOffsetY);

	m_rectConnectLeftTop.OffsetRect(iOffsetX, iOffsetY);
	m_rectConnectRightTop.OffsetRect(iOffsetX, iOffsetY);
	m_rectConnectBottom.OffsetRect(iOffsetX, iOffsetY);





	// ��sø�ϥΪ� vector
	if ((m_vecConnectPt.empty() == TRUE) && (m_vecConnectPtRect.empty() == TRUE))
	{
		// ���W��
		CPoint pointConnectLeftUp;
		pointConnectLeftUp.x = m_pointUnitLocation.x + 0;
		pointConnectLeftUp.y = m_pointUnitLocation.y + 0;

		CRect rectConnectLeftUp(CPoint(pointConnectLeftUp.x - m_iConnectPtRadius, pointConnectLeftUp.y - m_iConnectPtRadius),     // Left, Top
			CPoint(pointConnectLeftUp.x + m_iConnectPtRadius, pointConnectLeftUp.y + m_iConnectPtRadius));    // Right, Bottom

		// �k�W��
		CPoint pointConnectRightUp;
		pointConnectRightUp.x = m_pointUnitLocation.x + m_iUnitWidth;
		pointConnectRightUp.y = m_pointUnitLocation.y + 0;

		CRect rectConnectRightUp(CPoint(pointConnectRightUp.x - m_iConnectPtRadius, pointConnectRightUp.y - m_iConnectPtRadius),     // Left, Top
			CPoint(pointConnectRightUp.x + m_iConnectPtRadius, pointConnectRightUp.y + m_iConnectPtRadius));    // Right, Bottom

		// �U�褤�I��m
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


// �N�n�s�� FUN �� OUT ���󪺫��Цs�J�}�C
void UnitFUN::InsertUnit(UnitBase* ptNewUnit)
{

	//if (ptNewUnit->m_strUnitID == "FUN")
	//{
	//	m_vecPtsNextUnit.push_back(ptNewUnit);
	//}
	//else if (ptNewUnit->m_strUnitID = "IN")
	//{
	//	m_vecPtsPreUnit.push_back(ptNewUnit);
	//}

}


void UnitFUN::UpdateDotData(CPoint pointNewLocation)
{
	//m_vecConnectPt.push_back(pointNewLocation);
}


void UnitFUN::Result(double dTimeValue)
{


}