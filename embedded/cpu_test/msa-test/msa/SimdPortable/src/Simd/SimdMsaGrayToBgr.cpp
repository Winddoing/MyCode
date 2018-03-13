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
#include "Simd/SimdMsaType.h"
namespace Simd
{
#ifdef SIMD_MSA_ENABLE
	namespace Msa
	{
		const size_t A3 = A * 3;
		SIMD_INLINE void GrayToBgr(const uint8_t * gray, uint8_t * bgr)
		{
			v16u8 _gray;
			_gray = Load<1>(gray);
			const v16u8 shf = { 0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5};
			v16u8 _rgb = ShuffleEx(shf,_gray,_gray);
			Store(_rgb,bgr + 0 * A);

			const v16u8 shf1 = { 5, 5, 6, 6, 6, 7, 7, 7, 8, 8, 8, 9, 9, 9,10,10};
			v16u8 _rgb1 = ShuffleEx(shf1,_gray,_gray);
			Store(_rgb1,bgr + 1 * A);

			const v16u8 shf2 = {10,11,11,11,12,12,12,13,13,13,14,14,14,15,15,15};
			v16u8 _rgb2 = ShuffleEx(shf2,_gray,_gray);
			Store(_rgb2,bgr + 2 * A);
        }

		void GrayToBgr(const uint8_t * gray, size_t width, size_t height, size_t grayStride, uint8_t * bgr, size_t bgrStride)
		{
			assert(width >= A);
			size_t alignedWidth = AlignLo(width, A);

			for (size_t row = 0; row < height; ++row)
			{
				for (size_t col = 0, colBgr = 0; col < alignedWidth; col += A, colBgr += A3)
					GrayToBgr(gray + col, bgr + colBgr);
				if (width != alignedWidth)
					GrayToBgr(gray + width - A, bgr + 3 * (width - A));
				gray += grayStride;
				bgr += bgrStride;
			}
		}
	}
#endif// SIMD_MSA_ENABLE
}
