
#ifndef _SIMDMSALOAD_H_
#define _SIMDMSALOAD_H_
#include "Simd/SimdMsaType.h"
namespace Simd
{
#ifdef SIMD_MSA_ENABLE
	namespace Msa{
		template <size_t count> SIMD_INLINE v16u8 LoadBeforeFirst(v16u8 first)
		{
			v16u8 complement = Shift<count,LEFT>(first,first);
			return Shift<count,RIGHT>(first,complement);
		}

		template <size_t count> SIMD_INLINE v16u8 LoadAfterLast(v16u8 last)
		{
			v16u8 complement = Shift<count,RIGHT>(last,last);
			return Shift<count,LEFT>(last,complement);
		}

		template<int step>
		SIMD_INLINE void LoadNose3(const uint8_t *p,v16u8 a[3])
		{
			a[1] = Load<1>(p);
			a[2] = Load(p + step);
			a[0] = LoadBeforeFirst<step>(a[1]);
		}
		template<int step>
		SIMD_INLINE void LoadBody3(const uint8_t *p,v16u8 a[3])
		{
			a[0] = Load<1>(p - step);
			a[1] = Load(p);
			a[2] = Load(p + step);
		}
		template<int step>
		SIMD_INLINE void LoadTail3(const uint8_t *p,v16u8 a[3])
		{
			a[0] = Load(p - step);
			a[1] = Load(p);
			a[2] = LoadAfterLast<step>(a[1]);
		}

		template <size_t step> SIMD_INLINE void LoadNose5(const uint8_t * p, v16u8 a[5])
		{
			a[2] = Load<1>(p);
			a[1] = LoadBeforeFirst<step>(a[2]);
			a[0] = LoadBeforeFirst<step>(a[1]);
			a[3] = Load(p + step);
			a[4] = Load(p + 2 * step);
		}

		template <size_t step> SIMD_INLINE void LoadBody5(const uint8_t * p, v16u8 a[5])
		{
            a[0] = Load(p - 2 * step);
			a[1] = Load(p - step);
			a[2] = Load<1>(p);
			a[3] = Load(p + step);
			a[4] = Load(p + 2 * step);
		}

		template <size_t step> SIMD_INLINE void LoadTail5(const uint8_t * p, v16u8 a[5])
		{
			a[0] = Load(p - 2 * step);
			a[1] = Load(p - step);
			a[2] = Load(p);
			a[3] = LoadAfterLast<step>(a[2]);
			a[4] = LoadAfterLast<step>(a[3]);
		}
	}
#endif /* SIMD_MSA_ENABLE  */
}

#endif /* _SIMDMSALOAD_H_ */
