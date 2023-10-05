#include "pch.h"
#include "CUnitAND.h"



CUnitAND::CUnitAND(CRect rectShowRegion, CRect rectButton) : CUnitBase(rectShowRegion, rectButton)
{
	m_strUnitID = _T("AND");

	m_strFuncOrOpera = _T("AND");

	// ��l�Ƴs���I��m
	m_pointConnectLeftTop = CPoint(0, 0);
	m_pointConnectRightTop = CPoint(m_iUnitWidth, 0);
	m_pointConnectBottom = CPoint(m_iUnitWidth * 0.5, m_iUnitHeight);

	// ��l�Ƴs���I�~���x�Φ�m
	m_rectConnectLeftTop.SetRect(m_pointConnectLeftTop.x - m_iConnectPtRadius, m_pointConnectLeftTop.y - m_iConnectPtRadius,
								 m_pointConnectLeftTop.x + m_iConnectPtRadius, m_pointConnectLeftTop.y + m_iConnectPtRadius);

	m_rectConnectRightTop.SetRect(m_pointConnectRightTop.x - m_iConnectPtRadius, m_pointConnectRightTop.y - m_iConnectPtRadius,
								  m_pointConnectRightTop.x + m_iConnectPtRadius, m_pointConnectRightTop.y + m_iConnectPtRadius);

	m_rectConnectBottom.SetRect(m_pointConnectBottom.x - m_iConnectPtRadius, m_pointConnectBottom.y - m_iConnectPtRadius,
								m_pointConnectBottom.x + m_iConnectPtRadius, m_pointConnectBottom.y + m_iConnectPtRadius);

}


// ��s�s���I���y��
void CUnitAND::SetConnectPtAndRect(int iOffsetX, int iOffsetY)
{	// ���� AND �����@�ӳs���I�A�������k�U�@�ӳs���I

	// ��s�s���I��m
	m_pointConnectLeftTop.Offset(iOffsetX, iOffsetY);
	m_pointConnectRightTop.Offset(iOffsetX, iOffsetY);
	m_pointConnectBottom.Offset(iOffsetX, iOffsetY);

	// ��s�s���I�~���x�Φ�m
	m_rectConnectLeftTop.OffsetRect(iOffsetX, iOffsetY);
	m_rectConnectRightTop.OffsetRect(iOffsetX, iOffsetY);
	m_rectConnectBottom.OffsetRect(iOffsetX, iOffsetY);


	// ��sø�ϥΪ��s���I��T
	if ((m_vecConnectPt.empty() == TRUE) && (m_vecConnectPtRect.empty() == TRUE))
	{	// ���x�s����T���šA��l�Ƴs���I��m�P��~���x�Ϊ���m

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// ���W��
		// �s���I
		CPoint pointConnectLeftUp;
		pointConnectLeftUp.x = m_pointUnitLocation.x + 0;
		pointConnectLeftUp.y = m_pointUnitLocation.y + 0;

		// �~���x��
		CRect rectConnectLeftUp(CPoint(pointConnectLeftUp.x - m_iConnectPtRadius, pointConnectLeftUp.y - m_iConnectPtRadius),
								CPoint(pointConnectLeftUp.x + m_iConnectPtRadius, pointConnectLeftUp.y + m_iConnectPtRadius));
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// �k�W��
		// �s���I
		CPoint pointConnectRightUp;
		pointConnectRightUp.x = m_pointUnitLocation.x + m_iUnitWidth;
		pointConnectRightUp.y = m_pointUnitLocation.y + 0;

		// �~���x��
		CRect rectConnectRightUp(CPoint(pointConnectRightUp.x - m_iConnectPtRadius, pointConnectRightUp.y - m_iConnectPtRadius),
								 CPoint(pointConnectRightUp.x + m_iConnectPtRadius, pointConnectRightUp.y + m_iConnectPtRadius));
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// ����
		// �s���I
		CPoint pointConnectBottom;
		pointConnectBottom.x = m_pointUnitLocation.x + m_iUnitWidth * 0.5;
		pointConnectBottom.y = m_pointUnitLocation.y + m_iUnitHeight;

		// �~���x��
		CRect rectConnectBottom(CPoint(pointConnectBottom.x - m_iConnectPtRadius, pointConnectBottom.y - m_iConnectPtRadius),
								CPoint(pointConnectBottom.x + m_iConnectPtRadius, pointConnectBottom.y + m_iConnectPtRadius));
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		m_vecConnectPt.push_back(pointConnectLeftUp);
		m_vecConnectPt.push_back(pointConnectRightUp);
		m_vecConnectPt.push_back(pointConnectBottom);

		m_vecConnectPtRect.push_back(rectConnectLeftUp);
		m_vecConnectPtRect.push_back(rectConnectRightUp);
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

			CRect rectConnect(CPoint(m_vecConnectPt[i].x - m_iConnectPtRadius, m_vecConnectPt[i].y - m_iConnectPtRadius),
							  CPoint(m_vecConnectPt[i].x + m_iConnectPtRadius, m_vecConnectPt[i].y + m_iConnectPtRadius));

			m_vecConnectPtRect.push_back(rectConnect);
		}
	}
}

