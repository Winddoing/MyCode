compile
=======
	* mips-linux-gnu-g++ -o z zero.cpp -O2 -mmsa -flax-vector-conversions
	or
	* compile.sh z zero.cpp
run
===
	* qemu-mipsel -cpu P5600 z
	or
	* run.sh z
