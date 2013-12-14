#include <assert.h>
#include <stdio.h>
#include "primes.h"
#include "utility.h"
#include "quadraticsieve.h"

int quadratic_sieve(mpz_t result, mpz_t composite)
{
  mpz_t prime;
  mpz_init(prime);
  mpz_set_ui(prime, 7);

  int res = mpz_legendre(composite, prime);

  
  
  // NOTE: mpz_primes[i] shouldn't ever be larger than the number being factored
  const size_t mpz_primes_length = primes_length;
  mpz_t mpz_primes[mpz_primes_length];

  for(size_t i = 0; i < mpz_primes_length; i++)
    {
      mpz_init(mpz_primes[i]);
      mpz_set_ui(mpz_primes[i], primes[i]);
    }

  mpz_t a, b;
  mpz_init(a);
  mpz_init(b);
  mpz_set_ui(a, 5);
  mpz_set_ui(b, 10);

  mpz_gcd(result, a, b);
  gep(result);
  return 0;
}


