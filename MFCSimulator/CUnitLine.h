#pragma once

#include "CUnitBase.h"
#include <vector>

class CUnitLine : public CUnitBase
{
public:

    // �����u�q�s�I�_�I
    int m_iConnectPrePtIndex;

    // �����u�q�s���I���I
    int m_iConnectNextPtIndex;

    BOOL m_bIsConnect;

    // ���ʤ����u���I
    CPoint m_pointMovingLinePos;

	CUnitLine(CRect rectShowRegion, CRect rectButton);

    ~CUnitLine();

    // ���󤧶����J����
    virtual void InsertUnit(CUnitBase* ptNewUnit) override {};

    // �O���u�q�I���
    virtual void UpdateDotData(CPoint pointNewLocation) override {};

    // ��X���󪺵��G
    virtual void Result(double dTimeValue) override {};



};

