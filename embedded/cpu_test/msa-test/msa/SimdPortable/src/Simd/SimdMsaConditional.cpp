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
#include "Simd/SimdCompare.h"
#include "Simd/SimdMsaType.h"
#include "Simd/SimdMsaConversion.h"

namespace Simd
{
#ifdef SIMD_MSA_ENABLE
	namespace Msa
	{
        template <SimdCompareType compareType>
        void ConditionalCount8u(const uint8_t * src, size_t stride, size_t width, size_t height, uint8_t value, uint32_t * count)
        {
            assert(width >= A);
            size_t alignedWidth = Simd::AlignLo(width, A);

			v16u8 K8_FF = Fill((uint8_t)0xff);
			v16u8 K8_01;
			Set<1>(K8_01);
			v16u8 tailMask = ShiftLeft(K8_FF, A - width + alignedWidth);
			size_t blockSize = A << 8;
			size_t blockCount = (alignedWidth >> 8) + 1;

			v16u8 _value = Fill((uint8_t)value);

			v4u32 _count = Zero<v4u32>();
            for(size_t row = 0; row < height; ++row)
            {
				v8u16 rowSum = Zero<v4u32>();
				for (size_t block = 0; block < blockCount; ++block)
				{
					v16u8 blockSum = Zero<v16u8>();
					for (size_t col = block*blockSize, end = Simd::Min(col + blockSize, alignedWidth); col < end; col += A)
					{
						v16u8 mask = Compare8u<compareType>(Load<1>(src + col), _value);
						v16u8 inc = mask & K8_01;
						blockSum += inc;
					}
					rowSum = PadSum(rowSum,blockSum);
				}
                if(alignedWidth != width)
                {
					v16u8 mask = Compare8u<compareType>(Load(src + width - A), _value);
					mask = mask & tailMask;
					v16u8 inc = mask & K8_01;
					rowSum = PadSum(rowSum,inc);
                }
				_count = PadSum(_count,rowSum);
                src += stride;
            }
            *count = ExtractSum(_count);
        }

        void ConditionalCount8u(const uint8_t * src, size_t stride, size_t width, size_t height,
            uint8_t value, SimdCompareType compareType, uint32_t * count)
        {
            switch(compareType)
            {
            case SimdCompareEqual:
                return ConditionalCount8u<SimdCompareEqual>(src, stride, width, height, value, count);
            case SimdCompareNotEqual:
                return ConditionalCount8u<SimdCompareNotEqual>(src, stride, width, height, value, count);
            case SimdCompareGreater:
                return ConditionalCount8u<SimdCompareGreater>(src, stride, width, height, value, count);
            case SimdCompareGreaterOrEqual:
                return ConditionalCount8u<SimdCompareGreaterOrEqual>(src, stride, width, height, value, count);
            case SimdCompareLesser:
                return ConditionalCount8u<SimdCompareLesser>(src, stride, width, height, value, count);
            case SimdCompareLesserOrEqual:
                return ConditionalCount8u<SimdCompareLesserOrEqual>(src, stride, width, height, value, count);
            default:
                assert(0);
            }
        }

		template <SimdCompareType compareType>
		void ConditionalCount16i(const uint8_t * src, size_t stride, size_t width, size_t height, int16_t value, uint32_t * count)
		{
			assert(width >= HA);
			size_t alignedWidth = Simd::AlignLo(width, HA);
			v16u8 K8_FF = Fill((uint8_t)0xff);
			v8u16 tailMask = (v8u16)ShiftLeft(K8_FF, 2 * (HA - width + alignedWidth));
			v8i16 _value = Fill((int16_t)value);
			v8u16 K16_0001;
			Set<1>(K16_0001);
			v4u32 _count = Zero<v4u32>();

			for (size_t row = 0; row < height; ++row)
			{
				const int16_t * s = (const int16_t *)src;
				v8u16 rowSum = Zero<v8u16>();

				for (size_t col = 0; col < alignedWidth; col += HA)
				{
					v8u16 mask = Compare16i<compareType>(Load<1>(s + col), _value);
					v8i16 inc = mask & K16_0001;
					rowSum += inc;
				}
				if (alignedWidth != width)
				{
					v8u16 mask = Compare16i<compareType>(Load(s + width - HA), _value);
					v8i16 inc = mask & K16_0001 & tailMask;
					rowSum += inc;
				}
				_count = PadSum(_count, rowSum);
				src += stride;
			}
			*count = ExtractSum(_count);
		}

