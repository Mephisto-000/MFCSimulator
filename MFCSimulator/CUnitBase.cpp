#include "pch.h"
#include "CUnitBase.h"




// UnitBase �غc�l
CUnitBase::CUnitBase(CRect rectShowRegion, CRect rectButton)
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

	m_iUnitSaveNum = 0;


}


// UnitBase �Ѻc�l
CUnitBase::~CUnitBase()
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
		std::vector<CUnitBase*>().swap(m_vecPtsPreLeftUnit);

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
		std::vector<CUnitBase*>().swap(m_vecPtsPreRightUnit);

	}



	if (m_vecPtsNextUnit.empty() != TRUE)
	{

		// �M�Ű}�C�����A�A�ŧi�@�ӪŰ}�C�P�䰵�洫����O����
		m_vecPtsNextUnit.clear();
		std::vector<CUnitBase*>().swap(m_vecPtsNextUnit);
	}

}

