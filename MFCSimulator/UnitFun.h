#pragma once

#include "UnitBase.h"

class UnitFUN : public UnitBase
{
public:

    UnitFUN(CRect rectShowRegion, CRect rectButton);

    virtual void SetConnectPtAndRect(int iOffsetX, int iOffsetY) override;

    // �]�m���
    virtual void SetFuncOrOpera(CString strChoose) override;

    // ���󤧶����J����
    virtual void InsertUnit(UnitBase* ptNewUnit) override;

    // �O���u�q�I���
    virtual void UpdateDotData(CPoint pointNewLocation) override;

    // ��X���󪺵��G
    virtual void Result(double dRealTimeValue) override;

};

