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

	// 初始點取狀態
	m_bFocusState = FALSE;

	// 連接點半徑為 14 
	m_iConnectPtRadius = 14;

	// 輸出值為 0.0
	m_strOutValue = _T("");

}


// UnitBase 解構子
UnitBase::~UnitBase()
{
	if (m_vecPtsPreLeftUnit.empty() != TRUE)
	{
		// 釋放陣列內的指標記憶體
		for (int i = 0; i < m_vecPtsPreLeftUnit.size(); i++)
		{
			UnitBase* ptTemp = m_vecPtsPreLeftUnit[i];
			delete ptTemp;
		}

		// 清空陣列元素，再宣告一個空陣列與其做交換釋放記憶體
		m_vecPtsPreLeftUnit.clear();
		std::vector<UnitBase*>().swap(m_vecPtsPreLeftUnit);

	}


	if (m_vecPtsPreRightUnit.empty() != TRUE)
	{
		// 釋放陣列內的指標記憶體
		for (int i = 0; i < m_vecPtsPreRightUnit.size(); i++)
		{
			UnitBase* ptTemp = m_vecPtsPreRightUnit[i];
			delete ptTemp;
		}

		// 清空陣列元素，再宣告一個空陣列與其做交換釋放記憶體
		m_vecPtsPreRightUnit.clear();
		std::vector<UnitBase*>().swap(m_vecPtsPreRightUnit);

	}

	//if (m_vecPtsPreUnit.empty() != TRUE)
	//{
	//	// 釋放陣列內的指標記憶體
	//	for (int i = 0; i < m_vecPtsPreUnit.size(); i++)
	//	{
	//		UnitBase* ptTemp = m_vecPtsPreUnit[i];
	//		delete ptTemp;
	//	}

	//	// 清空陣列元素，再宣告一個空陣列與其做交換釋放記憶體
	//	m_vecPtsPreUnit.clear();
	//	std::vector<UnitBase*>().swap(m_vecPtsPreUnit);
	//}


	if (m_vecPtsNextUnit.empty() != TRUE)
	{
		// 釋放陣列內的指標記憶體
		for (int i = 0; i < m_vecPtsNextUnit.size(); i++)
		{
			UnitBase* ptTemp = m_vecPtsNextUnit[i];
			delete ptTemp;
		}

		// 清空陣列元素，再宣告一個空陣列與其做交換釋放記憶體
		m_vecPtsNextUnit.clear();
		std::vector<UnitBase*>().swap(m_vecPtsNextUnit);
	}

}


