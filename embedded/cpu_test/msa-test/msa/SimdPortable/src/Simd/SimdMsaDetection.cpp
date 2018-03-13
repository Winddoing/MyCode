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
#include "Simd/SimdDetection.h"
#include "Simd/SimdMsaType.h"
namespace Simd
{
#ifdef SIMD_MSA_ENABLE
    namespace Msa
	{
        using namespace Simd::Detection;
        SIMD_INLINE void UnpackMask32i(const uint8_t * src, uint32_t * dst, const v16u8 & mask)
        {
			v16u8 _src = Load<1>(src) & mask;
			const v16u8 zero = Zero<v16u8>();
			v16u8 _dst0 = Interleave<LO>(_src,zero);
			v16u8 _dst1 = Interleave<HI>(_src,zero);

			v16u8 _dst00 = Interleave<LO>(_dst0,zero);
			v16u8 _dst01 = Interleave<HI>(_dst0,zero);

			v16u8 _dst02 = Interleave<LO>(_dst1,zero);
			v16u8 _dst03 = Interleave<HI>(_dst1,zero);
			Store(_dst00,(uint8_t *)dst + 0 * A);
			Store(_dst01,(uint8_t *)dst + 1 * A);
			Store(_dst02,(uint8_t *)dst + 2 * A);
			Store(_dst03,(uint8_t *)dst + 3 * A);
        }

        SIMD_INLINE void UnpackMask32i(const uint8_t * src, size_t size, uint32_t * dst, const v16u8 & mask)
        {
            size_t alignedSize = Simd::AlignLo(size, A);
            for (size_t i = 0; i < alignedSize; i += A)
                UnpackMask32i(src + i, dst + i, mask);
            if (size != alignedSize)
                UnpackMask32i(src + size - A, dst + size - A, mask);
        }
        SIMD_INLINE void PackResult32i(const uint32_t * src, uint8_t * dst)
        {
            v16u8 _src00 = Load<1>((uint8_t*)src + 0 * A);
			v16u8 _src01 = Load((uint8_t*)src + 1 * A);
			v16u8 _src02 = Load((uint8_t*)src + 2 * A);
			v16u8 _src03 = Load((uint8_t*)src + 3 * A);

			v16u8 _src0 = Package<EVEN>(_src00,_src01);
			v16u8 _src1 = Package<EVEN>(_src02,_src03);
			v16u8 _src = Package<EVEN>(_src0,_src1);

            Store(_src,(uint8_t*)dst);
        }

        SIMD_INLINE void PackResult32i(const uint32_t * src, size_t size, uint8_t * dst)
        {
            size_t alignedSize = Simd::AlignLo(size, A);
            for (size_t i = 0; i < alignedSize; i += A)
                PackResult32i(src + i, dst + i);
            if (size != alignedSize)
                PackResult32i(src + size - A, dst + size - A);
        }

        SIMD_INLINE v4f32 ValidSqrt(const v4f32 & value)
        {

			v4u32 mask = Compare<GE>(value,Zero<v4f32>());
			v4f32 F32_1_0 = Fill(1.0f);
			v4f32 f = SelectVector(mask,F32_1_0,value);
            return Sqrt(f);
        }

		SIMD_INLINE v4u32 Sum32ip(uint32_t * const ptr[4], size_t offset)
        {
            v4u32 s0 = Load<1>(ptr[0] + offset);
			v4u32 s1 = Load<2>(ptr[1] + offset);
			v4u32 s2 = Load<1>(ptr[2] + offset);
			v4u32 s3 = Load<2>(ptr[3] + offset);
            return ((s0 - s1) - (s2 - s3));
        }

        SIMD_INLINE v4f32 Norm32fp(const HidHaarCascade & hid, size_t offset)
        {
            v4f32 area = Fill(hid.windowArea);
            v4f32 sum = ConvertFP(Sum32ip(hid.p, offset));
            v4f32 sqsum = ConvertFP(Sum32ip(hid.pq, offset));
			v4f32 q = MultiplySub(sqsum * area,sum,sum);
			return ValidSqrt(q);
        }

		SIMD_INLINE v4f32 WeightedSum32f(const WeightedRect & rect, size_t offset)
        {
            v4u32 s0 = Load<1>(rect.p0 + offset);
			v4u32 s1 = Load<2>(rect.p1 + offset);
			v4u32 s2 = Load<1>(rect.p2 + offset);
			v4u32 s3 = Load<2>(rect.p3 + offset);
            v4u32 sum = (s0 - s1) - (s2 - s3);
			v4f32 w = Fill(rect.weight);
			v4f32 sumf = ConvertFP(sum);
            return sumf * w;
        }

