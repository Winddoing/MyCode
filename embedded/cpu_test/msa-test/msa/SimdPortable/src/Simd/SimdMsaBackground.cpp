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
#include "Simd/SimdMsaType.h"
namespace Simd
{
#ifdef SIMD_MSA_ENABLE
    namespace Msa
    {
        SIMD_INLINE void BackgroundGrowRangeSlow(const uint8_t * value, uint8_t * lo, uint8_t * hi, v16u8 mask)
        {

            v16u8 _value = Load<1>(value);
			v16u8 _lo = Load<2>(lo);
			v16u8 _hi = Load<3>(hi);

            v16u8 inc = mask & Compare<LT>(_hi,_value);
			v16u8 dec = mask & Compare<LT>(_value,_lo);
            Store(_lo - dec,lo);
			Store(_hi + inc,hi);
        }

        void BackgroundGrowRangeSlow(const uint8_t * value, size_t valueStride, size_t width, size_t height,
             uint8_t * lo, size_t loStride, uint8_t * hi, size_t hiStride)
        {
            assert(width >= A);

			size_t alignedWidth = AlignLo(width, A);
			v16u8 K8_01;
		    Set<1>(K8_01);

			v16u8 tailMask = ShiftLeft(K8_01, A - width + alignedWidth);
            for(size_t row = 0; row < height; ++row)
            {
                for(size_t col = 0; col < alignedWidth; col += A)
                    BackgroundGrowRangeSlow(value + col, lo + col, hi + col, K8_01);
                if(alignedWidth != width)
                    BackgroundGrowRangeSlow(value + width - A, lo + width - A, hi + width - A, tailMask);
                value += valueStride;
                lo += loStride;
                hi += hiStride;
            }
        }

		SIMD_INLINE void BackgroundGrowRangeFast(const uint8_t * value, uint8_t * lo, uint8_t * hi)
		{
			const v16u8 _value = Load<1>(value);
			const v16u8 _lo = Load<2>(lo);
			const v16u8 _hi = Load<3>(hi);
			Store(Min(_lo,_value),lo);
			Store(Max(_hi,_value),hi);
		}

		void BackgroundGrowRangeFast(const uint8_t * value, size_t valueStride, size_t width, size_t height,
			uint8_t * lo, size_t loStride, uint8_t * hi, size_t hiStride)
		{
			assert(width >= A);
			size_t alignedWidth = AlignLo(width, A);
			for (size_t row = 0; row < height; ++row)
			{
				for (size_t col = 0; col < alignedWidth; col += A)
					BackgroundGrowRangeFast(value + col, lo + col, hi + col);
				if (alignedWidth != width)
					BackgroundGrowRangeFast(value + width - A, lo + width - A, hi + width - A);
				value += valueStride;
				lo += loStride;
				hi += hiStride;
			}
		}

		SIMD_INLINE void BackgroundIncrementCount(const uint8_t * value,const uint8_t * loValue, const uint8_t * hiValue,
												  uint8_t * loCount, uint8_t * hiCount, size_t offset, v16u8 mask)
		{
			const v16u8 FF = Fill((uint8_t)0xff);
			v16u8 _value = Load<1>(value + offset);
			v16u8 _loValue = Load<2>(loValue + offset);
			v16u8 _loCount = Load<3>(loCount + offset);
			v16u8 _hiValue = Load<4>(hiValue + offset);
			v16u8 _hiCount = Load<5>(hiCount + offset);

			v16u8 _loMaxMask = Compare<LT>(_loCount,FF);
			v16u8 _hiMaxMask = Compare<LT>(_hiCount,FF);

			v16u8 incLo = mask & Compare<LT>(_value,_loValue);
			incLo = _loMaxMask & incLo;
			v16u8 incHi = mask & Compare<LT>(_hiValue,_value);
			incHi = _hiMaxMask & incHi;

			_loCount += incLo;
			_hiCount += incHi;
			Store(_loCount,loCount + offset);
			Store(_hiCount,hiCount + offset);
		}

		void BackgroundIncrementCount(const uint8_t * value, size_t valueStride, size_t width, size_t height,
									  const uint8_t * loValue, size_t loValueStride, const uint8_t * hiValue, size_t hiValueStride,
									  uint8_t * loCount, size_t loCountStride, uint8_t * hiCount, size_t hiCountStride)
		{
			assert(width >= A);
			v16u8 K8_01;
			Set<1>(K8_01);
			size_t alignedWidth = AlignLo(width, A);
			v16u8 tailMask = ShiftLeft(K8_01, A - width + alignedWidth);

			for (size_t row = 0; row < height; ++row)
			{
				for (size_t col = 0; col < alignedWidth; col += A)
					BackgroundIncrementCount(value, loValue, hiValue, loCount, hiCount, col, K8_01);
				if (alignedWidth != width)
					BackgroundIncrementCount(value, loValue, hiValue, loCount, hiCount, width - A, tailMask);
				value += valueStride;
				loValue += loValueStride;
				hiValue += hiValueStride;
				loCount += loCountStride;
				hiCount += hiCountStride;
			}
		}

