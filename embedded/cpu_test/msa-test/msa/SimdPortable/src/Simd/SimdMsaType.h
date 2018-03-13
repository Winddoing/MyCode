#ifndef SIMDMSATYPE_H
#define SIMDMSATYPE_H

#include <stdint.h>
#include <stdio.h>
#include <msa.h>
#ifndef SIMD_INLINE
#define SIMD_INLINE inline __attribute__ ( (always_inline) )
#endif
namespace Simd
{
#define SIMD_MSA_PREFECH_SIZE 128
#ifdef SIMD_MSA_ENABLE
	namespace Msa{

#include "Simd/SimdMsaImmN16-15.h"
#include "Simd/SimdMsaImmN512-511.h"
#include "Simd/SimdMsaMacro.h"

		const int32_t LO = 0;
		const int32_t HI = 1;

		const int32_t ONES = 2;
		const int32_t LEADONES = 3;
		const int32_t LEADZERO = 4;

		const int32_t LEFT = 5;
		const int32_t RIGHT = 6;

		const int32_t ODD = 0x10;
		const int32_t EVEN = 0x20;


// don't reorder.
		const int32_t EQ = 0x100;
		const int32_t NE = 0x200;
		const int32_t LE = 0x300;
		const int32_t GT = 0x400;
		const int32_t LT = 0x500;
		const int32_t GE = 0x600;

		const int32_t ORDEREQ = 0x101;
		const int32_t ORDERNE = 0x201;
		const int32_t ORDERLE = 0x301;
		const int32_t ORDERGT = 0x401;
		const int32_t ORDERLT = 0x501;
		const int32_t ORDERGE = 0x601;

		const int32_t UNORDEREQ = 0x102;
		const int32_t UNORDERNE = 0x202;
		const int32_t UNORDERLE = 0x302;
		const int32_t UNORDERGT = 0x402;
		const int32_t UNORDERLT = 0x502;
		const int32_t UNORDERGE = 0x602;

		const int32_t NANEQ = 0x103;
		const int32_t NANNE = 0x104;

		template<typename T>
		void SIMD_INLINE dumpdata(T value,const char *info=NULL){
			unsigned char *p = (unsigned char *)&value;
			if(info)
				printf("%s",info);
			else
				printf("\n");
			for(int i = 0;i < sizeof(T);i++){
				printf("%02x ",p[i]);
			}
			printf("\n");
		}
		void SIMD_INLINE dumpdataValue(v4f32 value,const char *info=NULL){
			float *p = (float *)&value;
			if(info)
				printf("%s",info);
			else
				printf("\n");

			for(int i = 0;i < 4;i++){
				printf("%f ",p[i]);
			}
			printf("\n");
		}


		template<typename T> T SIMD_INLINE Zero();
#define	TEMPLATE_ZERO_ARG0(T,CODE)				\
		template<>								\
		T SIMD_INLINE Zero(){					\
			return (T)__builtin_msa_##CODE(0);	\
		}

		MACRO_S_FUNC_ARGS0(TEMPLATE_ZERO_ARG0,ldi);
		MACRO_U_FUNC_ARGS0(TEMPLATE_ZERO_ARG0,ldi);
		MACRO_F_FUNC_ARGS0(TEMPLATE_ZERO_ARG0,ldi);

#define SETICODE(T,CODE)						\
		template<int32_t imm>					\
		T SIMD_INLINE Set(T& a){				\
			a = __builtin_msa_##CODE(imm);		\
			return a;							\
		}

		MACRO_S_FUNC_ARGS0(SETICODE,ldi);
		MACRO_U_FUNC_ARGS0(SETICODE,ldi);

		v16u8  SIMD_INLINE Set(int byteoffset,int v)
		{
			v16u8 value = __builtin_msa_fill_b(v);
			const v16u8 zero = (v16u8)__builtin_msa_ldi_b(0);
			return (v16u8) __builtin_msa_sld_b(value,zero,byteoffset);
		}


#define FILL_FUNCTION(otype,itype,codetype)				\
		otype SIMD_INLINE Fill(itype a) {				\
			return (otype)__builtin_msa_##codetype(a);	\
	    }

		MACRO_S_FUNC_ARGS1(FILL_FUNCTION,fill);
		MACRO_U_FUNC_ARGS1(FILL_FUNCTION,fill);

