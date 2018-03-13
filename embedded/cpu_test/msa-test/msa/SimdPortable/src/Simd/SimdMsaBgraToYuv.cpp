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
#include "Simd/SimdConversion.h"

#include "Simd/SimdLog.h"
#include "Simd/SimdMsaType.h"
#include "Simd/SimdMsaConversion.h"

namespace Simd
{
#ifdef SIMD_MSA_ENABLE
    namespace Msa
    {
		SIMD_INLINE void SplitToRgb(v16u8& bgra2b,v16u8& bgra2g,v16u8& bgra2r,v16u8 bgra)
		{
			v16u8 br0 = Package<EVEN>(bgra2b,bgra2g);
			v16u8 ga0 = Package<ODD>(bgra2b,bgra2g);
			v16u8 br1 = Package<EVEN>(bgra2r,bgra);
			v16u8 ga1 = Package<ODD>(bgra2r,bgra);
			bgra2b = Package<EVEN>(br0,br1);
			bgra2r = Package<ODD>(br0,br1);
			bgra2g = Package<EVEN>(ga0,ga1);
		}

		SIMD_INLINE void BgraToYuv420p(const uint8_t * bgra0, size_t bgraStride, uint8_t * y0, size_t yStride, uint8_t * u, uint8_t * v)
        {
			const uint8_t * bgra1 = bgra0 + bgraStride;
			uint8_t * y1 = y0 + yStride;
			v16u8 _y;
			v16u8 bgra00 = Load<1>(bgra0 + 0 * A);
			v16u8 bgra01 = Load(bgra0 + 1 * A);
			v16u8 bgra02 = Load(bgra0 + 2 * A);
			v16u8 bgra03 = Load(bgra0 + 3 * A);
			SplitToRgb(bgra00,bgra01,bgra02,bgra03);

			const v16u8 zero = Zero<v16u8>();
			v8u16 bl0 = Interleave<LO>(bgra00,zero);
			v8u16 bh0 = Interleave<HI>(bgra00,zero);
			v8u16 gl0 = Interleave<LO>(bgra01,zero);
			v8u16 gh0 = Interleave<HI>(bgra01,zero);
			v8u16 rl0 = Interleave<LO>(bgra02,zero);
			v8u16 rh0 = Interleave<HI>(bgra02,zero);

			_y = BgrTo<Y>(bl0,gl0,rl0,bh0,gh0,rh0);
			Store(_y,y0 + A * 0);

			v16u8 bgra04 = Load(bgra0 + 4 * A);
			v16u8 bgra05 = Load(bgra0 + 5 * A);
			v16u8 bgra06 = Load(bgra0 + 6 * A);
			v16u8 bgra07 = Load(bgra0 + 7 * A);
			SplitToRgb(bgra04,bgra05,bgra06,bgra07);
			v8u16 bl1 = Interleave<LO>(bgra04,zero);
			v8u16 bh1 = Interleave<HI>(bgra04,zero);
			v8u16 gl1 = Interleave<LO>(bgra05,zero);
			v8u16 gh1 = Interleave<HI>(bgra05,zero);
			v8u16 rl1 = Interleave<LO>(bgra06,zero);
			v8u16 rh1 = Interleave<HI>(bgra06,zero);

			_y = BgrTo<Y>(bl1,gl1,rl1,bh1,gh1,rh1);
			Store(_y,y0 + A * 1);

			v16u8 bgra10 = Load<2>(bgra1 + 0 * A);
			v16u8 bgra11 = Load(bgra1 + 1 * A);
			v16u8 bgra12 = Load(bgra1 + 2 * A);
			v16u8 bgra13 = Load(bgra1 + 3 * A);
			SplitToRgb(bgra10,bgra11,bgra12,bgra13);
			v8u16 bl2 = Interleave<LO>(bgra10,zero);
			v8u16 bh2 = Interleave<HI>(bgra10,zero);
			v8u16 gl2 = Interleave<LO>(bgra11,zero);
			v8u16 gh2 = Interleave<HI>(bgra11,zero);
			v8u16 rl2 = Interleave<LO>(bgra12,zero);
			v8u16 rh2 = Interleave<HI>(bgra12,zero);

			_y = BgrTo<Y>(bl2,gl2,rl2,bh2,gh2,rh2);
			Store(_y,y1 + A * 0);

			v16u8 bgra14 = Load(bgra1 + 4 * A);
			v16u8 bgra15 = Load(bgra1 + 5 * A);
			v16u8 bgra16 = Load(bgra1 + 6 * A);
			v16u8 bgra17 = Load(bgra1 + 7 * A);
			SplitToRgb(bgra14,bgra15,bgra16,bgra17);

			v8u16 bl3 = Interleave<LO>(bgra14,zero);
			v8u16 bh3 = Interleave<HI>(bgra14,zero);
			v8u16 gl3 = Interleave<LO>(bgra15,zero);
			v8u16 gh3 = Interleave<HI>(bgra15,zero);
			v8u16 rl3 = Interleave<LO>(bgra16,zero);
			v8u16 rh3 = Interleave<HI>(bgra16,zero);

			_y = BgrTo<Y>(bl3,gl3,rl3,bh3,gh3,rh3);
			Store(_y,y1 + A * 1);

			v8u16 avb0 = AverageSlot(bl0,bl2,bh0,bh2);
			v8u16 avb1 = AverageSlot(bl1,bl3,bh1,bh3);

			v8u16 avg0 = AverageSlot(gl0,gl2,gh0,gh2);
			v8u16 avg1 = AverageSlot(gl1,gl3,gh1,gh3);

			v8u16 avr0 = AverageSlot(rl0,rl2,rh0,rh2);
			v8u16 avr1 = AverageSlot(rl1,rl3,rh1,rh3);

			v16u8 _u = BgrTo<U>(avb0,avg0,avr0,avb1,avg1,avr1);
			v16u8 _v = BgrTo<V>(avb0,avg0,avr0,avb1,avg1,avr1);

			Store(_u,u);
			Store(_v,v);
        }

