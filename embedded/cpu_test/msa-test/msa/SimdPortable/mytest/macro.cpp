#include <stdio.h>
#include <msa.h>
#include <stdint.h>
#define SIMD_INLINE inline __attribute__ ((always_inline))
#define SIMD_MSA_PREFECH_SIZE 128
const int EQ = 1;
v4f32 SIMD_INLINE Zero(){
	return (v4f32)__builtin_msa_ldi_w(0);
}
//template<typename O,typename I,int way>
//O SIMD_INLINE Load(I *a);
// {
// 	if(way > 0)
// 		__builtin_prefetch((uint8_t*)a + SIMD_MSA_PREFECH_SIZE + 32 * (way - 1),0);
// 	return (O)__builtin_msa_ld_b(a,0);
// }

template<int way>
v16i8 SIMD_INLINE Load(int8_t *a) {
	if(way > 0)
		__builtin_prefetch((int8_t*)a + SIMD_MSA_PREFECH_SIZE + 32 * (way - 1),0);
	return __builtin_msa_ld_b((void*)a,0);
}

template<int way>
v8i16 SIMD_INLINE Load(int16_t *a) {
	if(way > 0)
		__builtin_prefetch((int8_t*)a + SIMD_MSA_PREFECH_SIZE + 32 * (way - 1),0);
	return __builtin_msa_ld_h((void*)a,0);
}

template<typename T>
void dumpdata(T value,const char *info=NULL){
	unsigned char *p = (unsigned char *)&value;
	if(info)
		printf("%s",info);
	else
		printf("\n");
	for(int i = 0;i < sizeof(T);i++){
		printf("%02x ",p[i]);
	}
	printf("\n");
}

int main(int argc, char *argv[])
{
	int8_t c[16]={0};
	v16i8 a1;
	v8i16 a2;
	volatile v16i8 a = Load<1>(c);
	volatile v8i16 b = Load<2>((int16_t*)c);
	a = a * a;
	b = b * b;
	dumpdata<v16u8>(a);
	dumpdata<v8u16>(b);
	v4f32 f = Zero();
	volatile v4f32 f1 = {1.0,2.0,3.0,4.0};
	f1 = f * f1;
    return 0;
}
