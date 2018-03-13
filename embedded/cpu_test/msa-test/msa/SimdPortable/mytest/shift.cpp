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
	v4u32 a = {0x000000FF,0x0000FF00,0x00FF0000,0xFF000000};
	dumpdata<v4u32>(a,"before:\n");
	a = a >> 16;
	dumpdata<v4u32>(a,"after:\n");
    return 0;
}
