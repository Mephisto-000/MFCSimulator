#pragma once
#include "UnitBase.h"
class UnitAND : public UnitBase
{
public:

	double m_dLeftValue;
	double m_dRightValue;
	double m_dResult;


    UnitAND(CRect rectShowRegion, CRect rectButton);

    virtual void SetConnectPtAndRect(int iOffsetX, int iOffsetY) override;

    // ���󤧶����J����
    virtual void InsertUnit(UnitBase* ptNewUnit) override;

    // �O���u�q�I���
    virtual void UpdateDotData(CPoint pointNewLocation) override;

    // ��X���󪺵��G
    virtual void Result(double dTimeValue) override;
};

