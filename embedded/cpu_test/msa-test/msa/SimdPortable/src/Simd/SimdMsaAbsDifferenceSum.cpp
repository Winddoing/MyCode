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
#include "Simd/SimdExtract.h"
#include "Simd/SimdConst.h"

#include "Simd/SimdMsaType.h"

#include <stdio.h>
namespace Simd
{
#ifdef SIMD_MSA_ENABLE
	namespace Msa
	{
		void AbsDifferenceSum(const uint8_t *a, size_t aStride, const uint8_t *b, size_t bStride, size_t width, size_t height, uint64_t * sum)
		{
			size_t alignedWidth = Simd::AlignLo(width, A);
			size_t blockSize = (A << 8);
			size_t blockCount = (alignedWidth + blockSize - 1)/ blockSize;
			v2u64 _sum = Zero<v2u64>();
			for (size_t row = 0; row < height; ++row)
			{
				v4u32 rowSum = Zero<v4u32>();
				for (size_t block = 0; block < blockCount; ++block)
				{
					v8u16 blockSum = Zero<v8u16>();
					for (size_t col = block*blockSize, end = Simd::Min(col + blockSize, alignedWidth); col < end; col += A)
					{
						v16u8 va = Load<1>(a + col);
						v16u8 vb = Load<2>(b + col);

						blockSum = PadSum(blockSum,AbsDifference(va,vb));
					}
					rowSum =  PadSum(rowSum,blockSum);
				}

				if (alignedWidth != width)
				{
					v16u8 tailMask = Set(width - alignedWidth,0xff);
					v16u8 va,vb;
					va = Load<1>(a + width - A);
					vb = Load<2>(b + width - A);
					v16u8 ad = AbsDifference(va,vb);
					ad = ad & tailMask;
					rowSum =  PadSum(rowSum,PadSum(ad));
				}
				_sum = PadSum(_sum,rowSum);
				a += aStride;
				b += bStride;
			}
			*sum = ExtractSum(_sum);
		}

		void AbsDifferenceSumMasked(const uint8_t *a, size_t aStride, const uint8_t *b, size_t bStride,
			const uint8_t *mask, size_t maskStride, uint8_t index, size_t width, size_t height, uint64_t * sum)
		{
			assert(width >= A);
			size_t alignedWidth = Simd::AlignLo(width, A);
			size_t blockSize = A << 8;
			size_t blockCount = (alignedWidth + blockSize - 1)/ blockSize;

			v2u64 _sum = Zero<v2u64>();
			v16u8 _index = Fill(index);

			for (size_t row = 0; row < height; ++row)
			{
				v4u32 rowSum = Zero<v4u32>();
				for (size_t block = 0; block < blockCount; ++block)
				{
					v8u16 blockSum = Zero<v8u16>();
					for (size_t col = block*blockSize, end = Simd::Min(col + blockSize, alignedWidth); col < end; col += A)
					{
						v16u8 va = Load<1>(a + col);
						v16u8 vb = Load<2>(b + col);
						v16u8 _mask = Load<3>(mask + col);
						_mask = Compare<EQ>(_mask,_index);
						v16u8 ad = AbsDifference(va,vb);
						ad = ad & _mask;
						blockSum = PadSum(blockSum,ad);
					}
					rowSum = PadSum(rowSum,blockSum);
				}

				if (alignedWidth != width)
				{
					v16u8 tailMask = Set(width - alignedWidth,0xff);
					size_t col = width - A;
					v16u8 va = Load<1>(a + col);
					v16u8 vb = Load<2>(b + col);
					v16u8 _mask = Load<3>(mask + col);
					_mask = Compare<EQ>(_mask,_index);
					_mask = _mask & tailMask;
					v16u8 ad = AbsDifference(va,vb);
					ad = _mask & ad;
					rowSum = PadSum(rowSum,PadSum(ad));
				}
				_sum = PadSum(_sum,rowSum);
				a += aStride;
				b += bStride;
				mask += maskStride;
			}
			*sum = ExtractSum(_sum);
		}

		void AbsDifferenceSums3(v16u8 current, const uint8_t * background, v8u16 sums[3])
		{

			v16u8 va = Load<1>(background - 1);
			sums[0] = PadSum(sums[0],AbsDifference(va,current));
			va = Load(background);
			sums[1] = PadSum(sums[1],AbsDifference(va,current));
			va = Load(background + 1);
			sums[2] = PadSum(sums[2],AbsDifference(va,current));
		}

		void AbsDifferenceSums3x3(v16u8 current, const uint8_t * background, size_t stride, v8u16 sums[9])
		{
			AbsDifferenceSums3(current, background - stride, sums + 0);
			AbsDifferenceSums3(current, background, sums + 3);
			AbsDifferenceSums3(current, background + stride, sums + 6);
		}

		void AbsDifferenceSums3Masked(v16u8 current, const uint8_t * background, v16u8 mask, v4u32 sums[3])
		{
			v16u8 va = Load(background - 1);
			va &= mask;
			sums[0] = PadSum(sums[0],PadSum(AbsDifference(va,current)));
			va = Load<1>(background);
			va &= mask;
			sums[1] = PadSum(sums[1],PadSum(AbsDifference(va,current)));
			va = Load(background + 1);
			va &= mask;
			sums[2] = PadSum(sums[2],PadSum(AbsDifference(va,current)));
		}

		void AbsDifferenceSums3x3Masked(v16u8 current, const uint8_t * background, size_t stride, v16u8 mask, v4u32 sums[9])
		{
			AbsDifferenceSums3Masked(current, background - stride, mask, sums + 0);
			AbsDifferenceSums3Masked(current, background, mask, sums + 3);
			AbsDifferenceSums3Masked(current, background + stride, mask, sums + 6);
		}

