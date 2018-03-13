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
#include "Simd/SimdCompare.h"
#include "Simd/SimdStore.h"
#include "Simd/SimdMsaType.h"
namespace Simd
{
#ifdef SIMD_MSA_ENABLE
	namespace Msa
	{
        void LbpEstimate(const uint8_t * src, ptrdiff_t stride, uint8_t * dst)
        {
			v16u8 threshold = Load<1>(src);
			v16u8 K8_01;
			Set<1>(K8_01);
			v16u8 _src01 = Load<2>(src - 1 - stride);
			v16u8 v01 = Compare<GE>(_src01,threshold) & K8_01;
			v16u8 lbp = v01;
			v16u8 _src02 = Load(src - stride);
			v16u8 v02 = Compare<GE>(_src02,threshold) & (K8_01 << 1);
			lbp = lbp | v02;
			v16u8 _src04 = Load(src + 1 - stride);
			v16u8 v04 = Compare<GE>(_src04,threshold) & (K8_01 << 2);
			lbp = lbp | v04;

			v16u8 _src08 = Load(src + 1);
			v16u8 v08 = Compare<GE>(_src08,threshold) & (K8_01 << 3);
			lbp = lbp | v08;

			v16u8 _src10 = Load<3>(src + 1 + stride);
			v16u8 v10 = Compare<GE>(_src10,threshold) & (K8_01 << 4);
			lbp = lbp | v10;


			v16u8 _src20 = Load(src + stride);
			v16u8 v20 = Compare<GE>(_src20,threshold) & (K8_01 << 5);
			lbp = lbp | v20;

			v16u8 _src40 = Load(src - 1 + stride);
			v16u8 v40 = Compare<GE>(_src40,threshold) & (K8_01 << 6);
			lbp = lbp | v40;

			v16u8 _src80 = Load(src - 1);
			v16u8 v80 = Compare<GE>(_src80,threshold) & (K8_01 << 7);
			lbp = lbp | v80;

            Store(lbp,dst);
        }

		void LbpEstimate(const uint8_t * src, size_t srcStride, size_t width, size_t height, uint8_t * dst, size_t dstStride)
		{
			assert(width >= A + 2);
            size_t alignedWidth = AlignLo(width - 2, A) + 1;

            memset(dst, 0, width);
            src += srcStride;
            dst += dstStride;
            for (size_t row = 2; row < height; ++row)
            {
                dst[0] = 0;
                for (size_t col = 1; col < alignedWidth; col += A)
                    LbpEstimate(src + col, srcStride, dst + col);
                if(alignedWidth != width - 1)
                    LbpEstimate(src + width - 1 - A, srcStride, dst + width - 1 - A);
                dst[width - 1] = 0;

                src += srcStride;
                dst += dstStride;
            }
            memset(dst, 0, width);
		}
	}
#endif// SIMD_MSA_ENABLE
}
