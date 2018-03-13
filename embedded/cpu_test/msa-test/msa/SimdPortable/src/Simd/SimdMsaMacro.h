#ifndef _SIMDMSAMACRO_H_
#define _SIMDMSAMACRO_H_
typedef v8i16 v8f16;
/*******************************************************************************/
#define MACRO_S_FUNC(Macro)				\
	Macro(v16i8,v16u8);Macro(v8i16,v8u16);		\
	Macro(v4i32,v4u32);Macro(v2i64,v2u64);		\

#define MACRO_U_FUNC(Macro)				\
	Macro(v16u8,v16u8);Macro(v8u16,v8u16);		\
	Macro(v4u32,v4u32);Macro(v2u64,v2u64);		\

#define MACRO_F_FUNC(Macro)				\
	Macro(v4f32,v4u32);Macro(v2f64,v2u64);		\


#define MACRO_S_FUNC_ARGS0(Macro,Code)			\
	Macro(v16i8,Code##_b);Macro(v8i16,Code##_h);	\
	Macro(v4i32,Code##_w);Macro(v2i64,Code##_d);	\

#define MACRO_U_FUNC_ARGS0(Macro,Code)			\
	Macro(v16u8,Code##_b);Macro(v8u16,Code##_h);	\
	Macro(v4u32,Code##_w);Macro(v2u64,Code##_d);	\

#define MACRO_F_FUNC_ARGS0(Macro,Code)			\
	Macro(v4f32,Code##_b);Macro(v2f64,Code##_h);


#define MACRO_S_TFUNC(Macro,Code,Op)				\
	Macro(v16i8,Code##_b,Op);Macro(v8i16,Code##_h,Op);	\
	Macro(v4i32,Code##_w,Op);Macro(v2i64,Code##_d,Op);	\

#define MACRO_U_TFUNC(Macro,Code,Op)				\
	Macro(v16u8,Code##_b,Op);Macro(v8u16,Code##_h,Op);	\
	Macro(v4u32,Code##_w,Op);Macro(v2u64,Code##_d,Op);	\

#define MACRO_F_TFUNC(Macro,Code,Op)				\
	Macro(v4f32,Code##_b,Op);Macro(v2f64,Code##_h,Op);


/******************************************************************************/

#define MACRO_S_FUNC_ARGS1(Macro,Code)							\
	Macro(v16i8,int8_t,Code##_b);Macro(v8i16,int16_t,Code##_h);		\
	Macro(v4i32,int32_t,Code##_w);Macro(v2i64,int64_t,Code##_d);

#define MACRO_U_FUNC_ARGS1(Macro,Code)							\
	Macro(v16u8,uint8_t,Code##_b);Macro(v8u16,uint16_t,Code##_h);	\
	Macro(v4u32,uint32_t,Code##_w);Macro(v2u64,uint64_t,Code##_d);

#define MACRO_F_FUNC_ARGS1(Macro,Code)						\
	Macro(v4f32,float,Code##_w);Macro(v2f64,double,Code##_d);

/******************************************************************************/
#define MACRO_FCV_FUNC(Macro,Code)							 \
	Macro(v4f32,v4u32,Code##_u_w);Macro(v2f64,v2u64,Code##_u_d); \
	Macro(v4f32,v4i32,Code##_s_w);Macro(v2f64,v2i64,Code##_s_d);

#define MACRO_FCV_HALF_FUNC(Macro,Code)				\
	Macro(v4f32,v8f16,Code##_h);Macro(v2f64,v4f32,Code##_w);

#define MACRO_FCV_HALF_S_FUNC(Macro,Code)			\
	Macro(v4f32,v8i16,Code##_h);Macro(v2f64,v4i32,Code##_w);

/******************************************************************************/
/*
 * Defined functions:
 *        Set<int32_t imm>();
 */

#define TEMPLATE_SI_C_FUNC_ARG0(Func,IMM,CODE)	\
	template<>									\
	v16i8 SIMD_INLINE Func<IMM>(){				\
		return __builtin_msa_##CODE##_b(IMM);	\
	}											\
	template<>									\
	v8i16 SIMD_INLINE Func<IMM>(){				\
		return __builtin_msa_##CODE##_h(IMM);	\
	}											\
	template<>									\
	v4i32 SIMD_INLINE Func<IMM>(){				\
		return __builtin_msa_##CODE##_w(IMM);	\
	}											\
	template<>									\
	v2i64 SIMD_INLINE Func<IMM>(){				\
		return __builtin_msa_##CODE##_d(IMM);	\
	}


#define TEMPLATE_UI_C_FUNC_ARG0(Func,IMM,CODE)	\
	template<>									\
	v16u8 SIMD_INLINE Func<IMM>(){				\
		return __builtin_msa_##CODE##_b(IMM);	\
	}											\
	template<>									\
	v8u16 SIMD_INLINE Func<IMM>(){				\
		return __builtin_msa_##CODE##_h(IMM);	\
	}											\
	template<>									\
	v4u32 SIMD_INLINE Func<IMM>(){				\
		return __builtin_msa_##CODE##_w(IMM);	\
	}											\
	template<>									\
	v2u64 SIMD_INLINE Func<IMM>(){				\
		return __builtin_msa_##CODE##_d(IMM);	\
	}

/*******************************************************************************/

#define IMPLEMENT_F_FUNC_ARG1(Func,CODE)		\
	v4f32 SIMD_INLINE Func(v4f32 a){			\
		return __builtin_msa_##CODE##_w(a);		\
	}											\
	v2f64 SIMD_INLINE Func(v2f64 a){			\
		return __builtin_msa_##CODE##_d(a);		\
	}											\


/*******************************************************************************/
#define IMPLEMENT_S_FUNC_ARG2(Func,CODE)		\
	v16i8 SIMD_INLINE Func(v16i8 a,v16i8 b){	\
		return __builtin_msa_##CODE##_b(a,b);	\
	}											\
	v8i16 SIMD_INLINE Func(v8i16 a,v8i16 b){	\
		return __builtin_msa_##CODE##_h(a,b);	\
	}											\
	v4i32 SIMD_INLINE Func(v4i32 a,v4i32 b){	\
		return __builtin_msa_##CODE##_w(a,b);	\
	}											\
	v2i64 SIMD_INLINE Func(v2i64 a,v2i64 b){	\
		return __builtin_msa_##CODE##_d(a,b);	\
	}											\

#define IMPLEMENT_U_FUNC_ARG2(Func,CODE)		\
	v16u8 SIMD_INLINE Func(v16u8 a,v16u8 b){	\
		return __builtin_msa_##CODE##_b(a,b);	\
	}											\
	v8u16 SIMD_INLINE Func(v8u16 a,v8u16 b){	\
		return __builtin_msa_##CODE##_h(a,b);	\
	}											\
	v4u32 SIMD_INLINE Func(v4u32 a,v4u32 b){	\
		return __builtin_msa_##CODE##_w(a,b);	\
	}											\
	v2u64 SIMD_INLINE Func(v2u64 a,v2u64 b){	\
		return __builtin_msa_##CODE##_d(a,b);	\
	}											\

#define IMPLEMENT_F_FUNC_ARG2(Func,CODE)		\
	v4f32 SIMD_INLINE Func(v4f32 a,v4f32 b){	\
		return __builtin_msa_##CODE##_w(a,b);	\
	}											\
	v2f64 SIMD_INLINE Func(v2f64 a,v2f64 b){	\
		return __builtin_msa_##CODE##_d(a,b);	\
	}											\

#define IMPLEMENT_SU_FUNC_ARG2(Func,CODE)		\
	v16i8 SIMD_INLINE Func(v16u8 a,v16u8 b){	\
		return __builtin_msa_##CODE##_b(a,b);	\
	}											\
	v8i16 SIMD_INLINE Func(v8u16 a,v8u16 b){	\
		return __builtin_msa_##CODE##_h(a,b);	\
	}											\
	v4i32 SIMD_INLINE Func(v4u32 a,v4u32 b){	\
		return __builtin_msa_##CODE##_w(a,b);	\
	}											\
	v2i64 SIMD_INLINE Func(v2u64 a,v2u64 b){	\
		return __builtin_msa_##CODE##_d(a,b);	\
	}											\

/******************************************************************************/

#define IMPLEMENT_F_FUNC_ARG2_FI(Func,CODE)		\
	v4f32 SIMD_INLINE Func(v4f32 a,v4i32 b){	\
		return __builtin_msa_##CODE##_w(a,b);	\
	}											\
	v2f64 SIMD_INLINE Func(v2f64 a,v2i64 b){	\
		return __builtin_msa_##CODE##_d(a,b);	\
	}											\

/******************************************************************************/
#define IMPLEMENT_PS_FUNC_ARG2(Func,CODE)		\
	v16i8 SIMD_INLINE Func(v8i16 a,v8i16 b){	\
		return __builtin_msa_##CODE##_b(b,a);	\
	}											\
	v8i16 SIMD_INLINE Func(v4i32 a,v4i32 b){	\
		return __builtin_msa_##CODE##_h(b,a);	\
	}											\

#define IMPLEMENT_PU_FUNC_ARG2(Func,CODE)		\
	v16u8 SIMD_INLINE Func(v8u16 a,v8u16 b){	\
		return __builtin_msa_##CODE##_b(b,a);	\
	}											\
	v8u16 SIMD_INLINE Func(v4i32 a,v4u32 b){	\
		return __builtin_msa_##CODE##_h(b,a);	\
	}											\

/******************************************************************************/

#define IMPLEMENT_ES_FUNC_ARG3_E(Func,CODE)				\
	v8i16 SIMD_INLINE Func(v8i16 a,v16i8 b,v16i8 c){	\
		return __builtin_msa_##CODE##_h(a,b,c);			\
	}													\
	v4i32 SIMD_INLINE Func(v4i32 a,v8i16 b,v8i16 c){	\
		return __builtin_msa_##CODE##_w(a,b,c);			\
	}													\
	v2i64 SIMD_INLINE Func(v2i64 a,v4i32 b,v4i32 c){	\
		return __builtin_msa_##CODE##_d(a,b,c);			\
	}													\

#define IMPLEMENT_EU_FUNC_ARG3_E(Func,CODE)				\
	v8u16 SIMD_INLINE Func(v8u16 a,v16u8 b,v16u8 c){	\
		return __builtin_msa_##CODE##_h(a,b,c);			\
	}													\
	v4u32 SIMD_INLINE Func(v4i32 a,v8u16 b,v8u16 c){	\
		return __builtin_msa_##CODE##_w(a,b,c);			\
	}													\
	v2u64 SIMD_INLINE Func(v2u64 a,v4u32 b,v4u32 c){	\
		return __builtin_msa_##CODE##_d(a,b,c);			\
	}													\

/******************************************************************************/
#define IMPLEMENT_S_FUNC_ARG2_VC(Func,CODE)		\
	v16i8 SIMD_INLINE Func(v16i8 a,char b){		\
		return __builtin_msa_##CODE##_b(a,b);	\
	}											\
	v8i16 SIMD_INLINE Func(v8i16 a,char b){		\
		return __builtin_msa_##CODE##_h(a,b);	\
	}											\
	v4i32 SIMD_INLINE Func(v4i32 a,char b){		\
		return __builtin_msa_##CODE##_w(a,b);	\
	}											\

#define IMPLEMENT_U_FUNC_ARG2_VC(Func,CODE)		\
	v16u8 SIMD_INLINE Func(v16u8 a,char b){		\
		return __builtin_msa_##CODE##_b(a,b);	\
	}											\
	v8u16 SIMD_INLINE Func(v8u16 a,char b){		\
		return __builtin_msa_##CODE##_h(a,b);	\
	}											\
	v4u32 SIMD_INLINE Func(v4u32 a,char b){		\
		return __builtin_msa_##CODE##_w(a,b);	\
	}											\

/******************************************************************************/
#define IMPLEMENT_S_B_FUNC_ARG3(Func,CODE)				\
	v16i8 SIMD_INLINE Func(v16i8 a,v16i8 b,v16i8 c){	\
		return __builtin_msa_##CODE##_b(a,c,b);			\
	}													\
	v8i16 SIMD_INLINE Func(v8i16 a,v8i16 b,v8i16 c){	\
		return __builtin_msa_##CODE##_h(a,c,b);			\
	}													\
	v4i32 SIMD_INLINE Func(v4i32 a,v4i32 b,v4i32 c){	\
		return __builtin_msa_##CODE##_w(a,c,b);			\
	}													\
	v2i64 SIMD_INLINE Func(v2i64 a,v2i64 b,v2i64 c){	\
		return __builtin_msa_##CODE##_d(a,c,b);			\
	}													\

#define IMPLEMENT_U_B_FUNC_ARG3(Func,CODE)				\
	v16u8 SIMD_INLINE Func(v16u8 a,v16u8 b,v16u8 c){	\
		return __builtin_msa_##CODE##_b(a,c,b);			\
	}													\
	v8u16 SIMD_INLINE Func(v8u16 a,v8u16 b,v8u16 c){	\
		return __builtin_msa_##CODE##_h(a,c,b);			\
	}													\
	v4u32 SIMD_INLINE Func(v4u32 a,v4u32 b,v4u32 c){	\
		return __builtin_msa_##CODE##_w(a,c,b);			\
	}													\
	v2u64 SIMD_INLINE Func(v2u64 a,v2u64 b,v2u64 c){	\
		return __builtin_msa_##CODE##_d(a,c,b);			\
	}													\

#define IMPLEMENT_F_B_FUNC_ARG3(Func,CODE)				\
	v4f32 SIMD_INLINE Func(v4f32 a,v4f32 b,v4f32 c){	\
		return __builtin_msa_##CODE##_w(a,c,b);			\
	}													\
	v2f64 SIMD_INLINE Func(v2f64 a,v2f64 b,v2f64 c){	\
		return __builtin_msa_##CODE##_d(a,c,b);			\
	}													\

/******************************************************************************/

#define TYPE2_S_FUNC_ARG1(Func)											\
	template<int32_t op,int32_t imm> v16i8 SIMD_INLINE Func(v16i8 a);	\
	template<int32_t op,int32_t imm> v8i16 SIMD_INLINE Func(v8i16 a);	\
	template<int32_t op,int32_t imm> v4i32 SIMD_INLINE Func(v4i32 a);	\
	template<int32_t op,int32_t imm> v2i64 SIMD_INLINE Func(v2i64 a)

#define TEMPLATE2_SI_C_FUNC_ARG1(Func,OP,IMM,CODE)	\
	template<>										\
	v16i8 SIMD_INLINE Func<OP,IMM>(v16i8 a){		\
		return __builtin_msa_##CODE##_b(a,IMM);		\
	}												\
	template<>										\
	v8i16 SIMD_INLINE Func<OP,IMM>(v8i16 a){		\
		return __builtin_msa_##CODE##_h(a,IMM);		\
	}												\
	template<>										\
	v4i32 SIMD_INLINE Func<OP,IMM>(v4i32 a){		\
		return __builtin_msa_##CODE##_w(a,IMM);		\
	}												\
	template<>										\
	v2i64 SIMD_INLINE Func<OP,IMM>(v2i64 a){		\
		return __builtin_msa_##CODE##_d(a,IMM);		\
	}

#define TYPE2_U_FUNC_ARG1(Func)											\
	template<int32_t op,int32_t imm> v16u8 SIMD_INLINE Func(v16u8 a);	\
	template<int32_t op,int32_t imm> v8u16 SIMD_INLINE Func(v8u16 a);	\
	template<int32_t op,int32_t imm> v4u32 SIMD_INLINE Func(v4u32 a);	\
	template<int32_t op,int32_t imm> v2u64 SIMD_INLINE Func(v2u64 a)


#define TEMPLATE2_UI_C_FUNC_ARG1(Func,OP,IMM,CODE)	\
	template<>										\
	v16u8 SIMD_INLINE Func<OP,IMM>(v16u8 a){		\
		return __builtin_msa_##CODE##_b(a,IMM);		\
	}												\
	template<>										\
	v8u16 SIMD_INLINE Func<OP,IMM>(v8u16 a){		\
		return __builtin_msa_##CODE##_h(a,IMM);		\
	}												\
	template<>										\
	v4u32 SIMD_INLINE Func<OP,IMM>(v4u32 a){		\
		return __builtin_msa_##CODE##_w(a,IMM);		\
	}												\
	template<>										\
	v2u64 SIMD_INLINE Func<OP,IMM>(v2u64 a){		\
		return __builtin_msa_##CODE##_d(a,IMM);		\
	}

#define TYPE2_F_FUNC_ARG1_HS(Func)							\
	template<int32_t op> v4f32 SIMD_INLINE Func(v8i16 a);	\
	template<int32_t op> v2f64 SIMD_INLINE Func(v4i32 a);

#define TEMPLATE_F_FUNC_ARG1_HS(Func,OP,CODE)	\
	template<>									\
	v4f32 SIMD_INLINE Func<OP>(v8i16 a){		\
		return __builtin_msa_##CODE##_w(a);		\
	}											\
	template<>									\
	v2f64 SIMD_INLINE Func<OP>(v4i32 a){		\
		return __builtin_msa_##CODE##_d(a);		\
	}


#define TYPE2_F_FUNC_ARG1_Q(Func)							\
	template<int32_t op> v4f32 SIMD_INLINE Func(v8i16 a);	\
	template<int32_t op> v2f64 SIMD_INLINE Func(v4i32 a);

#define TEMPLATE_F_FUNC_ARG1_Q(Func,OP,CODE)	\
	template<>									\
	v4f32 SIMD_INLINE Func<OP>(v8i16 a){		\
		return __builtin_msa_##CODE##_w(a);		\
	}											\
	template<>									\
	v2f64 SIMD_INLINE Func<OP>(v4i32 a){		\
		return __builtin_msa_##CODE##_d(a);		\
	}



#define TYPE2_EF_FUNC_ARG1(Func)							\
	template<int32_t op> v4f32 SIMD_INLINE Func(v8f16 a);	\
	template<int32_t op> v2f64 SIMD_INLINE Func(v4f32 a);

#define TEMPLATE_EF_FUNC_ARG1_HF(Func,OP,CODE)	\
	template<>									\
	v4f32 SIMD_INLINE Func<OP>(v8f16 a){		\
		return __builtin_msa_##CODE##_w(a);		\
	}											\
	template<>									\
	v2f64 SIMD_INLINE Func<OP>(v4f32 a){		\
		return __builtin_msa_##CODE##_d(a);		\
	}


/******************************************************************************/
/*
 * Declare all interger vector template function.
 * these functions has 2's argument.
 * these function input and output parameter is samed.
 * eg:
 *    template<int32_t op> v16i8 SIMD_INLINE Compare(v16i8,v16i8)
 */
#define TYPE_S_FUNC_ARG2(Func)										\
	template<int32_t op> v16i8 SIMD_INLINE Func(v16i8 a,v16i8 b);	\
	template<int32_t op> v8i16 SIMD_INLINE Func(v8i16 a,v8i16 b);	\
	template<int32_t op> v4i32 SIMD_INLINE Func(v4i32 a,v4i32 b);	\
	template<int32_t op> v2i64 SIMD_INLINE Func(v2i64 a,v2i64 b)

/*
 * Declare all unsinged interger vector template functions.
 * these functions has 2's argument.
 * these function input and output parameter is samed.
 * eg:
 *     template<int32_t op> v16u8 SIMD_INLINE Compare(v16u8,v16u8)
 */
#define TYPE_U_FUNC_ARG2(Func)										\
	template<int32_t op> v16u8 SIMD_INLINE Func(v16u8 a,v16u8 b);	\
	template<int32_t op> v8u16 SIMD_INLINE Func(v8u16 a,v8u16 b);	\
	template<int32_t op> v4u32 SIMD_INLINE Func(v4u32 a,v4u32 b);	\
	template<int32_t op> v2u64 SIMD_INLINE Func(v2u64 a,v2u64 b)

/*
 * Defined some macro for TYPE_S_FUNC_ARG2 and TYPE_U_FUNC_ARG2 template function's implementation.
 *
 * TEMPLATE_SI_A_FUNC_ARG2: it's defined template function for implementation of all signal interger vector.
 *                          sequence of two argument is same as builtin code. a,b -> a,b
 * TEMPLATE_UI_A_FUNC_ARG2: it's defined template function for implementation of all unsignal interger vector.
 *                          sequence of two argument is same as builtin code. a,b -> a,b
 *
 * TEMPLATE_SI_B_FUNC_ARG2: it's defined template function for implementation of all signal interger vector.
 *                          sequence of two argument is cross over builtin code. a,b -> b,a
 * TEMPLATE_UI_B_FUNC_ARG2: it's defined template function for implementation of all unsignal interger vector.
 *                          sequence of two argument is cross over builtin code. a,b -> b,a
 *
 * Form:
 *     template<>
 *     v16i8 SIMD_INLINE Compare<op>(v16i8 a,v16i8 b) {
 *          return __builtin_msa_xxxx_b(a,b);
 *     }
 */
#define TEMPLATE_SI_A_FUNC_ARG2(Func,OP,CB)			\
	template<>										\
	v16i8 SIMD_INLINE Func<OP>(v16i8 a,v16i8 b){	\
		return  __builtin_msa_##CB##_b(a,b);		\
	}												\
	template<>										\
	v8i16 SIMD_INLINE Func<OP>(v8i16 a,v8i16 b){	\
		return  __builtin_msa_##CB##_h(a,b);		\
	}												\
	template<>										\
	v4i32 SIMD_INLINE Func<OP>(v4i32 a,v4i32 b){	\
		return __builtin_msa_##CB##_w(a,b);			\
	}												\
	template<>										\
	v2i64 SIMD_INLINE Func<OP>(v2i64 a,v2i64 b){	\
		return __builtin_msa_##CB##_d(a,b);			\
	}												\

#define TEMPLATE_SI_B_FUNC_ARG2(Func,OP,CB)			\
	template<>										\
	v16i8 SIMD_INLINE Func<OP>(v16i8 a,v16i8 b){	\
		return  __builtin_msa_##CB##_b(b,a);		\
	}												\
	template<>										\
	v8i16 SIMD_INLINE Func<OP>(v8i16 a,v8i16 b){	\
		return  __builtin_msa_##CB##_h(b,a);		\
	}												\
	template<>										\
	v4i32 SIMD_INLINE Func<OP>(v4i32 a,v4i32 b){	\
		return __builtin_msa_##CB##_w(b,a);			\
	}												\
	template<>										\
	v2i64 SIMD_INLINE Func<OP>(v2i64 a,v2i64 b){	\
		return __builtin_msa_##CB##_d(b,a);			\
	}												\


#define TEMPLATE_UI_A_FUNC_ARG2(Func,OP,CB)			\
	template<>										\
	v16u8 SIMD_INLINE Func<OP>(v16u8 a,v16u8 b){	\
		return  __builtin_msa_##CB##_b(a,b);		\
	}												\
	template<>										\
	v8u16 SIMD_INLINE Func<OP>(v8u16 a,v8u16 b){	\
		return  __builtin_msa_##CB##_h(a,b);		\
	}												\
	template<>										\
	v4u32 SIMD_INLINE Func<OP>(v4u32 a,v4u32 b){	\
		return __builtin_msa_##CB##_w(a,b);			\
	}												\
	template<>										\
	v2u64 SIMD_INLINE Func<OP>(v2u64 a,v2u64 b){	\
		return __builtin_msa_##CB##_d(a,b);			\
	}												\

#define TEMPLATE_UI_B_FUNC_ARG2(Func,OP,CB)			\
	template<>										\
	v16u8 SIMD_INLINE Func<OP>(v16u8 a,v16u8 b){	\
		return  __builtin_msa_##CB##_b(b,a);		\
	}												\
	template<>										\
	v8u16 SIMD_INLINE Func<OP>(v8u16 a,v8u16 b){	\
		return  __builtin_msa_##CB##_h(b,a);		\
	}												\
	template<>										\
	v4u32 SIMD_INLINE Func<OP>(v4u32 a,v4u32 b){	\
		return __builtin_msa_##CB##_w(b,a);			\
	}												\
	template<>										\
	v2u64 SIMD_INLINE Func<OP>(v2u64 a,v2u64 b){	\
		return __builtin_msa_##CB##_d(b,a);			\
	}												\

/*
 * Declare all float vector template functions.
 * these functions has 2's argument. and return corresponding size value.
 * form:
 *     template<int32_t op> v4u32 SIMD_INLINE Compare(v4f32,v4f32)
 */
#define TYPE_FC_FUNC_ARG2(Func)										\
	template<int32_t op> v4u32 SIMD_INLINE Func(v4f32 a,v4f32 b);	\
	template<int32_t op> v2u64 SIMD_INLINE Func(v2f64 a,v2f64 b);   \

/*
 * Defined some macro for TYPE_FC_FUNC_ARG2 template function's implementation.
 *
 * TEMPLATE_FC_A_FUNC_ARG2: it's defined template function for implementation of all float vector.
 *                          sequence of two argument is same as builtin code. a,b -> a,b
 *
 * TEMPLATE_FC_B_FUNC_ARG2: it's defined template function for implementation of all float vector.
 *                          sequence of two argument is cross over builtin code. a,b -> b,a
 *
 * Form:
 *     template<>
 *     v4u32 SIMD_INLINE Compare<op>(v4f32 a,v4f32 b) {
 *          return __builtin_msa_xxxx_b(a,b);
 *     }
 */
#define TEMPLATE_FC_A_FUNC_ARG2(Func,OP,CB)			\
	template<>										\
	v4u32 SIMD_INLINE Func<OP>(v4f32 a,v4f32 b){	\
		return  __builtin_msa_##CB##_w(a,b);		\
	}												\
	template<>										\
	v2u64 SIMD_INLINE Func<OP>(v2f64 a,v2f64 b){	\
		return  __builtin_msa_##CB##_d(a,b);		\
	}												\

#define TEMPLATE_FC_B_FUNC_ARG2(Func,OP,CB)			\
	template<>										\
	v4u32 SIMD_INLINE Func<OP>(v4f32 a,v4f32 b){	\
		return  __builtin_msa_##CB##_w(b,a);		\
	}												\
	template<>										\
	v2u64 SIMD_INLINE Func<OP>(v2f64 a,v2f64 b){	\
		return  __builtin_msa_##CB##_d(b,a);		\
	}												\


#define TYPE_ES_FUNC_ARG2(Func)										\
	template<int32_t op> v8i16 SIMD_INLINE Func(v16i8 a,v16i8 b);	\
	template<int32_t op> v4i32 SIMD_INLINE Func(v8i16 a,v8i16 b);

#define TYPE_EU_FUNC_ARG2(Func)										\
	template<int32_t op> v8u16 SIMD_INLINE Func(v16u8 a,v16u8 b);	\
	template<int32_t op> v4u32 SIMD_INLINE Func(v8u16 a,v8u16 b);

#define TYPE_ES_FUNC_ARG2_U(Func)									\
	template<int32_t op> v8i16 SIMD_INLINE Func(v16u8 a,v16u8 b);	\
	template<int32_t op> v4i32 SIMD_INLINE Func(v8u16 a,v8u16 b);

#define TEMPLATE_ES_A_FUNC_ARG2(Func,OP,CB)			\
	template<>										\
	v8i16 SIMD_INLINE Func<OP>(v16i8 a,v16i8 b){	\
		return  __builtin_msa_##CB##_h(a,b);		\
	}												\
	template<>										\
	v4i32 SIMD_INLINE Func<OP>(v8i16 a,v8i16 b){	\
		return  __builtin_msa_##CB##_w(a,b);		\
	}
#define TEMPLATE_EU_A_FUNC_ARG2(Func,OP,CB)			\
	template<>										\
	v8u16 SIMD_INLINE Func<OP>(v16u8 a,v16u8 b){	\
		return  __builtin_msa_##CB##_h(a,b);		\
	}												\
	template<>										\
	v4u32 SIMD_INLINE Func<OP>(v8u16 a,v8u16 b){	\
		return  __builtin_msa_##CB##_w(a,b);		\
	}

#define TEMPLATE_ES_A_FUNC_ARG2_U(Func,OP,CB)		\
	template<>										\
	v8i16 SIMD_INLINE Func<OP>(v16u8 a,v16u8 b){	\
		return  __builtin_msa_##CB##_h(a,b);		\
	}												\
	template<>										\
	v4i32 SIMD_INLINE Func<OP>(v8u16 a,v8u16 b){	\
		return  __builtin_msa_##CB##_w(a,b);		\
	}

/******************************************************************************/

#define TYPE_S_FUNC_ARG2_E(Func)									\
	template<int32_t op> v8i16 SIMD_INLINE Func(v8i16 a,v16i8 b);	\
	template<int32_t op> v4i32 SIMD_INLINE Func(v4i32 a,v8i16 b);

#define TYPE_U_FUNC_ARG2_E(Func)									\
	template<int32_t op> v8u16 SIMD_INLINE Func(v8u16 a,v16u8 b);	\
	template<int32_t op> v4u32 SIMD_INLINE Func(v4u32 a,v8u16 b);

#define TEMPLATE_S_A_FUNC_ARG2_E(Func,OP,CB)		\
	template<>										\
	v8i16 SIMD_INLINE Func<OP>(v8i16 a,v16i8 b){	\
		return  __builtin_msa_##CB##_h(a,b);		\
	}												\
	template<>										\
	v4i32 SIMD_INLINE Func<OP>(v4i32 a,v8i16 b){	\
		return  __builtin_msa_##CB##_w(a,b);		\
	}
#define TEMPLATE_U_A_FUNC_ARG2_E(Func,OP,CB)		\
	template<>										\
	v8u16 SIMD_INLINE Func<OP>(v8u16 a,v16u8 b){	\
		return  __builtin_msa_##CB##_h(a,b);		\
	}												\
	template<>										\
	v4u32 SIMD_INLINE Func<OP>(v4u32 a,v8u16 b){	\
		return  __builtin_msa_##CB##_w(a,b);		\
	}
/******************************************************************************/
#endif /* _SIMDMSAMACRO_H_ */
