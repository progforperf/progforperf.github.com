#include <inttypes.h>
//#include <stdio.h>
uint64_t fib(uint64_t n)
{
if (n < 2) { return n; }
return (fib(n-1) + fib(n-2));
}

