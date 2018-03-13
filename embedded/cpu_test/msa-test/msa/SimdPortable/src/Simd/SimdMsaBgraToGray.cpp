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
		void BgraToGray(const uint8_t * bgra, size_t width, size_t height, size_t bgraStride, uint8_t * gray, size_t grayStride)
        {
            assert(width >= A);
			size_t alignedWidth = AlignLo(width, A);
			for(size_t row = 0; row < height; ++row)
			{
				for(size_t col = 0; col < alignedWidth; col += A)
				{
					v16u8 _bgra1 = Load<1>(bgra + col * 4 + 0 * A);
					v16u8 _bgra2 = Load(bgra + col * 4 + 1 * A);
					v16u8 _bgra3 = Load(bgra + col * 4 + 2 * A);
					v16u8 _bgra4 = Load(bgra + col * 4 + 3 * A);
					v16u8 _gray = BgraToGray(_bgra1,_bgra2,_bgra3,_bgra4);
					Store(_gray,gray + col);
				}
				if(alignedWidth != width)
				{
					size_t col = width - A;
					v16u8 _bgra1 = Load(bgra + col * 4 + 0 * A);
					v16u8 _bgra2 = Load(bgra + col * 4 + 1 * A);
					v16u8 _bgra3 = Load(bgra + col * 4 + 2 * A);
					v16u8 _bgra4 = Load(bgra + col * 4 + 3 * A);
					Store(BgraToGray(_bgra1,_bgra2,_bgra3,_bgra4),gray + col);
				}
				bgra += bgraStride;
				gray += grayStride;
			}
        }
    }
#endif// SIMD_MSA_ENABLE
}
