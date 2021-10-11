#pragma once

//#include "resource.h"		// main symbols
#include "framework.h"

class CCalculatorApp : public CWinApp
{
public:
	CCalculatorApp();
	virtual BOOL InitInstance();
};

extern CCalculatorApp theApp;