        SIMD_INLINE void StageSum32f(const float * leaves, float threshold, const v4f32 & sum, const v4f32 & norm, v4f32 & stageSum)
        {
			v4f32 _threshold = Fill(threshold) * norm;
			v4u32 mask = Compare<GE>(sum,_threshold);

			v4u32 u32_sum = *(v4u32 *)&sum;
			v4u32 u32_threshold = *(v4u32 *)&_threshold;

			v4f32 _leaves0 = Fill(leaves[0]);
			v4f32 _leaves1 = Fill(leaves[1]);
			v4f32 _leaves = SelectVector(mask,_leaves0,_leaves1);
			stageSum += _leaves;
        }

        void Detect32f(const HidHaarCascade & hid, size_t offset, const v4f32 & norm, v4u32 & result)
        {
            typedef HidHaarCascade Hid;
            const float * leaves = hid.leaves.data();
            const Hid::Node * node = hid.nodes.data();
            const Hid::Stage * stages = hid.stages.data();
            for (int i = 0, n = (int)hid.stages.size(); i < n; ++i)
            {
                const Hid::Stage & stage = stages[i];
                if (stage.canSkip)
                    continue;
                const Hid::Node * end = node + stage.ntrees;
                v4f32 stageSum = Zero<v4f32>();
                if (stage.hasThree)
                {
                    for (; node < end; ++node, leaves += 2)
                    {
                        const Hid::Feature & feature = hid.features[node->featureIdx];
						v4f32 sum = WeightedSum32f(feature.rect[0], offset) + WeightedSum32f(feature.rect[1], offset);
                        if (feature.rect[2].p0)
                            sum = sum + WeightedSum32f(feature.rect[2], offset);
                        StageSum32f(leaves, node->threshold, sum, norm, stageSum);
                    }
                }
                else
                {
                    for (; node < end; ++node, leaves += 2)
                    {
                        const Hid::Feature & feature = hid.features[node->featureIdx];
						v4f32 sum = WeightedSum32f(feature.rect[0], offset) + WeightedSum32f(feature.rect[1], offset);
                        StageSum32f(leaves, node->threshold, sum, norm, stageSum);
                    }
                }
				v4f32 _threshold = Fill(stage.threshold);
				v4u32 K32_00000001;
				Set<1>(K32_00000001);
				//optimize.
				result = Compare<LE>(_threshold,stageSum) & result & K32_00000001;

                int resultCount = CountOnes(result);
                if (resultCount == 0)
                {
                    return;
                }
                else if (resultCount == 1)
                {
                    uint32_t *_result = (uint32_t *)&result;
                    float *_norm = (float *)&norm;
                    for (int j = 0; j < 4; ++j)
                    {
                        if (_result[j])
                        {
                            _result[j] = Base::Detect32f(hid, offset + j, i + 1, _norm[j]) > 0 ? 1 : 0;
                            break;
                        }
                    }
                    return;
                }
            }
        }

        void DetectionHaarDetect32fp(const HidHaarCascade & hid, const Image & mask, const Rect & rect, Image & dst)
        {
            size_t width = rect.Width();
            size_t alignedWidth = Simd::AlignLo(width, F);
            size_t evenWidth = Simd::AlignLo(width, 2);

            Buffer<uint32_t> buffer(width);
			v16u8 K8_01;
			Set<1>(K8_01);
            for (ptrdiff_t row = rect.top; row < rect.bottom; row += 1)
            {
                size_t col = 0;
                size_t p_offset = row * hid.sum.stride / sizeof(uint32_t) + rect.left;
                size_t pq_offset = row * hid.sqsum.stride / sizeof(uint32_t) + rect.left;

                UnpackMask32i(mask.data + row*mask.stride + rect.left, width, buffer.m, K8_01);
                memset(buffer.d, 0, width*sizeof(uint32_t));
                for (; col < alignedWidth; col += F)
                {
					v4u32 result = Load<3>(buffer.m + col);
					if (CountOnes(result) == 0)
                        continue;
                    v4f32 norm = Norm32fp(hid, pq_offset + col);
                    Detect32f(hid, p_offset + col, norm, result);
					Store(result,buffer.d + col);
                }
                if (evenWidth > alignedWidth + 2)
                {
                    col = evenWidth - F;
					v4u32 result = Load(buffer.m + col);
                    if (CountOnes(result) != 0)
                    {
                        v4f32 norm = Norm32fp(hid, pq_offset + col);
                        Detect32f(hid, p_offset + col, norm, result);
						Store(result,buffer.d + col);
                    }
                    col += F;
                }
                for (; col < width; col += 1)
                {
                    if (buffer.m[col] == 0)
                        continue;
                    float norm = Base::Norm32f(hid, pq_offset + col);
                    buffer.d[col] = Base::Detect32f(hid, p_offset + col, 0, norm) > 0 ? 1 : 0;
                }
                PackResult32i(buffer.d, width, dst.data + row*dst.stride + rect.left);
            }
        }