		v4f32 SIMD_INLINE Fill(float a) {
			uint32_t a32 = *(uint32_t *) &a;
			v4u32 v = Fill(a32);
			return *(v4f32 *)&v;
	    }
		v2f64 SIMD_INLINE Fill(double a) {
			uint64_t a32 = *(uint64_t *) &a;
			v2u64 v = Fill(a32);
			return *(v2f64 *)&v;
	    }


#define LOAD_FUNCTION(otype,itype,codetype)						\
		otype SIMD_INLINE Load(const itype *a) {				\
			return (otype)__builtin_msa_##codetype((void*)a,0);	\
	    }														\

		MACRO_S_FUNC_ARGS1(LOAD_FUNCTION,ld);
		MACRO_U_FUNC_ARGS1(LOAD_FUNCTION,ld);
		MACRO_F_FUNC_ARGS1(LOAD_FUNCTION,ld);

#define LOAD_TEMPLATE(otype,itype,codetype)								\
		template<int way>												\
 		otype SIMD_INLINE Load(const itype *a) {						\
 			if(way > 0)													\
 				__builtin_prefetch((uint8_t*)a + SIMD_MSA_PREFECH_SIZE + 32 * (way - 1),0);	\
 			return (otype)__builtin_msa_##codetype((void*)a,0);			\
 		}


		MACRO_S_FUNC_ARGS1(LOAD_TEMPLATE,ld);
		MACRO_U_FUNC_ARGS1(LOAD_TEMPLATE,ld);
		MACRO_F_FUNC_ARGS1(LOAD_TEMPLATE,ld);


#define STORE_FUNCTION(itype1,itype2,codetype)				\
		void SIMD_INLINE Store(itype1 a,const itype2* b) {	\
			__builtin_msa_##codetype(a,(void*)b,0);			\
	    }													\

#define STORE_FUNCTION2(itype1,itype2,codetype)				\
		void SIMD_INLINE Store(itype1 a,const itype2* b) {	\
			__builtin_msa_##codetype(a,(void*)b,0);			\
	    }													\

		MACRO_S_FUNC_ARGS1(STORE_FUNCTION,st);
		MACRO_U_FUNC_ARGS1(STORE_FUNCTION,st);

		void SIMD_INLINE Store(v4f32 a,const float* b) {
			v4i32 c = *(v4i32 *)&a;
			__builtin_msa_st_w(c,(void*)b,0);
		}
		void SIMD_INLINE Store(v2f64 a,const float* b) {
			v2i64 c = *(v2i64 *)&a;
			__builtin_msa_st_w(c,(void*)b,0);
		}


#define CODE_PADSUM(O,I,code)											\
		O SIMD_INLINE PadSum(I value) {									\
			O zero = Zero<O>();											\
			I one;														\
			Set<1>(one);												\
			return __builtin_msa_dpadd_##code(zero,one,value);			\
		}																\
		O SIMD_INLINE PadSum(O sum,I value) {							\
			I one;														\
			Set<1>(one);												\
			return __builtin_msa_dpadd_##code(sum,one,value);			\
		}

		CODE_PADSUM(v8u16,v16u8,u_h);
		CODE_PADSUM(v4u32,v8u16,u_w);
		CODE_PADSUM(v2u64,v4u32,u_d);

		CODE_PADSUM(v8i16,v16i8,s_h);
		CODE_PADSUM(v4i32,v8i16,s_w);
		CODE_PADSUM(v2i64,v4i32,s_d);

		v4u32 SIMD_INLINE PadMutiSum(v16u8 a,v16u8 b){
			v8u16 lo = __builtin_msa_mulur_h(a,b);
			v8u16 hi = __builtin_msa_mulul_h(a,b);
			return __builtin_msa_hadd_u_w(lo,hi) + __builtin_msa_hadd_u_w(hi,lo);
		}
		v2u64 SIMD_INLINE PadMutiSum(v8u16 a,v8u16 b){
			v4u32 lo = __builtin_msa_mulur_w(a,b);
			v4u32 hi = __builtin_msa_mulul_w(a,b);
			return __builtin_msa_hadd_u_d(lo,hi) + __builtin_msa_hadd_u_d(hi,lo);
		}

