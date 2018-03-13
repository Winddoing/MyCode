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
#include "Simd/SimdLog.h"
#include "Simd/SimdMsaConversion.h"
namespace Simd
{
#ifdef SIMD_MSA_ENABLE
    namespace Msa
    {
		const size_t A3 = A * 3;
		const size_t A6 = A * 6;

		SIMD_INLINE void BgrToYuv420p(const uint8_t * bgr0, size_t bgrStride, uint8_t * y0, size_t yStride, uint8_t * u, uint8_t * v)
        {
            const uint8_t * bgr1 = bgr0 + bgrStride;
            uint8_t * y1 = y0 + yStride;
			v16u8 _y,_u,_v;

			const v16u8 bShf1 ={0,0xff,3,0xff,6,0xff,9,0xff,12,0xff,15,0xff,18,0xff,21,0xff};
			const v16u8 gShf1 ={1,0xff,4,0xff,7,0xff,10,0xff,13,0xff,16,0xff,19,0xff,22,0xff};
			const v16u8 rShf1 ={2,0xff,5,0xff,8,0xff,11,0xff,14,0xff,17,0xff,20,0xff,23,0xff};

			const v16u8 bShf2 ={24,0xff,27,0xff,30,0xff,1,0xff,4,0xff,7,0xff,10,0xff,13,0xff};
			const v16u8 gShf2 ={25,0xff,28,0xff,31,0xff,2,0xff,5,0xff,8,0xff,11,0xff,14,0xff};
			const v16u8 rShf2 ={26,0xff,29,0xff,0,0xff,3,0xff,6,0xff,9,0xff,12,0xff,15,0xff};

			v16u8 bgr00 = Load<1>(bgr0 + 0 * A);
			v16u8 bgr01 = Load(bgr0 + 1 * A);
			v16u8 bgr02 = Load(bgr0 + 2 * A);

			v8i16 bl00 = (v8i16)ShuffleEx(bShf1,bgr00,bgr01);
			v8i16 bh00 = (v8i16)ShuffleEx(bShf2,bgr02,bgr01);

			v8i16 gl00 = (v8i16)ShuffleEx(gShf1,bgr00,bgr01);
			v8i16 gh00 = (v8i16)ShuffleEx(gShf2,bgr02,bgr01);

			v8i16 rl00 = (v8i16)ShuffleEx(rShf1,bgr00,bgr01);
			v8i16 rh00 = (v8i16)ShuffleEx(rShf2,bgr02,bgr01);

			_y = BgrTo<Y>(bl00,gl00,rl00,bh00,gh00,rh00);
			Store(_y,y0 + 0 * A);

			v16u8 bgr03 = Load(bgr0 + 3 * A);
			v16u8 bgr04 = Load(bgr0 + 4 * A);
			v16u8 bgr05 = Load(bgr0 + 5 * A);

			v8i16 bl01 = (v8i16)ShuffleEx(bShf1,bgr03,bgr04);
			v8i16 bh01 = (v8i16)ShuffleEx(bShf2,bgr05,bgr04);

			v8i16 gl01 = (v8i16)ShuffleEx(gShf1,bgr03,bgr04);
			v8i16 gh01 = (v8i16)ShuffleEx(gShf2,bgr05,bgr04);

			v8i16 rl01 = (v8i16)ShuffleEx(rShf1,bgr03,bgr04);
			v8i16 rh01 = (v8i16)ShuffleEx(rShf2,bgr05,bgr04);

			_y = BgrTo<Y>(bl01,gl01,rl01,bh01,gh01,rh01);
			Store(_y,y0 + 1 * A);

			v16u8 bgr10 = Load<2>(bgr1 + 0 * A);
			v16u8 bgr11 = Load(bgr1 + 1 * A);
			v16u8 bgr12 = Load(bgr1 + 2 * A);

			v8i16 bl10 = (v8i16)ShuffleEx(bShf1,bgr10,bgr11);
			v8i16 bh10 = (v8i16)ShuffleEx(bShf2,bgr12,bgr11);

			v8i16 gl10 = (v8i16)ShuffleEx(gShf1,bgr10,bgr11);
			v8i16 gh10 = (v8i16)ShuffleEx(gShf2,bgr12,bgr11);

			v8i16 rl10 = (v8i16)ShuffleEx(rShf1,bgr10,bgr11);
			v8i16 rh10 = (v8i16)ShuffleEx(rShf2,bgr12,bgr11);

			_y = BgrTo<Y>(bl10,gl10,rl10,bh10,gh10,rh10);
			Store(_y,y1 + 0 * A);

			v16u8 bgr13 = Load(bgr1 + 3 * A);
			v16u8 bgr14 = Load(bgr1 + 4 * A);
			v16u8 bgr15 = Load(bgr1 + 5 * A);

			v8i16 bl11 = (v8i16)ShuffleEx(bShf1,bgr13,bgr14);
			v8i16 bh11 = (v8i16)ShuffleEx(bShf2,bgr15,bgr14);

			v8i16 gl11 = (v8i16)ShuffleEx(gShf1,bgr13,bgr14);
			v8i16 gh11 = (v8i16)ShuffleEx(gShf2,bgr15,bgr14);

			v8i16 rl11 = (v8i16)ShuffleEx(rShf1,bgr13,bgr14);
			v8i16 rh11 = (v8i16)ShuffleEx(rShf2,bgr15,bgr14);

			_y = BgrTo<Y>(bl11,gl11,rl11,bh11,gh11,rh11);
			Store(_y,y1 + 1 * A);

			v8i16 avb0 = AverageSlot(bl00,bl10,bh00,bh10);
			v8i16 avb1 = AverageSlot(bl01,bl11,bh01,bh11);

			v8i16 avg0 = AverageSlot(gl00,gl10,gh00,gh10);
			v8i16 avg1 = AverageSlot(gl01,gl11,gh01,gh11);

			v8i16 avr0 = AverageSlot(rl00,rl10,rh00,rh10);
			v8i16 avr1 = AverageSlot(rl01,rl11,rh01,rh11);

			_u = BgrTo<U>(avb0,avg0,avr0,avb1,avg1,avr1);
			_v = BgrTo<V>(avb0,avg0,avr0,avb1,avg1,avr1);

			Store(_u,u);
			Store(_v,v);
        }

