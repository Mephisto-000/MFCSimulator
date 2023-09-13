#include "pch.h"
#include "UnitBase.h"
#include <cstddef>  // for size_t




// UnitBase �غc�l
UnitBase::UnitBase(UnitBase* ptPreUnit, CString strUnitID, CRect rectShowRegion, CRect rectButton)
{

	// ��l�ƫ��а}�C
	m_arrPtsPreUnit.push_back(ptPreUnit);

	// �T�{�������
	m_UnitID = strUnitID;

	// �s�إ߮ɨS���s��
	m_bConnectPoint = FALSE;

	// ����ͦ���m�b�ާ@�e����
	// ���o�ާ@�e�����e
	int iShowRegH = rectShowRegion.Height();
	int iShowRegW = rectShowRegion.Width();

	// ���o������e
	int iButtonH = rectButton.Height();
	int iButtonW = rectButton.Height();


	pointUnitLocation = CPoint(iShowRegW * 0.5, iShowRegH * 0.5);
	m_iUnitWidth = iButtonW;
	m_iUnitHeight = iButtonH;


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


