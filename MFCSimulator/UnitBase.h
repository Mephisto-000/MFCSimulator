#pragma once

#include "math.h"
#include <vector>

class UnitBase
{

protected:
	
	//std::vector<UnitBase*> m_arrPtsPreUnit;               // ���V�e�@�Ӥ��󪺫��а}�C
	//std::vector<UnitBase*> m_arrPtsNextUnit;              // ���V�U�@�Ӥ��󪺫��а}�C
														  
														  
public:			

	std::vector<UnitBase*> m_arrPtsPreUnit;               // ���V�e�@�Ӥ��󪺫��а}�C
	std::vector<UnitBase*> m_arrPtsNextUnit;              // ���V�U�@�Ӥ��󪺫��а}�C
	
	// ������
	CPoint m_pointUnitLocation;                           // �����m�A����x�Υ��W�����I
	int m_iUnitHeight;                                    // �����
	int m_iUnitWidth;                                     // ����e
	CString m_strUnitID;                                  // ��������
	BOOL m_bMoveState;                                    // �T�{�O�_�Q�즲
	
	// ��X�B�z
	CString m_strFuncOrOpera;							  // ������ܪ���ƩάO�B�⤸
	double m_dOutValue;                                   // ��X���ƭ�

	// �u�q���
	std::vector<CPoint> m_arrConnectPt;			          // �u�q�s���I
	int m_iConnectPtRadius;                               // �s���I�b�|
	BOOL m_bConnectPoint;                                 // �T�{�O�_�Q�s��
	



	// �غc�l
	UnitBase (CRect rectShowRegion, CRect rectButton);


	// �Ѻc�l
	~UnitBase ();


	// �]�m��ܪ���ƩάO�|�h�B�⤸
	virtual void SetFuncOrOpera(CString strChoose) {};


	// ��s�s��������
	virtual void InsertUnit(UnitBase* ptNewUnit) {};

	
	// �ھک즲��m��s�u�q�I���
	virtual void UpdateDotData(CPoint pointNewLocation) {};


	// ��X���󪺵��G
	virtual void Result(double dRealTimeValue) {};
};

