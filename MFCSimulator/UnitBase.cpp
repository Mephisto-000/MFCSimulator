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
	m_dOutValue = 0.0;

	m_iConnectPtAmount = 0;
	m_iConnectPtRectAmount = 0;
	m_iPreLeftPt = 0;
	m_iPreRightPt = 0;
	m_iNextPt = 0;

}


// UnitBase 解構子
UnitBase::~UnitBase()
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
		std::vector<UnitBase*>().swap(m_vecPtsPreLeftUnit);

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
		//// 釋放陣列內的指標記憶體
		//for (int i = 0; i < m_vecPtsNextUnit.size(); i++)
		//{
		//	UnitBase* ptTemp = m_vecPtsNextUnit[i];
		//	delete ptTemp;
		//}

		// 清空陣列元素，再宣告一個空陣列與其做交換釋放記憶體
		m_vecPtsNextUnit.clear();
		std::vector<UnitBase*>().swap(m_vecPtsNextUnit);
	}

}


//void UnitBase::Serialize(CArchive& ar)
//{
//	if (ar.IsStoring())
//	{
//
//		ar << m_pointUnitLocation;
//		ar << m_iUnitHeight;
//		ar << m_iUnitWidth;
//		ar << m_strUnitID;
//		ar << m_bMoveState; // 不用存
//		ar << m_bFocusState;
//
//		ar << m_strFuncOrOpera;
//		ar << m_dOutValue;
//
//
//		ar << m_pointConnectLeftTop;
//		ar << m_pointConnectRightTop;
//		ar << m_pointConnectBottom;
//		
//		ar << m_rectConnectLeftTop;
//		ar << m_rectConnectRightTop;
//		ar << m_rectConnectBottom;
//
//		ar << m_iConnectPtRadius;
//		ar << m_bConnectPoint;
//
//
//		m_iConnectPtAmount = m_vecConnectPt.size();
//		ar << m_iConnectPtAmount;
//		for (int i = 0; i < m_iConnectPtAmount; i++)
//		{
//			ar << m_vecConnectPt[i];
//		}
//
//
//		m_iConnectPtRectAmount = m_vecConnectPtRect.size();
//		ar << m_iConnectPtRectAmount;
//		for (int i = 0; i < m_iConnectPtRectAmount; i++)
//		{
//			ar << m_vecConnectPtRect[i];
//		}
//
//
//		
//		m_iPreLeftPt = m_vecPtsPreLeftUnit.size();
//		ar << m_iPreLeftPt;
//		for (int i = 0; i < m_iPreLeftPt; i++)
//		{
//			ar << m_vecPtsPreLeftUnit[i];
//		}
//		
//
//
//		m_iPreRightPt = m_vecPtsPreRightUnit.size();
//		ar << m_iPreRightPt;
//		for (int i = 0; i < m_iPreRightPt; i++)
//		{
//			ar << m_vecPtsPreRightUnit[i];
//		}
//
//
//		m_iNextPt = m_vecPtsNextUnit.size();
//		ar << m_iNextPt;
//		for (int i = 0; i < m_iNextPt; i++)
//		{
//			ar << m_vecPtsNextUnit[i];
//		}
//	}
//	else
//	{
//		ar >> m_pointUnitLocation;
//		ar >> m_iUnitHeight;
//		ar >> m_iUnitWidth;
//		ar >> m_strUnitID;
//		ar >> m_bMoveState;
//		ar >> m_bFocusState;
//		   
//		ar >> m_strFuncOrOpera;
//		ar >> m_dOutValue;
//		   
//		   
//		ar >> m_pointConnectLeftTop;
//		ar >> m_pointConnectRightTop;
//		ar >> m_pointConnectBottom;
//		   
//		ar >> m_rectConnectLeftTop;
//		ar >> m_rectConnectRightTop;
//		ar >> m_rectConnectBottom;
//		   
//		ar >> m_iConnectPtRadius;
//		ar >> m_bConnectPoint;
//
//
//
//		ar >> m_iConnectPtAmount;
//		if (m_iConnectPtAmount > 0)
//		{
//			m_vecConnectPt.resize(m_iConnectPtAmount);
//			for (int i = 0; i < m_iConnectPtAmount; i++)
//			{
//				ar >> m_vecConnectPt[i];
//			}
//		}
//
//
//
//		ar >> m_iConnectPtRectAmount;
//		if (m_iConnectPtRectAmount > 0)
//		{
//			m_vecConnectPtRect.resize(m_iConnectPtRectAmount);
//			for (int i = 0; i < m_iConnectPtRectAmount; i++)
//			{
//				ar >> m_vecConnectPtRect[i];
//			}
//		}
//
//
//		ar >> m_iPreLeftPt;
//		if (m_iPreLeftPt > 0)
//		{
//			m_vecPtsPreLeftUnit.resize(m_iPreLeftPt);
//			for (int i = 0; i < m_iPreLeftPt; i++)
//			{
//				ar >> m_vecPtsPreLeftUnit[i];
//			}
//		}
//
//
//
//		//for (int i = 0; i < 1; i++)
//		//{
//		//	
//
//		//}
//		
//
//
//		if (m_vecPtsPreRightUnit.empty() != TRUE)
//		{
//			for (int i = 0; i < m_vecPtsPreRightUnit.size(); i++)
//			{
//				ar << m_vecPtsPreRightUnit[i];
//			}
//		}
//
//
//		if (m_vecPtsNextUnit.empty() != TRUE)
//		{
//			for (int i = 0; i < m_vecPtsNextUnit.size(); i++)
//			{
//				ar << m_vecPtsNextUnit[i];
//			}
//		}
//
//	}
//
//}

