#include <iostream>

float dot_product(float*, float*, unsigned);

using namespace std;

int main() {
	unsigned N;
	cin >> N;
	float * A = new float[N];
	float * B = new float[N];

	for (unsigned i = 0; i < N; i++) {
		cin >> A[i];
	}

	for (unsigned i = 0; i < N; i++) {
		cin >> B[i];	
	}

	float fltDp = dot_product(A, B, N);
	cout << "Result: " << fltDp << '\n';
	return 0;
}
