#pragma once
#include "CUnitBase.h"



class CUnitFUN : public CUnitBase
{
public:

    CUnitFUN(CRect rectShowRegion, CRect rectButton);

    // �ھڤ��������M�즲�᪺�첾�A��s�s���I�P��~���x�Ϊ���m
    virtual void SetConnectPtAndRect(int iOffsetX, int iOffsetY) override;

};

