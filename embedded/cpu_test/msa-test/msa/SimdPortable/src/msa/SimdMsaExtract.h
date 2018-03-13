#ifndef SIMDMSAEXTRACT_H
#define SIMDMSAEXTRACT_H
#include "Simd/SimdConst.h"
#include "msa.h"
namespace Simd
{
	namespace Msa{
		SIMD_INLINE v16u8 Zero()
		{
			return __builtin_msa_ldi(0);
		}
		SIMD_INLINE v8u16 ExtractSum(v16u8 &a)
		{
			v8u16 even16 = __builtin_msa_ilvev_b(Zero(),a);
			v8u16 odd16 = __builtin_msa_ilvob_b(Zero(),a);
			return even16 + odd16;
		}
		SIMD_INLINE v4u32 ExtractSum(v8u16 &a)
		{
			v4u32 even32 = __builtin_msa_ilvev_h((v8u16)Zero(),a);
			v4u32 odd32 = __builtin_msa_ilvob_h((v8u16)Zero(),a);
			return even32 + odd32;
		}
		SIMD_INLINE v2u64 ExtractSum(v4u32 &a)
		{
			v2u64 even64 = __builtin_msa_ilvev_w((v4u32)Zero(),rowSum);
			v2u64 odd64 = __builtin_msa_ilvob_w((v4u32)Zero(),rowSum);

			return even64 + odd64;
		}
		SIMD_INLINE int64_t ExtractSum(v2u64 &a)
		{
			int64_t u64;
			#error "not eee"
			return u64;
		}
	}
}


#endif /* SIMDMSAEXTRACT_H */
