#include "pch.h"
#include "UnitBase.h"
#include <cstddef>  // for size_t




// UnitBase 建構子
UnitBase::UnitBase(UnitBase* ptPreUnit, CString strUnitID, CRect rectShowRegion, CRect rectButton)
{

	// 初始化指標陣列
	m_arrPtsPreUnit.push_back(ptPreUnit);

	// 確認元件種類
	m_UnitID = strUnitID;

	// 新建立時沒有連接
	m_bConnectPoint = FALSE;

	// 元件生成位置在操作畫面中
	// 取得操作畫面長寬
	int iShowRegH = rectShowRegion.Height();
	int iShowRegW = rectShowRegion.Width();

	// 取得元件長寬
	int iButtonH = rectButton.Height();
	int iButtonW = rectButton.Height();


	pointUnitLocation = CPoint(iShowRegW * 0.5, iShowRegH * 0.5);
	m_iUnitWidth = iButtonW;
	m_iUnitHeight = iButtonH;


	m_dOutValue = 0.0;

}


// UnitBase 解構子
UnitBase::~UnitBase()
{

	if (m_arrPtsPreUnit.empty() != TRUE)
	{
		// 釋放陣列內的指標記憶體
		for (int i = 0; i < m_arrPtsPreUnit.size(); i++)
		{
			UnitBase* ptTemp = m_arrPtsPreUnit[i];
			delete ptTemp;
		}

		// 清空陣列元素，再宣告一個空陣列與其做交換釋放記憶體
		m_arrPtsPreUnit.clear();
		std::vector<UnitBase*>().swap(m_arrPtsPreUnit);
	}


	if (m_arrPtsNextUnit.empty() != TRUE)
	{
		// 釋放陣列內的指標記憶體
		for (int i = 0; i < m_arrPtsNextUnit.size(); i++)
		{
			UnitBase* ptTemp = m_arrPtsNextUnit[i];
			delete ptTemp;
		}

		// 清空陣列元素，再宣告一個空陣列與其做交換釋放記憶體
		m_arrPtsNextUnit.clear();
		std::vector<UnitBase*>().swap(m_arrPtsNextUnit);
	}

}