		SIMD_INLINE v16u8 AdjustLo(v16u8 & count, v16u8 & value, const v16u8 & mask, const v16u8 & threshold)
		{
			const v16u8 FF = Fill((uint8_t)0xff);
			const v16u8 zero = Zero<v16u8>();
			v16u8 decMask = Compare<LT>(zero,value);
			v16u8 incMask = Compare<LT>(value,FF);
			v16u8 dec = Compare<LT>(threshold,count) & mask & decMask;
			v16u8 inc = Compare<LT>(count,threshold) & mask & incMask;

			return value + inc - dec;
		}

		SIMD_INLINE v16u8 AdjustHi(v16u8 & count, v16u8 & value, const v16u8 & mask, const v16u8 & threshold)
		{
			const v16u8 FF = Fill((uint8_t)0xff);
			const v16u8 zero = Zero<v16u8>();
			v16u8 decMask = Compare<LT>(zero,value);
			v16u8 incMask = Compare<LT>(value,FF);

			v16u8 inc = Compare<LT>(threshold,count) & mask & incMask;
			v16u8 dec = Compare<LT>(count,threshold) & mask & decMask;

			return value + inc - dec;
		}

		SIMD_INLINE void BackgroundAdjustRange(uint8_t * loCount, uint8_t * loValue,
			uint8_t * hiCount, uint8_t * hiValue, size_t offset, const v16u8 & threshold, const v16u8 & mask)
		{
			v16u8 _loCount = Load<1>(loCount + offset);
			v16u8 _loValue = Load<2>(loValue + offset);
			v16u8 _hiCount = Load<3>(hiCount + offset);
			v16u8 _hiValue = Load<4>(hiValue + offset);

			Store(AdjustLo(_loCount, _loValue, mask, threshold),loValue + offset);
			Store(AdjustHi(_hiCount, _hiValue, mask, threshold),hiValue + offset);

			Store(Zero<v16u8>(),loCount + offset);
			Store(Zero<v16u8>(),hiCount + offset);
		}

		void BackgroundAdjustRange(uint8_t * loCount, size_t loCountStride, size_t width, size_t height,
			uint8_t * loValue, size_t loValueStride, uint8_t * hiCount, size_t hiCountStride,
			uint8_t * hiValue, size_t hiValueStride, uint8_t threshold)
		{
			assert(width >= A);
			v16u8 _threshold = Fill(threshold);
			size_t alignedWidth = AlignLo(width, A);
			v16u8 K8_01;
			Set<1>(K8_01);

			v16u8 tailMask = ShiftLeft(K8_01, A - width + alignedWidth);
			for (size_t row = 0; row < height; ++row)
			{
				for (size_t col = 0; col < alignedWidth; col += A)
					BackgroundAdjustRange(loCount, loValue, hiCount, hiValue, col, _threshold, K8_01);
				if (alignedWidth != width)
					BackgroundAdjustRange(loCount, loValue, hiCount, hiValue, width - A, _threshold, tailMask);
				loValue += loValueStride;
				hiValue += hiValueStride;
				loCount += loCountStride;
				hiCount += hiCountStride;
			}
		}

		SIMD_INLINE void BackgroundAdjustRangeMasked(uint8_t * loCount, uint8_t * loValue, uint8_t * hiCount, uint8_t * hiValue,
			const uint8_t * mask, size_t offset, const v16u8 & threshold, const v16u8 & tailMask)
		{
			const v16u8 _mask = Load<5>(mask + offset) & tailMask;
			BackgroundAdjustRange(loCount, loValue, hiCount, hiValue, offset, threshold, _mask);
		}

		void BackgroundAdjustRangeMasked(uint8_t * loCount, size_t loCountStride, size_t width, size_t height,
			uint8_t * loValue, size_t loValueStride, uint8_t * hiCount, size_t hiCountStride,
			uint8_t * hiValue, size_t hiValueStride, uint8_t threshold, const uint8_t * mask, size_t maskStride)
		{
			assert(width >= A);

			const v16u8 _threshold = Fill(threshold);
			size_t alignedWidth = AlignLo(width, A);
			v16u8 K8_01;
			Set<1>(K8_01);
			v16u8 tailMask = ShiftLeft(K8_01, A - width + alignedWidth);
			for (size_t row = 0; row < height; ++row)
			{
				for (size_t col = 0; col < alignedWidth; col += A)
					BackgroundAdjustRangeMasked(loCount, loValue, hiCount, hiValue, mask, col, _threshold, K8_01);
				if (alignedWidth != width)
					BackgroundAdjustRangeMasked(loCount, loValue, hiCount, hiValue, mask, width - A, _threshold, tailMask);
				loValue += loValueStride;
				hiValue += hiValueStride;
				loCount += loCountStride;
				hiCount += hiCountStride;
				mask += maskStride;
			}
		}


