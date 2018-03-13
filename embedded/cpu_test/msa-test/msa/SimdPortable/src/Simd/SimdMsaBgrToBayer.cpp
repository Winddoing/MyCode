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
#include "Simd/SimdMemory.h"
#include "Simd/SimdStore.h"
#include "Simd/SimdMsaType.h"
namespace Simd
{
#ifdef SIMD_MSA_ENABLE
    namespace Msa
    {
        template <int c0, int c1>
        SIMD_INLINE void BgrToBayer(const uint8_t * bgr, uint8_t * bayer)
        {
			v16u8 _bgr1 = Load<1>(bgr + 0 * A);
			v16u8 _bgr2 = Load(bgr + 1 * A);

			const v16u8 shf1 = {
				c0 + 0 * 3,c1 + 1 * 3,c0 + 2 * 3,c1 + 3 * 3,
				c0 + 4 * 3,c1 + 5 * 3,c0 + 6 * 3,c1 + 7 * 3,
				c0 + 8 * 3,c1 + 9 * 3,c0 + 10 * 3 > 31 ? 0xff:c0 + 10 * 3,      0xff,
				      0xff,      0xff,      0xff,      0xff
			};
			v16u8 _shf1 = ShuffleEx(shf1,_bgr1,_bgr2);
			v16u8 _bgr3 = Load(bgr + 2 * A);
			const v16u8 shf2 = {
				0,                   1,               2,                3,
				4,                   5,               6,                7,
				8,                   9, c0 + 10 * 3 > 31 ? 16 : 10,  c1 + 11 * 3 - 16,
				c0 + 12 * 3 - 16,c1 + 13 * 3  - 16,c0 + 14 * 3 - 16,c1 + 15 * 3 - 16
			};
			v16u8 _shf2 = ShuffleEx(shf2,_shf1,_bgr3);
            Store(_shf2,bayer);
        }

        template <int c00, int c01, int c10, int c11>
        void BgrToBayer(const uint8_t * bgr, size_t width, size_t height, size_t bgrStride, uint8_t * bayer, size_t bayerStride)
        {
            assert(width >= A);
            size_t alignedWidth = AlignLo(width, A);
            const size_t A3 = A * 3;

            for(size_t row = 0; row < height; row += 2)
            {
                for(size_t col = 0, offset = 0; col < alignedWidth; col += A, offset += A3)
                    BgrToBayer<c00, c01>(bgr + offset, bayer + col);
                if(alignedWidth != width)
                    BgrToBayer<c00, c01>(bgr + 3*(width - A), bayer + width - A);
                bgr += bgrStride;
                bayer += bayerStride;

                for(size_t col = 0, offset = 0; col < alignedWidth; col += A, offset += A3)
                    BgrToBayer<c10, c11>(bgr + offset, bayer + col);
                if(alignedWidth != width)
                    BgrToBayer<c10, c11>(bgr + 3*(width - A), bayer + width - A);
                bgr += bgrStride;
                bayer += bayerStride;
            }
        }

        void BgrToBayer(const uint8_t * bgr, size_t width, size_t height, size_t bgrStride, uint8_t * bayer, size_t bayerStride, SimdPixelFormatType bayerFormat)
        {
            assert((width%2 == 0) && (height%2 == 0));

            switch(bayerFormat)
            {
            case SimdPixelFormatBayerGrbg:
                BgrToBayer<1, 2, 0, 1>(bgr, width, height, bgrStride, bayer, bayerStride);
                break;
            case SimdPixelFormatBayerGbrg:
                BgrToBayer<1, 0, 2, 1>(bgr, width, height, bgrStride, bayer, bayerStride);
                break;
            case SimdPixelFormatBayerRggb:
                BgrToBayer<2, 1, 1, 0>(bgr, width, height, bgrStride, bayer, bayerStride);
                break;
            case SimdPixelFormatBayerBggr:
                BgrToBayer<0, 1, 1, 2>(bgr, width, height, bgrStride, bayer, bayerStride);
                break;
            default:
                assert(0);
            }
        }

	}
#endif// SIMD_MSA_ENABLE
}
