all: dpps_test dpps_so

dpps_test: ./dppsTest/dppsTest.cpp
	g++ ./dppsTest/dppsTest.cpp -ldl -o dpps_test

dpps_so: dpps.avx.so dpps.sse.so

dpps.avx.so: ./dpps/dpps.avx/dpps.avx.cpp
	g++ ./dpps/dpps.avx/dpps.avx.cpp -fPIC -shared -o dpps.avx.so -mavx

dpps.sse.so: ./dpps/dpps.sse/dpps.sse.cpp
	g++ ./dpps/dpps.sse/dpps.sse.cpp -fPIC -shared -o dpps.sse.so -msse4.1

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

test_sse: dpps_test dpps.sse.so
	printf "\n[[[test without sse]]]\n"
	mkdir test_sse
	cp dpps_test dpps.sse.so test_sse/
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
