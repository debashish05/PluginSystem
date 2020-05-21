/* It is entry point of dll. In linux it is optional to provide entry point 
but can be provideda as

void __attribute__ ((constructor)) initLibrary(void) {}
void __attribute__ ((destructor)) cleanUpLibrary(void) {}

https://stackoverflow.com/questions/12463718/linux-equivalent-of-dllmain
*/
#pragma once


#if defined(_MSC_VER) // Microsoft compiler
	#include <windows.h>
#else
	#include <dlfcn.h>
#endif


#if defined(_MSC_VER)
	bool __cdecl DllMain( HANDLE hModule, 			
	// APIENTRY means __stdcall but we are using __cdecl convention in roadrunner
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
				 )
/*#elif defined(__GNUC__)
	 bool DllMain( void * hModule, 	//by default it is __cdecl
                       unsigned long  ul_reason_for_call, 
                       void *lpReserved
				 )

#endif // GNU compiler*/

{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return true;
}