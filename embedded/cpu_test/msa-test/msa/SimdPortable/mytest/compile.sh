#!/bin/bash
if [ $# -eq 2 ];then
mips-linux-gnu-g++ -o $1 $2 -O2 -mmsa -flax-vector-conversions -static
fi
