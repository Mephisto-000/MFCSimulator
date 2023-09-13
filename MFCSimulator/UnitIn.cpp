#include "pch.h"
#include "UnitIn.h"


double UnitIn::FunctionChoose (double dValue)
{
	if (m_strFunction == "sin(t)")
	{
		return sin(dValue);
	}
	else if (m_strFunction == "cos(t)")
	{
		return cos(dValue);
	}
	else if (m_strFunction == "True")
	{	// True
		return 1;
	}
	else
	{	// False
		return 0;
	}

	
}


void InsertDotData()
{



}



