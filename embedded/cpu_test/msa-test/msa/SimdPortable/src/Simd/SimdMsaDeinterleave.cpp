/*
* Simd Library (http://simd.sourceforge.net).
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
		SIMD_INLINE void Deinterleave2(const uint8_t *src,const uint8_t *dst1,const uint8_t *dst2){
			v16u8 _lo = Load<1>(src + 0);
			v16u8 _hi = Load(src + A);
			v16u8 loPack = Package<EVEN>(_lo,_hi);
			v16u8 hiPack = Package<ODD>(_lo,_hi);
			Store(loPack,dst1);
			Store(hiPack,dst2);
		}

        void DeinterleaveUv(const uint8_t * uv, size_t uvStride, size_t width, size_t height,
             uint8_t * u, size_t uStride, uint8_t * v, size_t vStride)
        {
            assert(width >= A);

            size_t bodyWidth = AlignLo(width, A);
            size_t tail = width - bodyWidth;
            for(size_t row = 0; row < height; ++row)
            {
                for(size_t col = 0, offset = 0; col < bodyWidth; col += A, offset += DA)
                {
					Deinterleave2(uv + offset,u + col,v + col);
                }
                if(tail)
                {
                    size_t col = width - A;
                    size_t offset = 2*col;
					Deinterleave2(uv + offset,u + col,v + col);
				}
                uv += uvStride;
                u += uStride;
                v += vStride;
            }
        }
		SIMD_INLINE void Deinterleave3(const uint8_t *src,const uint8_t *dst1,const uint8_t *dst2,const uint8_t *dst3){
			v16u8 _src1 = Load<1>(src + 0);
			v16u8 _src2 = Load(src + A);
			v16u8 _src3 = Load(src + 2 * A);

			const v16u8 shf1_lo = {0,3,6,9, 12,15,18,21,24,27,30,0xff,0xff,0xff,0xff,0xff};//1,4,7,10,13};
			const v16u8 shf2_lo = {1,4,7,10,13,16,19,22,25,28,31,0xff,0xff,0xff,0xff,0xff};//1,4,7,10,13};
			const v16u8 shf3_lo = {2,5,8,11,14,17,20,23,26,29,0xff,0xff,0xff,0xff,0xff,0xff};//1,4,7,10,13};

			const v16u8 shf1_hi = {0,1,2,3,4,5,6,7,8,9,10,17,20,23,26,29};
			const v16u8 shf2_hi = {0,1,2,3,4,5,6,7,8,9,10,18,21,24,27,30};
			const v16u8 shf3_hi = {0,1,2,3,4,5,6,7,8,9,16,19,22,25,28,31};

			v16u8 _dst1 = ShuffleEx(shf1_lo,_src1,_src2);
			v16u8 _dst2 = ShuffleEx(shf2_lo,_src1,_src2);
			v16u8 _dst3 = ShuffleEx(shf3_lo,_src1,_src2);

			_dst1 = ShuffleEx(shf1_hi,_dst1,_src3);
			_dst2 = ShuffleEx(shf2_hi,_dst2,_src3);
			_dst3 = ShuffleEx(shf3_hi,_dst3,_src3);

			Store(_dst1,dst1);
			Store(_dst2,dst2);
			Store(_dst3,dst3);
		}

		void DeinterleaveBgr(const uint8_t * bgr, size_t bgrStride, size_t width, size_t height,
							 uint8_t * b, size_t bStride, uint8_t * g, size_t gStride, uint8_t * r, size_t rStride)
        {
            assert(width >= A);

            size_t bodyWidth = AlignLo(width, A);
            size_t tail = width - bodyWidth;
            size_t A3 = A * 3;
            for (size_t row = 0; row < height; ++row)
            {
                for (size_t col = 0, offset = 0; col < bodyWidth; col += A, offset += A3)
                {
					Deinterleave3(bgr + offset,b + col,g + col,r + col);
                }
                if (tail)
                {
                    size_t col = width - A;
                    size_t offset = 3 * col;
					Deinterleave3(bgr + offset,b + col,g + col,r + col);
                }
                bgr += bgrStride;
                b += bStride;
                g += gStride;
                r += rStride;
            }
        }


		SIMD_INLINE void Deinterleave4(const uint8_t *src,const uint8_t *dst1,const uint8_t *dst2,const uint8_t *dst3,const uint8_t *dst4){
			v16u8 _src1 = Load<1>(src + 0);
			v16u8 _src2 = Load(src + A);
			v16u8 ev_dst1 = Package<EVEN>(_src1,_src2);
			v16u8 od_dst1 = Package<ODD>(_src1,_src2);

			v16u8 _src3 = Load(src + 2 * A);
			v16u8 _src4 = Load(src + 3 * A);
			v16u8 ev_dst2 = Package<EVEN>(_src3,_src4);
			v16u8 od_dst2 = Package<ODD>(_src3,_src4);

			v16u8 _dst1 = Package<EVEN>(ev_dst1,ev_dst2);
			v16u8 _dst3 = Package<ODD>(ev_dst1,ev_dst2);

			v16u8 _dst2 = Package<EVEN>(od_dst1,od_dst2);
			v16u8 _dst4 = Package<ODD>(od_dst1,od_dst2);

			Store(_dst1,dst1);
			Store(_dst2,dst2);
			Store(_dst3,dst3);
			Store(_dst4,dst4);

		}

		void DeinterleaveBgra(const uint8_t * bgra, size_t bgraStride, size_t width, size_t height,
							  uint8_t * b, size_t bStride, uint8_t * g, size_t gStride, uint8_t * r, size_t rStride, uint8_t * a, size_t aStride)
        {
            assert(width >= A);

            size_t bodyWidth = AlignLo(width, A);
            size_t tail = width - bodyWidth;
            for (size_t row = 0; row < height; ++row)
            {
                for (size_t col = 0, offset = 0; col < bodyWidth; col += A, offset += QA)
					Deinterleave4(bgra + offset,b + col,g + col,r + col,a + col);
                if (tail)
                {
                    size_t col = width - A;
                    size_t offset = 4 * col;
					Deinterleave4(bgra + offset,b + col,g + col,r + col,a + col);
                }
                bgra += bgraStride;
                b += bStride;
                g += gStride;
                r += rStride;
                a += aStride;
            }
        }
    }
#endif// SIMD_MSA_ENABLE
}
