#pragma once

#include "UnitBase.h"


class UnitIn : public UnitBase
{
public:

    UnitIn(CRect rectShowRegion, CRect rectButton);

    // �]�m���
    virtual void SetFuncOrOpera(CString strChoose) override;

    // ���󤧶����J����
    virtual void InsertUnit(UnitBase* ptNewUnit) override;

    // �O���u�q�I���
    virtual void UpdateDotData(CPoint pointNewLocation) override;

    // ��X���󪺵��G
    virtual void Result(double dRealTimeValue) override;
};
