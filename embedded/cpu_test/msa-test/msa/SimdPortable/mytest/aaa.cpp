#include <stdio.h>
#include <msa.h>
/*
-- bl:
62 00 a3 00 52 00 28 00 d4 00 95 00 8a 00 42 00
-- bw:
19 1c 19 1c 19 1c 19 1c 19 1c 19 1c 19 1c 19 1c
-- gl:
b8 00 c4 00 59 00 4d 00 92 00 77 00 80 00 b5 00
-- gw:
60 ed 60 ed 60 ed 60 ed 60 ed 60 ed 60 ed 60 ed
-- rl:
48 00 8b 00 5d 00 84 00 91 00 e0 00 21 00 57 00
-- rw:
87 f6 87 f6 87 f6 87 f6 87 f6 87 f6 87 f6 87 f6
-- b0:
92 c1 0a 00 eb e3 11 00 02 00 09 00 e8 63 04 00
-- g0:
00 9d f2 ff 80 bd f1 ff 60 86 f9 ff e0 65 fa ff
-- r0:
f8 55 fd ff 4d db fa ff 0b 8f fc ff 9c 1d fb ff
*/
int main(int argc, char *argv[])
{
	short b = 0x62;
	short bw = 0x1c19;
	short g = 0xb9;
	short gw = 0xed60;
	short r = 0x49;
	short rw = 0xf687;
	int mb = (int)b * (int)bw;
	int mg = (int)g * (int)gw;
	int mr = (int)r * (int)rw;

	printf("m: 0x%08x 0x%08x 0x%08x\n",mb,mg,mr);

	int u = mb + mg + mr + 0x2000;
	printf("mmm: 0x%08x\n",u);

	printf("u: 0x%08x\n",(u >> 14) + 128);

    return 0;
}
