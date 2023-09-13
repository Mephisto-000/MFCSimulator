#pragma once

#include <vector>

class UnitBase
{

protected:
	
	std::vector<UnitBase*> m_arrPtsPreUnit;               // ���V�e�@�Ӥ��󪺫��а}�C
	std::vector<UnitBase*> m_arrPtsNextUnit;              // ���V�U�@�Ӥ��󪺫��а}�C
														  
	CString m_UnitID;                                     // �T�{�O���@�ؤ���
														  
public:													  
														  
	CPoint pointUnitLocation;                             // �����m
	std::vector<CPoint> m_pointLineLocation;              // �u�q�s���I��m
	BOOL m_bConnectPoint;                                 // �T�{�O�_�Q�s��
	int m_iUnitHeight;                                    // �����
	int m_iUnitWidth;                                     // ����e
	double m_dOutValue;                                   // ��X���ƭ�
	




	// �غc�l
	UnitBase (UnitBase* ptPreUnit, CString strUnitID, CRect rectShowRegion, CRect rectButton);

	// �Ѻc�l
	~UnitBase ();



	// ���󤧶����J����
	void InsertUnit(UnitBase* ptPreUnit, CString strUnitID, CRect rectButton);



	//// �O���u�q���
	//void InsertLineData();

	//// �O���u�q�I���
	//void InsertDotData();
};

