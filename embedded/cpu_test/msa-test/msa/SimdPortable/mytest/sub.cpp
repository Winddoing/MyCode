#include <stdio.h>
#include <msa.h>

const int LO = 0;
const int HI = 1;
#define SIMD_INLINE inline

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

template<int half,typename T,typename I> T SIMD_INLINE ExtendSub(I minuend,I subtrahend);

#define CODE_EXTENDSUB(d,type1,type2,code)							\
	template<>														\
	type1 SIMD_INLINE ExtendSub<d>(type2 minuend,type2 subtrahend){	\
		return __builtin_msa_##code(minuend,subtrahend);			\
	}

CODE_EXTENDSUB(LO,v8i16,v16u8,subur_h);
CODE_EXTENDSUB(HI,v8i16,v16u8,subul_h);



int main(int argc, char *argv[])
{
    v16u8 a = {	0xf1,0xf1,0xf1,0xf1,0xf1,0xf1,0xf1,0xf1,0xf1,0xf1,0xf1,0xf1,0xf1,0xf1,0xf1,0xf1};
    v16u8 b = {	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

	v8i16 c = ExtendSub<LO,v8i16,v16u8>(a,b);
	dumpdata<v8i16>(c);


    return 0;
}
