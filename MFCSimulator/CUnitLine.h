#pragma once

#include "CUnitBase.h"
#include <vector>

class CUnitLine : public CUnitBase
{
public:

    // 紀錄線段連點起點
    int m_iConnectPrePtIndex;

    // 紀錄線段連接點終點
    int m_iConnectNextPtIndex;

    BOOL m_bIsConnect;

    // 移動中的線終點
    CPoint m_pointMovingLinePos;

	CUnitLine(CRect rectShowRegion, CRect rectButton);

    ~CUnitLine();

    // 元件之間插入元件
    virtual void InsertUnit(CUnitBase* ptNewUnit) override {};

    // 記錄線段點資料
    virtual void UpdateDotData(CPoint pointNewLocation) override {};

    // 輸出元件的結果
    virtual void Result(double dTimeValue) override {};



};

