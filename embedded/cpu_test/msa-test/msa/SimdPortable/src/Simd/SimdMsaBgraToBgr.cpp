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
		const size_t A4 = A * 4;
		SIMD_INLINE void BgraToBgr(uint8_t * bgra, uint8_t * bgr)
        {
			v16u8 _bgra0 = Load<1>(bgra + 0);
			v16u8 _bgra1 = Load(bgra + A);
			const v16u8 shuffle1 = {0,1,2,4,5,6,8,9,10,12,13,14,16,17,18,20};
			v16u8 _bgr = ShuffleEx(shuffle1,_bgra0,_bgra1);
			Store(_bgr,bgr + 0);

			_bgra0 = Load(bgra + 2 * A);
			const v16u8 shuffle2 = {21,22,24,25,26,28,29,30,0,1,2,4,5,6,8,9};
			_bgr = ShuffleEx(shuffle2,_bgra0,_bgra1);
			Store(_bgr,bgr + A);

			_bgra1 = Load(bgra + 3 * A);
			const v16u8 shuffle3 = {10,12,13,14, 16,17,18,20,21,22,24,25,26,28,29,30};
			_bgr = ShuffleEx(shuffle3,_bgra0,_bgra1);
			Store(_bgr,bgr + 2 * A);

        }
		void BgraToBgr(const uint8_t * bgra, size_t width, size_t height, size_t bgraStride, uint8_t * bgr, size_t bgrStride)
		{
            assert(width >= A);

            size_t alignedWidth = AlignLo(width, A);

            if(width == alignedWidth)
                alignedWidth -= A;

			for(size_t row = 0; row < height; ++row)
			{
				for (size_t col = 0, colBgra = 0, colBgr = 0; col < alignedWidth; col += A, colBgra += A4, colBgr += A3)
					BgraToBgr((uint8_t*)bgra + colBgra, bgr + colBgr);
                if(width != alignedWidth)
                    BgraToBgr((uint8_t*)bgra + 4*(width - A), bgr + 3*(width - A));
                bgra += bgraStride;
                bgr += bgrStride;
			}
		}
	}
#endif// SIMD_MSA_ENABLE
}
