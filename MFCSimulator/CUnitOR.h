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

    // 元件之間插入元件
    virtual void InsertUnit(CUnitBase* ptNewUnit) override;

    // 記錄線段點資料
    virtual void UpdateDotData(CPoint pointNewLocation) override;

    // 輸出元件的結果
    virtual void Result(double dTimeValue) override;

};