        void DetectionHaarDetect32fp(const void * _hid, const uint8_t * mask, size_t maskStride,
									 ptrdiff_t left, ptrdiff_t top, ptrdiff_t right, ptrdiff_t bottom, uint8_t * dst, size_t dstStride)
        {
            const HidHaarCascade & hid = *(HidHaarCascade*)_hid;
            return DetectionHaarDetect32fp(hid,
										   Image(hid.sum.width - 1, hid.sum.height - 1, maskStride, Image::Gray8, (uint8_t*)mask),
										   Rect(left, top, right, bottom),
										   Image(hid.sum.width - 1, hid.sum.height - 1, dstStride, Image::Gray8, dst).Ref());
        }


		SIMD_INLINE void UnpackMask16i(const uint8_t * src, uint16_t * dst, const v16u8 & mask)
        {
			const v16u8 zero = Zero<v16u8>();
			v16u8 _src = Load<1>(src) & mask;
			v16u8 _dst0 = Interleave<LO>(_src,zero);
			v16u8 _dst1 = Interleave<HI>(_src,zero);
            Store(_dst0,(uint8_t*)dst);
			Store(_dst1,(uint8_t*)dst + A);
        }

        SIMD_INLINE void UnpackMask16i(const uint8_t * src, size_t size, uint16_t * dst, const v16u8 & mask)
        {
            size_t alignedSize = Simd::AlignLo(size, A);
            for (size_t i = 0; i < alignedSize; i += A)
                UnpackMask16i(src + i, dst + i, mask);
            if (size != alignedSize)
                UnpackMask16i(src + size - A, dst + size - A, mask);
        }


        SIMD_INLINE void PackResult16i(const uint16_t * src, uint8_t * dst)
        {
			v16u8 _src0 = Load<1>((uint8_t *)src);
			v16u8 _src1 = Load((uint8_t *)src + A);
			v16u8 _dst = Package<EVEN>(_src0,_src1);
            Store(_dst,dst);
        }

        SIMD_INLINE void PackResult16i(const uint16_t * src, size_t size, uint8_t * dst)
        {
            size_t alignedSize = Simd::AlignLo(size, A);
            for (size_t i = 0; i < alignedSize; i += A)
                PackResult16i(src + i, dst + i);
            if (size != alignedSize)
                PackResult16i(src + size - A, dst + size - A);
        }

        SIMD_INLINE v4u32 Sum32ii(uint32_t * const ptr[4], size_t offset)
        {
			v4u32 s00 = Load<1>(ptr[0] + offset);
			v4u32 s01 = Load(ptr[0] + offset + 4);
			v4u32 s10 = Load<2>(ptr[1] + offset);
			v4u32 s11 = Load(ptr[1] + offset + 4);
			v4u32 s20 = Load<1>(ptr[2] + offset);
			v4u32 s21 = Load(ptr[2] + offset + 4);
			v4u32 s30 = Load<2>(ptr[3] + offset);
			v4u32 s31 = Load(ptr[3] + offset + 4);

			v4u32 s0 = Package<EVEN>(s00,s01);
			v4u32 s1 = Package<EVEN>(s10,s11);
			v4u32 s2 = Package<EVEN>(s20,s21);
			v4u32 s3 = Package<EVEN>(s30,s31);
            return (s0 - s1) - (s2 - s3);
        }

