// dppsTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#if defined(_MSC_VER)

#define cpuid(info, x)    __cpuidex(info, x, 0)

#endif

float *A, *B;
unsigned N;


#if defined(_MSC_VER)
	typedef float(__cdecl *dpps_t)(float*, float*, unsigned);
#elif defined(__GNUC__)
	typedef float(*dpps_t)(float*, float*, unsigned);
#endif

int info[4], nIds;
unsigned nExIds;

bool HW_MMX;
bool HW_x64;
bool HW_ABM;      // Advanced Bit Manipulation
bool HW_RDRAND;
bool HW_BMI1;
bool HW_BMI2;
bool HW_ADX;
bool HW_PREFETCHWT1;

//  SIMD: 128-bit
bool HW_SSE;
bool HW_SSE2;
bool HW_SSE3;
bool HW_SSSE3;
bool HW_SSE41;
bool HW_SSE42;
bool HW_SSE4a;
bool HW_AES;
bool HW_SHA;

//  SIMD: 256-bit
bool HW_AVX;
bool HW_XOP;
bool HW_FMA3;
bool HW_FMA4;
bool HW_AVX2;

//  SIMD: 512-bit
bool HW_AVX512F;    //  AVX512 Foundation
bool HW_AVX512CD;   //  AVX512 Conflict Detection
bool HW_AVX512PF;   //  AVX512 Prefetch
bool HW_AVX512ER;   //  AVX512 Exponential + Reciprocal
bool HW_AVX512VL;   //  AVX512 Vector Length Extensions
bool HW_AVX512BW;   //  AVX512 Byte + Word
bool HW_AVX512DQ;   //  AVX512 Doubleword + Quadword
bool HW_AVX512IFMA; //  AVX512 Integer 52-bit Fused Multiply-Add
bool HW_AVX512VBMI; //  AVX512 Vector Byte Manipulation Instructions

void cpuflags() {

	if (nIds >= 0x00000001) {
		cpuid(info, 0x00000001);
		HW_MMX = (info[3] & ((int)1 << 23)) != 0;
		HW_SSE = (info[3] & ((int)1 << 25)) != 0;
		HW_SSE2 = (info[3] & ((int)1 << 26)) != 0;
		HW_SSE3 = (info[2] & ((int)1 << 0)) != 0;

		HW_SSSE3 = (info[2] & ((int)1 << 9)) != 0;
		HW_SSE41 = (info[2] & ((int)1 << 19)) != 0;
		HW_SSE42 = (info[2] & ((int)1 << 20)) != 0;
		HW_AES = (info[2] & ((int)1 << 25)) != 0;

		HW_AVX = (info[2] & ((int)1 << 28)) != 0;
		HW_FMA3 = (info[2] & ((int)1 << 12)) != 0;

		HW_RDRAND = (info[2] & ((int)1 << 30)) != 0;
	}
	if (nIds >= 0x00000007) {
		cpuid(info, 0x00000007);
		HW_AVX2 = (info[1] & ((int)1 << 5)) != 0;

		HW_BMI1 = (info[1] & ((int)1 << 3)) != 0;
		HW_BMI2 = (info[1] & ((int)1 << 8)) != 0;
		HW_ADX = (info[1] & ((int)1 << 19)) != 0;
		HW_SHA = (info[1] & ((int)1 << 29)) != 0;
		HW_PREFETCHWT1 = (info[2] & ((int)1 << 0)) != 0;

		HW_AVX512F = (info[1] & ((int)1 << 16)) != 0;
		HW_AVX512CD = (info[1] & ((int)1 << 28)) != 0;
		HW_AVX512PF = (info[1] & ((int)1 << 26)) != 0;
		HW_AVX512ER = (info[1] & ((int)1 << 27)) != 0;
		HW_AVX512VL = (info[1] & ((int)1 << 31)) != 0;
		HW_AVX512BW = (info[1] & ((int)1 << 30)) != 0;
		HW_AVX512DQ = (info[1] & ((int)1 << 17)) != 0;
		HW_AVX512IFMA = (info[1] & ((int)1 << 21)) != 0;
		HW_AVX512VBMI = (info[2] & ((int)1 << 1)) != 0;
	}
	if (nExIds >= 0x80000001) {
		cpuid(info, 0x80000001);
		HW_x64 = (info[3] & ((int)1 << 29)) != 0;
		HW_ABM = (info[2] & ((int)1 << 5)) != 0;
		HW_SSE4a = (info[2] & ((int)1 << 6)) != 0;
		HW_FMA4 = (info[2] & ((int)1 << 16)) != 0;
		HW_XOP = (info[2] & ((int)1 << 11)) != 0;
	}
}

int testFunc(const wchar_t* strLib) {

	// typedef int(__cdecl *MYPROC)(float*, float*, unsigned);

	HINSTANCE hinstLib;
	dpps_t ProcAdd;
	BOOL fFreeResult, fRunTimeLinkSuccess = FALSE;
	int intReturn = 1;
	// Get a handle to the DLL module.

	hinstLib = LoadLibrary(strLib);

	// If the handle is valid, try to get the function address.

	if (hinstLib != NULL)
	{
		ProcAdd = (dpps_t) GetProcAddress(hinstLib, "dpps");

		// If the function address is valid, call the function.

		if (NULL != ProcAdd)
		{
			fRunTimeLinkSuccess = TRUE;
			float fltResult = ProcAdd(A, B, N);
			std::cout << "dpps result: " << fltResult << '\n';
			delete[] A;
			delete[] B;
			intReturn = 0;
		}
		// Free the DLL module.

		fFreeResult = FreeLibrary(hinstLib);
	}

	// If unable to call the DLL function, use an alternative.

	return intReturn;
}

int main() {
	cpuid(info, 0);
	nIds = info[0];
	cpuid(info, 0x80000000);
	nExIds = info[0];
	cpuflags();

	std::cin >> N;
	A = new float[N];
	B = new float[N];
	for (unsigned i = 0; i < N; i++) {
		std::cin >> A[i];
	}
	for (unsigned i = 0; i < N; i++) {
		std::cin >> B[i];
	}
	std::cout << "Vectors input finished\n";

	int intReturn = 0;
	if (HW_AVX) {
		std::cout << "AVX detected.\n";
		intReturn = testFunc(L".\\dpps.avx.dll");
	}
	if (HW_SSE && HW_SSE41 && intReturn) {
		std::cout << "SSE and SSE4.1 detected.\n";
		intReturn = testFunc(L".\\dpps.sse.dll");
	}
	if (intReturn) {
		std::cerr << "No availiable library.\n";
		delete[] A;
		delete[] B;
		return 1;
	}
	return 0;
}

