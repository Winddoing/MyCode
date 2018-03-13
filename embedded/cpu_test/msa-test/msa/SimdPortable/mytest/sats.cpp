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
void un_sat_test()
{
	v16u8 a = { 1, 2, 3, 0xff, 0xff, 6, 7, 8,
			    9,10,11,12,13,14,15,16};
	v16u8 b = { 2, 1, 3, 0, 1, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0};

	v16u8 c;
	dumpdata<v16u8>(a,"a:\n");
	dumpdata<v16u8>(b,"b:\n");
	printf("------------------------------------\n");
	printf("__builtin_msa_subsuu_u_b(a,b)\n");
	printf("------------------------------------\n");
	c = __builtin_msa_subs_u_b(a,b);

	dumpdata<v16u8>(a,"a:\n");
	dumpdata<v16u8>(b,"b:\n");
	dumpdata<v16u8>(c,"c:\n");

}
void sat_test()
{
	v16i8 a = { 1, 0x80, 0x7d, 0xff, 0xff, 6, 7, 8,
			    9,10,11,12,13,14,15,16};
	v16i8 b = { 5, 1, 0x80, 0, 1, 0xff, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0};

	v16i8 c;
	dumpdata<v16i8>(a,"a:\n");
	dumpdata<v16i8>(b,"b:\n");
	printf("------------------------------------\n");
	printf("____builtin_msa_subs_s_b(a,b)\n");
	printf("------------------------------------\n");
	c = __builtin_msa_subs_s_b(a,b);

	dumpdata<v16i8>(a,"a:\n");
	dumpdata<v16i8>(b,"b:\n");
	dumpdata<v16i8>(c,"c:\n");
}



int main(int argc, char *argv[])
{
	v16i8 a = { 1, 2, 3, 0xff, 0xff, 6, 7, 8,
			    9,10,11,12,13,14,15,16};
	v8i16 b = { 1, 2, 3, 0xff, 0xff, 6, 7, 8};
	v8i16 c;
	//un_sat_test();
	//sat_test();
	c = b;
	a = __builtin_msa_satss_b(b,c);
	dumpdata<v16i8>(c,"c:\n");
    return 0;
}
