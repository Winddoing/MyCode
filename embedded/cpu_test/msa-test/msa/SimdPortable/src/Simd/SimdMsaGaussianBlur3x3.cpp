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

#include "Simd/SimdLog.h"
#include "Simd/SimdMsaType.h"
#include "Simd/SimdMsaLoad.h"
namespace Simd
{
#ifdef SIMD_MSA_ENABLE
    namespace Msa
    {
        namespace
        {
            struct Buffer
            {
                Buffer(size_t width)
                {
                    _p = Allocate(sizeof(uint16_t)*3*width);
                    src0 = (uint16_t*)_p;
                    src1 = src0 + width;
                    src2 = src1 + width;
                }

                ~Buffer()
                {
                    Free(_p);
                }

                uint16_t * src0;
                uint16_t * src1;
                uint16_t * src2;
            private:
                void * _p;
            };
        }

		SIMD_INLINE v8u16 BinomialSum16(const v8u16 & a, const v8u16 & b, const v8u16 & c)
		{
			return a + b + b + c;
		}
		template<int32_t op>
		SIMD_INLINE v8u16 UnpackU8(const v16u8 & a)
		{
			v16u8 zero = Zero<v16u8>();
			return Interleave<op>(a,zero);
		}

        SIMD_INLINE void BlurCol(v16u8 a[3], uint16_t * b)
        {

            Store(BinomialSum16(UnpackU8<LO>(a[0]), UnpackU8<LO>(a[1]), UnpackU8<LO>(a[2])),b + 0);
            Store(BinomialSum16(UnpackU8<HI>(a[0]), UnpackU8<HI>(a[1]), UnpackU8<HI>(a[2])),b + HA);
        }

        SIMD_INLINE v8u16 BlurRow16(const Buffer & buffer, size_t offset)
        {
			v8u16 a0 = Load<1>(buffer.src0 + offset);
			v8u16 a1 = Load<2>(buffer.src1 + offset);
			v8u16 a2 = Load<3>(buffer.src2 + offset);
			v8u16 sum = BinomialSum16(a0,a1,a2);
			v8u16 up;
			Set<8>(up);
            return (sum + up) >> 4;
        }

        SIMD_INLINE v16u8 BlurRow(const Buffer & buffer, size_t offset)
        {
			v8u16 lo = BlurRow16(buffer,offset);
			v8u16 hi = BlurRow16(buffer,offset + HA);
			v16u8 p = Package<EVEN>((v16u8)lo,(v16u8)hi);
            return p;
        }

        template <size_t step> void GaussianBlur3x3(
            const uint8_t * src, size_t srcStride, size_t width, size_t height, uint8_t * dst, size_t dstStride)
        {
            assert(step*(width - 1) >= A);

			v16u8 a[3];

            size_t size = step*width;
            size_t bodySize = Simd::AlignHi(size, A) - A;

            Buffer buffer(Simd::AlignHi(size, A));

            LoadNose3<step>(src + 0, a);
            BlurCol(a, buffer.src0 + 0);
            for(size_t col = A; col < bodySize; col += A)
            {
                LoadBody3<step>(src + col, a);
                BlurCol(a, buffer.src0 + col);
            }
            LoadTail3<step>(src + size - A, a);
            BlurCol(a, buffer.src0 + size - A);

            memcpy(buffer.src1, buffer.src0, sizeof(uint16_t)*size);

            for(size_t row = 0; row < height; ++row, dst += dstStride)
            {
                const uint8_t *src2 = src + srcStride*(row + 1);
                if(row >= height - 2)
                    src2 = src + srcStride*(height - 1);

                LoadNose3<step>(src2 + 0, a);
                BlurCol(a, buffer.src2 + 0);
                for(size_t col = A; col < bodySize; col += A)
                {
                    LoadBody3<step>(src2 + col, a);
                    BlurCol(a, buffer.src2 + col);
                }
                LoadTail3<step>(src2 + size - A, a);
                BlurCol(a, buffer.src2 + size - A);

                for(size_t col = 0; col < bodySize; col += A)
                    Store(BlurRow(buffer, col),dst + col);
                Store(BlurRow(buffer, size - A),dst + size - A);

                Swap(buffer.src0, buffer.src2);
                Swap(buffer.src0, buffer.src1);
            }
        }

        void GaussianBlur3x3(const uint8_t * src, size_t srcStride, size_t width, size_t height,
            size_t channelCount, uint8_t * dst, size_t dstStride)
        {
            assert(channelCount > 0 && channelCount <= 4);

            switch(channelCount)
            {
            case 1: GaussianBlur3x3<1>(src, srcStride, width, height, dst, dstStride); break;
            case 2: GaussianBlur3x3<2>(src, srcStride, width, height, dst, dstStride); break;
            case 3: GaussianBlur3x3<3>(src, srcStride, width, height, dst, dstStride); break;
            case 4: GaussianBlur3x3<4>(src, srcStride, width, height, dst, dstStride); break;
            }
        }

    }
#endif// SIMD_MSA_ENABLE
}
