#include <limits.h>
int saturating_add(int x, int y){
int sum = x+y;
int w = (sizeof(int) << 3)-1;
int signX = (x>>w) & 1; // 1 if negative, 0 if positive
int signY = (y>>w) & 1;
int signSum = (sum>>w) & 1;
int same = !(signX ^ signY); // 0 if different, 1 if same
int overflow = (signSum ^ signX) & same; // 1 if overflow
overflow = ~overflow+1;
int overflowVal = overflow & (INT_MAX + signX);
sum = ~overflow & sum;
return sum ^ overflowVal;
}