        SIMD_INLINE v4f32 Norm32fi(const HidHaarCascade & hid, size_t offset)
        {
            v4f32 area = Fill(hid.windowArea);
            v4f32 sum = ConvertFP(Sum32ii(hid.p, offset));
            v4f32 sqsum = ConvertFP(Sum32ii(hid.pq, offset));
            return ValidSqrt(MultiplySub(sqsum * area,sum,sum));
        }
        void DetectionHaarDetect32fi(const HidHaarCascade & hid, const Image & mask, const Rect & rect, Image & dst)
        {
            const size_t step = 2;
            size_t width = rect.Width();
            size_t alignedWidth = Simd::AlignLo(width, HA);
            size_t evenWidth = Simd::AlignLo(width, 2);
			v8u16 K16_0001;
			Set<1>(K16_0001);

            Buffer<uint16_t> buffer(evenWidth);
            for (ptrdiff_t row = rect.top; row < rect.bottom; row += step)
            {
                size_t col = 0;
                size_t p_offset = row * hid.isum.stride / sizeof(uint32_t) + rect.left / 2;
                size_t pq_offset = row * hid.sqsum.stride / sizeof(uint32_t) + rect.left;

                UnpackMask16i(mask.data + row*mask.stride + rect.left, evenWidth, buffer.m, K16_0001);
                memset(buffer.d, 0, evenWidth*sizeof(uint16_t));
                for (; col < alignedWidth; col += HA)
                {
					v4u32 result = (v4u32)Load<3>(buffer.m + col);
                    if (CountOnes(result) == 0)
                        continue;
                    v4f32 norm = Norm32fi(hid, pq_offset + col);
                    Detect32f(hid, p_offset + col / 2, norm, result);
					Store((v8u16)result,buffer.d + col);
                }
                if (evenWidth > alignedWidth)
                {
                    col = evenWidth - HA;
					v4u32 result = (v4u32)Load(buffer.m + col);
                    if (CountOnes(result) != 0)
                    {
						v4f32 norm = Norm32fi(hid, pq_offset + col);
                        Detect32f(hid, p_offset + col / 2, norm, result);
						Store((v8u16)result,buffer.d + col);
                    }
                    col += HA;
                }
                for (; col < width; col += step)
                {
                    if (mask.At<uint8_t>(col + rect.left, row) == 0)
                        continue;
                    float norm = Base::Norm32f(hid, pq_offset + col);
                    if (Base::Detect32f(hid, p_offset + col / 2, 0, norm) > 0)
                        dst.At<uint8_t>(col + rect.left, row) = 1;
                }
                PackResult16i(buffer.d, evenWidth, dst.data + row*dst.stride + rect.left);
            }
        }

        void DetectionHaarDetect32fi(const void * _hid, const uint8_t * mask, size_t maskStride,
									 ptrdiff_t left, ptrdiff_t top, ptrdiff_t right, ptrdiff_t bottom, uint8_t * dst, size_t dstStride)
        {
            const HidHaarCascade & hid = *(HidHaarCascade*)_hid;
            return DetectionHaarDetect32fi(hid,
										   Image(hid.sum.width - 1, hid.sum.height - 1, maskStride, Image::Gray8, (uint8_t*)mask),
										   Rect(left, top, right, bottom),
										   Image(hid.sum.width - 1, hid.sum.height - 1, dstStride, Image::Gray8, dst).Ref());
        }

        SIMD_INLINE v4u32 IntegralSum32i(const v4u32 & s0, const v4u32 & s1, const v4u32 & s2, const v4u32 & s3)
        {
            return ((s0 - s1) - (s2 - s3));
        }

        template<int i> SIMD_INLINE void Load(v4u32 a[16], const HidLbpFeature<int> & feature, ptrdiff_t offset)
        {
			if(i == 5 || i == 9)
				a[i] = Load<2>((uint32_t*)feature.p[i] + offset);
			else
				a[i] = Load((uint32_t*)feature.p[i] + offset);
        }

		template<int bit>
		SIMD_INLINE v4u32 CalculateShuffle(v4u32 a0,v4u32 a1,v4u32 a2,v4u32 a3,v4u32 central)
		{
			v4u32 b = IntegralSum32i(a0, a1, a2, a3);
			v4u32 _cmp = Compare<GE>(b,central);
			v4u32 setbit;
			Set<bit>(setbit);
			return  _cmp & setbit;
		}

        SIMD_INLINE void Calculate(const HidLbpFeature<int> & feature, ptrdiff_t offset, v4u32 & shuffle, v4u32 & mask)
        {
			v4u32 a[16];
			Load<5>(a, feature, offset);
            Load<6>(a, feature, offset);
            Load<9>(a, feature, offset);
            Load<10>(a, feature, offset);
            v4u32 central = IntegralSum32i(a[5], a[6], a[9], a[10]);

            Load<0>(a, feature, offset);
            Load<1>(a, feature, offset);
            Load<4>(a, feature, offset);

			shuffle = CalculateShuffle<4>(a[0], a[1], a[4], a[5],central);
			Load<2>(a, feature, offset);
			shuffle |= CalculateShuffle<2>(a[1], a[2], a[5], a[6],central);
			Load<3>(a, feature, offset);
            Load<7>(a, feature, offset);
			shuffle |= CalculateShuffle<1>(a[2], a[3], a[6], a[7],central);



			Load<11>(a, feature, offset);
			mask = CalculateShuffle<0x10>(a[6], a[7], a[10], a[11],central);

            Load<14>(a, feature, offset);
            Load<15>(a, feature, offset);
			mask |= CalculateShuffle<8>(a[10], a[11], a[14], a[15],central);

			Load<13>(a, feature, offset);
			mask |= CalculateShuffle<4>(a[9], a[10], a[13], a[14],central);
			Load<12>(a, feature, offset);
            Load<8>(a, feature, offset);
			mask |= CalculateShuffle<2>(a[8], a[9], a[12], a[13],central);
			mask |= CalculateShuffle<1>(a[4], a[5], a[8], a[9],central);
        }

