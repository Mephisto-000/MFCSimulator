#include "pch.h"
#include "CUnitOUT.h"



CUnitOUT::CUnitOUT(CRect rectShowRegion, CRect rectButton) : CUnitBase(rectShowRegion, rectButton)
{

	m_strUnitID = _T("OUT");

	// 初始化連接點位置
	m_pointConnectLeftTop = CPoint(m_iUnitWidth * 0.5, 0);

	// 初始化連接點外切矩形位置
	m_rectConnectLeftTop.SetRect(m_pointConnectLeftTop.x - m_iConnectPtRadius, m_pointConnectLeftTop.y - m_iConnectPtRadius,
								 m_pointConnectLeftTop.x + m_iConnectPtRadius, m_pointConnectLeftTop.y + m_iConnectPtRadius);

}


// 更新連接點的座標
void CUnitOUT::SetConnectPtAndRect(int iOffsetX, int iOffsetY)
{	// 元件 OUT 只有頂部單一連接點

	// 更新頂部連接點位置
	m_pointConnectLeftTop.Offset(iOffsetX, iOffsetY);

	// 更新連接點外切矩形位置
	m_rectConnectLeftTop.OffsetRect(iOffsetX, iOffsetY);


	// 更新繪圖用的連接點資訊
	if ((m_vecConnectPt.empty() == TRUE) && (m_vecConnectPtRect.empty() == TRUE))
	{	// 當儲存的資訊為空，初始化連接點位置與其外切矩形的位置

		// 連接點
		CPoint pointConnect;
		pointConnect.x = m_pointUnitLocation.x + m_iUnitWidth * 0.5;
		pointConnect.y = m_pointUnitLocation.y + 0;
		m_vecConnectPt.push_back(pointConnect);

		// 外切矩形
		CRect rectConnect(CPoint(pointConnect.x - m_iConnectPtRadius, pointConnect.y - m_iConnectPtRadius),     // Left, Top
						  CPoint(pointConnect.x + m_iConnectPtRadius, pointConnect.y + m_iConnectPtRadius));    // Right, Bottom
		m_vecConnectPtRect.push_back(rectConnect);
	}
	else
	{	// 不為空，則依位移距離更新連接點與其外切矩形位置

		// 清空外切矩形原始資訊
		m_vecConnectPtRect.clear();

		// 更新連接點位置與其外切矩形
		for (int i = 0; i < m_vecConnectPt.size(); i++)
		{
			m_vecConnectPt[i].Offset(iOffsetX, iOffsetY);

			CRect rectConnect(CPoint(m_vecConnectPt[i].x - m_iConnectPtRadius, m_vecConnectPt[i].y - m_iConnectPtRadius),     // Left, Top
							  CPoint(m_vecConnectPt[i].x + m_iConnectPtRadius, m_vecConnectPt[i].y + m_iConnectPtRadius));    // Right, Bottom

			m_vecConnectPtRect.push_back(rectConnect);
		}
	}
}