		uint32_t SIMD_INLINE ExtractSum(v4u32 value)
		{
			uint32_t *sum = (uint32_t *)&value;
			return sum[0] + sum[1] + sum[2] + sum[3];
		}
		uint64_t SIMD_INLINE ExtractSum(v2u64 value)
		{
			uint64_t *sum = (uint64_t *)&value;
			return sum[0] + sum[1];
		}
		float SIMD_INLINE ExtractSum(v4f32 value)
		{
			float *sum;
			sum = (float*)&value;
			return sum[0] + sum[1] + sum[2] + sum[3];
		}

#define SHIFTICODE(T,CODE)												\
		template<uint32_t shiftcount,int32_t op> T Shift(T operand, T complement){ \
				if(op == LEFT){											\
					return __builtin_msa_##CODE(complement,operand,shiftcount);	\
				}														\
			return __builtin_msa_##CODE(operand,complement,16 - shiftcount); \
		}

		MACRO_S_FUNC_ARGS0(SHIFTICODE,sldi);
		MACRO_U_FUNC_ARGS0(SHIFTICODE,sldi);

#define SHIFTCODE(T,CODE)												\
		template<int32_t op> T Shift(T operand, T complement,uint32_t shiftcount){ \
			assert(shiftcount < 16);									\
			if(op == LEFT){												\
				return __builtin_msa_##CODE(complement,operand,shiftcount);	\
			}															\
			return __builtin_msa_##CODE(operand,complement,16 - shiftcount); \
		}
		MACRO_S_FUNC_ARGS0(SHIFTCODE,sld);
		MACRO_U_FUNC_ARGS0(SHIFTCODE,sld);


		v16u8 SIMD_INLINE ShiftLeft(v16u8 value,size_t shift)
		{
			v16u8 zero = (v16u8)__builtin_msa_ldi_b(0);
			if(shift == 0)
				return value;
			return __builtin_msa_sld_b(value,zero,16 - shift);
		}

		v16u8 SIMD_INLINE ShiftRight(v16u8 value,size_t shift)
		{
			v16u8 zero = (v16u8)__builtin_msa_ldi_b(0);
			return __builtin_msa_sld_b(zero,value,shift);
		}





		TYPE2_S_FUNC_ARG1(CompareI);
		TYPE2_U_FUNC_ARG1(CompareI);

/*
 *   Defined CompareI function.
 *   CompareI: immediate number compare.
 *   Form:
 *      template <int op,int imm> v16i8 SIMD_INLINE CompareI(v16i8 a);
 *   eg:
 *     v16i8 a = Zero<v16i8>();
 *     v16i8 b = CompareI<EQ,1>(a);
 */

		TYPE_IMM_N16_15_FUNC(TEMPLATE2_SI_C_FUNC_ARG1,CompareI,EQ,ceqi);
		TYPE_IMM_N16_15_FUNC(TEMPLATE2_SI_C_FUNC_ARG1,CompareI,LE,clei_s);
		TYPE_IMM_N16_15_FUNC(TEMPLATE2_SI_C_FUNC_ARG1,CompareI,LT,clti_s);

		TYPE_IMM_N16_15_FUNC(TEMPLATE2_UI_C_FUNC_ARG1,CompareI,EQ,ceqi);
		TYPE_IMM_N16_15_FUNC(TEMPLATE2_UI_C_FUNC_ARG1,CompareI,LE,clei_u);
		TYPE_IMM_N16_15_FUNC(TEMPLATE2_UI_C_FUNC_ARG1,CompareI,LT,clti_u);

/*
 *   Defined Compare function.
 *   Compare Type:
 *           v16i8,v8i16,v4i32,v2i64,v16u8,v8u16,v4u32,v2u64
 *           v4f32,v2f64
 *
 *   Normal OP:
 *           EQ,NE,LT,LE,GT,GE
 *
 *   Quiet Compare:
 *               Order,Unorder,NAN
 *               only for float type.
 *   Order OP:
 *           ORDEREQ,ORDERNE,ORDERLT,ORDERLE,ORDERGT,ORDERGE
 *           two arguments a b.
 *           Order: if all of a and b is nan, return zero, else compare it.
 *
 *   Unorder OP:
 *           UNORDEREQ,UNORDERNE,UNORDERLT,UNORDERLE,UNORDERGT,UNORDERGE
 *           two arguments a b.
 *           Unorder: if one of a or b is nan, return ff, else compare it.
 *
 *   NAN OP:
 *           NANEQ,NANNE.
 *           NANEQ two arguments a b. if a and b isn't nan, return zero, else ff.
 *           NANNE two arguments a b. if a and b isn't nan, return ff, else zero.
 *   Form:
 *      template <int op> v16i8 SIMD_INLINE Compare(v16i8 a,v16i8 b);
 *   eg:
 *     v16i8 a = Zero<v16i8>();
 *     v16i8 b = CompareI<EQ,1>(a);
 */


