#pragma once
#include "math.h"
#include "UnitBase.h"


class UnitIn : public UnitBase
{
public:
    
    // ������ܪ����
    CString m_strFunction; 

    double FunctionChoose(double dValue);

    // �O���u�q�I���
    void InsertDotData();


};