		void ConditionalCount16i(const uint8_t * src, size_t stride, size_t width, size_t height,
			int16_t value, SimdCompareType compareType, uint32_t * count)
		{
			switch (compareType)
			{
			case SimdCompareEqual:
				return ConditionalCount16i<SimdCompareEqual>(src, stride, width, height, value, count);
			case SimdCompareNotEqual:
				return ConditionalCount16i<SimdCompareNotEqual>(src, stride, width, height, value, count);
			case SimdCompareGreater:
				return ConditionalCount16i<SimdCompareGreater>(src, stride, width, height, value, count);
			case SimdCompareGreaterOrEqual:
				return ConditionalCount16i<SimdCompareGreaterOrEqual>(src, stride, width, height, value, count);
			case SimdCompareLesser:
				return ConditionalCount16i<SimdCompareLesser>(src, stride, width, height, value, count);
			case SimdCompareLesserOrEqual:
				return ConditionalCount16i<SimdCompareLesserOrEqual>(src, stride, width, height, value, count);
			default:
				assert(0);
			}
		}

		template <SimdCompareType compareType>
		void ConditionalSum(const uint8_t * src, size_t srcStride, size_t width, size_t height,
			const uint8_t * mask, size_t maskStride, uint8_t value, uint64_t * sum)
		{
			assert(width >= A);

			size_t alignedWidth = Simd::AlignLo(width, A);
			v16u8 K8_FF = Fill((uint8_t)0xff);
			v16u8 tailMask = ShiftLeft(K8_FF, A - width + alignedWidth);
			size_t blockSize = A << 8;
			size_t blockCount = (alignedWidth >> 8) + 1;

			v16u8 _value = Fill((uint8_t)value);
			v2u64 _sum = Zero<v2u64>();
			for (size_t row = 0; row < height; ++row)
			{
				v4u32 rowSum = Zero<v4u32>();
				for (size_t block = 0; block < blockCount; ++block)
				{
					v8u16 blockSum = Zero<v8u16>();
					for (size_t col = block*blockSize, end = Simd::Min(col + blockSize, alignedWidth); col < end; col += A)
					{
						v16u8 _src = Load<1>(src + col);
						v16u8 _mask = Compare8u<compareType>(Load<2>(mask + col), _value);
						_src = _src & _mask;
						blockSum = PadSum(blockSum,_src);
					}
					rowSum = PadSum(rowSum,blockSum);
				}
				if (alignedWidth != width)
				{
					v16u8 _src = Load(src + width - A);
					v16u8 _mask = Compare8u<compareType>(Load(mask + width - A), _value) & tailMask;
					_src = _src & _mask;
					rowSum = PadSum(rowSum,PadSum(_src));
				}
				_sum = PadSum(_sum,rowSum);
				src += srcStride;
				mask += maskStride;
			}
			*sum = ExtractSum(_sum);
		}

		void ConditionalSum(const uint8_t * src, size_t srcStride, size_t width, size_t height,
			const uint8_t * mask, size_t maskStride, uint8_t value, SimdCompareType compareType, uint64_t * sum)
		{
			switch (compareType)
			{
			case SimdCompareEqual:
				return ConditionalSum<SimdCompareEqual>(src, srcStride, width, height, mask, maskStride, value, sum);
			case SimdCompareNotEqual:
				return ConditionalSum<SimdCompareNotEqual>(src, srcStride, width, height, mask, maskStride, value, sum);
			case SimdCompareGreater:
				return ConditionalSum<SimdCompareGreater>(src, srcStride, width, height, mask, maskStride, value, sum);
			case SimdCompareGreaterOrEqual:
				return ConditionalSum<SimdCompareGreaterOrEqual>(src, srcStride, width, height, mask, maskStride, value, sum);
			case SimdCompareLesser:
				return ConditionalSum<SimdCompareLesser>(src, srcStride, width, height, mask, maskStride, value, sum);
			case SimdCompareLesserOrEqual:
				return ConditionalSum<SimdCompareLesserOrEqual>(src, srcStride, width, height, mask, maskStride, value, sum);
			default:
				assert(0);
			}
		}
		SIMD_INLINE v4u32 SquareSum(v16u8 src)
		{
			return PadMutiSum(src,src);
		}
		template <SimdCompareType compareType>
		void ConditionalSquareSum(const uint8_t * src, size_t srcStride, size_t width, size_t height,
			const uint8_t * mask, size_t maskStride, uint8_t value, uint64_t * sum)
		{
			assert(width >= A);

			size_t alignedWidth = Simd::AlignLo(width, A);
			v16u8 K8_FF = Fill((uint8_t)0xff);
			v16u8 tailMask = ShiftLeft(K8_FF, A - width + alignedWidth);

			v16u8 _value = Fill((uint8_t)value);

			v2u64 _sum = Zero<v2u64>();
			for (size_t row = 0; row < height; ++row)
			{
				v4u32 rowSum = Zero<v4u32>();
				for (size_t col = 0; col < alignedWidth; col += A)
				{
					v16u8 _mask = Compare8u<compareType>(Load<2>(mask + col), _value);
					v16u8 _src = _mask & Load<1>(src + col);
					rowSum += SquareSum(_src);
				}
				if (alignedWidth != width)
				{
					v16u8 _mask = Compare8u<compareType>(Load(mask + width - A), _value);
					v16u8 _src = _mask & Load(src + width - A) & tailMask;
					rowSum += SquareSum(_src);
				}
				_sum = PadSum(_sum, rowSum);
				src += srcStride;
				mask += maskStride;
			}
			*sum = ExtractSum(_sum);
		}

