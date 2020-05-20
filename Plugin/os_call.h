
#ifndef os_call_h
#define os_call_h

#if defined(_MSC_VER) // Microsoft compiler
	#include <windows.h>
#else
	#include <dlfcn.h>
#endif

#include<string>
/*
#define RTLD_LAZY   1
#define RTLD_NOW    2
#define RTLD_GLOBAL 4
*/

void* LoadSharedLibrary(char *pcDllname, int iMode = 2)	
//by default load all symbols now linux
{

	std::string sDllName = pcDllname;
	#if defined(_MSC_VER) // Microsoft compiler
	sDllName += ".dll";
		return (void*)LoadLibrary(pcDllname);
	#else // GNU compiler
	sDllName += ".so";
		return dlopen(sDllName.c_str(),iMode);
	#endif


}
void *GetFunction(void *Lib, char *Fnname)
{
	#if defined(_MSC_VER) // Microsoft compiler
		return (void*)GetProcAddress((HINSTANCE)Lib,Fnname);
	#else // GNU compiler
		return dlsym(Lib,Fnname);
	#endif
}

bool FreeSharedLibrary(void *hDLL)
{
	#if defined(_MSC_VER) // Microsoft compiler
		return FreeLibrary((HINSTANCE)hDLL);
	#elif defined(__GNUC__) // GNU compiler
		return dlclose(hDLL);
	#endif
}


#endif //os_call_h