        SIMD_INLINE v4u32 LeafMask(const HidLbpFeature<int> & feature, ptrdiff_t offset, const int * subset)
        {
            v4u32 shuffle, mask;
            Calculate(feature, offset, shuffle, mask);
			mask = SetBit(Zero<v4u32>(),mask);
			v4u32 _subset0 = Load<1>(subset);
			v4u32 _subset1 = Load(subset + A / 4);
			shuffle = Shuffle(shuffle,_subset0,_subset1);
			v4u32 value = shuffle & mask;
            return Compare<LE>(value,Zero<v4u32>());
        }

        void Detect(const HidLbpCascade<float, int> & hid, size_t offset, v4u32 & result)
        {
            typedef HidLbpCascade<float, int> Hid;

            size_t subsetSize = (hid.ncategories + 31) / 32;
            const int * subsets = hid.subsets.data();
            const Hid::Leave * leaves = hid.leaves.data();
            const Hid::Node * nodes = hid.nodes.data();
            const Hid::Stage * stages = hid.stages.data();
            int nodeOffset = 0, leafOffset = 0;
            for (int i_stage = 0, n_stages = (int)hid.stages.size(); i_stage < n_stages; i_stage++)
            {
                const Hid::Stage & stage = stages[i_stage];
				v4f32 sum = Zero<v4f32>();
                for (int i_tree = 0, n_trees = stage.ntrees; i_tree < n_trees; i_tree++)
                {
                    const Hid::Feature & feature = hid.features[nodes[nodeOffset].featureIdx];
                    const int * subset = subsets + nodeOffset*subsetSize;
					v4u32 mask = LeafMask(feature, offset, subset);
					v4f32 _leaves0 = Fill(leaves[leafOffset + 0]);
					v4f32 _leaves1 = Fill(leaves[leafOffset + 1]);
					v4f32 _leaves = SelectVector(mask,_leaves0,_leaves1);
					sum += _leaves;
                    nodeOffset++;
                    leafOffset += 2;
                }
				v4f32 _threshold = Fill(stage.threshold);
				v4u32 K32_00000001;
			    Set<1>(K32_00000001);
				//optimize.
				result &= Compare<LE>(_threshold,sum) & K32_00000001;
                int resultCount = CountOnes(result);
                if (resultCount == 0)
                    return;
                else if (resultCount == 1)
                {
                    uint32_t *_result = (uint32_t*)&result;
                    for (int i = 0; i < 4; ++i)
                    {
                        if (_result[i])
                        {
                            _result[i] = Base::Detect(hid, offset + i, i_stage + 1) > 0 ? 1 : 0;
                            break;
                        }
                    }
                    return;
                }
            }
        }

        void DetectionLbpDetect32fp(const HidLbpCascade<float, int> & hid, const Image & mask, const Rect & rect, Image & dst)
        {
            size_t width = rect.Width();
            size_t alignedWidth = Simd::AlignLo(width, 4);
            size_t evenWidth = Simd::AlignLo(width, 2);

            Buffer<uint32_t> buffer(width);
			v16u8 K8_01;
			Set<1>(K8_01);
            for (ptrdiff_t row = rect.top; row < rect.bottom; row += 1)
            {
                size_t col = 0;
                size_t offset = row * hid.sum.stride / sizeof(uint32_t) + rect.left;

                UnpackMask32i(mask.data + row*mask.stride + rect.left, width, buffer.m, K8_01);
                memset(buffer.d, 0, width*sizeof(uint32_t));
                for (; col < alignedWidth; col += 4)
                {
                    v4u32 result = Load<3>(buffer.m + col);
                    if (CountOnes(result) == 0)
                        continue;
                    Detect(hid, offset + col, result);
					Store(result,buffer.d + col);
                }
                if (evenWidth > alignedWidth + 2)
                {
                    col = evenWidth - 4;
                    v4u32 result = Load(buffer.m + col);
                    if (CountOnes(result) != 0)
                    {
                        Detect(hid, offset + col, result);
						Store(result,buffer.d + col);
                    }
                    col += 4;
                }
                for (; col < width; col += 1)
                {
                    if (buffer.m[col] == 0)
                        continue;
                    buffer.d[col] = Base::Detect(hid, offset + col, 0) > 0 ? 1 : 0;
                }
                PackResult32i(buffer.d, width, dst.data + row*dst.stride + rect.left);
            }
        }

