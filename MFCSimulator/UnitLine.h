#pragma once

#include "UnitBase.h"
#include <vector>

class UnitLine : public UnitBase
{
protected:
	std::vector<UnitBase*> m_arrPtsPreUnit;               // ���V�e�@�Ӥ��󪺫��а}�C
	std::vector<UnitBase*> m_arrPtsNextUnit;              // ���V�U�@�Ӥ��󪺫��а}�C

public:
	
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

