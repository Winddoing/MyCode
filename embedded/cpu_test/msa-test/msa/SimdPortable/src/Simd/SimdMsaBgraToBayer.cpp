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
		/*
		 *  c0 - even pixel position.
		 *  c1 - odd pixel position.
		 */
        template <int c0, int c1>
        SIMD_INLINE void BgraToBayer(const uint8_t * bgra, uint8_t * bayer)
        {
            v16u8 _bgra1 = Load<1>(bgra + 0 * A);
			v16u8 _bgra2 = Load(bgra + 1 * A);

			const v16u8 shf1 = {
				c0 + 0 * 4,c1 + 1 * 4,c0 + 2 * 4,c1 + 3 * 4,
				c0 + 4 * 4,c1 + 5 * 4,c0 + 6 * 4,c1 + 7 * 4,
				0xff,      0xff,      0xff,      0xff,
				0xff,      0xff,      0xff,      0xff
			};
			v16u8 gray_lo = ShuffleEx(shf1,_bgra1,_bgra2);

			v16u8 _bgra3 = Load(bgra + 2 * A);
			v16u8 _bgra4 = Load(bgra + 3 * A);
			const v16u8 shf2 = {
				0xff,      0xff,      0xff,      0xff,
				0xff,      0xff,      0xff,      0xff,
				c0 + 0 * 4,c1 + 1 * 4,c0 + 2 * 4,c1 + 3 * 4,
				c0 + 4 * 4,c1 + 5 * 4,c0 + 6 * 4,c1 + 7 * 4
			};
			v16u8 gray_hi = ShuffleEx(shf2,_bgra3,_bgra4);
			Store(gray_lo | gray_hi,bayer);
        }

        template <int c00, int c01, int c10, int c11>
        void BgraToBayer(const uint8_t * bgra, size_t width, size_t height, size_t bgraStride, uint8_t * bayer, size_t bayerStride)
        {
            assert(width >= A);
            size_t alignedWidth = AlignLo(width, A);

            for(size_t row = 0; row < height; row += 2)
            {
                for(size_t col = 0, offset = 0; col < alignedWidth; col += A, offset += QA)
                    BgraToBayer<c00, c01>(bgra + offset, bayer + col);
                if(alignedWidth != width)
                    BgraToBayer<c00, c01>(bgra + 4*(width - A), bayer + width - A);
                bgra += bgraStride;
                bayer += bayerStride;

                for(size_t col = 0, offset = 0; col < alignedWidth; col += A, offset += QA)
                    BgraToBayer<c10, c11>(bgra + offset, bayer + col);
                if(alignedWidth != width)
                    BgraToBayer<c10, c11>(bgra + 4*(width - A), bayer + width - A);
                bgra += bgraStride;
                bayer += bayerStride;
            }
        }

        void BgraToBayer(const uint8_t * bgra, size_t width, size_t height, size_t bgraStride, uint8_t * bayer, size_t bayerStride, SimdPixelFormatType bayerFormat)
        {
            assert((width%2 == 0) && (height%2 == 0));

            switch(bayerFormat)
            {
            case SimdPixelFormatBayerGrbg:
                BgraToBayer<1, 2, 0, 1>(bgra, width, height, bgraStride, bayer, bayerStride);
                break;
            case SimdPixelFormatBayerGbrg:
                BgraToBayer<1, 0, 2, 1>(bgra, width, height, bgraStride, bayer, bayerStride);
                break;
            case SimdPixelFormatBayerRggb:
                BgraToBayer<2, 1, 1, 0>(bgra, width, height, bgraStride, bayer, bayerStride);
                break;
            case SimdPixelFormatBayerBggr:
                BgraToBayer<0, 1, 1, 2>(bgra, width, height, bgraStride, bayer, bayerStride);
                break;
            default:
                assert(0);
            }
        }
    }
#endif// SIMD_MSA_ENABLE
}
