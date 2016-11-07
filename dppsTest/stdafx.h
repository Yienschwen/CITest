// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#if defined(_MSC_VER)
#pragma once
#endif

#include <iostream>

// cpuid
#if defined(_MSC_VER)

#define cpuid(info, x)    __cpuidex(info, x, 0)

#elif defined(__GNUC__) 

#include <cpuid.h>
void cpuid(int info[4], int InfoType) {
	__cpuid_count(InfoType, 0, info[0], info[1], info[2], info[3]);
}

#endif

#if defined(_WIN32) || defined(_WIN64)

#define DLFILE HINSTANCE
#include <Windows.h>
#include "targetver.h"
#include <tchar.h>

#elif defined(__linux__)

#include <dlfcn.h>
#define DLFILE void*
#define LoadLibrary(X) dlopen((X) , RTLD_LAZY )
#define FreeLibrary(X) dlclose((X))
#define GetProcAddress(X, Y) dlsym((X) , (Y))

#endif




#if defined(_MSC_VER)
typedef float(__cdecl *dpps_t)(float*, float*, unsigned);
typedef wchar_t cchar;

#define DL_APPEND L".dll"
#define OS_SEP L"\\"

#elif defined(__GNUC__)
typedef float(*dpps_t)(float*, float*, unsigned);
typedef char cchar;
#define TEXT(X) X

#define DL_APPEND ".so"
#define OS_SEP "/"

#endif




// TODO: reference additional headers your program requires here
