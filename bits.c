/* 
 * CS:APP Data Lab 
 * 
 * Scott Bauersfeld 604813474
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
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
       /*This function determines if x is a nonzero number by arithmetically 
	right shifting x and the inverse of x so that the most significant sign
       bit is in the least significant position. If both result in zero,
       then the original x value must have been zero.*/  
       return(~(((x>>31) & 1) | ((~x+1)>>31) & 1)) & 1;
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
  /*This fucntion creates three masks. maska consists of alternating 0s and 1s,
   maskb consists of alternating groups of two 0s and two 1s, and maskc consists
  of alternating groups of four 0s and four 1s. The first integer adds together
  all of the odd bits with the even bits, so that every two bits of the result
  contain a bit sequence equal to the number of 1s that were added together.
  This process is repeated until there are four groups of 8 bits that each contain
  a bit pattern equal to the number of bits that were added together to produce those
  8 bits. Adding up these four 8 bit patterns produces a number equal to the number of 1s
  in the original bit pattern of x.*/
  int maska = 0x55<<24 | 0x55<<16 | 0x55<<8 | 0x55;
  int maskb = 0x33<<24 | 0x33<<16 | 0x33<<8 | 0x33;
  int maskc = 0x0f<<24 | 0x0f<<16 | 0x0f<<8 | 0x0f;
  int first = (x & maska) + ((x>>1) & maska);
  int second = (first & maskb) + ((first>>2) & maskb);
  int third = (second & maskc) + ((second>>4) & maskc);
  int bitmask = (1<<6) + ~0;
  return ((third>>24) + (third>>16) + (third>>8) + third) & bitmask;
}
/* 
 * bitOr - x|y using only ~ and & 
 *   Example: bitOr(6, 5) = 7
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitOr(int x, int y) {
  /* De Morgans law states that the not of or equals the not of each literal
     anded together.*/
  return ~(~x & ~y);
}
/*
 * bitRepeat - repeat x's low-order n bits until word is full.
 *   Can assume that 1 <= n <= 32.
 *   Examples: bitRepeat(1, 1) = -1
 *             bitRepeat(7, 4) = 0x77777777
 *             bitRepeat(0x13f, 8) = 0x3f3f3f3f
 *             bitRepeat(0xfffe02, 9) = 0x10080402
 *             bitRepeat(-559038737, 31) = -559038737
 *             bitRepeat(-559038737, 32) = -559038737
 *   Legal ops: int and unsigned ! ~ & ^ | + - * / % << >>
 *             (This is more general than the usual integer coding rules.)
 *   Max ops: 40
 *   Rating: 4
 */
int bitRepeat(int x, int n) {
  /*This function first copies the low order n bits and sets the rest to 0.
    It then proceeds to duplicate the bit pattern up to five times by shifting
    itself over by 2^n repeatedly. However, it prevents itself from shifting if the
  shift would be greater than a 32 bit shift. This function will always work unless
  n is 32, so the returned value is set to be x if n is 32.*/
  int bits = x & ((1<<n) - 1);
  int result = bits;
  int first = n;
  int second = first<<1;
  int third = second<<1;
  int fourth = third<<1;
  int fifth = fourth<<1;
  int min = !(32 - n);
  result = result<<((first * !(first/32))) | result;
  result = result<<((second * !(second/32))) | result;
  result = result<<((third * !(third/32))) | result;
  result = result<<((fourth * !(fourth/32))) | result;
  result = result<<((fifth * !(fifth/32))) | result;
 
  min = (min<<31)>>31;
  return ~min & result | min & x;
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
  /*This function works by checking for the resulting value if x is shifted right
   by n - 1. If x is positive, then the resulting value must be zero or else n bits
  could not have contained a positive x value. If x is negative, the resulting shifted
  value must be equal to -1 (or have all 1 bits) or else n bits could not have contained
  a negative value of x.*/
  int result = x>>(n + ~0);
  return !((x>>31 & x>>(n + ~0)) ^ (~1 + 1)) | !result;
}
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
  /*This function simply multiplies the number of bytes to be moved by 8 to get the
    number of bits and shifts x right by that amount. Masking this with 0xff sets
  all other bits to 0 and returns only the specified byte value.*/
  int shifter = n<<3;
  return (x>>shifter) & 0xff;
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  /*This function tests if x-y >= 0. If the resulting sum is negative and x and y are the same sign,
   then x must be less than y. Similarly, if the result is zero, then x = y. Also, if x and y are
  not the same sign and x is negative, then x < y.*/
  int sum = x + 1 + ~y;
  int neg = (sum>>31) & 1;
  int negx = (x>>31) & 1;
  int negy = (y>>31) & 1;
  int sign = (negx^negy) & 1;
  return !sum | neg & !sign | sign & negx; 
}
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
  /*This function uses a double bang to ensure that x does not equal zero
   and an arithmetic right shift to ensure that x is not negative.*/
  return !(x>>31) & !!x;
}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
  /*This function first right shifts x by n. It then creates a bit mask to insert
   zeros by left shifting 1s equal to 31 - n. This works unless n is 0, in which case
  the original x value is returned. Otherwise, the right shifted value is anded with
  the bitmask and returned.*/
  int result = x>>n;
  int shifter = 32 + ~n;
  int bitmask = (1<<shifter) + ~0 + (1<<shifter);
  int zero = ((!n)<<31)>>31;
  result = result & bitmask;
  return result & ~zero | x & zero;
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  /*This function produces a 1 followed by 31 zeros, which is the min value. */
  return 1<<31;
}
