/*
* Simd Library (http://simd.sourceforge.net).
*
* Copyright (c) 2011-2016 Yermalayeu Ihar.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/
#include "Simd/SimdMemory.h"
#include "Simd/SimdExtract.h"
#include "Simd/SimdStore.h"
#include "Simd/SimdBase.h"
#include "Simd/SimdMsaType.h"
#include <stdio.h>
namespace Simd
{
#ifdef SIMD_MSA_ENABLE
	namespace Msa
    {

		SIMD_INLINE v4u32 SquaredDifferenceSum(v16u8 & a, v16u8 & b)
		{
			v16u8 ad = AbsDifference(a,b);
			return PadMutiSum(ad,ad);
		}

        SIMD_INLINE v4u32 SquaredDifferenceSumMasked(v16u8& a, v16u8 & b, v16u8 & mask)
        {
			v16u8 ad = AbsDifference(a,b) & mask;
            return PadMutiSum(ad,ad);
        }

		void SquaredDifferenceSum(
			const uint8_t * a, size_t aStride, const uint8_t * b, size_t bStride,
			size_t width, size_t height, uint64_t * sum)
		{
			assert(width < 0x10000);
			size_t alignedWidth = Simd::AlignLo(width, A);

			v2u64 _sum = Zero<v2u64>();

			for(size_t row = 0; row < height; ++row)
			{
				v4u32 rowSum = Zero<v4u32>();
				for(size_t col = 0; col < alignedWidth; col += A)
				{
					v16u8 _a = Load<1>(a + col);
					v16u8 _b = Load<2>(b + col);
					rowSum += SquaredDifferenceSum(_a,_b);
				}
				if(width - alignedWidth)
				{
					v16u8 tailMask = Set(width - alignedWidth,0xff);
					v16u8 _a = Load(a + width - A);
					v16u8 _b = Load(b + width - A);
					rowSum += SquaredDifferenceSumMasked(_a, _b, tailMask);

				}
				_sum = PadSum(_sum,rowSum);
				a += aStride;
				b += bStride;
			}
			*sum = ExtractSum(_sum);
		}

		void SquaredDifferenceSumMasked(
			const uint8_t *a, size_t aStride, const uint8_t *b, size_t bStride,
			const uint8_t *mask, size_t maskStride, uint8_t index, size_t width, size_t height, uint64_t * sum)
		{
			assert(width < 0x10000);
			size_t alignedWidth = Simd::AlignLo(width, A);
			v16u8 _index = Fill(index);
			v2u64 _sum = Zero<v2u64>();
			for (size_t row = 0; row < height; ++row)
			{
				v4u32 rowSum = Zero<v4u32>();
				for (size_t col = 0; col < alignedWidth; col += A)
				{
					v16u8 _mask = Load<3>(mask + col);
					_mask = Compare<EQ>(_mask,_index);
					v16u8 _a = Load<1>(a + col);
					v16u8 _b = Load<2>(b + col);
					rowSum += SquaredDifferenceSumMasked(_a, _b, _mask);
				}
				if (width - alignedWidth)
				{
					v16u8 tailMask = Set(width-alignedWidth,0xff);
					v16u8 _mask = Load(mask + width - A);
					_mask = tailMask & Compare<EQ>(_mask,_index);
					v16u8 _a = Load(a + width - A);
					v16u8 _b = Load(b + width - A);
					rowSum += SquaredDifferenceSumMasked(_a, _b, _mask);
				}
				_sum = PadSum(_sum,rowSum);
				a += aStride;
				b += bStride;
				mask += maskStride;
			}
			*sum = ExtractSum(_sum);
		}
		SIMD_INLINE void SquaredDifferenceSum32f(const float * a, const float * b, size_t offset, v4f32 & sum)
		{
			v4f32 _a = Load<1>(a + offset);
			v4f32 _b = Load<2>(b + offset);
			v4f32 _d = _a - _b;
			sum += _d *_d;
		}

		void SquaredDifferenceSum32f(const float * a, const float * b, size_t size, float * sum)
		{
			*sum = 0;
			size_t i = 0;
			size_t alignedSize = AlignLo(size, 4);
			v4f32 sums = Zero<v4f32>();
			for (; i < alignedSize; i += 4)
				SquaredDifferenceSum32f(a, b, i, sums);
			*sum += ExtractSum(sums);
			for (; i < size; ++i)
				*sum += Simd::Square(a[i] - b[i]);
		}

		SIMD_INLINE void SquaredDifferenceKahanSum32f(const float * a, const float * b, size_t offset, v4f32 & sum, v4f32 & correction)
		{
			v4f32 _a = Load<1>(a + offset);
			v4f32 _b = Load<2>(b + offset);
			v4f32 _d = _a - _b;
			v4f32 term = _d * _d - correction;
			v4f32 temp = sum + term;
			correction = (temp - sum) - term;
			sum = temp;
		}
		SIMD_INLINE void KahanSum(float value, float* sum, float & correction)
        {
            float term = value - correction;
            float temp = *sum + term;
            correction = (temp - *sum) - term;
            *sum = temp;
        }
		void SquaredDifferenceKahanSum32f(const float * a, const float * b, size_t size, float * sum)
		{
			*sum = 0;
			size_t alignedSize = AlignLo(size, 4);
			size_t i = 0;
			v4f32 sums = Zero<v4f32>();
			v4f32 corrections = Zero<v4f32>();
			if (alignedSize)
			{
				for (; i < alignedSize; i += 4)
					SquaredDifferenceKahanSum32f(a, b, i, sums, corrections);

			}
			if(alignedSize != size){
				float *correction = (float*)&corrections;
				for (; i < size; ++i)
					KahanSum(Simd::Square(a[i + 0] - b[i + 0]),sum, correction[0]);
			}
			*sum += ExtractSum(sums);
		}
    }
#endif// SIMD_MSA_ENABLE
}
