#pragma once

#include "UnitBase.h"
#include <vector>

class UnitLine : public UnitBase
{
public:

    CPoint m_pointLineStart;
    CPoint m_pointLineEnd;


	UnitLine(CRect rectShowRegion, CRect rectButton);


    // �]�m���
    virtual void SetFuncOrOpera(CString strChoose) override {};

    // ���󤧶����J����
    virtual void InsertUnit(UnitBase* ptNewUnit) override {};

    // �O���u�q�I���
    virtual void UpdateDotData(CPoint pointNewLocation) override {};

    // ��X���󪺵��G
    virtual void Result(double dRealTimeValue) override {};



};

