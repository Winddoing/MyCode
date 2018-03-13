/*
* Simd Library (http://simd.sourceforge.net).
*
* Copyright (c) 2011-2017 Yermalayeu Ihar,
*               2014-2015 Antonenka Mikhail.
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
#ifndef __SimdMsaConversion_h__
#define __SimdMsaConversion_h__

#include "Simd/SimdConst.h"
#include "Simd/SimdMsaType.h"
namespace Simd
{
    namespace Msa
    {
		SIMD_INLINE v4u32 BgraToGray(v16u8 bgra)
        {
			const v16u8 zero = Zero<v16u8>();
			v8u16 br = Interleave<EVEN>(bgra,zero);
			v8u16 ga = Interleave<ODD>(bgra,zero);
			const v8u16 br_weight = (v8u16)Fill((uint32_t)((Base::RED_TO_GRAY_WEIGHT << 16) | Base::BLUE_TO_GRAY_WEIGHT));
			const v8u16 ga_weight = (v8u16)Fill((uint32_t)Base::GREEN_TO_GRAY_WEIGHT);

			v4u32 term = Fill((uint32_t)Base::BGR_TO_GRAY_ROUND_TERM);
			term = PadMultiplyAdd(term,br,br_weight);
			term = PadMultiplyAdd(term,ga,ga_weight);
			return term >> Base::BGR_TO_GRAY_AVERAGING_SHIFT;
        }
		SIMD_INLINE v16u8 BgraToGray(v16u8 bgra1,v16u8 bgra2,v16u8 bgra3,v16u8 bgra4)
		{
			v4u32 gray32_left,gray32_right;
			v8u16 gray16_left,gray16_right;
			gray32_left = BgraToGray(bgra1);
			gray32_right = BgraToGray(bgra2);

			gray16_left = PadSat(gray32_left,gray32_right);
			gray32_left = BgraToGray(bgra3);
			gray32_right = BgraToGray(bgra4);
			gray16_right = PadSat(gray32_left,gray32_right);
			return PadSat(gray16_left,gray16_right);
		}
		v4u32 SIMD_INLINE BgraToGray(v8u16 br,v8u16 ga)
		{
			const v8u16 br_w = (v8u16)Fill((uint32_t)((Base::RED_TO_GRAY_WEIGHT << 16) | Base::BLUE_TO_GRAY_WEIGHT));
			const v4u32 term = Fill((uint32_t)Base::BGR_TO_GRAY_ROUND_TERM);
			v4u32 _br = PadMultiplyAdd(term,br,br_w);
			const v8u16 ga_w = (v8u16)Fill((uint32_t)Base::GREEN_TO_GRAY_WEIGHT);
			v4u32 _ra = PadMultiplyAdd(_br,ga,ga_w);
			return _ra >> Base::BGR_TO_GRAY_AVERAGING_SHIFT;
		}
		typedef enum{Y,U,V} ops_mode;
		template<ops_mode op> SIMD_INLINE v16u8 BgrTo(v8i16 bl,v8i16 gl,v8i16 rl,v8i16 bh,v8i16 gh,v8i16 rh)
        {

			v8i16 bw,gw,rw;
			v4i32 term,adjust;
			int shift;

			shift = Base::BGR_TO_YUV_AVERAGING_SHIFT;
			if(op == Y){
				bw = Fill((int16_t)Base::BLUE_TO_Y_WEIGHT);
				gw = Fill((int16_t)Base::GREEN_TO_Y_WEIGHT);
				rw = Fill((int16_t)Base::RED_TO_Y_WEIGHT);
				term = Fill((int32_t)Base::BGR_TO_YUV_ROUND_TERM);
				adjust = Fill((int32_t)Base::Y_ADJUST);
			}
			if(op == U)
			{
				bw = Fill((int16_t)Base::BLUE_TO_U_WEIGHT);
				gw = Fill((int16_t)Base::GREEN_TO_U_WEIGHT);
				rw = Fill((int16_t)Base::RED_TO_U_WEIGHT);
				term = Fill((int32_t)Base::BGR_TO_YUV_ROUND_TERM);
				adjust = Fill((int32_t)Base::UV_ADJUST);
			}
			if(op == V)
			{
				bw = Fill((int16_t)Base::BLUE_TO_V_WEIGHT);
				gw = Fill((int16_t)Base::GREEN_TO_V_WEIGHT);
				rw = Fill((int16_t)Base::RED_TO_V_WEIGHT);
				term = Fill((int32_t)Base::BGR_TO_YUV_ROUND_TERM);
				adjust = Fill((int32_t)Base::UV_ADJUST);
			}
			v4i32 b0 = ExtendMultipy<LO>(bl,bw);
			v4i32 b1 = ExtendMultipy<HI>(bl,bw);
			v4i32 b2 = ExtendMultipy<LO>(bh,bw);
			v4i32 b3 = ExtendMultipy<HI>(bh,bw);

			v4i32 g0 = ExtendMultipy<LO>(gl,gw);
			v4i32 g1 = ExtendMultipy<HI>(gl,gw);
			v4i32 g2 = ExtendMultipy<LO>(gh,gw);
			v4i32 g3 = ExtendMultipy<HI>(gh,gw);

			v4i32 r0 = ExtendMultipy<LO>(rl,rw);
			v4i32 r1 = ExtendMultipy<HI>(rl,rw);
			v4i32 r2 = ExtendMultipy<LO>(rh,rw);
			v4i32 r3 = ExtendMultipy<HI>(rh,rw);

			v4i32 yuv0 = b0 + g0 + r0 + term;
			yuv0 = (yuv0 >> shift) + adjust;

			v4i32 yuv1 = b1 + g1 + r1 + term;
			yuv1 = (yuv1 >> shift) + adjust;

			v4i32 yuv2 = b2 + g2 + r2 + term;
			yuv2 = (yuv2 >> shift) + adjust;

			v4i32 yuv3 = b3 + g3 + r3 + term;
			yuv3 = (yuv3 >> shift) + adjust;

			v8u16 lyuv = (v8u16)PadSat(yuv0,yuv1);
			v8u16 hyuv = (v8u16)PadSat(yuv2,yuv3);
			return PadSat(lyuv,hyuv);
		}
		SIMD_INLINE v8i16 AverageSlot(v8i16 al,v8i16 bl,v8i16 ah,v8i16 bh)
		{
			v8i16 two;
			Set<2>(two);
			v8i16 a = al + bl;
			v8i16 b = ah + bh;
			v8i16 even = Package<EVEN>(a,b);
			v8i16 odd = Package<ODD>(a,b);
			v8i16 total = (even + odd + two) >> 2;
			return total;
		}

		SIMD_INLINE v8i16 AverageSlot(v8i16 al,v8i16 ah)
		{
			v8i16 even = Package<EVEN>(al,ah);
			v8i16 odd = Package<ODD>(al,ah);
			v8i16 total = Average(even,odd);
			return total;
		}
		template <SimdCompareType compareType>
		v16u8  SIMD_INLINE Compare8u(v16u8 src,v16u8 value);
		template <>
		v16u8  SIMD_INLINE Compare8u<SimdCompareEqual>(v16u8 src,v16u8 value)
		{
			return Compare<EQ>(src,value);
		}
		template <>
		v16u8  SIMD_INLINE Compare8u<SimdCompareNotEqual>(v16u8 src,v16u8 value)
		{
			return ~Compare<EQ>(src,value);
		}
		template <>
		v16u8  SIMD_INLINE Compare8u<SimdCompareGreater>(v16u8 src,v16u8 value)
		{
			return Compare<LT>(value,src);
		}
		template <>
		v16u8  SIMD_INLINE Compare8u<SimdCompareGreaterOrEqual>(v16u8 src,v16u8 value)
		{
			return Compare<LE>(value,src);
		}
		template <>
		v16u8  SIMD_INLINE Compare8u<SimdCompareLesser>(v16u8 src,v16u8 value)
		{
			return Compare<LT>(src,value);
		}
		template <>
		v16u8  SIMD_INLINE Compare8u<SimdCompareLesserOrEqual>(v16u8 src,v16u8 value)
		{
			return Compare<LE>(src,value);
		}
		template <SimdCompareType compareType>
		v8i16  SIMD_INLINE Compare16i(v8i16 src,v8i16 value);
		template <>
		v8i16  SIMD_INLINE Compare16i<SimdCompareEqual>(v8i16 src,v8i16 value)
		{
			return Compare<EQ>(src,value);
		}
		template <>
		v8i16  SIMD_INLINE Compare16i<SimdCompareNotEqual>(v8i16 src,v8i16 value)
		{
			return ~Compare<EQ>(src,value);
		}
		template <>
		v8i16  SIMD_INLINE Compare16i<SimdCompareGreater>(v8i16 src,v8i16 value)
		{
			return Compare<LT>(value,src);
		}
		template <>
		v8i16  SIMD_INLINE Compare16i<SimdCompareGreaterOrEqual>(v8i16 src,v8i16 value)
		{
			return Compare<LE>(value,src);
		}
		template <>
		v8i16  SIMD_INLINE Compare16i<SimdCompareLesser>(v8i16 src,v8i16 value)
		{
			return Compare<LT>(src,value);
		}
		template <>
		v8i16  SIMD_INLINE Compare16i<SimdCompareLesserOrEqual>(v8i16 src,v8i16 value)
		{
			return Compare<LE>(src,value);
		}

		template <bool abs> SIMD_INLINE v8i16 ConditionalAbs(v8i16 a);

		template <> SIMD_INLINE v8i16 ConditionalAbs<true>(v8i16 a)
		{
			v8i16 zero = Zero<v8i16>();
			return AbsDifference(a,zero);
		}

		template <> SIMD_INLINE v8i16 ConditionalAbs<false>(v8i16 a)
		{
			return a;
		}
	}
}
#endif//__SimdMsaConversion_h__
