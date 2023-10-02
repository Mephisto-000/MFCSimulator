#include "pch.h"
#include "UnitBase.h"




// UnitBase �غc�l
UnitBase::UnitBase(CRect rectShowRegion, CRect rectButton)
{

	// �s�إ߮ɨS���s��
	m_bConnectPoint = FALSE;

	// ���o������e
	int iButtonH = rectButton.Height();
	int iButtonW = rectButton.Width();

	// �����l�ͦ�����m��e�����W
	m_iUnitWidth = iButtonW;
	m_iUnitHeight = iButtonH;
	m_pointUnitLocation = CPoint(0, 0);

	// ��l�즲���A
	m_bMoveState = FALSE;

	// ��l�I�����A
	m_bFocusState = FALSE;

	// �s���I�b�|�� 14 
	m_iConnectPtRadius = 14;

	// ��X�Ȭ� 0.0
	m_dOutValue = 0.0;

	m_iConnectPtAmount = 0;
	m_iConnectPtRectAmount = 0;
	m_iPreLeftPt = 0;
	m_iPreRightPt = 0;
	m_iNextPt = 0;

}


// UnitBase �Ѻc�l
UnitBase::~UnitBase()
{
	if (m_vecPtsPreLeftUnit.empty() != TRUE)
	{
		//// ����}�C�������аO����
		//for (int i = 0; i < m_vecPtsPreLeftUnit.size(); i++)
		//{
		//	UnitBase* ptTemp = m_vecPtsPreLeftUnit[i];
		//	delete ptTemp;
		//}

		// �M�Ű}�C�����A�A�ŧi�@�ӪŰ}�C�P�䰵�洫����O����
		m_vecPtsPreLeftUnit.clear();
		std::vector<UnitBase*>().swap(m_vecPtsPreLeftUnit);

	}


	if (m_vecPtsPreRightUnit.empty() != TRUE)
	{
		//// ����}�C�������аO����
		//for (int i = 0; i < m_vecPtsPreRightUnit.size(); i++)
		//{
		//	UnitBase* ptTemp = m_vecPtsPreRightUnit[i];
		//	delete ptTemp;
		//}

		// �M�Ű}�C�����A�A�ŧi�@�ӪŰ}�C�P�䰵�洫����O����
		m_vecPtsPreRightUnit.clear();
		std::vector<UnitBase*>().swap(m_vecPtsPreRightUnit);

	}

	//if (m_vecPtsPreUnit.empty() != TRUE)
	//{
	//	// ����}�C�������аO����
	//	for (int i = 0; i < m_vecPtsPreUnit.size(); i++)
	//	{
	//		UnitBase* ptTemp = m_vecPtsPreUnit[i];
	//		delete ptTemp;
	//	}

	//	// �M�Ű}�C�����A�A�ŧi�@�ӪŰ}�C�P�䰵�洫����O����
	//	m_vecPtsPreUnit.clear();
	//	std::vector<UnitBase*>().swap(m_vecPtsPreUnit);
	//}


	if (m_vecPtsNextUnit.empty() != TRUE)
	{
		//// ����}�C�������аO����
		//for (int i = 0; i < m_vecPtsNextUnit.size(); i++)
		//{
		//	UnitBase* ptTemp = m_vecPtsNextUnit[i];
		//	delete ptTemp;
		//}

		// �M�Ű}�C�����A�A�ŧi�@�ӪŰ}�C�P�䰵�洫����O����
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
//		ar << m_bMoveState; // ���Φs
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

