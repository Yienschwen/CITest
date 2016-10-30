#include "immintrin.h"

extern "C" float dot_product(float* pfltVecA, float* pfltVecB, unsigned N) {
	unsigned usgLoopCount = N / 8;
	unsigned usgRemain = N % 8;
	float *pfltAload, *pfltBload;
	pfltAload = pfltVecA;
	pfltBload = pfltVecB;
	float fltReturn = 0;
	for (unsigned i = 0; i < usgLoopCount; i++) {
		__m256 a = _mm256_loadu_ps(pfltAload);
		__m256 b = _mm256_loadu_ps(pfltBload);
		__m256 c = _mm256_dp_ps(a, b, 0xF1);
		fltReturn += c[0] + c[4];
		pfltAload += 8;
		pfltBload += 8;
	}
	for (unsigned i = 0; i < usgRemain; i++) {
		fltReturn += pfltAload[i] * pfltBload[i];	
	}
	return fltReturn;
}
