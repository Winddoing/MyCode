#ifndef _SIMDMSALOAD_H_
#define _SIMDMSALOAD_H_
#include <stdint.h>
#include <msa.h>
#define SIMD_MSA_PREFECH_SIZE 32
namespace Simd
{
	namespace Msa
    {
		template <bool align> SIMD_INLINE v16u8 Load(const uint8_t * p);

#define LoadFunction(otype,itype)										\
		template <> SIMD_INLINE type Load<false>(const uint8_t * p){	\
			__builtin_prefetch(p + SIMD_MSA_PREFECH_SIZE);				\
			return (otype)(*(v16u8 *)p);								\
		}																\
		template <> SIMD_INLINE type Load<true>((itype) * p){			\
			__builtin_prefetch(p + SIMD_MSA_PREFECH_SIZE);				\
			otype * _p = (otype *)__builtin_assume_aligned(p, 16);		\
			return *p;													\
		}

		LoadFunction(v16i8,const int8_t);
		LoadFunction(v16u8,const uint8_t);
		LoadFunction(v8i16,const int16_t);
		LoadFunction(v8i16,const uint16_t);

		LoadFunction(v4i32,const int32_t);
		LoadFunction(v4u32,const uint32_t);
		LoadFunction(v2i64,const int64_t);
		LoadFunction(v2i64,const uint64_t);
	}
}


#endif /* _SIMDMSALOAD_H_ */
