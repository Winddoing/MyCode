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

		SIMD_INLINE void BgrToBgra(const uint8_t * bgr, uint8_t * bgra, uint8_t alpha)
        {
			v16u8 _alpha = Fill(alpha);
			v16u8 _bgr1 = Load<1>(bgr + 0 * A);
			const v16u8 _shf1 = {  0, 1, 2,16, 3, 4, 5,16,
							 6, 7, 8,16, 9,10,11,16	};

			v16u8 _bgra = ShuffleEx(_shf1,_bgr1,_alpha);
			Store(_bgra,bgra + 0 * A);

			uint8_t *c = (uint8_t *)&_bgr1;
			c[0] = alpha;

			const v16u8 _shf2 = {  12, 13, 14,0, 15, 16, 17,  0,
							 18, 19, 20,0, 21, 22, 23,  0};

			v16u8 _bgr2 = Load(bgr + 1 * A);

			_bgra = ShuffleEx(_shf2,_bgr1,_bgr2);

			Store(_bgra,bgra + 1 * A);

			c = (uint8_t *)&_bgr2;
			c[0] = alpha;
			const v16u8 _shf3 = {  24, 25, 26, 16, 27, 28, 29,  16,
							 30, 31,  0, 16,  1,  2,  3,  16};

			v16u8 _bgr3 = Load(bgr + 2 * A);

			_bgra = ShuffleEx(_shf3,_bgr3,_bgr2);
			Store(_bgra,bgra + 2 * A);

			const v16u8 _shf4 = {  4,  5,   6, 16,   7,   8,   9,  16,
							 10, 11, 12, 16,  13,  14,  15,  16};

			_bgra = ShuffleEx(_shf4,_bgr3,_alpha);
			Store(_bgra,bgra + 3 * A);

        }

		void BgrToBgra(const uint8_t * bgr, size_t width, size_t height, size_t bgrStride, uint8_t * bgra, size_t bgraStride, uint8_t alpha)
		{
			assert(width >= A);
			size_t alignedWidth = AlignLo(width, A);
			for (size_t row = 0; row < height; ++row)
			{
				for (size_t col = 0, colBgra = 0, colBgr = 0; col < alignedWidth; col += A, colBgra += A4, colBgr += A3)
					BgrToBgra(bgr + colBgr, bgra + colBgra, alpha);
				if (width != alignedWidth)
					BgrToBgra(bgr + 3 * (width - A), bgra + 4 * (width - A), alpha);
				bgr += bgrStride;
				bgra += bgraStride;

			}
		}

		SIMD_INLINE void Bgr48pToBgra32(uint8_t * bgra,
										const uint8_t * blue, const uint8_t * green, const uint8_t * red, size_t offset, const uint8_t & alpha)
        {
			v16u8 _blue = Load<1>(blue + offset);
			v16u8 _green = Load<2>(green + offset);
			v16u8 _red = Load<3>(red + offset);
			v16u8 _alpha = Fill(alpha);
			v16u8 _br1 = Interleave<EVEN>(_blue,_red);
			v16u8 _ga1 = Interleave<EVEN>(_green,_alpha);

			v16u8 _bgra = Interleave<LO>(_br1,_ga1);
			Store(_bgra,bgra + 0 * A);

			_bgra = Interleave<HI>(_br1,_ga1);
			Store(_bgra,bgra + 1 * A);

        }

        void Bgr48pToBgra32(const uint8_t * blue, size_t blueStride, size_t width, size_t height,
            const uint8_t * green, size_t greenStride, const uint8_t * red, size_t redStride, uint8_t * bgra, size_t bgraStride, uint8_t alpha)
        {
            assert(width >= A);
            size_t alignedWidth = AlignLo(width, A / 2);
            for (size_t row = 0; row < height; ++row)
            {
                for (size_t srcOffset = 0, dstOffset = 0; srcOffset < alignedWidth * 2; srcOffset += A, dstOffset += DA)
                    Bgr48pToBgra32(bgra + dstOffset, blue, green, red, srcOffset, alpha);
                if (width != alignedWidth)
                    Bgr48pToBgra32(bgra + width * 4 - A * 2, blue, green, red, (width * 2- A), alpha);
                blue += blueStride;
                green += greenStride;
                red += redStride;
                bgra += bgraStride;
            }
        }
	}
#endif// SIMD_MSA_ENABLE
}