        void DetectionLbpDetect32fp(const void * _hid, const uint8_t * mask, size_t maskStride,
									ptrdiff_t left, ptrdiff_t top, ptrdiff_t right, ptrdiff_t bottom, uint8_t * dst, size_t dstStride)
        {
            const HidLbpCascade<float, int> & hid = *(HidLbpCascade<float, int>*)_hid;
            return DetectionLbpDetect32fp(hid,
										  Image(hid.sum.width - 1, hid.sum.height - 1, maskStride, Image::Gray8, (uint8_t*)mask),
										  Rect(left, top, right, bottom),
										  Image(hid.sum.width - 1, hid.sum.height - 1, dstStride, Image::Gray8, dst).Ref());
        }

        void DetectionLbpDetect32fi(const HidLbpCascade<float, int> & hid, const Image & mask, const Rect & rect, Image & dst)
        {
            const size_t step = 2;
            size_t width = rect.Width();
            size_t alignedWidth = Simd::AlignLo(width, HA);
            size_t evenWidth = Simd::AlignLo(width, 2);
			v8u16 K16_0001;
			Set<1>(K16_0001);
            Buffer<uint16_t> buffer(evenWidth);
            for (ptrdiff_t row = rect.top; row < rect.bottom; row += step)
            {
                size_t col = 0;
                size_t offset = row * hid.isum.stride / sizeof(uint32_t) + rect.left / 2;

                UnpackMask16i(mask.data + row*mask.stride + rect.left, evenWidth, buffer.m, K16_0001);
                memset(buffer.d, 0, evenWidth*sizeof(uint16_t));
                for (; col < alignedWidth; col += HA)
                {
					v4u32 result = Load<3>(buffer.m + col); //????
                    //uint32x4_t result = (uint32x4_t)vld1q_u16(buffer.m + col);
                    if (CountOnes(result) == 0)
                        continue;
                    Detect(hid, offset + col / 2, result);
					Store((v8u16)result,buffer.d + col);
                }
                if (evenWidth > alignedWidth)
                {
                    col = evenWidth - HA;
					v4u32 result = Load(buffer.m + col); //????
                    if (CountOnes(result) != 0)
                    {
                        Detect(hid, offset + col / 2, result);
						Store((v8u16)result,buffer.d + col);
                    }
                    col += HA;
                }
                for (; col < width; col += step)
                {
                    if (mask.At<uint8_t>(col + rect.left, row) == 0)
                        continue;
                    if (Base::Detect(hid, offset + col / 2, 0) > 0)
                        dst.At<uint8_t>(col + rect.left, row) = 1;
                }
                PackResult16i(buffer.d, evenWidth, dst.data + row*dst.stride + rect.left);
            }
        }

        void DetectionLbpDetect32fi(const void * _hid, const uint8_t * mask, size_t maskStride,
									ptrdiff_t left, ptrdiff_t top, ptrdiff_t right, ptrdiff_t bottom, uint8_t * dst, size_t dstStride)
        {
            const HidLbpCascade<float, int> & hid = *(HidLbpCascade<float, int>*)_hid;
            return DetectionLbpDetect32fi(hid,
										  Image(hid.sum.width - 1, hid.sum.height - 1, maskStride, Image::Gray8, (uint8_t*)mask),
										  Rect(left, top, right, bottom),
										  Image(hid.sum.width - 1, hid.sum.height - 1, dstStride, Image::Gray8, dst).Ref());
        }

        SIMD_INLINE v8u16 IntegralSum16i(const v8u16 & s0, const v8u16 & s1, const v8u16 & s2, const v8u16 & s3)
        {
            return (s0 - s1) - (s2 - s3);
        }

        template<int i> SIMD_INLINE void Load(v8u16 a[16], const HidLbpFeature<short> & feature, ptrdiff_t offset)
        {
			if(i == 5 || i == 9)
				a[i] = Load<2>((uint16_t*)feature.p[i] + offset);
			else
				a[i] = Load((uint16_t*)feature.p[i] + offset);
        }