        void BgraToYuv420p(const uint8_t * bgra, size_t width, size_t height, size_t bgraStride, uint8_t * y, size_t yStride,
            uint8_t * u, size_t uStride, uint8_t * v, size_t vStride)
        {
            assert((width%2 == 0) && (height%2 == 0) && (width >= DA) && (height >= 2));
            size_t alignedWidth = AlignLo(width, DA);
            const size_t A8 = A*8;
            for(size_t row = 0; row < height; row += 2)
            {
                for(size_t colUV = 0, colY = 0, colBgra = 0; colY < alignedWidth; colY += DA, colUV += A, colBgra += A8)
                    BgraToYuv420p(bgra + colBgra, bgraStride, y + colY, yStride, u + colUV, v + colUV);
                if(width != alignedWidth)
                {
                    size_t offset = width - DA;
                    BgraToYuv420p(bgra + offset*4, bgraStride, y + offset, yStride, u + offset/2, v + offset/2);
                }
                y += 2*yStride;
                u += uStride;
                v += vStride;
                bgra += 2*bgraStride;
            }
        }

		SIMD_INLINE void BgraToYuv422p(const uint8_t * bgra, uint8_t * y, uint8_t * u, uint8_t * v)
		{

			v16u8 _y;
			v16u8 bgra0 = Load<1>(bgra + 0 * A);
			v16u8 bgra1 = Load(bgra + 1 * A);
			v16u8 bgra2 = Load(bgra + 2 * A);
			v16u8 bgra3 = Load(bgra + 3 * A);
			SplitToRgb(bgra0,bgra1,bgra2,bgra3);

			const v16u8 zero = Zero<v16u8>();
			v8u16 bl0 = Interleave<LO>(bgra0,zero);
			v8u16 bh0 = Interleave<HI>(bgra0,zero);
			v8u16 gl0 = Interleave<LO>(bgra1,zero);
			v8u16 gh0 = Interleave<HI>(bgra1,zero);
			v8u16 rl0 = Interleave<LO>(bgra2,zero);
			v8u16 rh0 = Interleave<HI>(bgra2,zero);

			_y = BgrTo<Y>(bl0,gl0,rl0,bh0,gh0,rh0);
			Store(_y,y + A * 0);
			v16u8 bgra4 = Load(bgra + 4 * A);
			v16u8 bgra5 = Load(bgra + 5 * A);
			v16u8 bgra6 = Load(bgra + 6 * A);
			v16u8 bgra7 = Load(bgra + 7 * A);
			SplitToRgb(bgra4,bgra5,bgra6,bgra7);
			v8u16 bl1 = Interleave<LO>(bgra4,zero);
			v8u16 bh1 = Interleave<HI>(bgra4,zero);
			v8u16 gl1 = Interleave<LO>(bgra5,zero);
			v8u16 gh1 = Interleave<HI>(bgra5,zero);
			v8u16 rl1 = Interleave<LO>(bgra6,zero);
			v8u16 rh1 = Interleave<HI>(bgra6,zero);

			_y = BgrTo<Y>(bl1,gl1,rl1,bh1,gh1,rh1);
			Store(_y,y + A * 1);


			v8u16 avb0 = AverageSlot(bl0,bh0);
			v8u16 avb1 = AverageSlot(bl1,bh1);

			v8u16 avg0 = AverageSlot(gl0,gh0);
			v8u16 avg1 = AverageSlot(gl1,gh1);

			v8u16 avr0 = AverageSlot(rl0,rh0);
			v8u16 avr1 = AverageSlot(rl1,rh1);


			v16u8 _u = BgrTo<U>(avb0,avg0,avr0,avb1,avg1,avr1);
			v16u8 _v = BgrTo<V>(avb0,avg0,avr0,avb1,avg1,avr1);

			Store(_u,u);
			Store(_v,v);
		}

