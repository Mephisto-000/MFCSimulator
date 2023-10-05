#include "pch.h"
#include "CUnitAND.h"



CUnitAND::CUnitAND(CRect rectShowRegion, CRect rectButton) : CUnitBase(rectShowRegion, rectButton)
{
	m_strUnitID = _T("AND");

	m_strFuncOrOpera = _T("AND");

	// 初始化連接點位置
	m_pointConnectLeftTop = CPoint(0, 0);
	m_pointConnectRightTop = CPoint(m_iUnitWidth, 0);
	m_pointConnectBottom = CPoint(m_iUnitWidth * 0.5, m_iUnitHeight);

	// 初始化連接點外切矩形位置
	m_rectConnectLeftTop.SetRect(m_pointConnectLeftTop.x - m_iConnectPtRadius, m_pointConnectLeftTop.y - m_iConnectPtRadius,
								 m_pointConnectLeftTop.x + m_iConnectPtRadius, m_pointConnectLeftTop.y + m_iConnectPtRadius);

	m_rectConnectRightTop.SetRect(m_pointConnectRightTop.x - m_iConnectPtRadius, m_pointConnectRightTop.y - m_iConnectPtRadius,
								  m_pointConnectRightTop.x + m_iConnectPtRadius, m_pointConnectRightTop.y + m_iConnectPtRadius);

	m_rectConnectBottom.SetRect(m_pointConnectBottom.x - m_iConnectPtRadius, m_pointConnectBottom.y - m_iConnectPtRadius,
								m_pointConnectBottom.x + m_iConnectPtRadius, m_pointConnectBottom.y + m_iConnectPtRadius);

}


// 更新連接點的座標
void CUnitAND::SetConnectPtAndRect(int iOffsetX, int iOffsetY)
{	// 元件 AND 底部一個連接點，頂部左右各一個連接點

	// 更新連接點位置
	m_pointConnectLeftTop.Offset(iOffsetX, iOffsetY);
	m_pointConnectRightTop.Offset(iOffsetX, iOffsetY);
	m_pointConnectBottom.Offset(iOffsetX, iOffsetY);

	// 更新連接點外切矩形位置
	m_rectConnectLeftTop.OffsetRect(iOffsetX, iOffsetY);
	m_rectConnectRightTop.OffsetRect(iOffsetX, iOffsetY);
	m_rectConnectBottom.OffsetRect(iOffsetX, iOffsetY);


	// 更新繪圖用的連接點資訊
	if ((m_vecConnectPt.empty() == TRUE) && (m_vecConnectPtRect.empty() == TRUE))
	{	// 當儲存的資訊為空，初始化連接點位置與其外切矩形的位置

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// 左上角
		// 連接點
		CPoint pointConnectLeftUp;
		pointConnectLeftUp.x = m_pointUnitLocation.x + 0;
		pointConnectLeftUp.y = m_pointUnitLocation.y + 0;

		// 外切矩形
		CRect rectConnectLeftUp(CPoint(pointConnectLeftUp.x - m_iConnectPtRadius, pointConnectLeftUp.y - m_iConnectPtRadius),
								CPoint(pointConnectLeftUp.x + m_iConnectPtRadius, pointConnectLeftUp.y + m_iConnectPtRadius));
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// 右上角
		// 連接點
		CPoint pointConnectRightUp;
		pointConnectRightUp.x = m_pointUnitLocation.x + m_iUnitWidth;
		pointConnectRightUp.y = m_pointUnitLocation.y + 0;

		// 外切矩形
		CRect rectConnectRightUp(CPoint(pointConnectRightUp.x - m_iConnectPtRadius, pointConnectRightUp.y - m_iConnectPtRadius),
								 CPoint(pointConnectRightUp.x + m_iConnectPtRadius, pointConnectRightUp.y + m_iConnectPtRadius));
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// 底部
		// 連接點
		CPoint pointConnectBottom;
		pointConnectBottom.x = m_pointUnitLocation.x + m_iUnitWidth * 0.5;
		pointConnectBottom.y = m_pointUnitLocation.y + m_iUnitHeight;

		// 外切矩形
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
	{	// 不為空，則依位移距離更新連接點與其外切矩形位置

		// 清空外切矩形原始資訊
		m_vecConnectPtRect.clear();

		// 更新連接點位置與其外切矩形
		for (int i = 0; i < m_vecConnectPt.size(); i++)
		{
			m_vecConnectPt[i].Offset(iOffsetX, iOffsetY);

			CRect rectConnect(CPoint(m_vecConnectPt[i].x - m_iConnectPtRadius, m_vecConnectPt[i].y - m_iConnectPtRadius),
							  CPoint(m_vecConnectPt[i].x + m_iConnectPtRadius, m_vecConnectPt[i].y + m_iConnectPtRadius));

			m_vecConnectPtRect.push_back(rectConnect);
		}
	}
}