		TYPE_S_FUNC_ARG2(Compare);
		TYPE_U_FUNC_ARG2(Compare);
		TYPE_FC_FUNC_ARG2(Compare);


		TEMPLATE_SI_A_FUNC_ARG2(Compare,EQ,ceq);
		TEMPLATE_UI_A_FUNC_ARG2(Compare,EQ,ceq);

		TEMPLATE_SI_A_FUNC_ARG2(Compare,LE,cle_s);
		TEMPLATE_SI_A_FUNC_ARG2(Compare,LT,clt_s);

		TEMPLATE_SI_B_FUNC_ARG2(Compare,GT,clt_s);
		TEMPLATE_SI_B_FUNC_ARG2(Compare,GE,cle_s);

		TEMPLATE_UI_A_FUNC_ARG2(Compare,LE,cle_u);
		TEMPLATE_UI_A_FUNC_ARG2(Compare,LT,clt_u);

		TEMPLATE_UI_B_FUNC_ARG2(Compare,GT,clt_u);
		TEMPLATE_UI_B_FUNC_ARG2(Compare,GE,cle_u);

		TEMPLATE_FC_A_FUNC_ARG2(Compare,EQ,fseq);
		TEMPLATE_FC_A_FUNC_ARG2(Compare,NE,fsne);
		TEMPLATE_FC_A_FUNC_ARG2(Compare,LE,fsle);
		TEMPLATE_FC_B_FUNC_ARG2(Compare,GE,fsle);

		TEMPLATE_FC_A_FUNC_ARG2(Compare,LT,fslt);
		TEMPLATE_FC_B_FUNC_ARG2(Compare,GT,fslt);

		TEMPLATE_FC_A_FUNC_ARG2(Compare,ORDEREQ,fceq);
		TEMPLATE_FC_A_FUNC_ARG2(Compare,ORDERNE,fcne);
		TEMPLATE_FC_A_FUNC_ARG2(Compare,ORDERLE,fcle);
		TEMPLATE_FC_B_FUNC_ARG2(Compare,ORDERGT,fclt);
		TEMPLATE_FC_A_FUNC_ARG2(Compare,ORDERLT,fclt);
		TEMPLATE_FC_B_FUNC_ARG2(Compare,ORDERGE,fcle);

		TEMPLATE_FC_A_FUNC_ARG2(Compare,UNORDEREQ,fcueq);
		TEMPLATE_FC_A_FUNC_ARG2(Compare,UNORDERNE,fcune);
		TEMPLATE_FC_A_FUNC_ARG2(Compare,UNORDERLE,fcule);
		TEMPLATE_FC_B_FUNC_ARG2(Compare,UNORDERGT,fcult);
		TEMPLATE_FC_A_FUNC_ARG2(Compare,UNORDERLT,fcult);
		TEMPLATE_FC_B_FUNC_ARG2(Compare,UNORDERGE,fcule);

		TEMPLATE_FC_A_FUNC_ARG2(Compare,NANEQ,fcun);
		TEMPLATE_FC_A_FUNC_ARG2(Compare,NANNE,fcor);

/*
 * v16i8 AbsDifference(v16i8 a,v16i8 b)
 */
		IMPLEMENT_S_FUNC_ARG2(AbsDifference,asub_s);
		IMPLEMENT_U_FUNC_ARG2(AbsDifference,asub_u);

/*
 * v16i8 Max(v16i8 a,v16i8 b)
 */

