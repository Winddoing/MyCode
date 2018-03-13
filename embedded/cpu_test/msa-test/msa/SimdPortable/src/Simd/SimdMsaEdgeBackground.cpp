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
#include "Simd/SimdBase.h"
#include "Simd/SimdMsaType.h"

namespace Simd
{
#ifdef SIMD_MSA_ENABLE
	namespace Msa
	{
		SIMD_INLINE void EdgeBackgroundGrowRangeSlow(const uint8_t * value, uint8_t * background, v16u8 mask)
		{
			v16u8 _value = Load<1>(value);
			v16u8 _background = Load<2>(background);
			v16u8 cmpMask = Compare<LT>(_background,_value);
			v16u8 inc = mask & cmpMask;
			Store(_background + inc,background);
		}

		void EdgeBackgroundGrowRangeSlow(const uint8_t * value, size_t valueStride, size_t width, size_t height,
			uint8_t * background, size_t backgroundStride)
		{
			assert(width >= A);

			size_t alignedWidth = AlignLo(width, A);
			v16u8 K8_01;
			Set<1>(K8_01);
			v16u8 tailMask = ShiftLeft(K8_01, A - width + alignedWidth);

			for (size_t row = 0; row < height; ++row)
			{
				for (size_t col = 0; col < alignedWidth; col += A)
					EdgeBackgroundGrowRangeSlow(value + col, background + col, K8_01);
				if (alignedWidth != width)
					EdgeBackgroundGrowRangeSlow(value + width - A, background + width - A, tailMask);
				value += valueStride;
				background += backgroundStride;
			}
		}

		SIMD_INLINE void EdgeBackgroundGrowRangeFast(const uint8_t * value, uint8_t * background)
		{
			const v16u8 _value = Load<1>(value);
			const v16u8 _background = Load<2>(background);
			const v16u8 _dst = Max(_background,_value);
			Store(_dst,background);
		}

		void EdgeBackgroundGrowRangeFast(const uint8_t * value, size_t valueStride, size_t width, size_t height,
			uint8_t * background, size_t backgroundStride)
		{
			assert(width >= A);

			size_t alignedWidth = AlignLo(width, A);
			for (size_t row = 0; row < height; ++row)
			{
				for (size_t col = 0; col < alignedWidth; col += A)
					EdgeBackgroundGrowRangeFast(value + col, background + col);
				if (alignedWidth != width)
					EdgeBackgroundGrowRangeFast(value + width - A, background + width - A);
				value += valueStride;
				background += backgroundStride;
			}
		}

		SIMD_INLINE void EdgeBackgroundIncrementCount(const uint8_t * value,
			const uint8_t * backgroundValue, uint8_t * backgroundCount, size_t offset, v16u8 mask)
		{
			v16u8 _value = Load<1>(value + offset);
			v16u8 _backgroundValue = Load<2>(backgroundValue + offset);
			v16u8 _backgroundCount = Load<3>(backgroundCount + offset);

			v16u8 cmpMask = Compare<LT>(_backgroundValue,_value);
			const v16u8 FF = Fill((uint8_t)0xff);
			v16u8 FFMask = Compare<LT>(_backgroundCount,FF);
			v16u8 inc = mask & cmpMask & FFMask;

			Store(inc + _backgroundCount,backgroundCount + offset);
		}

		void EdgeBackgroundIncrementCount(const uint8_t * value, size_t valueStride, size_t width, size_t height,
			const uint8_t * backgroundValue, size_t backgroundValueStride, uint8_t * backgroundCount, size_t backgroundCountStride)
		{
			assert(width >= A);

			size_t alignedWidth = AlignLo(width, A);
			v16u8 K8_01;
			Set<1>(K8_01);
			v16u8 tailMask = ShiftLeft(K8_01, A - width + alignedWidth);
			for (size_t row = 0; row < height; ++row)
			{
				for (size_t col = 0; col < alignedWidth; col += A)
					EdgeBackgroundIncrementCount(value, backgroundValue, backgroundCount, col, K8_01);
				if (alignedWidth != width)
					EdgeBackgroundIncrementCount(value, backgroundValue, backgroundCount, width - A, tailMask);
				value += valueStride;
				backgroundValue += backgroundValueStride;
				backgroundCount += backgroundCountStride;
			}
		}


		SIMD_INLINE v16u8 AdjustEdge(const v16u8 & count, const v16u8 & value, const v16u8 & mask, const v16u8 & threshold)
		{
			v16u8 incCmpMask = Compare<LT>(threshold,count);
			v16u8 decCmpMask = Compare<LT>(count,threshold);
			v16u8 FF = Fill((uint8_t)0xff);
			v16u8 FFMask = Compare<LT>(value,FF);

			v16u8 inc = mask & incCmpMask & FFMask;
			v16u8 dec = mask & decCmpMask;
			v16u8 _value = value + inc;
			_value = SubSat(_value,dec);
			return _value;
		}

