#include <stdio.h>
#include <msa.h>
void dumpdataValue(v4f32 value,const char *info=NULL){
	float *p = (float *)&value;
	if(info)
		printf("%s",info);
	else
		printf("\n");

	for(int i = 0;i < 4;i++){
		printf("%f ",p[i]);
	}
	printf("\n");
}

int main(int argc, char *argv[])
{
	volatile v4i32 a = {1,2,3,4};
    volatile v4f32 f = a;
	dumpdataValue(f);
    return 0;
}