		template<int bit>
		SIMD_INLINE v8u16 CalculateShuffle(v8u16 a0,v8u16 a1,v8u16 a2,v8u16 a3,v8u16 central)
		{
			v8u16 b = IntegralSum16i(a0, a1, a2, a3);
			v8u16 _cmp = Compare<GE>(b,central);
			v8u16 setbit;
			Set<bit>(setbit);
			return  _cmp & setbit;
		}
        SIMD_INLINE void Calculate(const HidLbpFeature<short> & feature, ptrdiff_t offset, v8u16 & shuffle, v8u16 & mask)
        {
            v8u16 a[16];
            Load<5>(a, feature, offset);
            Load<6>(a, feature, offset);
            Load<9>(a, feature, offset);
            Load<10>(a, feature, offset);
            v8u16 central = IntegralSum16i(a[5], a[6], a[9], a[10]);
            Load<0>(a, feature, offset);
            Load<1>(a, feature, offset);
            Load<4>(a, feature, offset);

			shuffle = CalculateShuffle<4>(a[0], a[1], a[4], a[5],central);
			Load<2>(a, feature, offset);
			shuffle |= CalculateShuffle<2>(a[1], a[2], a[5], a[6],central);
			Load<3>(a, feature, offset);
            Load<7>(a, feature, offset);
			shuffle |= CalculateShuffle<1>(a[2], a[3], a[6], a[7],central);

			Load<11>(a, feature, offset);
			mask = CalculateShuffle<0x10>(a[6], a[7], a[10], a[11],central);

            Load<14>(a, feature, offset);
            Load<15>(a, feature, offset);
			mask |= CalculateShuffle<8>(a[10], a[11], a[14], a[15],central);

			Load<13>(a, feature, offset);
			mask |= CalculateShuffle<4>(a[9], a[10], a[13], a[14],central);
			Load<12>(a, feature, offset);
            Load<8>(a, feature, offset);
			mask |= CalculateShuffle<2>(a[8], a[9], a[12], a[13],central);
			mask |= CalculateShuffle<1>(a[4], a[5], a[8], a[9],central);


        }

        SIMD_INLINE v8u16 LeafMask(const HidLbpFeature<short> & feature, ptrdiff_t offset, const int * subset)
        {
            v8u16 shuffle, mask;
            Calculate(feature, offset, shuffle, mask);
			const v8u16 zero = Zero<v8u16>();
			v4u32 shuffle_lo = Interleave<LO>(shuffle,zero);
			v4u32 shuffle_hi = Interleave<HI>(shuffle,zero);

			v4u32 mask_lo = Interleave<LO>(mask,zero);
			v4u32 mask_hi = Interleave<HI>(mask,zero);

			mask_lo = SetBit((v4u32)zero,mask_lo);
			mask_hi = SetBit((v4u32)zero,mask_hi);

			v4u32 _subset0 = Load<1>(subset);
			v4u32 _subset1 = Load(subset + A / 4);

			v4u32 value_lo = Shuffle(shuffle_lo,_subset0,_subset1) & mask_lo;
			v4u32 value_hi = Shuffle(shuffle_hi,_subset0,_subset1) & mask_hi;
			v8u16 value = PadSat(value_lo,value_hi);
            return Compare<LE>(value,zero);
        }

        void Detect(const HidLbpCascade<int, short> & hid, size_t offset, v8u16 & result)
        {
            typedef HidLbpCascade<int, short> Hid;

            size_t subsetSize = (hid.ncategories + 31) / 32;
            const int * subsets = hid.subsets.data();
            const Hid::Leave * leaves = hid.leaves.data();
            const Hid::Node * nodes = hid.nodes.data();
            const Hid::Stage * stages = hid.stages.data();
            int nodeOffset = 0, leafOffset = 0;
            for (int i_stage = 0, n_stages = (int)hid.stages.size(); i_stage < n_stages; i_stage++)
            {
                const Hid::Stage & stage = stages[i_stage];
                v8i16 sum = Zero<v8i16>();
                for (int i_tree = 0, n_trees = stage.ntrees; i_tree < n_trees; i_tree++)
                {
                    const Hid::Feature & feature = hid.features[nodes[nodeOffset].featureIdx];
                    const int * subset = subsets + nodeOffset*subsetSize;
                    v8u16 mask = LeafMask(feature, offset, subset);
					v8i16 _leaves0 = Fill((int16_t)leaves[leafOffset + 0]);
					v8i16 _leaves1 = Fill((int16_t)leaves[leafOffset + 1]);

					v8i16 _leaves = SelectVector(mask,_leaves0,_leaves1);
					sum += _leaves;
                    nodeOffset++;
                    leafOffset += 2;
                }
				v8i16 K16_0001;
				Set<1>(K16_0001);
				v8i16 _threshold = Fill((int16_t)stage.threshold);
				v8u16 cmp = Compare<LE>(_threshold,sum);
				v8u16 r = result;
				result &= cmp & K16_0001;
                int resultCount = CountOnes(result);
                if (resultCount == 0)
                    return;
                else if (resultCount == 1)
                {
                    uint16_t *_result = (uint16_t *)&result;
                    for (int i = 0; i < HA; ++i)
                    {
                        if (_result[i])
                        {
                            _result[i] = Base::Detect(hid, offset + i, i_stage + 1) > 0 ? 1 : 0;
                            break;
                        }
                    }
                    return;
                }
            }
        }

