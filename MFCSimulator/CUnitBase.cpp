#include "pch.h"
#include "CUnitBase.h"




// UnitBase 建構子
CUnitBase::CUnitBase(CRect rectShowRegion, CRect rectButton)
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
	m_dOutValue = 0.0;

	m_iConnectPtAmount = 0;
	m_iConnectPtRectAmount = 0;
	m_iPreLeftPt = 0;
	m_iPreRightPt = 0;
	m_iNextPt = 0;

	m_iUnitSaveNum = 0;


}


// UnitBase 解構子
CUnitBase::~CUnitBase()
{
	if (m_vecPtsPreLeftUnit.empty() != TRUE)
	{
		//// 釋放陣列內的指標記憶體
		//for (int i = 0; i < m_vecPtsPreLeftUnit.size(); i++)
		//{
		//	UnitBase* ptTemp = m_vecPtsPreLeftUnit[i];
		//	delete ptTemp;
		//}

		// 清空陣列元素，再宣告一個空陣列與其做交換釋放記憶體
		m_vecPtsPreLeftUnit.clear();
		std::vector<CUnitBase*>().swap(m_vecPtsPreLeftUnit);

	}


	if (m_vecPtsPreRightUnit.empty() != TRUE)
	{
		//// 釋放陣列內的指標記憶體
		//for (int i = 0; i < m_vecPtsPreRightUnit.size(); i++)
		//{
		//	UnitBase* ptTemp = m_vecPtsPreRightUnit[i];
		//	delete ptTemp;
		//}

		// 清空陣列元素，再宣告一個空陣列與其做交換釋放記憶體
		m_vecPtsPreRightUnit.clear();
		std::vector<CUnitBase*>().swap(m_vecPtsPreRightUnit);

	}



	if (m_vecPtsNextUnit.empty() != TRUE)
	{

		// 清空陣列元素，再宣告一個空陣列與其做交換釋放記憶體
		m_vecPtsNextUnit.clear();
		std::vector<CUnitBase*>().swap(m_vecPtsNextUnit);
	}

}

