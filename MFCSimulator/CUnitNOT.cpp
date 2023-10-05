#include "pch.h"
#include "CUnitNOT.h"



CUnitNOT::CUnitNOT(CRect rectShowRegion, CRect rectButton) : CUnitBase(rectShowRegion, rectButton)
{
	m_strUnitID = _T("NOT");

	m_strFuncOrOpera = _T("NOT");

	// 初始化連接點位置
	m_pointConnectLeftTop = CPoint(m_iUnitWidth * 0.5, 0);
	m_pointConnectBottom = CPoint(m_iUnitWidth * 0.5, m_iUnitHeight);

	// 初始化連接點外切矩形位置
	m_rectConnectLeftTop.SetRect(m_pointConnectLeftTop.x - m_iConnectPtRadius, m_pointConnectLeftTop.y - m_iConnectPtRadius,
								 m_pointConnectLeftTop.x + m_iConnectPtRadius, m_pointConnectLeftTop.y + m_iConnectPtRadius);

	m_rectConnectBottom.SetRect(m_pointConnectBottom.x - m_iConnectPtRadius, m_pointConnectBottom.y - m_iConnectPtRadius,
								m_pointConnectBottom.x + m_iConnectPtRadius, m_pointConnectBottom.y + m_iConnectPtRadius);

}


// 更新連接點的座標
void CUnitNOT::SetConnectPtAndRect(int iOffsetX, int iOffsetY)
{	// 元件 NOT 只頂部單一連接點和底部單一連接點

	// 更新連接點位置
	m_pointConnectLeftTop.Offset(iOffsetX, iOffsetY);
	m_rectConnectLeftTop.OffsetRect(iOffsetX, iOffsetY);

	// 更新連接點外切矩形位置
	m_pointConnectBottom.Offset(iOffsetX, iOffsetY);
	m_rectConnectBottom.OffsetRect(iOffsetX, iOffsetY);


	// 更新繪圖用的連接點資訊
	if ((m_vecConnectPt.empty() == TRUE) && (m_vecConnectPtRect.empty() == TRUE))
	{	// 當儲存的資訊為空，初始化連接點位置與其外切矩形的位置

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// 頂部中點位置
		// 連接點
		CPoint pointConnectTop;
		pointConnectTop.x = m_pointUnitLocation.x + m_iUnitWidth * 0.5;
		pointConnectTop.y = m_pointUnitLocation.y + 0;

		// 外切矩形
		CRect rectConnectTop(CPoint(pointConnectTop.x - m_iConnectPtRadius, pointConnectTop.y - m_iConnectPtRadius),
							 CPoint(pointConnectTop.x + m_iConnectPtRadius, pointConnectTop.y + m_iConnectPtRadius));
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// 底部中點位置
		// 連接點
		CPoint pointConnectBottom;
		pointConnectBottom.x = m_pointUnitLocation.x + m_iUnitWidth * 0.5;
		pointConnectBottom.y = m_pointUnitLocation.y + m_iUnitHeight;

		// 外切矩形
		CRect rectConnectBottom(CPoint(pointConnectBottom.x - m_iConnectPtRadius, pointConnectBottom.y - m_iConnectPtRadius),
							    CPoint(pointConnectBottom.x + m_iConnectPtRadius, pointConnectBottom.y + m_iConnectPtRadius));
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		m_vecConnectPt.push_back(pointConnectTop);
		m_vecConnectPt.push_back(pointConnectBottom);

		m_vecConnectPtRect.push_back(rectConnectTop);
		m_vecConnectPtRect.push_back(rectConnectBottom);
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

