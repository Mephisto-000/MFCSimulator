#pragma once
#include "CUnitBase.h"
class CUnitOUT : public CUnitBase
{
public:

    CUnitOUT(CRect rectShowRegion, CRect rectButton);

    virtual void SetConnectPtAndRect(int iOffsetX, int iOffsetY) override;

    // ���󤧶����J����
    virtual void InsertUnit(CUnitBase* ptNewUnit) override;

    // �O���u�q�I���
    virtual void UpdateDotData(CPoint pointNewLocation) override;

    // ��X���󪺵��G
    virtual void Result(double dTimeValue) override;


};

