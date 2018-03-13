#include <stdio.h>
#include <stdint.h>
#include <math.h>
template <typename T> class msatype;
typedef msatype<unsigned char> U8;
typedef msatype<int> I32;
template <typename T> class msatype
{
private:
	T v;
public:
	msatype<T>(){
	}
	msatype<T>(unsigned char d){
		v = (T)d;
	}
	msatype<T>(int d){
		v = (T)d;
	}
	// T operator = (unsigned char d)
	// {
	// 	return (T)d;
	// }
	template<> unsigned char absDifference<U8>(U8 a)
	{
		return (abs(v) + abs(a.v));
	}
	T operator = (int d){
		return (T)d;
	}
	int absDifference(I32 a)
	{
		return (abs(v) + abs(a.v));
	}
};
int main(int argc, char *argv[])
{
	U8 a,b,c;
	c = a.absDifference(b);
    return 0;
}