		void BgraToYuv422p(const uint8_t * bgra, size_t width, size_t height, size_t bgraStride, uint8_t * y, size_t yStride,
			uint8_t * u, size_t uStride, uint8_t * v, size_t vStride)
		{
			assert((width % 2 == 0) && (width >= DA));
			size_t alignedWidth = AlignLo(width, DA);
			const size_t A8 = A * 8;
			for (size_t row = 0; row < height; ++row)
			{
				for (size_t colUV = 0, colY = 0, colBgra = 0; colY < alignedWidth; colY += DA, colUV += A, colBgra += A8)
					BgraToYuv422p(bgra + colBgra, y + colY, u + colUV, v + colUV);
				if (width != alignedWidth)
				{
					size_t offset = width - DA;
					BgraToYuv422p(bgra + offset * 4, y + offset, u + offset / 2, v + offset / 2);
				}
				y += yStride;
				u += uStride;
				v += vStride;
				bgra += bgraStride;
			}
		}


		SIMD_INLINE void BgraToYuv444p(const uint8_t * bgra, uint8_t * y, uint8_t * u, uint8_t * v)
		{
			v16u8 bgra0 = Load<1>(bgra + 0 * A);
			v16u8 bgra1 = Load(bgra + 1 * A);
			v16u8 bgra2 = Load(bgra + 2 * A);
			v16u8 bgra3 = Load(bgra + 3 * A);
			SplitToRgb(bgra0,bgra1,bgra2,bgra3);

			const v16u8 zero = Zero<v16u8>();
			v8u16 bl0 = Interleave<LO>(bgra0,zero);
			v8u16 bh0 = Interleave<HI>(bgra0,zero);
			v8u16 gl0 = Interleave<LO>(bgra1,zero);
			v8u16 gh0 = Interleave<HI>(bgra1,zero);
			v8u16 rl0 = Interleave<LO>(bgra2,zero);
			v8u16 rh0 = Interleave<HI>(bgra2,zero);

			v16u8 _y = BgrTo<Y>(bl0,gl0,rl0,bh0,gh0,rh0);
			v16u8 _u = BgrTo<U>(bl0,gl0,rl0,bh0,gh0,rh0);
			v16u8 _v = BgrTo<V>(bl0,gl0,rl0,bh0,gh0,rh0);

			Store(_y,y);
			Store(_u,u);
			Store(_v,v);

		}


		void BgraToYuv444p(const uint8_t * bgra, size_t width, size_t height, size_t bgraStride, uint8_t * y, size_t yStride,
			uint8_t * u, size_t uStride, uint8_t * v, size_t vStride)
		{
			assert(width >= A);
			size_t alignedWidth = AlignLo(width, A);
			for (size_t row = 0; row < height; ++row)
			{
				for (size_t col = 0, colBgra = 0; col < alignedWidth; col += A, colBgra += QA)
					BgraToYuv444p(bgra + colBgra, y + col, u + col, v + col);
				if (width != alignedWidth)
				{
					size_t offset = width - A;
					BgraToYuv444p(bgra + offset * 4, y + offset, u + offset, v + offset);
				}
				y += yStride;
				u += uStride;
				v += vStride;
				bgra += bgraStride;
			}
		}
    }
#endif// SIMD_MSA_ENABLE
}
