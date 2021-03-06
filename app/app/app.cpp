#include <iostream>
#include "..\..\exercise\01\lib\public.h"
#include "..\..\exercise\01\dll2\public.h"
#include <windows.h>
#include <stdlib.h>

#ifdef _M_X64
	char *platformFolder = "x64";
#else
	char *platformFolder = "Win32";
#endif

#ifdef _DEBUG
	char *configuartionFolder = "Debug";
#else
	char *configurationFolder = "Release";
#endif // DEBUG



typedef double func(int);

void staticlib (int v) 
{
	double ret = static_lib::get_value (v);
	std::cout << "Static library get_value returned :" << ret << "\n";
}

void dlllib(int v) 
{
	char buffer[200];
	char* dll1Lib = "..\\..\\exercise\\01\\dll1";
	sprintf_s(buffer, "%s\\%s\\%s\\dynamic_library.dll", dll1Lib, platformFolder, configurationFolder);
	
	HMODULE dll_lib_handle = LoadLibraryA(buffer);
	if (dll_lib_handle != NULL) {
		func* f = (func *)GetProcAddress(dll_lib_handle, "get_value");
		double r = f(v);
		if (f != NULL) 
		{
			std::cout << "Dynamic library function get_value returned :" << r << "\n";
		}
		
		else 
		{
			std::cout << "GetProcAddress returned null pointer\n";
			std::cout << GetLastError();
		}

	}
	else 
	{
		std::cout << "Failed to load dynamic_library.dll";
	}

	FreeLibrary(dll_lib_handle);

}

void dlllib_with_implib (int v) 
{
	double ret = get_value (v);
	std::cout << "Dynamic library with implib returned :" << ret << "\n";
}

int main() 
{
	int val = 5;

	staticlib (val);
	dlllib(val);
	dlllib_with_implib (val);
	return 0;
}