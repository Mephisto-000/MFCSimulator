#pragma once

#include "math.h"
#include <vector>

class UnitBase
{

																												  
public:			

	std::vector<UnitBase*> m_vecPtsPreUnit;               // ���V�e�@�Ӥ��󪺫��а}�C
	std::vector<UnitBase*> m_vecPtsNextUnit;              // ���V�U�@�Ӥ��󪺫��а}�C
	
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
	std::vector<CPoint> m_vecConnectPt;			          // �u�q�s���I
	std::vector<CRect> m_vecConnectPtRect;                // �u�q�s���I�x��
	int m_iConnectPtRadius;                               // �s���I�b�|
	BOOL m_bConnectPoint;                                 // �T�{�O�_�Q�s��
	



	// �غc�l
	UnitBase (CRect rectShowRegion, CRect rectButton);


	// �Ѻc�l
	~UnitBase ();

	// �ھڤ����������X�s���I�s���I�x��
	virtual void SetConnectPtAndRect (int iOffsetX, int iOffsetY) {};


	// �]�m��ܪ���ƩάO�|�h�B�⤸
	virtual void SetFuncOrOpera (CString strChoose) {};


	// ��s�s��������
	virtual void InsertUnit (UnitBase* ptNewUnit) {};

	
	// �ھک즲��m��s�u�q�I���
	virtual void UpdateDotData (CPoint pointNewLocation) {};


	// ��X���󪺵��G
	virtual void Result (double dRealTimeValue) {};
};

