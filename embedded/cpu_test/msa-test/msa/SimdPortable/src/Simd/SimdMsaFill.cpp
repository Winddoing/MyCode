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
        void FillBgr(uint8_t * dst, size_t stride, size_t width, size_t height, uint8_t blue, uint8_t green, uint8_t red)
        {
            size_t size = width*3;
            size_t step = A*3;
            size_t alignedSize = AlignLo(width, A)*3;

			v16u8 b = Fill(blue);
			v16u8 g = Fill(green);
			v16u8 r = Fill(red);

			v16u8 bg0 = Interleave<LO>(b,g);
			v16u8 bg1 = Interleave<HI>(b,g);

			v16u8 shf = {  0, 1,16,
						   2, 3,17,
						   4, 5,18,
						   6, 7,19,
						   8, 9,20,
						   10};
			v16u8 bgr0 = Shuffle(shf,bg0,r);

			v16u8 shf1 ={     11,21,
						   12,13,22,
						   14,15,23,
						   32,32,24,
						   32,32,25,
						   32,32};
			v16u8 bgr1 = Shuffle(shf1,bg0,r);

			v16u8 shf2 ={        26,
						    6, 7,27,
							8, 9,28,
						   10,11,29,
						   12,13,30,
						   14,15,31};

			v16u8 bgr2 = Shuffle(shf2,bg1,r);

			v16u8 shf3 ={     0, 1,
						   2, 3, 4,
						   5, 6, 7,
						   16,17,10,
						   18,19,13,
						   20,21};
			bgr1 = Shuffle(shf3,bgr1,bg1);

            for(size_t row = 0; row < height; ++row)
            {
                size_t offset = 0;
                for(; offset < alignedSize; offset += step){
                    Store(bgr0,dst + offset);
					Store(bgr1,dst + offset + A);
					Store(bgr2,dst + offset + 2 * A);
				}
                if(offset < size){
					int offset;
					offset = size - step;
					Store(bgr0,dst + offset);
					Store(bgr1,dst + offset + A);
					Store(bgr2,dst + offset + 2 * A);
				}
                dst += stride;
            }
        }

        void FillBgra(uint8_t * dst, size_t stride, size_t width, size_t height, uint8_t blue, uint8_t green, uint8_t red, uint8_t alpha)
        {
            size_t size = width * 4;
            size_t alignedSize = AlignLo(width, A) * 4;

			v16u8 b = Fill(blue);
			v16u8 g = Fill(green);
			v16u8 r = Fill(red);
			v16u8 a = Fill(alpha);

			v8u16 bg0 = Interleave<LO>(b,g);
			v8u16 bg1 = Interleave<HI>(b,g);

			v8u16 ra0 = Interleave<LO>(r,a);
			v8u16 ra1 = Interleave<HI>(r,a);

			v8u16 bgra0 = Interleave<LO>(bg0,ra0);
			v8u16 bgra1 = Interleave<HI>(bg0,ra0);
			v8u16 bgra2 = Interleave<LO>(bg1,ra1);
			v8u16 bgra3 = Interleave<HI>(bg1,ra1);

            for (size_t row = 0; row < height; ++row)
            {
                size_t offset = 0;
                for (; offset < alignedSize; offset += QA){
                    Store((v16u8)bgra0,dst + offset + 0 * A);
					Store((v16u8)bgra1,dst + offset + 1 * A);
					Store((v16u8)bgra2,dst + offset + 2 * A);
					Store((v16u8)bgra3,dst + offset + 3 * A);
				}
                if (offset < size){
					int offset = size - QA;
					Store((v16u8)bgra0,dst + offset + 0 * A);
					Store((v16u8)bgra1,dst + offset + 1 * A);
					Store((v16u8)bgra2,dst + offset + 2 * A);
					Store((v16u8)bgra3,dst + offset + 3 * A);
				}
                dst += stride;
            }
        }
    }
#endif// SIMD_MSA_ENABLE
}
