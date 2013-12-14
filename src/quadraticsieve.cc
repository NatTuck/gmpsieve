#include <assert.h>
#include <stdio.h>

#include "utility.h"
#include "quadraticsieve.h"

long long legendre_symbol(long long a, long long p)
{
  return (a ^ ((p - 1) / 2)) % p;
}

void quadratic_sieve(long long& result, long long input, int& err)
{
  printf("%lld", legendre_symbol(input, 2));
}


