#!/bin/bash
if [ $# -eq 2 ];then
mips-linux-gnu-g++ -o $1 $2 -O2 -mmsa -flax-vector-conversions -static  -I../src -DSIMD_MSA_ENABLE -march=xburst2 -mdouble-float -mgp32 -mfp64 -Wpragmas
fi
