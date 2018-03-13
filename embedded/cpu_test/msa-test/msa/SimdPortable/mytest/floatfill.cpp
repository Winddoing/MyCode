#include "Simd/SimdMsaType.h"
using namespace Simd::Msa;

int main(int argc, char *argv[])
{
	float f = 5.0f;
	v4f32 vf = Fill(f);
	dumpdata(vf);
	return 0;
}
