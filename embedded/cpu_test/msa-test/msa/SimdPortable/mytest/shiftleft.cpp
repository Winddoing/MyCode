#include <stdio.h>
#include <msa.h>
#define SIMD_INLINE inline

v16u8 SIMD_INLINE ShiftLeft(v16u8 value,size_t shift)
{
	v16u8 zero = (v16u8)__builtin_msa_ldi_b(0);
	return __builtin_msa_sld_b(value,zero,16 - shift);
}




int main(int argc, char *argv[])
{
    v16u8 a = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
	v16u8 b = {16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31};

	__builtin_msa_sld_b(b,a,16);

    return 0;
}
