#pragma once

#include "math.h"
#include <vector>

class UnitBase
{

																												  
public:			

	// TODO ���륪�k
	std::vector<UnitBase*> m_vecPtsPreLeftUnit;			  // ���V�e�@�ӥ�����䤸�󪺫��а}�C�A�άO�u����@���V�e�@�Ӥ��䤸�󪺫��а}�C
	std::vector<UnitBase*>  m_vecPtsPreRightUnit;		  // ���V�e�@�ӥk����䤸�󪺫��а}�C	
	std::vector<UnitBase*> m_vecPtsNextUnit;              // ���V�U�@�Ӥ��󪺫��а}�C

	int m_iPreLeftPt;									  // ������V�e����s��������ƶq
	int m_iPreRightPt;									  // �k����V�e����s��������ƶq
	int m_iNextPt;                                        // ���V�U�@�Ӥ���s��������ƶq


	
	// ������
	CPoint m_pointUnitLocation;                           // �����m�A����x�Υ��W�����I
	int m_iUnitHeight;                                    // �����
	int m_iUnitWidth;                                     // ����e
	CString m_strUnitID;                                  // ��������
	BOOL m_bMoveState;                                    // �T�{�O�_�Q�즲
	BOOL m_bFocusState;                                   // �T�{�O�_�Q�I��
	int m_iUnitSaveNum;                                   // ��������ͦ�����
	
	// ��X�B�z
	CString m_strFuncOrOpera;							  // ������ܪ���ƩάO�B�⤸
	double m_dOutValue;                                   // ��X���ƭ�

	// �u�q��� 
	// �����u����@�s���I�ɡA�N��@�����I�s�󥪤W���I
	// �Ω���륪�k���I : 
	CPoint m_pointConnectLeftTop;                         // ���W���s���I�γ��������s���I
	CPoint m_pointConnectRightTop;						  // �k�W���s���I
	CPoint m_pointConnectBottom;						  // �����s���I

	CRect m_rectConnectLeftTop;                           // ���W�s���I�x�Ωγ��������s���I�x��
	CRect m_rectConnectRightTop;                          // �k�W�s���I�x��
	CRect m_rectConnectBottom;                            // �����s���I�x��

	// �Ω�ø�� : 
	std::vector<CPoint> m_vecConnectPt;			          // �u�q�s���I
	std::vector<CRect> m_vecConnectPtRect;                // �u�q�s���I�x��
	int m_iConnectPtAmount;								  // �u�q�s���I�ƶq
	int m_iConnectPtRectAmount;                           // �u�q�s���I�x�μƶq
	

	int m_iConnectPtRadius;                               // �s���I�b�|
	BOOL m_bConnectPoint;                                 // �T�{�O�_�Q�s��




	// �غc�l
	UnitBase (CRect rectShowRegion, CRect rectButton);


	// �Ѻc�l
	~UnitBase ();

	// �ھڤ��������M�즲�᪺�첾�A��s�s���I�P��~���x�Ϊ���m
	virtual void SetConnectPtAndRect (int iOffsetX, int iOffsetY) {};


	// ��s�s��������
	virtual void InsertUnit (UnitBase* ptNewUnit) {};

	
	// �ھک즲��m��s�u�q�I���
	virtual void UpdateDotData (CPoint pointNewLocation) {};


	// ��X���󪺵��G
	virtual void Result (double dTimeValue) {};


	//// �ǦC�ƨ�ơA�Ω��x�s�MŪ��
	//virtual void Serialize(CArchive& ar);

};

