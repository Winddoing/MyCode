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
#include "Simd/SimdStore.h"
#include "Simd/SimdMemory.h"
#include "Simd/SimdMsaConversion.h"
namespace Simd
{
#ifdef SIMD_MSA_ENABLE
    namespace Msa
	{
		SIMD_INLINE v16u8 BgrToGray(v16u8 _bgr1,v16u8 _bgr2,v16u8 _bgr3)
		{
			const v16u8 vshf0 = {0,0xff,2,0xff,3,0xff,5,0xff,6,0xff,8,0xff,9,0xff,11,0xff};
			const v16u8 vshf1 = {1,0xff,0xff,0xff,4,0xff,0xff,0xff,7,0xff,0xff,0xff,10,0xff,0xff,0xff};
			v8u16 br1 = ShuffleEx(vshf0,_bgr1,_bgr1);
			v8u16 ga1 = ShuffleEx(vshf1,_bgr1,_bgr1);
			v4u32 gray1 = BgraToGray(br1,ga1);

			const v16u8 vshf3 = {12,0xff,14,0xff,15,0xff,17,0xff,18,0xff,20,0xff,21,0xff, 23,0xff};
			const v16u8 vshf4 = {13,0xff,0xff,0xff,16,0xff,0xff,0xff,19,0xff,0xff,0xff,22,0xff,0xff,0xff};
			v8u16 br2 = ShuffleEx(vshf3,_bgr1,_bgr2);
			v8u16 ga2 = ShuffleEx(vshf4,_bgr1,_bgr2);
			v4u32 gray2 = BgraToGray(br2,ga2);

			const v16u8 vshf5 = {24,0xff,26,0xff,27,0xff,29,0xff,30,0xff,0,0xff,1,0xff, 3,0xff};
			const v16u8 vshf6 = {25,0xff,0xff,0xff,28,0xff,0xff,0xff,31,0xff,0xff,0xff,2,0xff,0xff,0xff};
			v8u16 br3 = ShuffleEx(vshf5,_bgr3,_bgr2);
			v8u16 ga3 = ShuffleEx(vshf6,_bgr3,_bgr2);
			v4u32 gray3 = BgraToGray(br3,ga3);

			const v16u8 vshf7 = {4,0xff,6,0xff,7,0xff,9,0xff,10,0xff,12,0xff,13,0xff, 15,0xff};
			const v16u8 vshf8 = {5,0xff,0xff,0xff,8,0xff,0xff,0xff,11,0xff,0xff,0xff,14,0xff,0xff,0xff};
			v8u16 br4 = ShuffleEx(vshf7,_bgr3,_bgr3);
			v8u16 ga4 = ShuffleEx(vshf8,_bgr3,_bgr3);
			v4u32 gray4 = BgraToGray(br4,ga4);

			v8u16 gray16_lo = PadSat(gray1,gray2);
			v8u16 gray16_hi = PadSat(gray3,gray4);
			return PadSat(gray16_lo,gray16_hi);
		}

		void BgrToGray(const uint8_t * bgr, size_t width, size_t height, size_t bgrStride, uint8_t * gray, size_t grayStride)
        {
            assert(width >= A);
			size_t alignedWidth = AlignLo(width, A);
			for(size_t row = 0; row < height; ++row)
			{
				for(size_t col = 0; col < alignedWidth; col += A)
				{
					v16u8 _bgr1 = Load<1>(bgr + 3 * col + 0 * A);
					v16u8 _bgr2 = Load(bgr + 3 * col + 1 * A);
					v16u8 _bgr3 = Load(bgr + 3 * col + 2 * A);
					v16u8 _gray = BgrToGray(_bgr1,_bgr2,_bgr3);
					Store(_gray ,gray + col);
				}
				if(alignedWidth != width)
				{
					size_t col = width - A;
					v16u8 _bgr1 = Load(bgr + 3 * col + 0 * A);
					v16u8 _bgr2 = Load(bgr + 3 * col + 1 * A);
					v16u8 _bgr3 = Load(bgr + 3 * col + 2 * A);
					v16u8 _gray = BgrToGray(_bgr1,_bgr2,_bgr3);
					Store(_gray ,gray + col);
				}
				bgr += bgrStride;
				gray += grayStride;
			}
        }


    }
#endif// SIMD_NEON_ENABLE
}