		SIMD_INLINE void BackgroundShiftRange(const uint8_t * value, uint8_t * lo, uint8_t * hi, size_t offset)
		{
			const v16u8 _value = Load<1>(value + offset);
			v16u8 _lo = Load<2>(lo + offset);
			v16u8 _hi = Load<3>(hi + offset);
			const v16u8 hiMask = Compare<LT>(_hi,_value);
			const v16u8 loMask = Compare<LT>(_value,_lo);
			const v16u8 FF = Fill((uint8_t)0xff);

			v16u8 add = (_value - _hi) & hiMask;
			v16u8 sub = (_lo - _value) & loMask;

			v16u8 loDiffMask = Compare<LT>(~_lo,add);
			_lo = Min(_lo + add,FF) | loDiffMask;
			_lo = SubSat(_lo,sub);

			v16u8 hiDiffMask = Compare<LT>(~_hi,add);
			_hi = Min(_hi + add,FF) | hiDiffMask;
			_hi = SubSat(_hi,sub);

			Store(_lo,lo + offset);
			Store(_hi,hi + offset);
		}


		SIMD_INLINE void BackgroundShiftRange(const uint8_t * value, uint8_t * lo, uint8_t * hi, size_t offset,v16u8 mask)
		{
			const v16u8 _value = Load<1>(value + offset);
			v16u8 _lo = Load<2>(lo + offset);
			v16u8 _hi = Load<3>(hi + offset);
			const v16u8 hiMask = Compare<LT>(_hi,_value);
			const v16u8 loMask = Compare<LT>(_value,_lo);
			const v16u8 FF = Fill((uint8_t)0xff);

			v16u8 add = (_value - _hi) & hiMask & mask;
			v16u8 sub = (_lo - _value) & loMask & mask;

			v16u8 loDiffMask = Compare<LT>(~_lo,add);
			_lo = Min(_lo + add,FF) | loDiffMask;
			_lo = SubSat(_lo,sub);

			v16u8 hiDiffMask = Compare<LT>(~_hi,add);
			_hi = Min(_hi + add,FF) | hiDiffMask;
			_hi = SubSat(_hi,sub);

			Store(_lo,lo + offset);
			Store(_hi,hi + offset);
		}
		void BackgroundShiftRange(const uint8_t * value, size_t valueStride, size_t width, size_t height,
			uint8_t * lo, size_t loStride, uint8_t * hi, size_t hiStride)
		{
			assert(width >= A);
			size_t alignedWidth = AlignLo(width, A);
			const v16u8 K8_FF = Fill((uint8_t)0xff);
			const v16u8 tailMask = ShiftLeft(K8_FF, A - width + alignedWidth);

			for (size_t row = 0; row < height; ++row)
			{
				for (size_t col = 0; col < alignedWidth; col += A)
					BackgroundShiftRange(value, lo, hi, col);
				if (alignedWidth != width)
					BackgroundShiftRange(value, lo, hi, width - A, tailMask);
				value += valueStride;
				lo += loStride;
				hi += hiStride;
			}
		}


		SIMD_INLINE void BackgroundShiftRangeMasked(const uint8_t * value, uint8_t * lo, uint8_t * hi, const uint8_t * mask,
			size_t offset, v16u8 tailMask)
		{
			const v16u8 _mask = Load<4>(mask + offset);
			BackgroundShiftRange(value, lo, hi, offset, _mask & tailMask);
		}

		void BackgroundShiftRangeMasked(const uint8_t * value, size_t valueStride, size_t width, size_t height,
			uint8_t * lo, size_t loStride, uint8_t * hi, size_t hiStride, const uint8_t * mask, size_t maskStride)
		{
			assert(width >= A);

			size_t alignedWidth = AlignLo(width, A);
			const v16u8 K8_FF = Fill((uint8_t)0xff);
			v16u8 tailMask = ShiftLeft(K8_FF, A - width + alignedWidth);
			for (size_t row = 0; row < height; ++row)
			{
				for (size_t col = 0; col < alignedWidth; col += A)
					BackgroundShiftRangeMasked(value, lo, hi, mask, col, K8_FF);
				if (alignedWidth != width)
					BackgroundShiftRangeMasked(value, lo, hi, mask, width - A, tailMask);
				value += valueStride;
				lo += loStride;
				hi += hiStride;
				mask += maskStride;
			}
		}

		SIMD_INLINE void BackgroundInitMask(const uint8_t * src, uint8_t * dst, const v16u8 & index, const v16u8 & value)
		{
			v16u8 _mask = Compare<EQ>(Load<1>(src), index);
			v16u8 _old = Load<2>(dst);
			v16u8 _v = SelectVector(_mask,_old,value);
			Store(_v,dst);
		}

		void BackgroundInitMask(const uint8_t * src, size_t srcStride, size_t width, size_t height,
			uint8_t index, uint8_t value, uint8_t * dst, size_t dstStride)
		{
			assert(width >= A);

			size_t alignedWidth = AlignLo(width, A);
			const v16u8 _index = Fill(index);
			const v16u8 _value = Fill(value);
			for (size_t row = 0; row < height; ++row)
			{
				for (size_t col = 0; col < alignedWidth; col += A)
					BackgroundInitMask(src + col, dst + col, _index, _value);
				if (alignedWidth != width)
					BackgroundInitMask(src + width - A, dst + width - A, _index, _value);
				src += srcStride;
				dst += dstStride;
			}
		}
    }
#endif// SIMD_MSA_ENABLE
}
