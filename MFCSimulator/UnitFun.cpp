#include "pch.h"
#include "UnitFUN.h"


UnitFUN::UnitFUN(CRect rectShowRegion, CRect rectButton) : UnitBase(rectShowRegion, rectButton)
{
	m_strUnitID = _T("FUN");
}

void UnitFUN::SetConnectPtAndRect()
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


void UnitFUN::SetFuncOrOpera(CString strChoose)
{
	m_strFuncOrOpera = strChoose;
}


// �N�n�s�� FUN �� OUT ���󪺫��Цs�J�}�C
void UnitFUN::InsertUnit(UnitBase* ptNewUnit)
{

	if (ptNewUnit->m_strUnitID == "FUN")
	{
		m_vecPtsNextUnit.push_back(ptNewUnit);
	}
	else if (ptNewUnit->m_strUnitID = "IN")
	{
		m_vecPtsPreUnit.push_back(ptNewUnit);
	}

}


void UnitFUN::UpdateDotData(CPoint pointNewLocation)
{
	m_vecConnectPt.push_back(pointNewLocation);
}


void UnitFUN::Result(double dRealTimeValue)
{


}