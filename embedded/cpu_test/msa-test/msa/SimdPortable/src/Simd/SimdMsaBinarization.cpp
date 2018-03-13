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
#include "Simd/SimdCompare.h"
#include "Simd/SimdSet.h"
#include "Simd/SimdMsaType.h"
#include "Simd/SimdMsaConversion.h"
namespace Simd
{
#ifdef SIMD_MSA_ENABLE
	namespace Msa
	{
		template <SimdCompareType compareType>
		void Binarization(const uint8_t *src,const uint8_t *dst,v16u8 _value,v16u8 positive,v16u8 negative)
		{
			v16u8  _src = Load<1>(src);
			v16u8 mask = Compare8u<compareType>(_src,_value);
			Store(SelectVector(mask,negative,positive),dst);
		}
		template <SimdCompareType compareType>
		void Binarization(const uint8_t * src, size_t srcStride, size_t width, size_t height,
						  uint8_t value, uint8_t positive, uint8_t negative, uint8_t * dst, size_t dstStride)
        {
			assert(width >= A);

            size_t alignedWidth = Simd::AlignLo(width, A);
			size_t alignedWidth4 = Simd::AlignLo(width, A * 4);
			v16u8 _value = Fill(value);
			v16u8 _positive = Fill(positive);
			v16u8 _negative = Fill(negative);

            for(size_t row = 0; row < height; ++row)
            {
				size_t col = 0;
                for(; col < alignedWidth4; col += 4 * A)
                {
					size_t offset = col + 0 * A;
					Binarization<compareType>(src + offset,dst + offset,_value,_positive,_negative);
					offset = col + 1 * A;
					Binarization<compareType>(src + offset,dst + offset,_value,_positive,_negative);
					offset = col + 2 * A;
					Binarization<compareType>(src + offset,dst + offset,_value,_positive,_negative);
					offset = col + 3 * A;
					Binarization<compareType>(src + offset,dst + offset,_value,_positive,_negative);

                }
				if(alignedWidth != alignedWidth4){
					for(; col < alignedWidth; col += A)
					{
						Binarization<compareType>(src +  col,dst + col,_value,_positive,_negative);
					}
				}

                if(alignedWidth != width)
					Binarization<compareType>(src + width - A,dst + width - A,_value,_positive,_negative);

                src += srcStride;
                dst += dstStride;
            }
        }

        void Binarization(const uint8_t * src, size_t srcStride, size_t width, size_t height,
            uint8_t value, uint8_t positive, uint8_t negative, uint8_t * dst, size_t dstStride, SimdCompareType compareType)
        {
            switch(compareType)
            {
            case SimdCompareEqual:
                return Binarization<SimdCompareEqual>(src, srcStride, width, height, value, positive, negative, dst, dstStride);
            case SimdCompareNotEqual:
                return Binarization<SimdCompareNotEqual>(src, srcStride, width, height, value, positive, negative, dst, dstStride);
            case SimdCompareGreater:
                return Binarization<SimdCompareGreater>(src, srcStride, width, height, value, positive, negative, dst, dstStride);
            case SimdCompareGreaterOrEqual:
                return Binarization<SimdCompareGreaterOrEqual>(src, srcStride, width, height, value, positive, negative, dst, dstStride);
            case SimdCompareLesser:
                return Binarization<SimdCompareLesser>(src, srcStride, width, height, value, positive, negative, dst, dstStride);
            case SimdCompareLesserOrEqual:
                return Binarization<SimdCompareLesserOrEqual>(src, srcStride, width, height, value, positive, negative, dst, dstStride);
            default:
                assert(0);
            }
        }
		namespace
		{
			struct Buffer
			{
				Buffer(size_t width, size_t edge)
				{
					size_t size = sizeof(uint16_t)*(width + 2 * edge) + sizeof(uint32_t)*(2 * width + 2 * edge);
					_p = Allocate(size);
					memset(_p, 0, size);
					sa = (uint16_t*)_p + edge;
					s0a0 = (uint32_t*)(sa + width + edge) + edge;
					sum = (uint32_t*)(s0a0 + width + edge);
				}

