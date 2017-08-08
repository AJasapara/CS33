/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
	/* uses the fact that -0 is still 0 to differentiate
	from other numbers, and return appropriate value. */
  return ((((~x) +1) | x)>>31) +1;
} 


/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
	/* Forms 5 numbers with bit patterns 01010, 011011, etc. to
	find location of 1s, right shift them, and then add the values. 
	Thus, the final sum is formed at the very right. */
  int first = (0x55 << 8) + 0x55;
  int second = (0x33 << 8) + 0x33;
  int third = (0x0F << 8) + 0x0F;
  int fourth = (0x00 << 8) + 0xFF;
  int fifth = (0x00 << 24) + (fourth << 8) + 0xFF; // forms 0000FFFF
  first = (first << 16) + first; // forms 0x55555555
  second = (second << 16) + second; // forms 0x33333333
  third = (third << 16) + third; // forms 0F0F0F0F
  fourth = (fourth << 16) + fourth; // forms 00FF00FF
  x = (x & first) + ((x >> 1) & first);
  x = (x & second) + ((x >> 2) & second);
  x = (x & third) + ((x >> 4) & third);
  x = (x & fourth) + ((x >> 8) & fourth);
  x = (x & fifth) + ((x >> 16) & fifth);
  return x;
}


/* 
 * bitOr - x|y using only ~ and & 
 *   Example: bitOr(6, 5) = 7
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitOr(int x, int y) {
	/* Uses DeMorgan's theorems and the complement
	to replicate the behavior of or. */
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
	/* Creates a number with 1s in the low-order n bits, and 0 elsewhere.
	Proceeds to use this number shifting to the left 5 times (because 2^5 = 32),
	and thus repeating the number until the end. */
	int ones = ~((1 << 31) >> (32 - n) << 1);  // 0000000011111 (times n)
	x = x & ones;
	x = ((x<<n) & ~ones) + x;
	ones = (ones << n) | ones;
	n = n << 1;
	x = ((x<<n) & ~ones) + x;
	ones = (ones << n) | ones;
	n = n << 1;
	x = ((x<<n) & ~ones) + x;
	ones = (ones << n) | ones;
	n = n << 1;
	x = ((x<<n) & ~ones) + x;
	ones = (ones << n) | ones;
	n = n << 1;
	x = ((x<<n) & ~ones) + x;
  return x;
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
	/* Uses the sign to remove left-most 1 if it exists, and then
	shifts n-1 to the right. If only 0s remain, the bits fit, and
	if not then the bits don't fit. */
	int sign = x >> 31;
	x = x ^ sign;
	x = x >> (n + ~0);
  return !x;
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
	/* Changes n from hex to binary, then shifts to the right
	to remove unneeded bits, and to the left for the same reason.
	Shifts back to the right and returns only right-most byte. */
	n = n << 3;
  return (((x >> n) << 24) >> 24) & 0xFF;
} 


/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
	/* Gets each integer's sign to determine if signs are same. If
	they're not then changes signDif into 0 (to return 0) or 2 (to return 1).
	If signs are same, calculates absolute difference (no overflow) and returns
	1 is positive, and 0 if negative.*/
	int xSign = x>>31;
	int ySign = y>>31;
	int signDif = ySign + ~xSign + 2; // if 0, x is pos, y is neg, if 2, x is neg, y is pos, if 1, signs are same
	int diff = 0;
	x = x ^ (xSign<<31); // make both numbers into positive
	y = y ^ (ySign<<31);
	diff = (y + ~x + 1) >> 31; // if positive, and signs same, returns 0, if negative and signs same, returns -1
	diff = diff + signDif; // signs same: 1, 0; signDif is 2: 2, 1; signDif is 0, get 0, -1 
 	return !!(signDif & (~diff+1)); // if difference is positive/equal, returns 0, if dif is negative returns 1
}


/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
	/* Shifts x to get 0 if positive, and 1 if negative. 
	adds 1 if x is zero (putting it in the negative case),
	and bangs the result to return the opposite. */
	int zero = !x;
  return !(((x >> 31)&1) + zero);
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
	/*Shifts ans right, and ands it with 0s for the left most n bits,
	to change an arithmetic shift into a logical shift. */
	int ans = x >> n;
	int zeros = ~((~1) << (32 + ~n));
  return ans & zeros;
}


/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
	/* Shifts 1 to the right to get 0x80000000, which 
	is the minimum two's complement integer. */
  return 1<<31;
} 
