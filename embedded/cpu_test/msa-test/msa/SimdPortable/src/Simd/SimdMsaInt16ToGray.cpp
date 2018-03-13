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
#include "Simd/SimdMsaType.h"
namespace Simd
{
#ifdef SIMD_MSA_ENABLE
    namespace Msa
    {
        SIMD_INLINE void Int16ToGray(const uint8_t * src, uint8_t * dst)
        {
			v8i16 _src1 = Load<1>((int16_t*)src);
			v8i16 _src2 = Load((int16_t*)(src + A));
			const v8i16 _FF = Fill((int16_t)255);
			const v8i16 zero = Zero<v8i16>();
			_src1 = Min(_src1,_FF);
			_src1 = Max(_src1,zero);
			_src2 = Min(_src2,_FF);
			_src2 = Max(_src2,zero);
			v16u8 _dst = PadSat((v8u16)_src1,(v8u16)_src2);
			Store(_dst,dst);
        }

		void Int16ToGray(const uint8_t * src, size_t width, size_t height, size_t srcStride, uint8_t * dst, size_t dstStride)
        {
            assert(width >= A);
            size_t alignedWidth = AlignLo(width, A);
            for (size_t row = 0; row < height; ++row)
            {
                for (size_t col = 0; col < alignedWidth; col += A)
                    Int16ToGray(src + col * sizeof(uint16_t), dst + col);

                if (alignedWidth != width)
                    Int16ToGray(src + (width - A) * sizeof(uint16_t), dst + width - A);

                src += srcStride;
                dst += dstStride;
            }
        }
    }
#endif// SIMD_MSA_ENABLE
}
