// dpps.sse.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "dpps.sse.h"


extern "C" DPPSSSE_API float dpps(float* pfltVecA, float* pfltVecB, unsigned N) {
	unsigned usgLoopCount = N / 4;
	unsigned usgRemain = N % 4;
	float *pfltAload, *pfltBload;
	pfltAload = pfltVecA;
	pfltBload = pfltVecB;
	float fltReturn = 0;
	__m128 sum = _mm_setzero_ps();
	for (unsigned i = 0; i < usgLoopCount; i++) {
		__m128 a = _mm_loadu_ps(pfltAload);
		__m128 b = _mm_loadu_ps(pfltBload);
		__m128 c = _mm_dp_ps(a, b, 0xF1);
		sum = _mm_add_ps(sum, c);
		pfltAload += 4;
		pfltBload += 4;
	}
	float pfSum[4];
	_mm_storeu_ps(pfSum, sum);
	fltReturn = pfSum[0];
	for (unsigned i = 0; i < usgRemain; i++) {
		fltReturn += pfltAload[i] * pfltBload[i];
	}
	return fltReturn;
}

