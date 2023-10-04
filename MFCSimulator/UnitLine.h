#pragma once

#include "UnitBase.h"
#include <vector>

class UnitLine : public UnitBase
{
public:

    // �����u�q�s�I�_�I
    int m_iConnectPrePtIndex;

    // �����u�q�s���I���I
    int m_iConnectNextPtIndex;

    BOOL m_bIsConnect;

    // ���ʤ����u���I
    CPoint m_pointMovingLinePos;

	UnitLine(CRect rectShowRegion, CRect rectButton);

    ~UnitLine();

    // ���󤧶����J����
    virtual void InsertUnit(UnitBase* ptNewUnit) override {};

    // �O���u�q�I���
    virtual void UpdateDotData(CPoint pointNewLocation) override {};

    // ��X���󪺵��G
    virtual void Result(double dTimeValue) override {};



};

