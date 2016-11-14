/* 
 * CS:APP Data Lab 
 * 
 * <Cameron MacDonald - cmacdona>
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
/* Copyright (C) 1991-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
/* wchar_t uses Unicode 8.0.0.  Version 8.0 of the Unicode Standard is
   synchronized with ISO/IEC 10646:2014, plus Amendment 1 (published
   2015-05-15).  */
/* We do not support C11 <threads.h>.  */
/* 
 * evenBits - return word with all even-numbered bits set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int evenBits(void) {
  int even = 0x55;
  even = (even<<8) + even;
  even = (even<<16) + even;
  return even;
}
/* 
 * addOK - Determine if can compute x+y without overflow
 *   Example: addOK(0x80000000,0x80000000) = 0,
 *            addOK(0x80000000,0x70000000) = 1, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int addOK(int x, int y) {
  int sum = x + y;

  int xSign = x >> 31;
  int ySign = y >> 31;

  int sumSign = sum >> 31;

  /*If x and y sign are different, overflow happens. Else, check that x sign and the sum sign are the same.*/
  return !(~(xSign ^ ySign) & (xSign ^ sumSign));
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  /*Make x explicitly 1 or 0*/
  int ToF = !(!x);

  ToF = ToF << 31;
  ToF = ToF >> 31;

  /*If x was true, y is extracted and z is obliterated. Else, vice versa.*/
  return ((y & ToF) | (z & ~ToF));
}
/* 
 * absVal - absolute value of x
 *   Example: absVal(-1) = 1.
 *   You may assume -TMax <= x <= TMax
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4
 */
int absVal(int x) {
  int sign = x >> 31;

  /*Exclusive or to handle the addition if sign was positive, else sign was negative and x is flipped summed with 1*/
  return ((x ^ sign) + (1 + (~sign)));
}
/*
 * bitParity - returns 1 if x contains an odd number of 0's
 *   Examples: bitParity(5) = 0, bitParity(7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int bitParity(int x) {
  /*Split and compare second half against first half, repeat until either 1 or 0 remains*/
  x = x ^ (x << 16);
  x = x ^ (x << 8);
  x = x ^ (x << 4);
  x = x ^ (x << 2);
  x = x ^ (x << 1);
  return !(!(x>>31));
}
/* 
 * fitsShort - return 1 if x can be represented as a 
 *   16-bit, two's complement integer.
 *   Examples: fitsShort(33000) = 0, fitsShort(-32768) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int fitsShort(int x) {
  /*Check to see if first half is all zeroes or all ones. 1 if true, 0 otherwise.*/
  int check = x>>15;
  int allZ = !check;
  int allO = !(~(check));

  return (allZ | allO);
}
/* 
 * copyLSB - set all bits of result to least significant bit of x
 *   Example: copyLSB(5) = 0xFFFFFFFF, copyLSB(6) = 0x00000000
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int copyLSB(int x) {
  return ((x << 31) >> 31);

}
/* 
 * oddBits - return word with all odd-numbered bits set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 2
 */
int oddBits(void) {
  int odd;
  odd = 0xAA;
  odd = (odd<<8) + odd;
  odd = (odd<<16) + odd;
  return odd;
}
/* 
 * isGreater - if x > y  then return 1, else return 0 
 *   Example: isGreater(4,5) = 0, isGreater(5,4) = 1
 *   Legal ops:! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isGreater(int x, int y) {
  int xSign, ySign, signsSame, signsDiff;
  xSign = x >> 31;
  ySign = y >> 31;

  /*Obliterates if signs same and negative, else it checks the sign of the sum of the complement of y and x*/
  signsSame = (!(xSign ^ ySign)) & ((~y + x) >> 31);

  /*Simple case - will return 1 when signs are different*/
  signsDiff = xSign & !ySign;

  return !(signsSame | signsDiff);
}
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {

  int backHalfValid, validSmall, validBigOne, validBigTwo;
  /*Make sure back half is all zeroes*/
  backHalfValid = !((x>>16 & 0x00) & (x>>24 & 0x00));

  /*Check if matches 00110--- format*/
  validSmall = !(x>>3 ^ 0x06);

  /*Check if matches 00111000*/
  validBigOne = !(x ^ 0x38);

  /*Check if matches 00111001*/
  validBigTwo = !(x ^ 0x39);

  return backHalfValid & (validSmall | (validBigOne | validBigTwo));
}
/* 
 * leastBitPos - return a mask that marks the position of the
 *               least significant 1 bit. If x == 0, return 0
 *   Example: leastBitPos(96) = 0x20
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2 
 */
int leastBitPos(int x) {
  return (~x + 1) & x;
}
/* 
 * greatestBitPos - return a mask that marks the position of the
 *               most significant 1 bit. If x == 0, return 0
 *   Example: greatestBitPos(96) = 0x40
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 70
 *   Rating: 4 
 */
int greatestBitPos(int x) {
  int leadOne = (0x01 << 31);

  /*Make all bits to the right of GSB into 1's*/
  x = x | (x >> 1);
  x = x | (x >> 2);
  x = x | (x >> 4);
  x = x | (x >> 8);
  x = x | (x >> 16);

  /*Extract GSB*/
  x = x & ((~x >> 1) ^ leadOne);
  return x;
}
/* 
 * float_abs - Return bit-level equivalent of absolute value of f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument..
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_abs(unsigned uf) {
  unsigned tMax, tMin, trueVal;
  tMax = 0x7FFFFFFF;
  tMin = 0x7F800001;
  trueVal = uf & tMax;

  /*Check to see if uf is already positive, return calculated value otherwise*/
  if (trueVal >= tMin){
    return uf;
  } else {
    return trueVal;
  }
}
/* 
 * float_f2i - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int float_f2i(unsigned uf) {
  unsigned sign, exp, frac, bias, E;
  sign = uf >> 31;
  exp = (uf >> 23) & 0xFF;
  frac =(uf & 0x7FFFFF);
  bias = 0x7F;

  /*Check if infinity or NaN*/
  if (exp == 0xFF) return 0x80000000;

  /*Make sure exp isn't less than bias. If it is, value is zero.*/
  if (exp < bias) return 0x0;

  E = exp - bias;

  /*E is too large for any other value.*/
  if (E > 31) return 0x80000000;

  /*Shift bits to achieve appropriate integer value*/
  if (E > 22) 
  {
    frac = frac << (E - 23);
  } else {
    frac = frac >> (23 - E);
  }

  frac += 1 << E;

  /*If negative, make integer value negative.*/
  if (sign) {
    frac = -frac;
  }
  
  return frac;
}
/* 
 * float_half - Return bit-level equivalent of expression 0.5*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_half(unsigned uf) {
  int expMask, signMask, fracMask, S, frac, exp, tmp, oneMask;
  /*Create a bunch of masks to check for vital parts of float binary. Make a mask for extracting values from frac.*/
  tmp = 0;
  expMask = 0x7F800000;
  signMask = 0x80000000;
  fracMask = 0x007FFFFF;
  oneMask = 0x00FFFFFF;
  exp = (uf & expMask) >> 23;
  frac = uf & fracMask;
  /*Grab sign from uf*/
  S = uf & signMask;

  /*NaN or infinity*/
  if (exp == 0xFF) return uf;

  /*Denormalized*/
  if (exp == 0 || exp == 1) 
  {
    tmp = (uf & oneMask) >> 1;

    if ((frac & 3) == 3)
    {
      tmp++;
    }
    return S | tmp;
  
}
  /*Assume normalized*/
  return S | ((exp - 1) << 23) | frac;
}