		void BgrToYuv420p(const uint8_t * bgr, size_t width, size_t height, size_t bgrStride, uint8_t * y, size_t yStride,
            uint8_t * u, size_t uStride, uint8_t * v, size_t vStride)
        {
            assert((width%2 == 0) && (height%2 == 0) && (width >= DA) && (height >= 2));
            size_t alignedWidth = AlignLo(width, DA);
            for(size_t row = 0; row < height; row += 2)
            {
                for(size_t colUV = 0, colY = 0, colBgr = 0; colY < alignedWidth; colY += DA, colUV += A, colBgr += A6)
                    BgrToYuv420p(bgr + colBgr, bgrStride, y + colY, yStride, u + colUV, v + colUV);
                if(width != alignedWidth)
                {
                    size_t offset = width - DA;
                    BgrToYuv420p(bgr + offset*3, bgrStride, y + offset, yStride, u + offset/2, v + offset/2);
                }
                y += 2*yStride;
                u += uStride;
                v += vStride;
                bgr += 2*bgrStride;
            }
        }

		SIMD_INLINE void BgrToYuv422p(const uint8_t * bgr, uint8_t * y, uint8_t * u, uint8_t * v)
		{
			v16u8 _y,_u,_v;
			const v16u8 bShf1 ={0,0xff,3,0xff,6,0xff,9,0xff,12,0xff,15,0xff,18,0xff,21,0xff};
			const v16u8 gShf1 ={1,0xff,4,0xff,7,0xff,10,0xff,13,0xff,16,0xff,19,0xff,22,0xff};
			const v16u8 rShf1 ={2,0xff,5,0xff,8,0xff,11,0xff,14,0xff,17,0xff,20,0xff,23,0xff};

			const v16u8 bShf2 ={24,0xff,27,0xff,30,0xff,1,0xff,4,0xff,7,0xff,10,0xff,13,0xff};
			const v16u8 gShf2 ={25,0xff,28,0xff,31,0xff,2,0xff,5,0xff,8,0xff,11,0xff,14,0xff};
			const v16u8 rShf2 ={26,0xff,29,0xff,0,0xff,3,0xff,6,0xff,9,0xff,12,0xff,15,0xff};

			v16u8 bgr00 = Load<1>(bgr + 0 * A);
			v16u8 bgr01 = Load(bgr + 1 * A);
			v16u8 bgr02 = Load(bgr + 2 * A);

			v8i16 bl0 = (v8i16)ShuffleEx(bShf1,bgr00,bgr01);
			v8i16 bh0 = (v8i16)ShuffleEx(bShf2,bgr02,bgr01);

			v8i16 gl0 = (v8i16)ShuffleEx(gShf1,bgr00,bgr01);
			v8i16 gh0 = (v8i16)ShuffleEx(gShf2,bgr02,bgr01);

			v8i16 rl0 = (v8i16)ShuffleEx(rShf1,bgr00,bgr01);
			v8i16 rh0 = (v8i16)ShuffleEx(rShf2,bgr02,bgr01);

			_y = BgrTo<Y>(bl0,gl0,rl0,bh0,gh0,rh0);
			Store(_y,y + 0 * A);

			v16u8 bgr03 = Load(bgr + 3 * A);
			v16u8 bgr04 = Load(bgr + 4 * A);
			v16u8 bgr05 = Load(bgr + 5 * A);

			v8i16 bl1 = (v8i16)ShuffleEx(bShf1,bgr03,bgr04);
			v8i16 bh1 = (v8i16)ShuffleEx(bShf2,bgr05,bgr04);

			v8i16 gl1 = (v8i16)ShuffleEx(gShf1,bgr03,bgr04);
			v8i16 gh1 = (v8i16)ShuffleEx(gShf2,bgr05,bgr04);

			v8i16 rl1 = (v8i16)ShuffleEx(rShf1,bgr03,bgr04);
			v8i16 rh1 = (v8i16)ShuffleEx(rShf2,bgr05,bgr04);

			_y = BgrTo<Y>(bl1,gl1,rl1,bh1,gh1,rh1);
			Store(_y,y + 1 * A);

			v8i16 avb0 = AverageSlot(bl0,bh0);
			v8i16 avb1 = AverageSlot(bl1,bh1);

			v8i16 avg0 = AverageSlot(gl0,gh0);
			v8i16 avg1 = AverageSlot(gl1,gh1);

			v8i16 avr0 = AverageSlot(rl0,rh0);
			v8i16 avr1 = AverageSlot(rl1,rh1);

			_u = BgrTo<U>(avb0,avg0,avr0,avb1,avg1,avr1);
			_v = BgrTo<V>(avb0,avg0,avr0,avb1,avg1,avr1);

			Store(_u,u);
			Store(_v,v);
		}

