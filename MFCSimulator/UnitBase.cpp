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

	// �s���I�b�|�� 10 
	m_iConnectPtRadius = 10;

	// ��X�Ȭ� 0.0
	m_dOutValue = 0.0;

}


// UnitBase �Ѻc�l
UnitBase::~UnitBase()
{

	if (m_vecPtsPreUnit.empty() != TRUE)
	{
		// ����}�C�������аO����
		for (int i = 0; i < m_vecPtsPreUnit.size(); i++)
		{
			UnitBase* ptTemp = m_vecPtsPreUnit[i];
			delete ptTemp;
		}

		// �M�Ű}�C�����A�A�ŧi�@�ӪŰ}�C�P�䰵�洫����O����
		m_vecPtsPreUnit.clear();
		std::vector<UnitBase*>().swap(m_vecPtsPreUnit);
	}


	if (m_vecPtsNextUnit.empty() != TRUE)
	{
		// ����}�C�������аO����
		for (int i = 0; i < m_vecPtsNextUnit.size(); i++)
		{
			UnitBase* ptTemp = m_vecPtsNextUnit[i];
			delete ptTemp;
		}

		// �M�Ű}�C�����A�A�ŧi�@�ӪŰ}�C�P�䰵�洫����O����
		m_vecPtsNextUnit.clear();
		std::vector<UnitBase*>().swap(m_vecPtsNextUnit);
	}

}