		void ConditionalSquareSum(const uint8_t * src, size_t srcStride, size_t width, size_t height,
			const uint8_t * mask, size_t maskStride, uint8_t value, SimdCompareType compareType, uint64_t * sum)
		{
			switch (compareType)
			{
			case SimdCompareEqual:
				return ConditionalSquareSum<SimdCompareEqual>(src, srcStride, width, height, mask, maskStride, value, sum);
			case SimdCompareNotEqual:
				return ConditionalSquareSum<SimdCompareNotEqual>(src, srcStride, width, height, mask, maskStride, value, sum);
			case SimdCompareGreater:
				return ConditionalSquareSum<SimdCompareGreater>(src, srcStride, width, height, mask, maskStride, value, sum);
			case SimdCompareGreaterOrEqual:
				return ConditionalSquareSum<SimdCompareGreaterOrEqual>(src, srcStride, width, height, mask, maskStride, value, sum);
			case SimdCompareLesser:
				return ConditionalSquareSum<SimdCompareLesser>(src, srcStride, width, height, mask, maskStride, value, sum);
			case SimdCompareLesserOrEqual:
				return ConditionalSquareSum<SimdCompareLesserOrEqual>(src, srcStride, width, height, mask, maskStride, value, sum);
			default:
				assert(0);
			}
		}

		SIMD_INLINE v4u32 SquaredDifference(const uint8_t * src, ptrdiff_t step, v16u8 mask)
		{
			const v16u8 a = Load<1>(src - step) & mask;
			const v16u8 b = Load<2>(src + step) & mask;
			return SquareSum(AbsDifference(a,b));
		}

		template <SimdCompareType compareType>
		void ConditionalSquareGradientSum(const uint8_t * src, size_t srcStride, size_t width, size_t height,
			const uint8_t * mask, size_t maskStride, uint8_t value, uint64_t * sum)
		{
			assert(width >= A + 2 && height >= 3);

			src += srcStride;
			mask += maskStride;
			height -= 2;

			const v16u8 K8_FF = Fill((uint8_t)0xff);
			size_t alignedWidth = Simd::AlignLo(width - 1, A);

			v16u8 noseMask = ShiftRight(K8_FF, 1);
			// dumpdata<v16u8>(noseMask,"noseMask");
			// exit(0);
			v16u8 tailMask = ShiftLeft(K8_FF, A - width + 1 + alignedWidth);
			v16u8 _value = Fill(value);

			v2u64 _sum = Zero<v2u64>();

			for (size_t row = 0; row < height; ++row)
			{
				v4u32 rowSum = Zero<v4u32>();
				{
					const v16u8 _mask = Compare8u<compareType>(Load<3>(mask + 1), _value) & noseMask;
					rowSum += SquaredDifference(src + 1,1,_mask);
					rowSum += SquaredDifference(src + 1,srcStride,_mask);
				}
				for (size_t col = A; col < alignedWidth; col += A)
				{
					const v16u8 _mask = Compare8u<compareType>(Load<3>(mask + col), _value);
					rowSum += SquaredDifference(src + col,1,_mask);
					rowSum += SquaredDifference(src + col,srcStride,_mask);
				}
				if (alignedWidth != width - 1)
				{
					size_t offset = width - A - 1;
					const v16u8 _mask = Compare8u<compareType>(Load(mask + offset), _value) & tailMask;
					rowSum += SquaredDifference(src + offset,1,_mask);
					rowSum += SquaredDifference(src + offset,srcStride,_mask);
				}
				_sum = PadSum(_sum,rowSum);
				src += srcStride;
				mask += maskStride;
			}
			*sum = ExtractSum(_sum);
		}

