#pragma once

#include "math.h"
#include <vector>



class CUnitBase
{

																												  
public:			

	// ����s�����
	std::vector<CUnitBase*> m_vecPtsPreLeftUnit;						// ���V�e�@�ӥ�����䤸�󪺫��а}�C�A�άO�u����@���V�e�@�Ӥ��䤸�󪺫��а}�C
	std::vector<CUnitBase*>  m_vecPtsPreRightUnit;						// ���V�e�@�ӥk����䤸�󪺫��а}�C	
	std::vector<CUnitBase*> m_vecPtsNextUnit;							// ���V�U�@�Ӥ��󪺫��а}�C


	// ������
	CPoint m_pointUnitLocation;											// �����m�A����x�Υ��W�����I
	int m_iUnitHeight;													// �����
	int m_iUnitWidth;													// ����e
	CString m_strUnitID;												// ��������
	BOOL m_bMoveState;													// �T�{�O�_�Q�즲
	BOOL m_bFocusState;													// �T�{�O�_�Q�I��
	int m_iUnitSaveNum;													// �O������ͦ����ǧǸ�
	

	// ��X�B�z
	CString m_strFuncOrOpera;											// �O����ܪ���ƩάO�B�⤸
	double m_dOutValue;													// ��X���ƭ�


	// �s���I��� 
	// �Ω���륪�k���I : 
	CPoint m_pointConnectLeftTop;										// ���W���s���I�γ��������s���I
	CPoint m_pointConnectRightTop;										// �k�W���s���I
	CPoint m_pointConnectBottom;										// �����s���I

	CRect m_rectConnectLeftTop;											// ���W�s���I�x�Ωγ��������s���I�x��
	CRect m_rectConnectRightTop;										// �k�W�s���I�x��
	CRect m_rectConnectBottom;											// �����s���I�x��

	int m_iConnectPtRadius;												// �s���I�b�|
	BOOL m_bConnectPoint;												// �T�{�O�_�Q�s��


	// �Ω�ø�� : 
	std::vector<CPoint> m_vecConnectPt;									// �x�s�s���I�I��T
	std::vector<CRect> m_vecConnectPtRect;								// �x�s�s���I�~���x�θ�T
	int m_iConnectPtAmount;												// �x�s���u�q�s���I�ƶq
	int m_iConnectPtRectAmount;											// �x�s���u�q�s���I�x�μƶq
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// �غc�l
	CUnitBase (CRect rectShowRegion, CRect rectButton);


	// �Ѻc�l
	~CUnitBase ();


	// �ھڤ��������M�즲�᪺�첾�A��s�s���I�P��~���x�Ϊ���m
	virtual void SetConnectPtAndRect (int iOffsetX, int iOffsetY) {};


};

