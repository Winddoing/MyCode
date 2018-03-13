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
#include "Simd/SimdMsaType.h"
#include "Simd/SimdMsaConversion.h"
namespace Simd
{
#ifdef SIMD_MSA_ENABLE
    namespace Msa
    {
		SIMD_INLINE v8i16 BinomialSum(v8i16 a,v8i16 b,v8i16 c){
			return c + a + b + b;
		}

		template<bool abs,int sequence> SIMD_INLINE v8i16 SobelDx(v16u8 a[3][3])
		{
			v8i16 d0,d1,d2;
			d0 = ExtendSub<sequence>(a[0][2],a[0][0]);
			d1 = ExtendSub<sequence>(a[1][2],a[1][0]);
			d2 = ExtendSub<sequence>(a[2][2],a[2][0]);
			v8i16 b = BinomialSum(d0,d1,d2);
			return ConditionalAbs<abs>(b);
		}
		template<bool abs> SIMD_INLINE void SobelDx(v16u8 a[3][3],int16_t *dst)
		{
			v8i16 blo = SobelDx<abs,LO>(a);
			v8i16 bhi = SobelDx<abs,HI>(a);
			Store(blo,dst);
			Store(bhi,dst + HA);
		}

		SIMD_INLINE void LoadNoseDx(const uint8_t *p,v16u8 a[3])
		{
			v16u8 shf ={0,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14};
			a[0] = Load<1>(p);
			a[2] = Load(p + 1);
			a[0] = Shuffle(shf,a[0],a[0]);
		}

		SIMD_INLINE void LoadBodyDx(const uint8_t *p,v16u8 a[3])
		{
			a[0] = Load<1>(p - 1);
			a[2] = Load(p + 1);
		}

		SIMD_INLINE void LoadTailDx(const uint8_t *p,v16u8 a[3])
		{
			v16u8 shf ={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,15};
			a[0] = Load(p - 1);
			a[2] = Load(p);
			a[2] = Shuffle(shf,a[2],a[2]);
		}

		template <bool abs>
		void SobelDx(const uint8_t * src, size_t srcStride, size_t width, size_t height, int16_t * dst, size_t dstStride)
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

                LoadNoseDx(src0 + 0, a[0]);
                LoadNoseDx(src1 + 0, a[1]);
                LoadNoseDx(src2 + 0, a[2]);
                SobelDx<abs>(a, dst + 0);
                for(size_t col = A; col < bodyWidth; col += A)
                {
                    LoadBodyDx(src0 + col, a[0]);
                    LoadBodyDx(src1 + col, a[1]);
                    LoadBodyDx(src2 + col, a[2]);
                    SobelDx<abs>(a, dst + col);
                }
                LoadTailDx(src0 + width - A, a[0]);
                LoadTailDx(src1 + width - A, a[1]);
                LoadTailDx(src2 + width - A, a[2]);
                SobelDx<abs>(a, dst + width - A);

