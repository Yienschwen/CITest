// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the DPPSSSE_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// DPPSSSE_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#if defined(_MSC_VER)

#ifdef DPPSSSE_EXPORTS
#define DPPSSSE_API __declspec(dllexport)
#else
#define DPPSSSE_API __declspec(dllimport)
#endif

#elif defined(__GNUC__)

#if __GNUC__ >= 4
#define DPPSSSE_API __attribute__ ((visibility ("default")))
#else
#define DPPSSSE_API
#endif

#endif

extern "C" DPPSSSE_API float dpps(float*, float*, unsigned);