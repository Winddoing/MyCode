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
		SIMD_INLINE v16u8 AbsGradientSaturatedSum(const uint8_t * src, size_t stride)
		{
			v16u8 _src1 = Load<1>(src + 1);
			v16u8 _src2 = Load(src - 1);

			v16u8 dx = AbsDifference(_src1,_src2);
			v16u8 _src3 = Load<2>(src + stride);
			v16u8 _src4 = Load<3>(src - stride);


			v16u8 dy = AbsDifference(_src3,_src4);
			v8u16 K16_00FF;
			Set<0xff>(K16_00FF);

			v8u16 lo = Min(ExtendAdd<LO>(dx,dy),K16_00FF);
			v8u16 hi = Min(ExtendAdd<HI>(dx,dy),K16_00FF);
			return Package<EVEN>((v16u8)lo,(v16u8)hi);
		}

		void AbsGradientSaturatedSum(const uint8_t * src, size_t srcStride, size_t width, size_t height, uint8_t * dst, size_t dstStride)
		{
			size_t alignedWidth = AlignLo(width, A);
			memset(dst, 0, width);
			src += srcStride;
			dst += dstStride;
			for (size_t row = 2; row < height; ++row)
			{
				for (size_t col = 0; col < alignedWidth; col += A)
					Store(AbsGradientSaturatedSum(src + col, srcStride),dst + col);
				if(width != alignedWidth)
					Store(AbsGradientSaturatedSum(src + width - A, srcStride),dst + width - A);

				dst[0] = 0;
				dst[width - 1] = 0;

				src += srcStride;
				dst += dstStride;
			}
			memset(dst, 0, width);
		}
	}
#endif// SIMD_MSA_ENABLE
}
