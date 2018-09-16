
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
