#include <stdio.h>
#include <msa.h>
#include <stdint.h>

#define SIMD_INLINE inline
template<typename O,typename I> O SIMD_INLINE Fill(I v);

#define CODE_FILL(O,I,code)						\
	template<>									\
	O SIMD_INLINE Fill(I v){					\
		return __builtin_msa_##code(v);	\
	}

CODE_FILL(v16i8,int32_t,fill_b);
CODE_FILL(v8i16,int32_t,fill_h);
CODE_FILL(v4i32,int32_t,fill_w);
CODE_FILL(v2i64,int64_t,fill_d);


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
	unsigned char x = 0x85;
	int32_t u = (int32_t)x;
	v16u8 v = (v16u8)Fill<v16i8>(u);
	dumpdata<v16i8>(v);

    return 0;
}
