#include <assert.h>
#include <stdio.h>

#include "utility.h"
#include "quadraticsieve.h"



int quadratic_sieve(mpz_t result, mpz_t composite)
{
  mpz_t prime;
  mpz_init(prime);
  mpz_set_ui(prime, 7);

  int res = mpz_legendre(composite, prime);
  
  mpz_t a, b;
  mpz_init(a);
  mpz_init(b);
  mpz_set_ui(a, 5);
  mpz_set_ui(b, 10);

  mpz_gcd(result, a, b);
  gep(result);
  return 0;
}


