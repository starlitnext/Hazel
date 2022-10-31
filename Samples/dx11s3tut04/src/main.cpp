////////////////////////////////////////////////////////////////////////////////
// Filename: main.cpp
// https://www.rastertek.com/dx11s3tut04.html
////////////////////////////////////////////////////////////////////////////////
#include "systemclass.h"


int main()
{
	SystemClass* System;
	bool result;
	
	
	// Create the system object.
	System = new SystemClass;

	// Initialize and run the system object.
	result = System->Initialize();
	if(result)
	{
		System->Run();
	}

	// Shutdown and release the system object.
	System->Shutdown();
	delete System;
	System = 0;

	return 0;
}