		SIMD_INLINE void EdgeBackgroundAdjustRange(uint8_t * backgroundCount, uint8_t * backgroundValue,
			size_t offset, const v16u8 & threshold, const v16u8 & mask)
		{
			const v16u8 _backgroundCount = Load<1>(backgroundCount + offset);
			const v16u8 _backgroundValue = Load<2>(backgroundValue + offset);

			Store(AdjustEdge(_backgroundCount, _backgroundValue, mask, threshold),backgroundValue + offset);
			Store(Zero<v16u8>(),backgroundCount + offset);
		}

		void EdgeBackgroundAdjustRange(uint8_t * backgroundCount, size_t backgroundCountStride, size_t width, size_t height,
			uint8_t * backgroundValue, size_t backgroundValueStride, uint8_t threshold)
		{
			assert(width >= A);

			const v16u8 _threshold = Fill((uint8_t)threshold);
			size_t alignedWidth = AlignLo(width, A);
			v16u8 K8_01;
			Set<1>(K8_01);
			v16u8 tailMask = ShiftLeft(K8_01, A - width + alignedWidth);
			for (size_t row = 0; row < height; ++row)
			{
				for (size_t col = 0; col < alignedWidth; col += A)
					EdgeBackgroundAdjustRange(backgroundCount, backgroundValue, col, _threshold, K8_01);
				if (alignedWidth != width)
					EdgeBackgroundAdjustRange(backgroundCount, backgroundValue, width - A, _threshold, tailMask);
				backgroundValue += backgroundValueStride;
				backgroundCount += backgroundCountStride;
			}
		}

		SIMD_INLINE void EdgeBackgroundAdjustRangeMasked(uint8_t * backgroundCount, uint8_t * backgroundValue,
			const uint8_t * mask, size_t offset, const v16u8 & threshold, const v16u8 & tailMask)
		{
			const v16u8 _mask = Load<1>(mask + offset);
			EdgeBackgroundAdjustRange(backgroundCount, backgroundValue, offset, threshold, _mask & tailMask);
		}

		void EdgeBackgroundAdjustRangeMasked(uint8_t * backgroundCount, size_t backgroundCountStride, size_t width, size_t height,
			uint8_t * backgroundValue, size_t backgroundValueStride, uint8_t threshold, const uint8_t * mask, size_t maskStride)
		{
			assert(width >= A);
			const v16u8 _threshold = Fill((uint8_t)threshold);
			size_t alignedWidth = AlignLo(width, A);
			v16u8 K8_01;
			Set<1>(K8_01);
			v16u8 tailMask = ShiftLeft(K8_01, A - width + alignedWidth);
			for (size_t row = 0; row < height; ++row)
			{
				for (size_t col = 0; col < alignedWidth; col += A)
					EdgeBackgroundAdjustRangeMasked(backgroundCount, backgroundValue, mask, col, _threshold, K8_01);
				if (alignedWidth != width)
					EdgeBackgroundAdjustRangeMasked(backgroundCount, backgroundValue, mask, width - A, _threshold, tailMask);
				backgroundValue += backgroundValueStride;
				backgroundCount += backgroundCountStride;
				mask += maskStride;
			}
		}
		void SIMD_INLINE EdgeBackgroundShiftRange(uint8_t *dst,const uint8_t *src)
		{
			v16u8 _src = Load<1>(src);
			Store(_src,dst);
		}

		void EdgeBackgroundShiftRange(const uint8_t * value, size_t valueStride, size_t width, size_t height, uint8_t * background, size_t backgroundStride)
		{
			assert(width >= A);
			size_t alignedWidth = AlignLo(width, A);
			for(size_t row = 0; row < height; ++row)
            {
                for(size_t col = 0; col < alignedWidth; col += A)
                    EdgeBackgroundShiftRange(background + col,value + col);

				if (alignedWidth != width)
					EdgeBackgroundShiftRange(background + width - A,value + width - A);
                value += valueStride;
                background += backgroundStride;
            }
		}
		SIMD_INLINE void EdgeBackgroundShiftRangeMasked(const uint8_t * value, uint8_t * background, const uint8_t * mask, size_t offset)
		{
			v16u8 _value = Load<1>(value + offset);
			v16u8 _background = Load<2>(background + offset);
			v16u8 _mask = Load<3>(mask + offset);
			v16u8 _dstValue = SelectVector(_mask,_background,_value);
			Store(_dstValue,background + offset);
		}

		void EdgeBackgroundShiftRangeMasked(const uint8_t * value, size_t valueStride, size_t width, size_t height,
			uint8_t * background, size_t backgroundStride, const uint8_t * mask, size_t maskStride)
		{
			assert(width >= A);
			size_t alignedWidth = AlignLo(width, A);
			for (size_t row = 0; row < height; ++row)
			{
				for (size_t col = 0; col < alignedWidth; col += A)
					EdgeBackgroundShiftRangeMasked(value, background, mask, col);
				if (alignedWidth != width)
					EdgeBackgroundShiftRangeMasked(value, background, mask, width - A);
				value += valueStride;
				background += backgroundStride;
				mask += maskStride;
			}
		}
	}
#endif// SIMD_MSA_ENABLE
}