		IMPLEMENT_S_FUNC_ARG2(Max,max_s);
		IMPLEMENT_U_FUNC_ARG2(Max,max_u);
		IMPLEMENT_F_FUNC_ARG2(Max,fmax_a)
/*
 * v16i8 Min(v16i8 a,v16i8 b)
 */
		IMPLEMENT_S_FUNC_ARG2(Min,min_s);
		IMPLEMENT_U_FUNC_ARG2(Min,min_u);
		IMPLEMENT_F_FUNC_ARG2(Min,fmin_a)

/*
 * SubSat Saturate Subtracting
 * v16i8 SubSat(v16i8 a,v16i8 b)
 */

		IMPLEMENT_S_FUNC_ARG2(SubSat,subs_s);
		IMPLEMENT_U_FUNC_ARG2(SubSat,subs_u);
		IMPLEMENT_SU_FUNC_ARG2(SubSatEx,subsuu_s);

/*
 * template<int32_t op> v8i16 ExtendMultipy(v16i8 a,v16i8 b)
 */

		TYPE_ES_FUNC_ARG2(ExtendMultipy);
		TYPE_EU_FUNC_ARG2(ExtendMultipy);

		TEMPLATE_ES_A_FUNC_ARG2(ExtendMultipy,LO,mulsr);
		TEMPLATE_ES_A_FUNC_ARG2(ExtendMultipy,HI,mulsl);

		TEMPLATE_EU_A_FUNC_ARG2(ExtendMultipy,LO,mulur);
		TEMPLATE_EU_A_FUNC_ARG2(ExtendMultipy,HI,mulul);


/*
 * template<int32_t op> v8i16 ExtendAdd(v16i8 a,v16i8 b)
 */

		TYPE_ES_FUNC_ARG2(ExtendAdd);
		TYPE_EU_FUNC_ARG2(ExtendAdd);

		TEMPLATE_ES_A_FUNC_ARG2(ExtendAdd,LO,addsr);
		TEMPLATE_ES_A_FUNC_ARG2(ExtendAdd,HI,addsl);

		TEMPLATE_EU_A_FUNC_ARG2(ExtendAdd,LO,addur);
		TEMPLATE_EU_A_FUNC_ARG2(ExtendAdd,HI,addul);


/*
 * template<int32_t op> v8i16 Sum(v8i16 a,v16i8 b)
 */

		TYPE_S_FUNC_ARG2_E(ExtendSum);
		TYPE_U_FUNC_ARG2_E(ExtendSum);
		TEMPLATE_S_A_FUNC_ARG2_E(ExtendSum,LO,accsr);
		TEMPLATE_S_A_FUNC_ARG2_E(ExtendSum,HI,accsl);
		TEMPLATE_U_A_FUNC_ARG2_E(ExtendSum,LO,accur);
		TEMPLATE_U_A_FUNC_ARG2_E(ExtendSum,HI,accul);

/*
 * template<int32_t op> v8i16 ExtendAdd(v16i8 minuend,v16i8 subtrahend)
 * template<int32_t op> v8i16 ExtendAdd(v16u8 minuend,v16u8 subtrahend)
 */

		TYPE_ES_FUNC_ARG2(ExtendSub);
		TYPE_ES_FUNC_ARG2_U(ExtendSub);
		TEMPLATE_ES_A_FUNC_ARG2(ExtendSub,LO,subsr);
		TEMPLATE_ES_A_FUNC_ARG2(ExtendSub,HI,subsl);
		TEMPLATE_ES_A_FUNC_ARG2_U(ExtendSub,LO,subur);
		TEMPLATE_ES_A_FUNC_ARG2_U(ExtendSub,HI,subul);

/*
 * v16i8 PatSat(v8i16 a,v8i16 b)
 */
		IMPLEMENT_PS_FUNC_ARG2(PadSat,satss);
		IMPLEMENT_PU_FUNC_ARG2(PadSat,satuu);


/*
 * template<int32_t op> v16i8 Package(v16i8 a,v16i8 b)
 */
		TYPE_S_FUNC_ARG2(Package);
		TYPE_U_FUNC_ARG2(Package);

		TEMPLATE_SI_B_FUNC_ARG2(Package,EVEN,pckev);
		TEMPLATE_UI_B_FUNC_ARG2(Package,EVEN,pckev);
		TEMPLATE_SI_B_FUNC_ARG2(Package,ODD,pckod);
		TEMPLATE_UI_B_FUNC_ARG2(Package,ODD,pckod);

/*
 * template<int32_t op> v16i8 Interleave(v16i8 lo,v16i8 hi)
 */
		TYPE_S_FUNC_ARG2(Interleave);
		TYPE_U_FUNC_ARG2(Interleave);

