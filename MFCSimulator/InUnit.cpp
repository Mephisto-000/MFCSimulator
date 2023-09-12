#include "pch.h"
#include "InUnit.h"




double InUnit::FunctionChoose (double dValue)
{
	if (strFunction == "sin(t)")
	{
		return sin(dValue);
	}
	else if (strFunction == "cos(t)")
	{
		return cos(dValue);
	}
	else if (strFunction == "True")
	{	// True
		return 1;
	}
	else
	{	// False
		return 0;
	}
}