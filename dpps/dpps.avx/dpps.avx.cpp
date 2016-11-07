// dpps.avx.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "dpps.avx.h"

extern "C" DPPSAVX_API float dpps(float* pfltVecA, float* pfltVecB, unsigned N) {
	unsigned usgLoopCount = N / 8;
	unsigned usgRemain = N % 8;
	float *pfltAload, *pfltBload;
	pfltAload = pfltVecA;
	pfltBload = pfltVecB;
	float fltReturn = 0;
	__m256 sum = _mm256_setzero_ps();
	for (unsigned i = 0; i < usgLoopCount; i++) {
		__m256 a = _mm256_loadu_ps(pfltAload);
		__m256 b = _mm256_loadu_ps(pfltBload);
		__m256 c = _mm256_dp_ps(a, b, 0xF1);
		sum = _mm256_add_ps(sum, c);
		pfltAload += 8;
		pfltBload += 8;
	}
	float pfSum[8];
	_mm256_storeu_ps(pfSum, sum);
	fltReturn = pfSum[0] + pfSum[4];
	for (unsigned i = 0; i < usgRemain; i++) {
		fltReturn += pfltAload[i] * pfltBload[i];
	}
	return fltReturn;
}