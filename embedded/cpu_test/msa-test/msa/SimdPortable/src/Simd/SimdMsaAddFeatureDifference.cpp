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
#include "Simd/SimdStore.h"

#include "Simd/SimdLog.h"
#include "Simd/SimdMsaType.h"
namespace Simd
{
#ifdef SIMD_MSA_ENABLE
	namespace Msa
	{
        SIMD_INLINE v16u8 FeatureDifference(v16u8 value, v16u8 lo, v16u8 hi)
        {
            return Max(SubSat(value,hi), SubSat(lo,value));
        }
		SIMD_INLINE v16u8 ShiftedWeightedSquare(v16u8 sum,v16u8 difference, v8u16 weight)
        {
			v8u16 lo16 = ExtendMultipy<LO>(difference,difference);
			v8u16 hi16 = ExtendMultipy<HI>(difference,difference);
			v4u32 multi0,multi1,multi2,multi3;

			multi0 = ExtendMultipy<LO>(lo16,weight);
			multi1 = ExtendMultipy<HI>(lo16,weight);

			multi2 = ExtendMultipy<LO>(hi16,weight);
			multi3 = ExtendMultipy<HI>(hi16,weight);

			v8u16 a = (v8u16)PadSat((v8u16)multi0,(v8u16)multi1);
			v8u16 b = (v8u16)PadSat((v8u16)multi2,(v8u16)multi3);

			v16u8 z = Zero<v16i8>();
			a = a >> 8;
			b = b >> 8;

			lo16 = Interleave<LO>(sum,z);
			hi16 = Interleave<HI>(sum,z);

			a += lo16;
			b += hi16;
			return PadSat(a,b);

		}

        SIMD_INLINE void AddFeatureDifference(const uint8_t * value, const uint8_t * lo, const uint8_t * hi,
            uint8_t * difference, size_t offset, v16u8 weight)
        {
            v16u8  _value = Load<1>(value + offset);
            v16u8 _lo = Load<2>(lo + offset);
            v16u8 _hi = Load<3>(hi + offset);
            v16u8 _difference = Load<4>(difference + offset);
            v16u8 featureDifference = FeatureDifference(_value, _lo, _hi);
			v16u8 inc = ShiftedWeightedSquare(_difference,featureDifference,weight);
			Store(inc,difference + offset);
        }
        SIMD_INLINE void AddFeatureDifference(const uint8_t * value, const uint8_t * lo, const uint8_t * hi,
											  uint8_t * difference, size_t offset, v16u8 weight, v16u8 mask)
        {
            v16u8  _value = Load<1>(value + offset);
            v16u8 _lo = Load<2>(lo + offset);
            v16u8 _hi = Load<3>(hi + offset);
            v16u8 _difference = Load<4>(difference + offset);
            v16u8 featureDifference = FeatureDifference(_value, _lo, _hi);
			v16u8 inc = ShiftedWeightedSquare(_difference,featureDifference & mask,weight);
			Store(inc,difference + offset);
        }

        void AddFeatureDifference(const uint8_t * value, size_t valueStride, size_t width, size_t height,
            const uint8_t * lo, size_t loStride, const uint8_t * hi, size_t hiStride,
            uint16_t weight, uint8_t * difference, size_t differenceStride)
        {
            assert(width >= A);
            size_t alignedWidth = AlignLo(width, A);
			v8u16 _weight = Fill(weight);
            for(size_t row = 0; row < height; ++row)
            {
                for(size_t col = 0; col < alignedWidth; col += A)
                    AddFeatureDifference(value, lo, hi, difference, col, _weight);

                if(alignedWidth != width){
					v16u8 _mask = Fill((uint8_t)0xff);
					v16u8 tailMask = ShiftLeft(_mask, A - width + alignedWidth);
                    AddFeatureDifference(value, lo, hi, difference, width - A, _weight, tailMask);
				}
                value += valueStride;
                lo += loStride;
                hi += hiStride;
                difference += differenceStride;
            }
        }
	}
#endif// SIMD_MSA_ENABLE
}
