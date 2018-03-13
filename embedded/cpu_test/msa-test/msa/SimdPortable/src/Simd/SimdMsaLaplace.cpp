/*
* Simd Library (http://ermig1979.github.io/Simd).
*
* Copyright (c) 2011-2017 Yermalayeu Ihar.
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
#include "Simd/SimdStore.h"
#include "Simd/SimdExtract.h"
#include "Simd/SimdMsaConversion.h"
#include "Simd/SimdMsaLoad.h"
namespace Simd
{
#ifdef SIMD_MSA_ENABLE
    namespace Msa
    {
		template<int32_t part> SIMD_INLINE
		v8u16 UnpackSum(v16u8 a0,v16u8 a1,v16u8 a2)
		{
			v8u16 sum = ExtendAdd<part>(a0,a1);
			return ExtendSum<part>(sum,a2);
		}

        template<int32_t part> SIMD_INLINE
		v8u16 Laplace(v16u8 a[3][3])
        {
			v8u16 sum0 = UnpackSum<part>(a[0][0],a[0][1],a[0][2]);
			v8u16 sum2 = UnpackSum<part>(a[2][0],a[2][1],a[2][2]);
			v8u16 sum = sum0 + sum2;
			sum = ExtendSum<part>(sum,a[1][0]);
			sum = ExtendSum<part>(sum,a[1][2]);
			v16u8 K8_08;
			Set<8>(K8_08);
			v8i16 mult = ExtendMultipy<part>(K8_08,a[1][1]);
			return mult - (v8i16)sum;
        }

		template <bool abs> SIMD_INLINE void Laplace(v16u8 a[3][3], int16_t * dst)
        {
			Store(ConditionalAbs<abs>(Laplace<LO>(a)),dst + 0);
			Store(ConditionalAbs<abs>(Laplace<HI>(a)),dst + 8);
        }

		template <bool abs> void Laplace(const uint8_t * src, size_t srcStride, size_t width, size_t height, int16_t * dst, size_t dstStride)
        {
            assert(width > A);

            size_t bodyWidth = Simd::AlignHi(width, A) - A;
            const uint8_t *src0, *src1, *src2;
            v16u8 a[3][3];

            for(size_t row = 0; row < height; ++row)
            {
                src0 = src + srcStride*(row - 1);
                src1 = src0 + srcStride;
                src2 = src1 + srcStride;
                if(row == 0)
                    src0 = src1;
                if(row == height - 1)
                    src2 = src1;

                LoadNose3<1>(src0 + 0, a[0]);
                LoadNose3<1>(src1 + 0, a[1]);
				LoadNose3<1>(src2 + 0, a[2]);
                Laplace<abs>(a, dst + 0);
                for(size_t col = A; col < bodyWidth; col += A)
                {
                    LoadBody3<1>(src0 + col, a[0]);
					LoadBody3<1>(src1 + col, a[1]);
					LoadBody3<1>(src2 + col, a[2]);
                    Laplace<abs>(a, dst + col);
                }
                LoadTail3<1>(src0 + width - A, a[0]);
				LoadTail3<1>(src1 + width - A, a[1]);
				LoadTail3<1>(src2 + width - A, a[2]);
                Laplace<abs>(a, dst + width - A);

                dst += dstStride;
            }
        }

        void Laplace(const uint8_t * src, size_t srcStride, size_t width, size_t height, uint8_t * dst, size_t dstStride)
        {
            assert(dstStride%sizeof(int16_t) == 0);
			Laplace<false>(src, srcStride, width, height, (int16_t *)dst, dstStride/sizeof(int16_t));
     }

		void LaplaceAbs(const uint8_t * src, size_t srcStride, size_t width, size_t height, uint8_t * dst, size_t dstStride)
		{
			assert(dstStride%sizeof(int16_t) == 0);
			Laplace<true>(src, srcStride, width, height, (int16_t *)dst, dstStride / sizeof(int16_t));
		}

		SIMD_INLINE void LaplaceAbsSum(v16u8 a[3][3], v4u32 & sum)
		{
			v8u16 v0 = ConditionalAbs<true>(Laplace<LO>(a));
			v8u16 v1 = ConditionalAbs<true>(Laplace<HI>(a));
			sum = PadSum(sum,v0);
			sum = PadSum(sum,v1);
		}

		SIMD_INLINE void SetMask3(v16u8 a[3], v16u8 mask)
		{
			a[0] = a[0] & mask;
			a[1] = a[1] & mask;
			a[2] = a[2] & mask;
		}

		SIMD_INLINE void SetMask3x3(v16u8 a[3][3], v16u8 mask)
		{
			SetMask3(a[0], mask);
			SetMask3(a[1], mask);
			SetMask3(a[2], mask);
		}

		void LaplaceAbsSum(const uint8_t * src, size_t stride, size_t width, size_t height, uint64_t * sum)
		{
			assert(width > A);

			size_t bodyWidth = Simd::AlignHi(width, A) - A;
			const uint8_t *src0, *src1, *src2;
			v16u8 K8_FF;
			Set<0xff>(K8_FF);
			v16u8 a[3][3];
			v16u8 tailMask = ShiftLeft(K8_FF, A - width + bodyWidth);

			v2u64 fullSum = Zero<v2u64>();
			for (size_t row = 0; row < height; ++row)
			{
				src0 = src + stride*(row - 1);
				src1 = src0 + stride;
				src2 = src1 + stride;
				if (row == 0)
					src0 = src1;
				if (row == height - 1)
					src2 = src1;

				v4u32 rowSum = Zero<v4u32>();

				LoadNose3<1>(src0 + 0, a[0]);
				LoadNose3<1>(src1 + 0, a[1]);
				LoadNose3<1>(src2 + 0, a[2]);
				LaplaceAbsSum(a, rowSum);
				for (size_t col = A; col < bodyWidth; col += A)
				{
					LoadBody3<1>(src0 + col, a[0]);
					LoadBody3<1>(src1 + col, a[1]);
					LoadBody3<1>(src2 + col, a[2]);
					LaplaceAbsSum(a, rowSum);
				}
				LoadTail3<1>(src0 + width - A, a[0]);
				LoadTail3<1>(src1 + width - A, a[1]);
				LoadTail3<1>(src2 + width - A, a[2]);
				SetMask3x3(a, tailMask);
				LaplaceAbsSum(a, rowSum);

				fullSum = PadSum(fullSum, rowSum);
			}
			*sum = ExtractSum(fullSum);
		}

    }
#endif// SIMD_MSA_ENABLE
}
