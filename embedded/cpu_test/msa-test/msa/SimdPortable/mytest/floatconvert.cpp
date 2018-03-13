#include <stdio.h>
#include <stdint.h>
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

void dumpdataValue(v4u32 value,const char *info=NULL){
	int32_t *p = (int *)&value;
	if(info)
		printf("%s",info);
	else
		printf("\n");

	for(int i = 0;i < 4;i++){
		printf("%d ",p[i]);
	}
	printf("\n");
}

int main(int argc, char *argv[])
{
	v4f32 f = {1.5,1.4,1.6,2.0};
	v4i32 u;
	u = __builtin_msa_ftrunc_s_w(f);
	dumpdataValue(f,"float->\t");
	dumpdataValue(u,"truncate->\t");
	u = __builtin_msa_ftint_s_w(f);
	dumpdataValue(u,"convert->\t");

	printf("int = %d\n",(int)1.5f);
    return 0;
}