        void DetectionLbpDetect16ip(const HidLbpCascade<int, short> & hid, const Image & mask, const Rect & rect, Image & dst)
        {
            size_t width = rect.Width();
            size_t alignedWidth = Simd::AlignLo(width, HA);
            size_t evenWidth = Simd::AlignLo(width, 2);
            Buffer<uint16_t> buffer(width);
            for (ptrdiff_t row = rect.top; row < rect.bottom; row += 1)
            {
                size_t col = 0;
                size_t offset = row * hid.isum.stride / sizeof(uint16_t) + rect.left;
				v16u8 K8_01;
				Set<1>(K8_01);
                UnpackMask16i(mask.data + row*mask.stride + rect.left, width, buffer.m, K8_01);
                memset(buffer.d, 0, width*sizeof(uint16_t));
                for (; col < alignedWidth; col += HA)
                {
                    v8u16 result = Load<3>(buffer.m + col);
                    if (CountOnes(result) == 0)
                        continue;
                    Detect(hid, offset + col, result);
					Store(result,buffer.d + col);
                }
                if (evenWidth > alignedWidth + 2)
                {
                    col = evenWidth - HA;
                    v8u16 result = Load(buffer.m + col);
                    if (CountOnes(result) != 0)
                    {
                        Detect(hid, offset + col, result);
						Store(result,buffer.d + col);
                    }
                    col += HA;
                }
                for (; col < width; ++col)
                {
                    if (buffer.m[col] == 0)
                        continue;
                    buffer.d[col] = Base::Detect(hid, offset + col, 0) > 0 ? 1 : 0;
                }
                PackResult16i(buffer.d, width, dst.data + row*dst.stride + rect.left);
            }
        }

        void DetectionLbpDetect16ip(const void * _hid, const uint8_t * mask, size_t maskStride,
									ptrdiff_t left, ptrdiff_t top, ptrdiff_t right, ptrdiff_t bottom, uint8_t * dst, size_t dstStride)
        {
            const HidLbpCascade<int, short> & hid = *(HidLbpCascade<int, short>*)_hid;
            return DetectionLbpDetect16ip(hid,
										  Image(hid.sum.width - 1, hid.sum.height - 1, maskStride, Image::Gray8, (uint8_t*)mask),
										  Rect(left, top, right, bottom),
										  Image(hid.sum.width - 1, hid.sum.height - 1, dstStride, Image::Gray8, dst).Ref());
        }



        void DetectionLbpDetect16ii(const HidLbpCascade<int, short> & hid, const Image & mask, const Rect & rect, Image & dst)
        {
            const size_t step = 2;
            size_t width = rect.Width();
            size_t alignedWidth = Simd::AlignLo(width, A);
            size_t evenWidth = Simd::AlignLo(width, 2);

            for (ptrdiff_t row = rect.top; row < rect.bottom; row += step)
            {
                size_t col = 0;
                size_t offset = row * hid.isum.stride / sizeof(uint16_t) + rect.left / 2;
                const uint8_t * m = mask.data + row*mask.stride + rect.left;
				v8u16 K16_0001;
				Set<1>(K16_0001);
                uint8_t * d = dst.data + row*dst.stride + rect.left;
                for (; col < alignedWidth; col += A)
                {
                    v8u16 result = (v8u16)Load(m + col) & K16_0001;
                    if (CountOnes(result) == 0)
                        continue;
                    Detect(hid, offset + col / 2, result);
					Store((v16u8)result,d + col);
				}
                if (evenWidth > alignedWidth + 2)
                {
                    col = evenWidth - A;
					v8u16 result = (v8u16)Load(m + col) & K16_0001;
                    if (CountOnes(result) != 0)
                    {
                        Detect(hid, offset + col / 2, result);
						Store((v16u8)result,d + col);
                    }
                    col += A;
                }
                for (; col < width; col += step)
                {
                    if (mask.At<uint8_t>(col + rect.left, row) == 0)
                        continue;
                    if (Base::Detect(hid, offset + col / 2, 0) > 0)
                        dst.At<uint8_t>(col + rect.left, row) = 1;
                }
            }
        }

        void DetectionLbpDetect16ii(const void * _hid, const uint8_t * mask, size_t maskStride,
									ptrdiff_t left, ptrdiff_t top, ptrdiff_t right, ptrdiff_t bottom, uint8_t * dst, size_t dstStride)
        {
            const HidLbpCascade<int, short> & hid = *(HidLbpCascade<int, short>*)_hid;
            return DetectionLbpDetect16ii(hid,
										  Image(hid.sum.width - 1, hid.sum.height - 1, maskStride, Image::Gray8, (uint8_t*)mask),
										  Rect(left, top, right, bottom),
										  Image(hid.sum.width - 1, hid.sum.height - 1, dstStride, Image::Gray8, dst).Ref());
        }
    }
#endif// SIMD_NEON_ENABLE
}