		void BgrToYuv422p(const uint8_t * bgr, size_t width, size_t height, size_t bgrStride, uint8_t * y, size_t yStride,
			uint8_t * u, size_t uStride, uint8_t * v, size_t vStride)
		{
			assert((width % 2 == 0) && (width >= DA));

			size_t alignedWidth = AlignLo(width, DA);
			for (size_t row = 0; row < height; ++row)
			{
				for (size_t colUV = 0, colY = 0, colBgr = 0; colY < alignedWidth; colY += DA, colUV += A, colBgr += A6)
					BgrToYuv422p(bgr + colBgr, y + colY, u + colUV, v + colUV);
				if (width != alignedWidth)
				{
					size_t offset = width - DA;
					BgrToYuv422p(bgr + offset * 3, y + offset, u + offset / 2, v + offset / 2);
				}
				y += yStride;
				u += uStride;
				v += vStride;
				bgr += bgrStride;
			}
		}

		SIMD_INLINE void BgrToYuv444p(const uint8_t * bgr, uint8_t * y, uint8_t * u, uint8_t * v)
		{
			v16u8 bgr0 = Load<1>(bgr + 0 * A);
			v16u8 bgr1 = Load(bgr + 1 * A);
			v16u8 bgr2 = Load(bgr + 2 * A);

			const v16u8 bShf1 ={0,0xff,3,0xff,6,0xff,9,0xff,12,0xff,15,0xff,18,0xff,21,0xff};
			const v16u8 gShf1 ={1,0xff,4,0xff,7,0xff,10,0xff,13,0xff,16,0xff,19,0xff,22,0xff};
			const v16u8 rShf1 ={2,0xff,5,0xff,8,0xff,11,0xff,14,0xff,17,0xff,20,0xff,23,0xff};

			const v16u8 bShf2 ={24,0xff,27,0xff,30,0xff,1,0xff,4,0xff,7,0xff,10,0xff,13,0xff};
			const v16u8 gShf2 ={25,0xff,28,0xff,31,0xff,2,0xff,5,0xff,8,0xff,11,0xff,14,0xff};
			const v16u8 rShf2 ={26,0xff,29,0xff,0,0xff,3,0xff,6,0xff,9,0xff,12,0xff,15,0xff};

			v8i16 bl0 = (v8i16)ShuffleEx(bShf1,bgr0,bgr1);
			v8i16 bh0 = (v8i16)ShuffleEx(bShf2,bgr2,bgr1);

			v8i16 gl0 = (v8i16)ShuffleEx(gShf1,bgr0,bgr1);
			v8i16 gh0 = (v8i16)ShuffleEx(gShf2,bgr2,bgr1);

			v8i16 rl0 = (v8i16)ShuffleEx(rShf1,bgr0,bgr1);
			v8i16 rh0 = (v8i16)ShuffleEx(rShf2,bgr2,bgr1);

			v16u8 _y = BgrTo<Y>(bl0,gl0,rl0,bh0,gh0,rh0);
			v16u8 _u = BgrTo<U>(bl0,gl0,rl0,bh0,gh0,rh0);
			v16u8 _v = BgrTo<V>(bl0,gl0,rl0,bh0,gh0,rh0);

			Store(_y,y);
			Store(_u,u);
			Store(_v,v);

		}

		void BgrToYuv444p(const uint8_t * bgr, size_t width, size_t height, size_t bgrStride, uint8_t * y, size_t yStride,
			uint8_t * u, size_t uStride, uint8_t * v, size_t vStride)
		{
			assert(width >= A);

			size_t alignedWidth = AlignLo(width, A);
			for (size_t row = 0; row < height; ++row)
			{
				for (size_t col = 0, colBgr = 0; col < alignedWidth; col += A, colBgr += A3)
					BgrToYuv444p(bgr + colBgr, y + col, u + col, v + col);
				if (width != alignedWidth)
				{
					size_t offset = width - A;
					BgrToYuv444p(bgr + offset * 3, y + offset, u + offset, v + offset);
				}
				y += yStride;
				u += uStride;
				v += vStride;
				bgr += bgrStride;
			}
		}
    }
#endif// SIMD_MSA_ENABLE
}
