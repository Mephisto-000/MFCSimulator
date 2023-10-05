#include "pch.h"
#include "CUnitOUT.h"



CUnitOUT::CUnitOUT(CRect rectShowRegion, CRect rectButton) : CUnitBase(rectShowRegion, rectButton)
{

	m_strUnitID = _T("OUT");

	// ��l�Ƴs���I��m
	m_pointConnectLeftTop = CPoint(m_iUnitWidth * 0.5, 0);

	// ��l�Ƴs���I�~���x�Φ�m
	m_rectConnectLeftTop.SetRect(m_pointConnectLeftTop.x - m_iConnectPtRadius, m_pointConnectLeftTop.y - m_iConnectPtRadius,
								 m_pointConnectLeftTop.x + m_iConnectPtRadius, m_pointConnectLeftTop.y + m_iConnectPtRadius);

}


// ��s�s���I���y��
void CUnitOUT::SetConnectPtAndRect(int iOffsetX, int iOffsetY)
{	// ���� OUT �u��������@�s���I

	// ��s�����s���I��m
	m_pointConnectLeftTop.Offset(iOffsetX, iOffsetY);

	// ��s�s���I�~���x�Φ�m
	m_rectConnectLeftTop.OffsetRect(iOffsetX, iOffsetY);


	// ��sø�ϥΪ��s���I��T
	if ((m_vecConnectPt.empty() == TRUE) && (m_vecConnectPtRect.empty() == TRUE))
	{	// ���x�s����T���šA��l�Ƴs���I��m�P��~���x�Ϊ���m

		// �s���I
		CPoint pointConnect;
		pointConnect.x = m_pointUnitLocation.x + m_iUnitWidth * 0.5;
		pointConnect.y = m_pointUnitLocation.y + 0;
		m_vecConnectPt.push_back(pointConnect);

		// �~���x��
		CRect rectConnect(CPoint(pointConnect.x - m_iConnectPtRadius, pointConnect.y - m_iConnectPtRadius),     // Left, Top
						  CPoint(pointConnect.x + m_iConnectPtRadius, pointConnect.y + m_iConnectPtRadius));    // Right, Bottom
		m_vecConnectPtRect.push_back(rectConnect);
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

