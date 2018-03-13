#include <stdio.h>
#include <msa.h>



int main()
{
	unsigned char *v;
	v16u8 a;



	unsigned char value;

	for(value = 1; value<16; value++) {

		v = (unsigned char*)&a;
		memset(v,0,16);
		v[0]=value;

		v8u16 lo = __builtin_msa_mulur_h(a,a);
		v=(unsigned char *)&lo;

		printf("%02x %02x: %04x\n", v[0], v[1], value*value);
	}
}