				~Buffer()
				{
					Free(_p);
				}

				uint16_t * sa;
				uint32_t * s0a0;
				uint32_t * sum;
			private:
				void *_p;
			};
		}

		template <SimdCompareType compareType>
		SIMD_INLINE void AddRows(const uint8_t * src, uint16_t * sa, const v16u8 & value, const v16u8 &mask)
		{
			v16u8 _src = Load<1>(src);
			v16u8 cmp = Compare8u<compareType>(_src,value);
			v16u8 inc = cmp & mask;

			v16u8 incLo = Interleave<LO>(inc,mask);
			v16u8 incHi = Interleave<HI>(inc,mask);

			v16u8 _saLo = Load<2>((uint8_t*)sa);
			v16u8 _saHi = Load((uint8_t*)(sa + HA));

			_saLo += incLo;
			_saHi += incHi;

			Store(_saLo,(uint8_t*)sa);
			Store(_saHi,(uint8_t*)(sa + HA));
		}

		template <SimdCompareType compareType>
		SIMD_INLINE void SubRows(const uint8_t * src, uint16_t * sa, const v16u8 & value, const v16u8 & mask)
		{
			v16u8 _src = Load<1>(src);
			v16u8 cmp = Compare8u<compareType>(_src,value);
			v16u8 dec = cmp & mask;

			v16u8 decLo = Interleave<LO>(dec,mask);
			v16u8 decHi = Interleave<HI>(dec,mask);

			v16u8 _saLo = Load((uint8_t*)sa);
			v16u8 _saHi = Load((uint8_t*)(sa + HA));

			_saLo -= decLo;
			_saHi -= decHi;

			Store(_saLo,(uint8_t*)sa);
			Store(_saHi,(uint8_t*)(sa + HA));
		}

		SIMD_INLINE v4u32 CompareSum(const v4u32 & sum, const v4u32 & area, const v4u32 & threshold)
		{
			const v4u32 FF = Fill((uint32_t)0xff);
			v4u32 _sum = FF * sum;
			v4u32 _area = area * threshold;
			return Compare<LT>(_area,_sum);
		}

		SIMD_INLINE v8u16 CompareSum(const uint16_t * sum, const v4u32 & threshold)
		{
			v8u16 _sumLo = Load<2>(sum);
			v8u16 _sumHi = Load(sum + HA);
			const v8u16 zero = Zero<v8u16>();
			v4u32 _sum0 = Interleave<EVEN>(_sumLo,zero);
			v4u32 _area0 = Interleave<ODD>(_sumLo,zero);
			v4u32 _sum1 = Interleave<EVEN>(_sumHi,zero);
			v4u32 _area1 = Interleave<ODD>(_sumHi,zero);

			v4u32 lo = CompareSum(_sum0,_area0,threshold);
			v4u32 hi = CompareSum(_sum1,_area1,threshold);

			return PadSat(lo,hi);
		}

		SIMD_INLINE v16u8 CompareSum(const uint32_t * sum, const v4u32 & threshold)
		{
			v8u16 lo = CompareSum((uint16_t*)sum + 0, threshold);
			v8u16 hi = CompareSum((uint16_t*)sum + A, threshold);
			return PadSat(lo,hi);
		}

