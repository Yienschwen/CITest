all: dpps_test dpps_so

dpps_test: dpps_test.cc
	g++ dpps_test.cc -ldl -o dpps_test

dpps_so: dpps.avx.so dpps.sse41.so

dpps.avx.so: dpps.avx.cc
	g++ dpps.avx.cc -fPIC -shared -o dpps.avx.so -mavx

dpps.sse41.so: dpps.sse41.cc
	g++ dpps.sse41.cc -fPIC -shared -o dpps.sse41.so -msse4.1

test: test_both test_avx test_sse test_none

test_both: all
	printf "\n[[[test both]]]\n"
	mkdir test_both
	cp dpps_test dpps.*.so test_both/
	cd test_both && ./dpps_test < ../input.txt

test_avx: dpps_test dpps.avx.so
	printf "\n[[[test without avx]]]\n"
	mkdir test_avx
	cp dpps_test dpps.avx.so test_avx/
	cd test_avx/ && ./dpps_test < ../input.txt

test_sse: dpps_test dpps.sse41.so
	printf "\n[[[test without sse]]]\n"
	mkdir test_sse
	cp dpps_test dpps.sse41.so test_sse/
	cd test_sse/ && ./dpps_test < ../input.txt

test_none: dpps_test
	printf "\n[[[test with no library]]]\n"
	mkdir test_none
	cp dpps_test test_none/
	cd test_none/ && ! ./dpps_test < ../input.txt


clean: .PHONY
.PHONY:
	rm dpps_test dpps.*.so
	rm ./test*/ -rf
