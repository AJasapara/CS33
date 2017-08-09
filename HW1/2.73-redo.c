#include <limits.h>
int saturating_add(int x, int y){
int sum;
int overflow = __builtin_add_overflow(x,y,&sum);
overflow = ~overflow+1;
int overflowVal = overflow & (INT_MAX + ((x>>31) & 1));
sum = ~overflow & sum;
return sum ^ overflowVal;
}
