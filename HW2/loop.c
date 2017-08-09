long loop (long x, int n)
{
	long result = 0;
	long mask;
	for (mask = 1; mask != 0; mask = mask << (n & 0xFF) ) {
		result |= (x & mask);
	}
	return result;
}

/* Answers to the Homework:
A. Registers that Hold Program Values
%rdi = x
%rsi = %rcx = n
%rax = result
%rdx = mask

B. Initial Values
result: 0
mask: 1

C. Test Condition for Mask
mask != 0

D. How Mask is Updated
In Assembly:
salq %cl, %rdx
In C, this means: 
mask << (n & 0xFF)

E. How Result is Updated
In Assembly:
andq %rdx, %r8
orq %r8, %rax
In C, this means:
result |= mask & x

F. See Above
*/