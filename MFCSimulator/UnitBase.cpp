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

	// �s���I�b�|�� 8 
	m_iConnectPtRadius = 15;

	// ��X�Ȭ� 0.0
	m_dOutValue = 0.0;

}


// UnitBase �Ѻc�l
UnitBase::~UnitBase()
{

	if (m_arrPtsPreUnit.empty() != TRUE)
	{
		// ����}�C�������аO����
		for (int i = 0; i < m_arrPtsPreUnit.size(); i++)
		{
			UnitBase* ptTemp = m_arrPtsPreUnit[i];
			delete ptTemp;
		}

		// �M�Ű}�C�����A�A�ŧi�@�ӪŰ}�C�P�䰵�洫����O����
		m_arrPtsPreUnit.clear();
		std::vector<UnitBase*>().swap(m_arrPtsPreUnit);
	}


	if (m_arrPtsNextUnit.empty() != TRUE)
	{
		// ����}�C�������аO����
		for (int i = 0; i < m_arrPtsNextUnit.size(); i++)
		{
			UnitBase* ptTemp = m_arrPtsNextUnit[i];
			delete ptTemp;
		}

		// �M�Ű}�C�����A�A�ŧi�@�ӪŰ}�C�P�䰵�洫����O����
		m_arrPtsNextUnit.clear();
		std::vector<UnitBase*>().swap(m_arrPtsNextUnit);
	}

}


