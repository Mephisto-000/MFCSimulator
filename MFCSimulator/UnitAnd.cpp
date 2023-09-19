#include "pch.h"
#include "UnitAND.h"

UnitAND::UnitAND(CRect rectShowRegion, CRect rectButton) : UnitBase(rectShowRegion, rectButton)
{
	m_strUnitID = _T("AND");
}


void UnitAND::SetConnectPtAndRect()
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


void UnitAND::SetFuncOrOpera(CString strChoose)
{

}


// �N�n�s�� FUN �� OUT ���󪺫��Цs�J�}�C
void UnitAND::InsertUnit(UnitBase* ptNewUnit)
{



}


void UnitAND::UpdateDotData(CPoint pointNewLocation)
{

}


void UnitAND::Result(double dRealTimeValue)
{

}