		TEMPLATE_SI_B_FUNC_ARG2(Interleave,EVEN,ilvev);
		TEMPLATE_SI_B_FUNC_ARG2(Interleave,ODD,ilvod);

		TEMPLATE_UI_B_FUNC_ARG2(Interleave,EVEN,ilvev);
		TEMPLATE_UI_B_FUNC_ARG2(Interleave,ODD,ilvod);

		TEMPLATE_SI_B_FUNC_ARG2(Interleave,LO,ilvr);
		TEMPLATE_SI_B_FUNC_ARG2(Interleave,HI,ilvl);

		TEMPLATE_UI_B_FUNC_ARG2(Interleave,LO,ilvr);
		TEMPLATE_UI_B_FUNC_ARG2(Interleave,HI,ilvl);


/*
 * v16i8 Shuffle(v16i8 vshf,v16i8 lo,v16i8 hi)
 */
		IMPLEMENT_S_B_FUNC_ARG3(Shuffle,vshf);
		IMPLEMENT_U_B_FUNC_ARG3(Shuffle,vshf);

/*
 * ShuffleEx is all args will reserved.
 */

		v16i8 SIMD_INLINE ShuffleEx(v16i8 c,v16i8 lo,v16i8 hi)
		{
			return __builtin_msa_vshfr_b(hi,lo,c);
		}
		v16u8 SIMD_INLINE ShuffleEx(v16u8 c,v16u8 lo,v16u8 hi)
		{
			return (v16u8)__builtin_msa_vshfr_b(hi,lo,c);
		}

/*
 * v16i8 Shuffle(v16i8 a,char shf)
 */
		IMPLEMENT_S_FUNC_ARG2_VC(Shuffle,shf);
		IMPLEMENT_U_FUNC_ARG2_VC(Shuffle,shf);

/*
 * v8i16 PadMultiplyAdd(v8i16 a,v16i8 b,v16i8 c)
 * return a + ((int16_t)b[0] * (int16_t)c[0] + (int16_t)b[1] * (int16_t)c[1])
 */
		IMPLEMENT_ES_FUNC_ARG3_E(PadMultiplyAdd,dpadd_s);
		IMPLEMENT_EU_FUNC_ARG3_E(PadMultiplyAdd,dpadd_u);

/*
 * v8i16 PadMultiplySub(v8i16 a,v16i8 b,v16i8 c)
 * return a - ((int16_t)b[0] * (int16_t)c[0] + (int16_t)b[1] * (int16_t)c[1])
 */
		IMPLEMENT_ES_FUNC_ARG3_E(PadMultiplySub,dpsub_s);
		IMPLEMENT_EU_FUNC_ARG3_E(PadMultiplySub,dpsub_u);

/*
 * v16i8 MultiplyAdd(v16i8 add,v16i8 ma,v16i8 mb)
 * return (add + ma * mb)
 */
		IMPLEMENT_S_B_FUNC_ARG3(MultiplyAdd,maddv);
		IMPLEMENT_F_B_FUNC_ARG3(MultiplyAdd,fmadd);

/*
 * v16i8 MultiplySub(v16i8 sub,v16i8 ma,v16i8 mb)
 * return sub - ma * mb
 */
		IMPLEMENT_S_B_FUNC_ARG3(MultiplySub,msubv);
		IMPLEMENT_F_B_FUNC_ARG3(MultiplySub,fmsub);

/*
 * v16i8 Average(v16i8 a,v16i8 b)
 * return (a + b + 1) / 2
 */
		IMPLEMENT_S_FUNC_ARG2(Average,aver_s);
		IMPLEMENT_U_FUNC_ARG2(Average,aver_u);

/*
 * v4f32 Sqrt(v4f32 a)
 */
		IMPLEMENT_F_FUNC_ARG1(Sqrt,fsqrt);
/*
 * v4f32 SqrtReciprocal(v4f32 a)
 * return 1.0 / Sqrt(a)
 */