		void ConditionalSquareGradientSum(const uint8_t * src, size_t srcStride, size_t width, size_t height,
			const uint8_t * mask, size_t maskStride, uint8_t value, SimdCompareType compareType, uint64_t * sum)
		{
			switch (compareType)
			{
			case SimdCompareEqual:
				return ConditionalSquareGradientSum<SimdCompareEqual>(src, srcStride, width, height, mask, maskStride, value, sum);
			case SimdCompareNotEqual:
				return ConditionalSquareGradientSum<SimdCompareNotEqual>(src, srcStride, width, height, mask, maskStride, value, sum);
			case SimdCompareGreater:
				return ConditionalSquareGradientSum<SimdCompareGreater>(src, srcStride, width, height, mask, maskStride, value, sum);
			case SimdCompareGreaterOrEqual:
				return ConditionalSquareGradientSum<SimdCompareGreaterOrEqual>(src, srcStride, width, height, mask, maskStride, value, sum);
			case SimdCompareLesser:
				return ConditionalSquareGradientSum<SimdCompareLesser>(src, srcStride, width, height, mask, maskStride, value, sum);
			case SimdCompareLesserOrEqual:
				return ConditionalSquareGradientSum<SimdCompareLesserOrEqual>(src, srcStride, width, height, mask, maskStride, value, sum);
			default:
				assert(0);
			}
		}

		template <SimdCompareType compareType>
		SIMD_INLINE void ConditionalFill(const uint8_t * src, size_t offset, const v16u8 & threshold, const v16u8 & value, uint8_t * dst)
		{
			v16u8 _src = Load<1>(src + offset);
			v16u8 _dst = Load<2>(dst + offset);
			v16u8 cmpMask = Compare8u<compareType>(_src,threshold);
			v16u8 _value = SelectVector(cmpMask,_dst,value);
			Store(_value,dst + offset);
		}

		template <SimdCompareType compareType>
		void ConditionalFill(const uint8_t * src, size_t srcStride, size_t width, size_t height,
			uint8_t threshold, uint8_t value, uint8_t * dst, size_t dstStride)
		{
			assert(width >= A);
			size_t alignedWidth = Simd::AlignLo(width, A);

			v16u8 _value = Fill(value);
			v16u8 _threshold = Fill(threshold);

			for (size_t row = 0; row < height; ++row)
			{
				for (size_t col = 0; col < alignedWidth; col += A)
					ConditionalFill<compareType>(src, col, _threshold, _value, dst);
				if (alignedWidth != width)
					ConditionalFill<compareType>(src, width - A, _threshold, _value, dst);
				src += srcStride;
				dst += dstStride;
			}
		}

		void ConditionalFill(const uint8_t * src, size_t srcStride, size_t width, size_t height,
			uint8_t threshold, SimdCompareType compareType, uint8_t value, uint8_t * dst, size_t dstStride)
		{
			switch (compareType)
			{
			case SimdCompareEqual:
				return ConditionalFill<SimdCompareEqual>(src, srcStride, width, height, threshold, value, dst, dstStride);
			case SimdCompareNotEqual:
				return ConditionalFill<SimdCompareNotEqual>(src, srcStride, width, height, threshold, value, dst, dstStride);
			case SimdCompareGreater:
				return ConditionalFill<SimdCompareGreater>(src, srcStride, width, height, threshold, value, dst, dstStride);
			case SimdCompareGreaterOrEqual:
				return ConditionalFill<SimdCompareGreaterOrEqual>(src, srcStride, width, height, threshold, value, dst, dstStride);
			case SimdCompareLesser:
				return ConditionalFill<SimdCompareLesser>(src, srcStride, width, height, threshold, value, dst, dstStride);
			case SimdCompareLesserOrEqual:
				return ConditionalFill<SimdCompareLesserOrEqual>(src, srcStride, width, height, threshold, value, dst, dstStride);
			default:
				assert(0);
			}
		}
	}
#endif// SIMD_MSA_ENABLE
}
