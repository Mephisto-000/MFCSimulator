#pragma once

#include "UnitBase.h"
#include <vector>

class UnitLine : public UnitBase
{
public:

    // 紀錄連接哪個點
    int m_iConnectPrePtIndex;
    int m_iConnectNextPtIndex;

    BOOL m_bIsConnect;

    // 移動中的線終點
    CPoint m_pointMovingLinePos;

	UnitLine(CRect rectShowRegion, CRect rectButton);


    // 設置函數
    virtual void SetFuncOrOpera(CString strChoose) override {};

    // 元件之間插入元件
    virtual void InsertUnit(UnitBase* ptNewUnit) override {};

    // 記錄線段點資料
    virtual void UpdateDotData(CPoint pointNewLocation) override {};

    // 輸出元件的結果
    virtual void Result(double dRealTimeValue) override {};



};

