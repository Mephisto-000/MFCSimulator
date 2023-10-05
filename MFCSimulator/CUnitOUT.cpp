#include "pch.h"
#include "CUnitOUT.h"



CUnitOUT::CUnitOUT(CRect rectShowRegion, CRect rectButton) : CUnitBase(rectShowRegion, rectButton)
{
	m_strUnitID = _T("OUT");

	// ��l�Ƴs���I��m
	m_pointConnectLeftTop = CPoint(m_iUnitWidth * 0.5, 0);
	m_rectConnectLeftTop.SetRect(m_pointConnectLeftTop.x - m_iConnectPtRadius, m_pointConnectLeftTop.y - m_iConnectPtRadius,
		m_pointConnectLeftTop.x + m_iConnectPtRadius, m_pointConnectLeftTop.y + m_iConnectPtRadius);

}

void CUnitOUT::SetConnectPtAndRect(int iOffsetX, int iOffsetY)
{	// ���� OUT �u������@�s���I

	m_pointConnectLeftTop.Offset(iOffsetX, iOffsetY);
	m_rectConnectLeftTop.OffsetRect(iOffsetX, iOffsetY);


	// ��sø�ϥΪ� vector
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


// �N�n�s�� FUN �� OUT ���󪺫��Цs�J�}�C
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