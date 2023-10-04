#include "pch.h"
#include "UnitLine.h"


UnitLine::UnitLine(CRect rectShowRegion, CRect rectButton) : UnitBase(rectShowRegion, rectButton)
{
	m_strUnitID = _T("LINE");
	
	m_bIsConnect = FALSE;

	CPoint m_pointMovingLinePos(0, 0);
}


UnitLine::~UnitLine()
{

}

