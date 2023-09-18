#include "pch.h"
#include "UnitBase.h"




// UnitBase 建構子
UnitBase::UnitBase(CRect rectShowRegion, CRect rectButton)
{

	// 新建立時沒有連接
	m_bConnectPoint = FALSE;

	// 取得元件長寬
	int iButtonH = rectButton.Height();
	int iButtonW = rectButton.Width();

	// 元件初始生成的位置於畫面左上
	m_iUnitWidth = iButtonW;
	m_iUnitHeight = iButtonH;
	m_pointUnitLocation = CPoint(0, 0);

	// 初始拖曳狀態
	m_bMoveState = FALSE;

	// 連接點半徑為 8 
	m_iConnectPtRadius = 15;

	// 輸出值為 0.0
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