		template <SimdCompareType compareType>
		void AveragingBinarization(const uint8_t * src, size_t srcStride, size_t width, size_t height,
			uint8_t value, size_t neighborhood, uint8_t threshold, uint8_t positive, uint8_t negative, uint8_t * dst, size_t dstStride)
		{
			assert(width > neighborhood && height > neighborhood && neighborhood < 0x7F);

			const size_t alignedWidth = AlignLo(width, A);
			v16u8 K8_01;
			Set<1>(K8_01);
			const v16u8 tailMask = ShiftLeft(K8_01, A - width + alignedWidth);

			v16u8 _value = Fill(value);
			v16u8 _positive = Fill(positive);
			v16u8 _negative = Fill(negative);
			v4u32 _threshold = Fill((uint32_t)threshold);

			Buffer buffer(AlignHi(width, A), AlignHi(neighborhood + 1, A));

			for (size_t row = 0; row < neighborhood; ++row)
			{
				const uint8_t * s = src + row*srcStride;
				for (size_t col = 0; col < alignedWidth; col += A)
					AddRows<compareType>(s + col, buffer.sa + col, _value, K8_01);
				if (alignedWidth != width)
					AddRows<compareType>(s + width - A, buffer.sa + width - A, _value, tailMask);
			}
			for (size_t row = 0; row < height; ++row)
			{
				if (row < height - neighborhood)
				{
					const uint8_t * s = src + (row + neighborhood)*srcStride;
					for (size_t col = 0; col < alignedWidth; col += A)
						AddRows<compareType>(s + col, buffer.sa + col, _value, K8_01);
					if (alignedWidth != width)
						AddRows<compareType>(s + width - A, buffer.sa + width - A, _value, tailMask);
				}
				if (row > neighborhood)
				{
					const uint8_t * s = src + (row - neighborhood - 1)*srcStride;
					for (size_t col = 0; col < alignedWidth; col += A)
						SubRows<compareType>(s + col, buffer.sa + col, _value, K8_01);
					if (alignedWidth != width)
						SubRows<compareType>(s + width - A, buffer.sa + width - A, _value, tailMask);
				}

				for (size_t col = 0; col < width; col += HA)
				{
					const v16u8 _sa = Load<3>(buffer.sa + col);
					const v16u8 zero = Zero<v16u8>();
					const v16u8 _saLo = Interleave<LO>(_sa,zero);
					const v16u8 _saHi = Interleave<HI>(_sa,zero);
					Store(_saLo,(uint8_t*)(buffer.s0a0 + col + 0));
					Store(_saHi,(uint8_t*)(buffer.s0a0 + col + 4));
				}

				uint32_t sum = 0;
				for (size_t col = 0; col < neighborhood; ++col)
				{
					sum += buffer.s0a0[col];
				}

				for (size_t col = 0; col < width; ++col)
				{
					sum += buffer.s0a0[col + neighborhood];
					sum -= buffer.s0a0[col - neighborhood - 1];

					buffer.sum[col] = sum;

				}
				for (size_t col = 0; col < alignedWidth; col += A)
				{
					const v16u8 mask = CompareSum(buffer.sum + col, _threshold);
					Store(SelectVector(mask,_negative,_positive),dst + col);
				}
				if (alignedWidth != width)
				{
					const v16u8 mask = CompareSum(buffer.sum + width - A, _threshold);
					Store(SelectVector(mask,_negative,_positive),dst + width - A);
				}
				dst += dstStride;
			}
		}

		void AveragingBinarization(const uint8_t * src, size_t srcStride, size_t width, size_t height,
			uint8_t value, size_t neighborhood, uint8_t threshold, uint8_t positive, uint8_t negative,
			uint8_t * dst, size_t dstStride, SimdCompareType compareType)
		{
			switch (compareType)
			{
			case SimdCompareEqual:
				return AveragingBinarization<SimdCompareEqual>(src, srcStride, width, height, value, neighborhood, threshold, positive, negative, dst, dstStride);
			case SimdCompareNotEqual:
				return AveragingBinarization<SimdCompareNotEqual>(src, srcStride, width, height, value, neighborhood, threshold, positive, negative, dst, dstStride);
			case SimdCompareGreater:
				return AveragingBinarization<SimdCompareGreater>(src, srcStride, width, height, value, neighborhood, threshold, positive, negative, dst, dstStride);
			case SimdCompareGreaterOrEqual:
				return AveragingBinarization<SimdCompareGreaterOrEqual>(src, srcStride, width, height, value, neighborhood, threshold, positive, negative, dst, dstStride);
			case SimdCompareLesser:
				return AveragingBinarization<SimdCompareLesser>(src, srcStride, width, height, value, neighborhood, threshold, positive, negative, dst, dstStride);
			case SimdCompareLesserOrEqual:
				return AveragingBinarization<SimdCompareLesserOrEqual>(src, srcStride, width, height, value, neighborhood, threshold, positive, negative, dst, dstStride);
			default:
				assert(0);
			}
		}
    }
#endif// SIMD_MSA_ENABLE
}