		IMPLEMENT_F_FUNC_ARG1(SqrtReciprocal,frsqrt);
/*
 * v4f32 SqrtReciprocal(v4f32 a)
 * return 1.0 / a
 */
		IMPLEMENT_F_FUNC_ARG1(Reciprocal,frcp);
/*
 * v4f32 Log2(v4f32 a)
 */
		IMPLEMENT_F_FUNC_ARG1(Log2,flog2);
/*
 * v4f32 Round(v4f32 a)
 */
		IMPLEMENT_F_FUNC_ARG1(Ceil,frint);

/*
 * v4f32 Exp2(v4f32 a,v4i32 b)
 */
		IMPLEMENT_F_FUNC_ARG2_FI(Exp2,fexp2)

		v4f32 SIMD_INLINE ComplexMultipy(v4f32 a,v4f32 b){
			return __builtin_msa_fcmul_w(a,b);
		}

#define CONVERTFROM(O,I,CODE)					\
		O SIMD_INLINE ConvertFP(I v){			\
			return __builtin_msa_##CODE(v);		\
		}
		template <typename I,typename O> I ConvertFP(O a);
		template <typename I,typename O> I UpConvertFP(O a);

#define CONVERTTO(O,I,CODE)						\
		template<>								\
		I SIMD_INLINE ConvertFP(O v){			\
			return __builtin_msa_##CODE(v);		\
		}

#define CONVERTUP(O,I,CODE)						\
		template<>								\
		I SIMD_INLINE UpConvertFP(O v){			\
			return __builtin_msa_##CODE(v);		\
		}

		MACRO_FCV_FUNC(CONVERTFROM,ffint);
		MACRO_FCV_FUNC(CONVERTTO,ftrunc);

		MACRO_FCV_FUNC(CONVERTUP,ftint);


#define CONVERTQF(O,I,CODE)							\
		I SIMD_INLINE ConvertQF(O lob,O hib){		\
			return __builtin_msa_##CODE(hib,lob);	\
		}

		MACRO_FCV_HALF_S_FUNC(CONVERTQF,ftq);

		TYPE2_F_FUNC_ARG1_Q(ConvertQF);
		TEMPLATE_F_FUNC_ARG1_Q(ConvertQF,LO,ffqr);
		TEMPLATE_F_FUNC_ARG1_Q(ConvertQF,HI,ffql);



#define DOWNCONVERTHF(O,I,CODE)							\
		I SIMD_INLINE DownConvertHFP(O lob,O hib){		\
			return __builtin_msa_##CODE(hib,lob);		\
		}

		MACRO_FCV_HALF_FUNC(DOWNCONVERTHF,fexdo);

		TYPE2_EF_FUNC_ARG1(UpConvertHFP);
		TEMPLATE_EF_FUNC_ARG1_HF(UpConvertHFP,EVEN,fexupl);
		TEMPLATE_EF_FUNC_ARG1_HF(UpConvertHFP,ODD,fexupr);

		template <int32_t op> v4f32 SIMD_INLINE ConvertHFP(v8f16 f,v8i16 control);
		template<>
		v4f32 SIMD_INLINE ConvertHFP<LO>(v8f16 f,v8i16 control){
			return __builtin_msa_fexuprc_w(f,control);
		}
		template<>
		v4f32 SIMD_INLINE ConvertHFP<HI>(v8f16 f,v8i16 control){
			return __builtin_msa_fexuplc_w(f,control);
		}

#define SELECT0VECTOR(T1,T2)								\
		T1 SIMD_INLINE Select0Vector(T2 m,T1 s0,T1 s1){		\
			v16u8 u1 = *(v16u8 *)&s1;						\
			v16u8 u0 = *(v16u8 *)&s0;						\
			v16u8 r = __builtin_msa_bmnz_v(u1,u0,(v16u8)m);	\
			return *(T1 *)&r;								\
		}

		MACRO_S_FUNC(SELECT0VECTOR);
		MACRO_U_FUNC(SELECT0VECTOR);
		MACRO_F_FUNC(SELECT0VECTOR);

#define SELECT1VECTOR(T1,T2)								\
		T1 SIMD_INLINE Select1Vector(T2 m,T1 s0,T1 s1){		\
			v16u8 u1 = *(v16u8 *)&s1;						\
			v16u8 u0 = *(v16u8 *)&s0;						\
			v16u8 r = __builtin_msa_bmz_v(u1,u0,(v16u8)m);	\
			return *(T1 *)&r;								\
		}

