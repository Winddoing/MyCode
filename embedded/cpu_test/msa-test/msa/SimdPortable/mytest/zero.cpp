#include <stdio.h>
#include <msa.h>
#include <stdint.h>

template<typename O,typename I> O inline Fill(I v);

template<>
v16u8 inline Fill(int32_t v){
	return __builtin_msa_fill_b(v);
}
template<>
v8u16 inline Fill(int32_t v){
	return __builtin_msa_fill_h(v);
}

template<>
v4u32 inline Fill(int32_t v){
	return __builtin_msa_fill_w(v);
}

template<>
v2u64 inline Fill(int64_t v){
	return __builtin_msa_fill_d(v);
}



template<typename O,typename I> O inline PadSum(I v);
template<typename O,typename I> O inline PadSum(O sum,I v);

template<>
v8u16 inline PadSum(v16u8 value)
{
	const v8u16 zero = __builtin_msa_ldi_h(0);
	const v16u8 one = __builtin_msa_ldi_b(1);
	return __builtin_msa_dpadd_u_h(zero,one,value);
}
template<>
v8u16 inline PadSum(v8u16 sum,v16u8 value)
{
	const v16u8 one = __builtin_msa_ldi_b(1);
	return __builtin_msa_dpadd_u_h(sum,one,value);
}

template<>
v4u32 inline PadSum(v8u16 value)
{
	const v4u32 zero = __builtin_msa_ldi_w(0);
	const v8u16 one = __builtin_msa_ldi_h(1);
	return __builtin_msa_dpadd_u_h(zero,one,value);
}
template<>
v4u32 inline PadSum(v4u32 sum,v8u16 value)
{
	const v8u16 one = __builtin_msa_ldi_h(1);
	return __builtin_msa_dpadd_u_w(sum,one,value);
}

template<>
v2u64 inline PadSum(v4u32 value)
{
	const v2u64 zero = __builtin_msa_ldi_d(0);
	const v4u32 one = __builtin_msa_ldi_w(1);
	return __builtin_msa_dpadd_u_h(zero,one,value);
}
template<>
v2u64 inline PadSum(v2u64 sum,v4u32 value)
{
	const v4u32 one = __builtin_msa_ldi_w(1);
	return __builtin_msa_dpadd_u_h(sum,one,value);
}





template<typename T> void dumpdata(T value){
 	unsigned char *p = (unsigned char *)&value;
 	for(int i = 0;i < sizeof(T);i++){
 		printf("%02x ",p[i]);
 	}
	printf("\n");
}

int main(int argc, char *argv[])
{
	v16u8 a;
	v8u16 e;
	v8u16 f;
	v4u32 g;
	unsigned char *c;
	a = Fill<v16u8>(2);
	f = Fill<v8u16>(1);
	e = PadSum<v8u16>(f,a);
	g = PadSum<v4u32>(e);
	dumpdata(g);

    return 0;
}
