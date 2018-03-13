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
    v4i32 a;
	volatile v4f32 f1 ={0.1f,1.2f,2.3f,3.4f};
	volatile v4f32 f2 ={0.1f,1.2f,2.5f,3.4f};
	dumpdata<v4f32>(f1,"\n");
	f1 = f1 + f2;
	dumpdata<v4f32>(f1,"\n");
	a = *(v4i32 *)&f1;
	dumpdata<v4i32>(a,"\n");
    return 0;
}
