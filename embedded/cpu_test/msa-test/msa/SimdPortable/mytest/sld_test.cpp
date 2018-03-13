#include <stdio.h>
#include <msa.h>
int main(int argc, char *argv[])
{
	v16u8 a,b,o;
	unsigned char *c;
	c = (unsigned char *)&a;
	for(int i = 0;i < 16;i++)
		*c++ = i;
	c = (unsigned char *)&b;
	for(int i = 0;i < 16;i++)
		*c++ = i + 16;
	printf("a:= ");
	for(int i = 0;i < 16;i++){
		printf("%02x ",*c++);
	}
	printf("\n");

	c = (unsigned char *)&b;
	printf("b:= ");
	for(int i = 0;i < 16;i++){
		printf("%02x ",*c++);
	}
	printf("\n------------------------------\n");


	o = __builtin_msa_sld_b(b,a,5);

	c = (unsigned char *)&a;
	printf("a:= ");
	for(int i = 0;i < 16;i++){
		printf("%02x ",*c++);
	}
	printf("\n");

	c = (unsigned char *)&b;
	printf("b:= ");
	for(int i = 0;i < 16;i++){
		printf("%02x ",*c++);
	}
	printf("\n");

	c = (unsigned char *)&o;
	printf("o:= ");
	for(int i = 0;i < 16;i++){
		printf("%02x ",*c++);
	}
	printf("\n");

	return 0;
}
