// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the DPPSAVX_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// DPPSAVX_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.

#if defined(_MSC_VER)

	#ifdef DPPSAVX_EXPORTS
		#define DPPSAVX_API __declspec(dllexport)
	#else
		#define DPPSAVX_API __declspec(dllimport)
	#endif

#elif defined(__GNUC__)

	#if __GNUC__ >= 4
		#define DPPSAVX_API __attribute__ ((visibility ("default")))
	#else
		#define DPPSAVX_API
	#endif

#endif

extern "C" DPPSAVX_API float dpps(float*, float*, unsigned);
