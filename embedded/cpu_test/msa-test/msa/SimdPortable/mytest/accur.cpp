#include <stdio.h>
#include <msa.h>
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
	volatile v8u16 a = {1,2,3,4,5,6,7,8};
	volatile v16u8 b = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
	volatile v8u16 c;
	c = __builtin_msa_accur_h(a,b);
	dumpdata(c);
    return 0;
}
