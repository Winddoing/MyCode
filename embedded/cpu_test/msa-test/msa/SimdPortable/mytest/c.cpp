#include <stdio.h>
namespace Simd{

	template<typename T>
	T Load(void *v){
		return *(T*)v;
	}
	template<typename T> T absDifference(T a,T b);
	template<>
	char absDifference(char a,char b){
		return a - b;
	}
};

int main(int argc, char *argv[])
{
	unsigned char o[2] = {0,1};
	char d,e,f;
	d = Simd::Load<char>((void*)o);
	e = Simd::Load<char>((void*)&o[1]);
	f = Simd::absDifference<char>(d,e);
	printf("%d %d\n",d,f);
    return 0;
}
