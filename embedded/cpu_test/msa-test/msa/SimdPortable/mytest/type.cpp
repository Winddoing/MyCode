#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <msa.h>
#include <typeinfo>
template <typename T> class msatype;
typedef msatype<v16u8> V16U8;
typedef msatype<v16i8> V16I8;
typedef msatype<v8u16> V8U16;
template <typename T> class msatype
{
private:
	T v;
public:
	msatype<T>(){
	}
	bool type()
	{
		return typeid(v16u8) == typeid(v);
	}
};
int main(int argc, char *argv[])
{
	// V16U8 a;
	// V16I8 b;
	// V8U16 c;


	// printf("%d %d %d\n",a.type(),b.type(),c.type());
	msatype<v16u8> a;
	printf("%d %d\n",a.type(),typeof(a));
    return 0;
}
