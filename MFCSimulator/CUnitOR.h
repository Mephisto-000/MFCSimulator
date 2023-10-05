#pragma once
#include "CUnitBase.h"



class CUnitOR : public CUnitBase
{
public:

    CUnitOR(CRect rectShowRegion, CRect rectButton);

    // 根據元件類型和拖曳後的位移，更新連接點與其外切矩形的位置
    virtual void SetConnectPtAndRect(int iOffsetX, int iOffsetY) override;

};

