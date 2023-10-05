#include "pch.h"
#include "CUnitNOT.h"



CUnitNOT::CUnitNOT(CRect rectShowRegion, CRect rectButton) : CUnitBase(rectShowRegion, rectButton)
{
	m_strUnitID = _T("NOT");

	m_strFuncOrOpera = _T("NOT");

	// ��l�Ƴs���I��m
	m_pointConnectLeftTop = CPoint(m_iUnitWidth * 0.5, 0);
	m_pointConnectBottom = CPoint(m_iUnitWidth * 0.5, m_iUnitHeight);

	// ��l�Ƴs���I�~���x�Φ�m
	m_rectConnectLeftTop.SetRect(m_pointConnectLeftTop.x - m_iConnectPtRadius, m_pointConnectLeftTop.y - m_iConnectPtRadius,
								 m_pointConnectLeftTop.x + m_iConnectPtRadius, m_pointConnectLeftTop.y + m_iConnectPtRadius);

	m_rectConnectBottom.SetRect(m_pointConnectBottom.x - m_iConnectPtRadius, m_pointConnectBottom.y - m_iConnectPtRadius,
								m_pointConnectBottom.x + m_iConnectPtRadius, m_pointConnectBottom.y + m_iConnectPtRadius);

}


// ��s�s���I���y��
void CUnitNOT::SetConnectPtAndRect(int iOffsetX, int iOffsetY)
{	// ���� NOT �u������@�s���I�M������@�s���I

	// ��s�s���I��m
	m_pointConnectLeftTop.Offset(iOffsetX, iOffsetY);
	m_rectConnectLeftTop.OffsetRect(iOffsetX, iOffsetY);

	// ��s�s���I�~���x�Φ�m
	m_pointConnectBottom.Offset(iOffsetX, iOffsetY);
	m_rectConnectBottom.OffsetRect(iOffsetX, iOffsetY);


	// ��sø�ϥΪ��s���I��T
	if ((m_vecConnectPt.empty() == TRUE) && (m_vecConnectPtRect.empty() == TRUE))
	{	// ���x�s����T���šA��l�Ƴs���I��m�P��~���x�Ϊ���m

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// �������I��m
		// �s���I
		CPoint pointConnectTop;
		pointConnectTop.x = m_pointUnitLocation.x + m_iUnitWidth * 0.5;
		pointConnectTop.y = m_pointUnitLocation.y + 0;

		// �~���x��
		CRect rectConnectTop(CPoint(pointConnectTop.x - m_iConnectPtRadius, pointConnectTop.y - m_iConnectPtRadius),
							 CPoint(pointConnectTop.x + m_iConnectPtRadius, pointConnectTop.y + m_iConnectPtRadius));
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// �������I��m
		// �s���I
		CPoint pointConnectBottom;
		pointConnectBottom.x = m_pointUnitLocation.x + m_iUnitWidth * 0.5;
		pointConnectBottom.y = m_pointUnitLocation.y + m_iUnitHeight;

		// �~���x��
		CRect rectConnectBottom(CPoint(pointConnectBottom.x - m_iConnectPtRadius, pointConnectBottom.y - m_iConnectPtRadius),
							    CPoint(pointConnectBottom.x + m_iConnectPtRadius, pointConnectBottom.y + m_iConnectPtRadius));
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		m_vecConnectPt.push_back(pointConnectTop);
		m_vecConnectPt.push_back(pointConnectBottom);

		m_vecConnectPtRect.push_back(rectConnectTop);
		m_vecConnectPtRect.push_back(rectConnectBottom);
	}
	else
	{	// �����šA�h�̦첾�Z����s�s���I�P��~���x�Φ�m

		// �M�ť~���x�έ�l��T
		m_vecConnectPtRect.clear();

		// ��s�s���I��m�P��~���x��
		for (int i = 0; i < m_vecConnectPt.size(); i++)
		{
			m_vecConnectPt[i].Offset(iOffsetX, iOffsetY);

			CRect rectConnect(CPoint(m_vecConnectPt[i].x - m_iConnectPtRadius, m_vecConnectPt[i].y - m_iConnectPtRadius),     // Left, Top
							  CPoint(m_vecConnectPt[i].x + m_iConnectPtRadius, m_vecConnectPt[i].y + m_iConnectPtRadius));    // Right, Bottom

			m_vecConnectPtRect.push_back(rectConnect);
		}
	}
}