		void AbsDifferenceSums3x3(const uint8_t * current, size_t currentStride,
			const uint8_t * background, size_t backgroundStride, size_t width, size_t height, uint64_t * sums)
		{
			assert(height > 2 && width >= A + 2);
			width -= 2;
			height -= 2;
			current += 1 + currentStride;
			background += 1 + backgroundStride;

			size_t alignedWidth = Simd::AlignLo(width, A);
			size_t blockSize = A << 8;
			size_t blockCount = (alignedWidth >> 8) + 1;

			v2u64 _sums[9];
			for (size_t i = 0; i < 9; ++i)
				_sums[i] = Zero<v2u64>();

			for (size_t row = 0; row < height; ++row)
			{
				v4u32 rowSums[9];
				for (size_t i = 0; i < 9; ++i)
					rowSums[i] =  Zero<v4u32>();

				for (size_t block = 0; block < blockCount; ++block)
				{
					v8u16 blockSums[9];
					for (size_t i = 0; i < 9; ++i)
						blockSums[i] = Zero<v8u16>();

					for (size_t col = block*blockSize, end = Simd::Min(col + blockSize, alignedWidth); col < end; col += A)
					{
						v16u8 _current = Load<2>(current + col);
						AbsDifferenceSums3x3(_current, background + col, backgroundStride, blockSums);
					}

					for (size_t i = 0; i < 9; ++i)
						rowSums[i] =  PadSum(rowSums[i],blockSums[i]);
				}

				if (alignedWidth != width)
				{
					v16u8 tailMask = Set(width - alignedWidth,0xff);
					v16u8 va = Load<2>(current + width - A);
					v16u8 _current = va & tailMask;
					AbsDifferenceSums3x3Masked(_current, background + width - A, backgroundStride, tailMask, rowSums);
				}

				for (size_t i = 0; i < 9; ++i)
					_sums[i] = PadSum(_sums[i],rowSums[i]);

				current += currentStride;
				background += backgroundStride;
			}

			for (size_t i = 0; i < 9; ++i)
				sums[i] = ExtractSum(_sums[i]);
		}

		void AbsDifferenceSums3Masked(v16u8 current, const uint8_t * background, v16u8 mask, v8u16 sums[3])
		{
			v16u8 va = Load(background - 1);
			va &= mask;
			v16u8 ad = AbsDifference(va,current);
			sums[0] = PadSum(sums[0],ad);

			va = Load<1>(background);
			va &= mask;
			ad = AbsDifference(va,current);
			sums[1] = PadSum(sums[1],ad);

			va = Load(background + 1);
			va &= mask;
			ad = AbsDifference(va,current);
			sums[2] = PadSum(sums[2],ad);
		}

		void AbsDifferenceSums3x3Masked(v16u8 current, const uint8_t * background, size_t stride, v16u8 mask, v8u16 sums[9])
		{

			AbsDifferenceSums3Masked(current, background - stride, mask, sums + 0);
			AbsDifferenceSums3Masked(current, background, mask, sums + 3);
			AbsDifferenceSums3Masked(current, background + stride, mask, sums + 6);
		}

		void AbsDifferenceSums3x3Masked(const uint8_t *current, size_t currentStride, const uint8_t *background, size_t backgroundStride,
			const uint8_t *mask, size_t maskStride, uint8_t index, size_t width, size_t height, uint64_t * sums)
		{
			assert(height > 2 && width >= A + 2);
			width -= 2;
			height -= 2;
			current += 1 + currentStride;
			background += 1 + backgroundStride;
			mask += 1 + maskStride;

			size_t alignedWidth = Simd::AlignLo(width, A);
			size_t blockSize = A << 8;
			size_t blockCount = (alignedWidth >> 8) + 1;

			v16u8 _index = Fill(index);

			v2u64 _sums[9];
			for (size_t i = 0; i < 9; ++i)
				_sums[i] = Zero<v2u64>();

			for (size_t row = 0; row < height; ++row)
			{
				v4u32 rowSums[9];
				for (size_t i = 0; i < 9; ++i)
					rowSums[i] = Zero<v4u32>();

				for (size_t block = 0; block < blockCount; ++block)
				{
					v8u16 blockSums[9];
					for (size_t i = 0; i < 9; ++i)
						blockSums[i] = Zero<v8u16>();
					for (size_t col = block*blockSize, end = Simd::Min(col + blockSize, alignedWidth); col < end; col += A)
					{
						v16u8 _mask = Load<3>(mask + col);
						_mask = Compare<EQ>(_mask,_index);
						v16u8 _current = Load<2>(current + col);
						_current &= _mask;
						AbsDifferenceSums3x3Masked(_current, background + col, backgroundStride, _mask, blockSums);
					}

					for (size_t i = 0; i < 9; ++i)
						rowSums[i] = PadSum(rowSums[i],blockSums[i]);
				}

				if (alignedWidth != width)
				{
					size_t col = width - A;
					v16u8 tailMask = Set(width - alignedWidth,0xff);
					v16u8 _mask = Load<3>(mask + col);
					_mask = tailMask & Compare<EQ>(_mask,_index);
					v16u8 _current = Load<2>(current + col) & _mask ;
					AbsDifferenceSums3x3Masked(_current, background + col, backgroundStride, _mask, rowSums);
				}

				for (size_t i = 0; i < 9; ++i)
					_sums[i] = PadSum(_sums[i],rowSums[i]);

				current += currentStride;
				background += backgroundStride;
				mask += maskStride;
			}

			for (size_t i = 0; i < 9; ++i)
				sums[i] = ExtractSum(_sums[i]);
		}
	}
#endif// SIMD_MSA_ENABLE
}
