#ifndef _SIMDMSAIMMN16_15_H_
#define _SIMDMSAIMMN16_15_H_

#define TYPE_IMM_N16_15_FUNC(Template,Func,OP,CODE)						\
		Template(Func,OP,-16,CODE);	Template(Func,OP,-15,CODE);	Template(Func,OP,-14,CODE);	Template(Func,OP,-13,CODE);	\
		Template(Func,OP,-12,CODE);	Template(Func,OP,-11,CODE);	Template(Func,OP,-10,CODE);	Template(Func,OP,-9,CODE); \
		Template(Func,OP,-8,CODE);	Template(Func,OP,-7,CODE);	Template(Func,OP,-6,CODE);	Template(Func,OP,-5,CODE); \
		Template(Func,OP,-4,CODE);	Template(Func,OP,-3,CODE);	Template(Func,OP,-2,CODE);	Template(Func,OP,-1,CODE); \
		Template(Func,OP,0,CODE);	Template(Func,OP,1,CODE);	Template(Func,OP,2,CODE);	Template(Func,OP,3,CODE); \
		Template(Func,OP,4,CODE);	Template(Func,OP,5,CODE);	Template(Func,OP,6,CODE);	Template(Func,OP,7,CODE); \
		Template(Func,OP,8,CODE);	Template(Func,OP,9,CODE);	Template(Func,OP,10,CODE);	Template(Func,OP,11,CODE); \
		Template(Func,OP,12,CODE);	Template(Func,OP,13,CODE);	Template(Func,OP,14,CODE);	Template(Func,OP,15,CODE); \


#endif /* _SIMDMSAIMMN16_15_H_ */
