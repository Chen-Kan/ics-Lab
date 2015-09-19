/* 
 * CS:APP Data Lab 
 * 
 * <14307130198-Chen Kan>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */
//#include <stdlib.h>
#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */
You will provide your solution to the Data Lab by
editing the collection of functions in this source file.
INTEGER CODING RULES:
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;
      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }
  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.
  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.
EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }
  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }
FLOATING POINT CODING RULES
For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.
You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.
NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.
/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */
#endif
/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
	//由摩尔定理即可得到
  return ~((~x) | (~y));
}
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n){
	//1.将n乘以8获得需要移动的位数
	//2.将x右移
	//3.取出右边八位
	return (x >> (n << 3)) & 0xff;
}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
	int maxBit = (1 << 31);
	//根据算术右移的特性maxBit >> n << 1结果为111...000
	//即左边n个1，其他为0
	//将这个数字取反，再and (x >> n) 即可取出右边32-n位
	int shiftAnd = ~(maxBit >> n << 1);
	return (x >> n) & shiftAnd;
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
	//从右边数起每两位进行分析
	//总共有4种状态：					x=11,10,01,00
	//1.可以发现，x - (x>>1)有四种结果：    10,01,01,00
	//	可以看出10,01,00的十进制数2,1,0分别为四种状态对应1的个数
	//再对每四位进行操作：
	//	2.将1.的结果右移两位并相加，就得到了每四位中1的个数
	//	例：1101 ---(1.操作)---> 1001 ---(2.操作)---> 0011(3)
	//同理再对每八位进行操作：
	//	3.将2.的结果右移四位并相加，就得到了每八位中1的个数
	//	例：1101 0111  ---(1.2.操作)--> 0011 0011 --(3.)-->0000 1010
	//最后将每八位的结果相加即可
	//
	int ox55555555 =0x55 + (0x55<<8) + (0x55<<16) + (0x55<<24);
	int ox33333333 =0x33 + (0x33<<8) + (0x33<<16) + (0x33<<24);
	int	ox0f0f0f0f =0x0f + (0x0f<<8) + (0x0f<<16) + (0x0f<<24);
	x = x + ~((x >> 1) & ox55555555) + 1;
	x = (x & ox33333333) + ((x >> 2) & ox33333333);
	x = (x + (x >> 4)) & ox0f0f0f0f;
	return ( x + (x >> 8) + (x >> 16) + (x >> 24)) & 0xff;
}
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
	//首先将左边16位与右边16位进行 or 运算
	//再将左边八位与右边八位进行 or 运算
	//重复一直到只剩一位
	//只要x非0，最后一位一定为1
	//再将最后一位取出并取反即可
	x |= x >> 16;
	x |= x >> 8;
	x |= x >> 4;
	x |= x >> 2;
	x |= x >> 1;
	return ((x & 1) ^ 1);
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
	//最小二进制数-2^31
	//2^31反码为0x7fffffff (unsigned)
	//将反码+1得0x80000000
	//即为1<<31
	return 1<<31;
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
	//将x右移n-1位
	//若n位二进制可以装的下x，则移位后x全为1或者全为0
	x = x >> (n + ~0);
	return !x | !(~x);
}
/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {
	//将x分为三种情况：x>=0,0x80000000 < x <0, x=0x80000000
	//sign 和 all1 的用处如下：
	//	sign为x的符号，为0x80000000 或 0
	//	当x>=0时all1=0xffffffff,
	//	当0x80000000 < x < 0时 all1=0 
	//	对于x>=0的时候，sign=all1=0，下面mark1操作后x不变，
	//		右移n位后进行mark1的反操作，为答案
	//	对于0x80000000 < x < 0, sign=0x80000000,all1=0xffffffff
	//		mark1操作后，x会变成x的原码（即取相反数）在mark0处，
	//			进行判断，如果x=0x80000000，sign会变成0，直接右移，
	//		右移n位后进行mark1的反操作，求出补码，即为答案
	//	对于x=0x80000000,只需对原数右移即可，所以在mark0处，
	//		进行判断，如果x=0x80000000，sign会变成0，直接右移
	int sign, all1, oneOrZero;
	sign = (1<<31) & x;
	sign ^= (!(x ^ sign) << 31);//mark0
	all1 = sign >> 31;
	oneOrZero = all1 & 1;
	x = (x ^ all1) + oneOrZero;//mark1:求原码
	//printf("x=%d  x-1=%d  sign=%d  oneOrZero=%d\n",x,x+~oneOrZero+1,sign,oneOrZero);
	x >>= n;
	//printf("x=%d\n",x);
	x = (x ^ (all1 )) + oneOrZero;
	return x;
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  return ~x+1;
}
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
	//分别取出x和x-1的符号位判断。（x-1是为了将0也变成负数）
	int x1 = x + (~0);//~0 == -1,等价于x1 = x-1
	x >>= 31;//将符号位移动到右边
	x1 >>= 31;
	return ((x | x1) & 1)^1;
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
	int sign1 = (y >> 31) & 1;//取出ｙ的符号
	int sign2 = (x >> 31) & 1;//取出ｘ的符号
	//x符号减去y的符号，结果有三种：0,1,-1。
	//如果 x<0  且 y>=0 则ysubx == 1，此时一定返回1
	//如果 x>=0 且 y<0  则ysubx == -1, 此时一定返回0
	int ysubx = (sign2 + (~sign1 + 1));
	return (((~(y + (~x+1))>>31) & 1) | ysubx) & (~ysubx >> 31) & 1;
}
/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int ilog2(int x) {
	int a,count=0,n,m;
	a = x & (1 << 31 >> 15);
	n = !!a;
	m = !n;
	//printf("%d %d\n",n,m);
	//printf("%d\n",(a>>16) & ((n << 16) + ~0));
	//printf("%d\n",(x & ((m << 16) + ~0)));
	count += n << 4;
	x = ((a >> 16) & ((n << 16) + ~0)) + (x & ((m << 16) + (~m+1)));
	//printf("%d\n",x);
	
	a = x & (1 << 31 >> 23);
	n = !!a;
	m = !n;
	count += n << 3;
	x = ((a >> 8) & ((n << 8) + ~0)) + (x & ((m << 8) + (~m+1)));
	//printf("%d\n",x);
	
	a = x & (1 << 31 >> 27);
	n = !!a;
	m = !n;
	count += n << 2;
	x = ((a >> 4) & ((n << 4) + ~0)) + (x & ((m << 4) + (~m+1)));
	//printf("%d\n",x);
	
	a = x & (1 << 31 >> 29);
	n = !!a;
	m = !n;
	count += n << 1;
	x = ((a >> 2) & ((n << 2) + ~0)) + (x & ((m << 2) + (~m+1)));
	//("%d\n",x);
	
	a = x & (1 << 31 >> 30);
	n = !!a;
	m = !n;
	count += n;
	x = ((a >> 1) & ((n << 1) + ~0)) + (x & ((m << 1) + ~0));
	//printf("%d\n\n\n",x);
	
	return count;
}
/* 
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {
 return 2;
}
/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
  return 2;
}
/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
  return 2;
}
