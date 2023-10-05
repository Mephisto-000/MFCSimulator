#include "pch.h"
#include "CUnitLine.h"


CUnitLine::CUnitLine(CRect rectShowRegion, CRect rectButton) : CUnitBase(rectShowRegion, rectButton)
{
	m_strUnitID = _T("LINE");
	
	m_bIsConnect = FALSE;

	CPoint m_pointMovingLinePos(0, 0);
}


CUnitLine::~CUnitLine()
{

}

