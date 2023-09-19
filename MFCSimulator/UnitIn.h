#pragma once

#include "UnitBase.h"


class UnitIN : public UnitBase
{
public:

    UnitIN(CRect rectShowRegion, CRect rectButton);

    virtual void SetConnectPtAndRect() override;

    // 設置函數
    virtual void SetFuncOrOpera(CString strChoose) override;

    // 元件之間插入元件
    virtual void InsertUnit(UnitBase* ptNewUnit) override;

    // 記錄線段點資料
    virtual void UpdateDotData(CPoint pointNewLocation) override;

    // 輸出元件的結果
    virtual void Result(double dRealTimeValue) override;
};

