#pragma once
#include "math.h"
#include "UnitBase.h"


class UnitIn : public UnitBase
{
public:
    
    // 紀錄選擇的函數
    CString m_strFunction; 

    double FunctionChoose(double dValue);

    // 記錄線段點資料
    void InsertDotData();


};

