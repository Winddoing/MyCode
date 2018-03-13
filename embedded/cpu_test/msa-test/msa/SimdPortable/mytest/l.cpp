#include <stdio.h>
#include <stdint.h>
#include <msa.h>
#define SIMD_INLINE inline
#define SIMD_MSA_PREFECH_SIZE 32

template <typename T>
class Load
{
	// static SIMD_INLINE  T Data<false>(void * p)
	// {
	// 	v16u8 d = *(v16u8*)p;
	// 	__builtin_prefetch(p + SIMD_MSA_PREFECH_SIZE);
	// 	return (T)__buildin_msa_ld_h(p,0);
	// }

	// static SIMD_INLINE v16u8  Data<true>(void * p)
	// {
	// 	uint8_t * _p = (uint8_t *)__builtin_assume_aligned(p, 16);
	// 	__builtin_prefetch(p + SIMD_MSA_PREFECH_SIZE);
	// 	return *(typeof(T) *)p;
	// }
};

template <bool align>
class Data{

};

template <typename T> void Dump(T d){
	unsigned char *c = (unsigned char *)&d;
	printf("\n");
	for(int i = 0;i < 16;i++)
		printf("%x ",c[i]);
	printf("\n");
}
int main(int argc, char *argv[])
{
    unsigned char d[20];
	bool align = true;
	for(int i = 0;i < 20;i++)
	{
		d[i] = i & 0xff;
	}
	v16u8 b16 = Load<v16u8>::Data<align>((void*)d);

	Dump(b16);
    return 0;
}