		MACRO_S_FUNC(SELECT1VECTOR);
		MACRO_U_FUNC(SELECT1VECTOR);
		MACRO_F_FUNC(SELECT1VECTOR);

#define SELECTVECTOR(T1,T2)										\
		T1 SIMD_INLINE SelectVector(T2 m,T1 s0,T1 s1){			\
			v16u8 u1 = *(v16u8 *)&s1;							\
			v16u8 u0 = *(v16u8 *)&s0;							\
			v16u8 _m = *(v16u8 *)&m;							\
			v16u8 r = __builtin_msa_bsel_v(_m,u0,u1);			\
			return *(T1 *)&r;									\
		}

		MACRO_S_FUNC(SELECTVECTOR);
		MACRO_U_FUNC(SELECTVECTOR);
		MACRO_F_FUNC(SELECTVECTOR);

#define CLEARBIT(T,CODE)							\
		T SIMD_INLINE ClearBit(T data,T bits) {		\
			return __builtin_msa_##CODE(data,bits);	\
		}

		MACRO_S_FUNC_ARGS0(CLEARBIT,bclr);
		MACRO_U_FUNC_ARGS0(CLEARBIT,bclr);

#define SETBIT(T,CODE)								\
		T SIMD_INLINE SetBit(T data,T bits) {		\
			return __builtin_msa_##CODE(data,bits);	\
		}
		MACRO_S_FUNC_ARGS0(SETBIT,bset);
		MACRO_U_FUNC_ARGS0(SETBIT,bset);


		template<int32_t op,typename T> T SIMD_INLINE SelectBits(T lo,T hi,T sel);

#define SELECTBITS(T,CODE,OP)							\
		template<>										\
		T SIMD_INLINE SelectBits<OP>(T lo,T hi,T s){	\
			return __builtin_msa_##CODE(hi,lo,s);		\
		}												\

		MACRO_S_TFUNC(SELECTBITS,binsr,LO);
		MACRO_S_TFUNC(SELECTBITS,binsl,HI);
		MACRO_U_TFUNC(SELECTBITS,binsr,LO);
		MACRO_U_TFUNC(SELECTBITS,binsl,HI);

#define	REVERSEBIT(T,CODE)							\
		T SIMD_INLINE ReverseBit(T data,T bits) {	\
			return __builtin_msa_##CODE(data,bits); \
		}

		MACRO_S_FUNC_ARGS0(REVERSEBIT,bneg);
		MACRO_U_FUNC_ARGS0(REVERSEBIT,bneg);



#define COUNTONES(T,T1,CODE)							\
		int SIMD_INLINE CountOnes(T v){					\
			v16i8 src = *(v16i8 *)&v;					\
			v16i8 dcount = __builtin_msa_pcnt_v(src);	\
			return dcount[0];							\
		}

		MACRO_S_FUNC_ARGS1(COUNTONES,pcnt);
		MACRO_U_FUNC_ARGS1(COUNTONES,pcnt);
		MACRO_F_FUNC_ARGS1(COUNTONES,pcnt);

		template<int32_t op,typename T> T SIMD_INLINE CountBits(T v);

#define VCOUNTONES(T,T1,code)					\
		template<>								\
		T SIMD_INLINE CountBits<ONES>(T ma){	\
			return __builtin_msa_##code(ma);	\
		}
		MACRO_S_FUNC_ARGS1(VCOUNTONES,pcnt);
		MACRO_U_FUNC_ARGS1(VCOUNTONES,pcnt);



#define	COUNTLEADONE(T,CODE)						\
		template<>									\
		T SIMD_INLINE CountBits<LEADONES>(T data) {	\
			return __builtin_msa_##CODE(data);		\
		}

		MACRO_S_FUNC_ARGS0(COUNTLEADONE,nloc);
		MACRO_U_FUNC_ARGS0(COUNTLEADONE,nloc);

#define	COUNTLEADZERO(T,CODE)						\
		template<>									\
		T SIMD_INLINE CountBits<LEADZERO>(T data) {	\
			return __builtin_msa_##CODE(data);		\
		}

		MACRO_S_FUNC_ARGS0(COUNTLEADZERO,nlzc);
		MACRO_U_FUNC_ARGS0(COUNTLEADZERO,nlzc);

	}
#endif /* SIMD_MSA_ENABLE  */
}
#endif /* SIMDMSATYPE_H */
