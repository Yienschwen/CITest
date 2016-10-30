#include "smmintrin.h"

extern "C" float dot_product(float* pfltVecA, float* pfltVecB, unsigned N) {
	unsigned usgLoopCount = N / 4;
	unsigned usgRemain = N % 4;
	float *pfltAload, *pfltBload;
	pfltAload = pfltVecA;
	pfltBload = pfltVecB;
	float fltReturn = 0;
	for (unsigned i = 0; i < usgLoopCount; i++) {
		__m128 a = _mm_loadu_ps(pfltAload);
		__m128 b = _mm_loadu_ps(pfltBload);
		__m128 c = _mm_dp_ps(a, b, 0xF1);
		fltReturn += c[0];
		pfltAload += 4;
		pfltBload += 4;
	}
	for (unsigned i = 0; i < usgRemain; i++) {
		fltReturn += pfltAload[i] * pfltBload[i];	
	}
	return fltReturn;
}
