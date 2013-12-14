#include <assert.h>
#include <stdio.h>
#include "primes.h"
#include "utility.h"
#include "quadraticsieve.h"

size_t generate_factor_base(mpz_t result[], mpz_t mpz_primes[], size_t mpz_primes_length, mpz_t composite)
{
  int legendre = 0;
  size_t factor_index = 0;
  for(size_t i = 0; i < mpz_primes_length; i++)
    {
      if (mpz_cmp(mpz_primes[i], composite) != -1)
	{
	  return factor_index;
	}
	
      legendre = mpz_legendre(mpz_primes[i], composite);
      if (legendre == 1)
	{
	  mpz_set(result[factor_index++], mpz_primes[i]);
	}
    }
  return factor_index;
}

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

  mpz_t factor_base[mpz_primes_length];
  for(size_t i = 0; i < mpz_primes_length; i++)
    {
      mpz_init(factor_base[i]);
    }

  const size_t factor_base_length = generate_factor_base(factor_base, mpz_primes, mpz_primes_length, composite);
    
  for(size_t i = 0; i < factor_base_length; i++)
    gep(factor_base[i]);
  
  mpz_t a, b;
  mpz_init(a);
  mpz_init(b);
  mpz_set_ui(a, 5);
  mpz_set_ui(b, 10);

  mpz_gcd(result, a, b);
  gep(result);
  return 0;
}


