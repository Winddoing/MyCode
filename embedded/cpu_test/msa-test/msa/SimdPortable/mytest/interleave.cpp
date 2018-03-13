#include <stdio.h>
#include <msa.h>
#define SIMD_INLINE inline
const int ODD = 1;
const int EVEN = 0;
template<int d,typename T> T SIMD_INLINE Interleave(T a,T b);

#define CODE_INTERLEAVE(interleave,type,code)				\
	template<>												\
	type SIMD_INLINE Interleave<interleave>(type a,type b){	\
		return __builtin_msa_##code(a,b);					\
	}

CODE_INTERLEAVE(EVEN,v16i8,ilvev_b);


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

	v16i8 a = {
		1,2,3,4,5,6,7,8,
		9,10,11,12,13,14,15,16,
	};
	v16i8 b = {
		1,2,3,4,5,6,7,8,
		9,10,11,12,13,14,15,16,
	};
	v16i8 c = Interleave<EVEN>(a,b);
	dumpdata<v16i8>(c);
    return 0;
}
