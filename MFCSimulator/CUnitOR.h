#pragma once
#include "CUnitBase.h"
class CUnitOR : public CUnitBase
{
public:

	double m_dLeftValue;
	double m_dRightValue;
	double m_dResult;

    CUnitOR(CRect rectShowRegion, CRect rectButton);

    virtual void SetConnectPtAndRect(int iOffsetX, int iOffsetY) override;

    // ���󤧶����J����
    virtual void InsertUnit(CUnitBase* ptNewUnit) override;

    // �O���u�q�I���
    virtual void UpdateDotData(CPoint pointNewLocation) override;

    // ��X���󪺵��G
    virtual void Result(double dTimeValue) override;

};