                dst += dstStride;
            }
        }

        void SobelDx(const uint8_t * src, size_t srcStride, size_t width, size_t height, uint8_t * dst, size_t dstStride)
        {
            assert(dstStride%sizeof(int16_t) == 0);
			SobelDx<false>(src, srcStride, width, height, (int16_t *)dst, dstStride/sizeof(int16_t));
        }

		void SobelDxAbs(const uint8_t * src, size_t srcStride, size_t width, size_t height, uint8_t * dst, size_t dstStride)
		{
			assert(dstStride%sizeof(int16_t) == 0);
			SobelDx<true>(src, srcStride, width, height, (int16_t *)dst, dstStride / sizeof(int16_t));
		}

		SIMD_INLINE void SobelDxAbsSum(v16u8 a[3][3], v4u32 & sum)
		{
			v8i16 lo = SobelDx<true,LO>(a);
			v8i16 hi = SobelDx<true,HI>(a);
			sum = PadSum(sum,(v8u16)(lo + hi));
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

		void SobelDxAbsSum(const uint8_t * src, size_t stride, size_t width, size_t height, uint64_t * sum)
		{
			assert(width > A);
			size_t bodyWidth = Simd::AlignHi(width, A) - A;
			const uint8_t *src0, *src1, *src2;

			v16u8 a[3][3];
			v2u64 fullSum = Zero<v2u64>();
			const v16u8 K8_FF = Fill((uint8_t)0xff);
			v16u8 tailMask = ShiftLeft(K8_FF, A - width + bodyWidth);

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

				LoadNoseDx(src0 + 0, a[0]);
				LoadNoseDx(src1 + 0, a[1]);
				LoadNoseDx(src2 + 0, a[2]);
				SobelDxAbsSum(a, rowSum);
				for (size_t col = A; col < bodyWidth; col += A)
				{
					LoadBodyDx(src0 + col, a[0]);
					LoadBodyDx(src1 + col, a[1]);
					LoadBodyDx(src2 + col, a[2]);
					SobelDxAbsSum(a, rowSum);
				}
				LoadTailDx(src0 + width - A, a[0]);
				LoadTailDx(src1 + width - A, a[1]);
				LoadTailDx(src2 + width - A, a[2]);
				SetMask3x3(a, tailMask);
				SobelDxAbsSum(a, rowSum);
				fullSum = PadSum(fullSum,rowSum);
			}
			*sum = ExtractSum(fullSum);
        }
		template<bool abs,int sequence> SIMD_INLINE v8i16 SobelDy(v16u8 a[3][3])
		{
			v8i16 d0,d1,d2;
			d0 = ExtendSub<sequence>(a[2][0],a[0][0]);
			d1 = ExtendSub<sequence>(a[2][1],a[0][1]);
			d2 = ExtendSub<sequence>(a[2][2],a[0][2]);
			v8i16 b = BinomialSum(d0,d1,d2);
			return ConditionalAbs<abs>(b);
		}
		template<bool abs> SIMD_INLINE void SobelDy(v16u8 a[3][3],int16_t *dst)
		{
			v8i16 blo = SobelDy<abs,LO>(a);
			v8i16 bhi = SobelDy<abs,HI>(a);
			Store(blo,dst);
			Store(bhi,dst + HA);
		}

		SIMD_INLINE void LoadNose(const uint8_t *p,v16u8 a[3])
		{
			const v16u8 shf ={0,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14};
			a[1] = Load<1>(p);
			a[0] = Shuffle(shf,a[1],a[1]);
			a[2] = Load(p + 1);
		}
		SIMD_INLINE void LoadBody(const uint8_t *p,v16u8 a[3])
		{
			a[0] = Load(p - 1);
			a[1] = Load<1>(p + 0);
			a[2] = Load(p + 1);
		}
		SIMD_INLINE void LoadTail(const uint8_t *p,v16u8 a[3])
		{
			const v16u8 shf ={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,15};
			a[0] = Load(p - 1);
			a[1] = Load(p);
			a[2] = Shuffle(shf,a[1],a[1]);
		}

		template <bool abs>
	    void SobelDy(const uint8_t * src, size_t srcStride, size_t width, size_t height, int16_t * dst, size_t dstStride)
		{
			assert(width > A);
			size_t bodyWidth = Simd::AlignHi(width, A) - A;
			const uint8_t *src0, *src1, *src2;
			v16u8 a[3][3];

			for (size_t row = 0; row < height; ++row)
			{
				src0 = src + srcStride*(row - 1);
				src1 = src0 + srcStride;
				src2 = src1 + srcStride;
				if (row == 0)
					src0 = src1;
				if (row == height - 1)
					src2 = src1;

				LoadNose(src0 + 0, a[0]);
				LoadNose(src2 + 0, a[2]);
				SobelDy<abs>(a, dst + 0);
				for (size_t col = A; col < bodyWidth; col += A)
				{
					LoadBody(src0 + col, a[0]);
					LoadBody(src2 + col, a[2]);
					SobelDy<abs>(a, dst + col);
				}
				LoadTail(src0 + width - A, a[0]);
				LoadTail(src2 + width - A, a[2]);
				SobelDy<abs>(a, dst + width - A);

				dst += dstStride;
			}
		}

		void SobelDy(const uint8_t * src, size_t srcStride, size_t width, size_t height, uint8_t * dst, size_t dstStride)
		{
			assert(dstStride%sizeof(int16_t) == 0);
			SobelDy<false>(src, srcStride, width, height, (int16_t *)dst, dstStride / sizeof(int16_t));
		}

		void SobelDyAbs(const uint8_t * src, size_t srcStride, size_t width, size_t height, uint8_t * dst, size_t dstStride)
		{
			assert(dstStride%sizeof(int16_t) == 0);
			SobelDy<true>(src, srcStride, width, height, (int16_t *)dst, dstStride / sizeof(int16_t));

		}
		SIMD_INLINE void SobelDyAbsSum(v16u8 a[3][3], v4u32 & sum)
		{
			v8i16 lo = SobelDy<true,LO>(a);
			v8i16 hi = SobelDy<true,HI>(a);
			sum = PadSum(sum,(v8u16)(lo + hi));
		}

	    void SobelDyAbsSum(const uint8_t * src, size_t stride, size_t width, size_t height, uint64_t * sum)
		{
			assert(width > A);

			size_t bodyWidth = Simd::AlignHi(width, A) - A;
			const uint8_t *src0, *src1, *src2;

			v16u8 a[3][3];
			v16u8 K8_FF = Fill((uint8_t)0xff);
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

				LoadNose(src0 + 0, a[0]);
				LoadNose(src2 + 0, a[2]);
				SobelDyAbsSum(a, rowSum);
				for (size_t col = A; col < bodyWidth; col += A)
				{
					LoadBody(src0 + col, a[0]);
					LoadBody(src2 + col, a[2]);
					SobelDyAbsSum(a, rowSum);
				}
				LoadTail(src0 + width - A, a[0]);
				LoadTail(src2 + width - A, a[2]);
				SetMask3x3(a, tailMask);
				SobelDyAbsSum(a, rowSum);

				fullSum = PadSum(fullSum,rowSum);
			}
			*sum = ExtractSum(fullSum);
		}

		template<int sequence> SIMD_INLINE v8i16 ContourMetrics(v16u8 a[3][3])
		{
			v8i16 dx = SobelDx<true,sequence>(a);
			v8i16 dy = SobelDy<true,sequence>(a);
			v8i16 K16_0001;
			Set<1>(K16_0001);
			v8u16 mask = Compare<LT>(dx,dy);
			v8i16 inc = K16_0001 & mask;
			return ((dx + dy) << 1) + inc;
		}

		SIMD_INLINE void ContourMetrics(v16u8 a[3][3], int16_t * dst)
		{
			Store(ContourMetrics<LO>(a),dst);
			Store(ContourMetrics<HI>(a),dst + HA);
		}
		SIMD_INLINE void ContourMetrics(const uint8_t * src, size_t srcStride, size_t width, size_t height, int16_t * dst, size_t dstStride)
		{
			assert(width > A);
			size_t bodyWidth = Simd::AlignHi(width, A) - A;
			const uint8_t *src0, *src1, *src2;
			v16u8 a[3][3];

			for (size_t row = 0; row < height; ++row)
			{
				src0 = src + srcStride*(row - 1);
				src1 = src0 + srcStride;
				src2 = src1 + srcStride;
				if (row == 0)
					src0 = src1;
				if (row == height - 1)
					src2 = src1;

				LoadNose(src0 + 0, a[0]);
				LoadNose(src1 + 0, a[1]);
				LoadNose(src2 + 0, a[2]);
				ContourMetrics(a, dst + 0);
				for (size_t col = A; col < bodyWidth; col += A)
				{
					LoadBody(src0 + col, a[0]);
					LoadBody(src1 + col, a[1]);
					LoadBody(src2 + col, a[2]);
					ContourMetrics(a, dst + col);
				}
				LoadTail(src0 + width - A, a[0]);
				LoadTail(src1 + width - A, a[1]);
				LoadTail(src2 + width - A, a[2]);
				ContourMetrics(a, dst + width - A);

				dst += dstStride;
			}
		}
		void ContourMetrics(const uint8_t * src, size_t srcStride, size_t width, size_t height, uint8_t * dst, size_t dstStride)
		{
			assert(dstStride%sizeof(int16_t) == 0);
			ContourMetrics(src, srcStride, width, height, (int16_t *)dst, dstStride / sizeof(int16_t));
		}
		template<int sequence> SIMD_INLINE v8i16 ContourMetricsMasked(v16u8 a[3][3],v16u8 mask)
		{
			v8u16 _mask = (v8u16)Interleave<sequence>(mask,mask);
			v8i16 dx = SobelDx<true,sequence>(a);
			v8i16 dy = SobelDy<true,sequence>(a);
			v8i16 K16_0001;
			Set<1>(K16_0001);

			v8u16 cmp_mask = Compare<LT>(dx,dy);
			v8i16 inc = K16_0001 & cmp_mask;
			return (((dx + dy) << 1) + inc) & _mask;
		}
		SIMD_INLINE void ContourMetricsMasked(v16u8 a[3][3], const uint8_t * mask, const v16u8 & indexMin, int16_t * dst)
		{
			v16u8 _mask = Compare<LE>(indexMin,Load<3>(mask));
			Store(ContourMetricsMasked<LO>(a,_mask),dst);
			Store(ContourMetricsMasked<HI>(a,_mask),dst + HA);
		}

		SIMD_INLINE void ContourMetricsMasked(const uint8_t * src, size_t srcStride, size_t width, size_t height,
			const uint8_t * mask, size_t maskStride, uint8_t indexMin, int16_t * dst, size_t dstStride)
		{
			assert(width > A);

			size_t bodyWidth = Simd::AlignHi(width, A) - A;
			const uint8_t *src0, *src1, *src2;
			v16u8 _indexMin = Fill((uint8_t)indexMin);
			v16u8 a[3][3];

			for (size_t row = 0; row < height; ++row)
			{
				src0 = src + srcStride*(row - 1);
				src1 = src0 + srcStride;
				src2 = src1 + srcStride;
				if (row == 0)
					src0 = src1;
				if (row == height - 1)
					src2 = src1;

				LoadNose(src0 + 0, a[0]);
				LoadNose(src1 + 0, a[1]);
				LoadNose(src2 + 0, a[2]);
				ContourMetricsMasked(a, mask + 0, _indexMin, dst + 0);
				for (size_t col = A; col < bodyWidth; col += A)
				{
					LoadBody(src0 + col, a[0]);
					LoadBody(src1 + col, a[1]);
					LoadBody(src2 + col, a[2]);
					ContourMetricsMasked(a, mask + col, _indexMin, dst + col);
				}
				LoadTail(src0 + width - A, a[0]);
				LoadTail(src1 + width - A, a[1]);
				LoadTail(src2 + width - A, a[2]);
				ContourMetricsMasked(a, mask + width - A, _indexMin, dst + width - A);

				dst += dstStride;
				mask += maskStride;
			}
		}

		void ContourMetricsMasked(const uint8_t * src, size_t srcStride, size_t width, size_t height,
			const uint8_t * mask, size_t maskStride, uint8_t indexMin, uint8_t * dst, size_t dstStride)
		{
			assert(dstStride%sizeof(int16_t) == 0);
		 	ContourMetricsMasked(src, srcStride, width, height, mask, maskStride, indexMin, (int16_t *)dst, dstStride / sizeof(int16_t));
		}

		SIMD_INLINE v8u16 AnchorComponent(const int16_t * src, size_t step, const v8i16 & value, const v8u16 & mask)
		{
			v8i16 last = (v8u16)Load(src - step) >> 1;
			v8i16 next = (v8u16)Load(src + step) >> 1;

			v8u16 _lastmask = (v8u16)Compare<LE>(last,value);
			v8u16 _nextmask = (v8u16)Compare<LE>(next,value);
			return _lastmask & _nextmask & mask;
		}

		SIMD_INLINE v8u16 Anchor(const int16_t * src, size_t stride, const v8i16 & threshold)
		{
		    v8u16 _src = Load<1>(src);
			v8u16 K16_0001;
			Set<1>(K16_0001);
			v8u16 direction = _src & K16_0001;
			v8u16 dirmask = Compare<EQ>(direction, K16_0001);

			v8i16 magnitude = _src >> 1;
			v8i16 value = magnitude - threshold;
			v8u16 vertical = AnchorComponent(src, 1, value,dirmask);
			v8u16 horizontal = AnchorComponent(src, stride, value, ~dirmask);
			v8u16 alldir = vertical | horizontal;

			v8i16 zero = Zero<v8i16>();
			v8u16 _valuecmp = Compare<LT>(zero,magnitude);
			return _valuecmp & alldir;
		}

		SIMD_INLINE void Anchor(const int16_t * src, size_t stride, const v8i16 & threshold, uint8_t * dst)
		{
			v8u16 lo = Anchor(src, stride, threshold);
			v8u16 hi = Anchor(src + HA, stride, threshold);
			v16u8 pack = Package<EVEN>((v16u8)lo,(v16u8)hi);
			Store(pack,dst);
		}

		SIMD_INLINE void ContourAnchors(const int16_t * src, size_t srcStride, size_t width, size_t height,
			size_t step, int16_t threshold, uint8_t * dst, size_t dstStride)
		{
			assert(width > A);
			size_t bodyWidth = Simd::AlignHi(width, A) - A;
			v8i16 _threshold = Fill(threshold);
			memset(dst, 0, width);
			memset(dst + dstStride*(height - 1), 0, width);
			src += srcStride;
			dst += dstStride;
			for (size_t row = 1; row < height - 1; row += step)
			{
				dst[0] = 0;
				Anchor(src + 1, srcStride, _threshold, dst + 1);
				for (size_t col = A; col < bodyWidth; col += A)
					Anchor(src + col, srcStride, _threshold, dst + col);
				Anchor(src + width - A - 1, srcStride, _threshold, dst + width - A - 1);
				dst[width - 1] = 0;
				src += step*srcStride;
				dst += step*dstStride;
			}
		}

		void ContourAnchors(const uint8_t * src, size_t srcStride, size_t width, size_t height,
			size_t step, int16_t threshold, uint8_t * dst, size_t dstStride)
		{
			assert(srcStride%sizeof(int16_t) == 0);
			ContourAnchors((const int16_t *)src, srcStride / sizeof(int16_t), width, height, step, threshold, dst, dstStride);
		}
    }
#endif// SIMD_MSA_ENABLE
}
