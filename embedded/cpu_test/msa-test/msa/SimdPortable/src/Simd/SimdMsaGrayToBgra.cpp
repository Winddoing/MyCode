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
		const size_t A4 = A * 4;
		SIMD_INLINE void GrayToBgra(const uint8_t * gray, uint8_t * bgra)
		{
			v16u8 _gray;
			const v16u8 allFF = Fill((uint8_t)0xff);
			_gray = Load<1>(gray);

			const v16u8 shf = { 0, 0, 0,17, 1, 1, 1,17, 2, 2, 2,17, 3, 3, 3, 17};
			v16u8 _rgba = ShuffleEx(shf,_gray,allFF);
			Store(_rgba,bgra + 0 * A);

			const v16u8 shf1 = {4, 4, 4,17, 5, 5, 5,17, 6, 6, 6,17, 7, 7, 7,17};
			v16u8 _rgba1 = ShuffleEx(shf1,_gray,allFF);
			Store(_rgba1,bgra + 1 * A);


			const v16u8 shf2 = { 8, 8, 8,17, 9, 9, 9,17, 10,10,10,17,11,11,11,17};
			v16u8 _rgba2 = ShuffleEx(shf2,_gray,allFF);
			Store(_rgba2,bgra + 2 * A);

			const v16u8 shf3 = {12,12,12,17,13,13,13,17,14,14,14,17,15,15,15,17};
			v16u8 _rgba3 = ShuffleEx(shf3,_gray,allFF);
			Store(_rgba3,bgra + 3 * A);
        }
		void GrayToBgra(const uint8_t * gray, size_t width, size_t height, size_t grayStride, uint8_t * bgra, size_t bgraStride, uint8_t alpha)
		{
			assert(width >= A);
			size_t alignedWidth = AlignLo(width, A);

			for (size_t row = 0; row < height; ++row)
			{

				for (size_t col = 0, colBgra = 0; col < alignedWidth; col += A, colBgra += A4)
					GrayToBgra(gray + col, bgra + colBgra);

				if (width != alignedWidth)
					GrayToBgra(gray + width - A, bgra + 4 * (width - A));
				gray += grayStride;
				bgra += bgraStride;
			}
		}
	}
#endif// SIMD_NEON_ENABLE
}
