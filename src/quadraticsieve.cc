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
	
      legendre = mpz_legendre(composite, mpz_primes[i]);
      if (legendre == 1)
	{
	  mpz_set(result[factor_index++], mpz_primes[i]);
	}
    }
  return factor_index;
}

size_t calculate_start(mpz_t composite)
{
  mpz_t root;
  mpz_init(root);
  mpz_sqrt(root, composite);
  size_t res = mpz_get_ui(root);
  mpz_clear(root);
  return res;
};

size_t calculate_end(mpz_t composite)
{
  mpz_t root;
  mpz_t doubled_composite;
  mpz_init(root);
  mpz_init(doubled_composite);

  mpz_mul_ui(doubled_composite, composite, 2);
  mpz_sqrt(root, doubled_composite);
  size_t res = mpz_get_ui(root);
  size_t much_more_crashes_my_machine = 100000;
  // The world is cruel !
  if(res > much_more_crashes_my_machine)
    {
      size_t s = calculate_start(composite);
      res = s + much_more_crashes_my_machine;
    }
  mpz_clear(root);
  mpz_clear(doubled_composite);

  return res;
};

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
  
  if(DEBUG)
    {
      printf("Factor base includes the following:\n");
      for(size_t i = 0; i < factor_base_length; i++)
	{
	  gep(factor_base[i]);
	}
    }

  {
    size_t start = calculate_start(composite);
    size_t end = calculate_end(composite);
  
    if(DEBUG)
      printf("Sieving range %zu-%zu\n", start, end);
    size_t sieve_length = end - start;
    mpz_t sieve[sieve_length];

    for(size_t i = 0; i < sieve_length; i++)
      {
	mpz_init(sieve[i]);
	mpz_set_ui(sieve[i], i + start);
	mpz_powm_ui(sieve[i], sieve[i], 2, composite);
      }

    if(DEBUG)
      printf("Done initializing sieve in range %zu-%zu\n", start, end);

    if(DEBUG)
      printf("Finding smooth numbers over sieve\n");

    mpz_t roots[2]; 
    size_t roots_length = 2;
    mpz_init(roots[0]);    
    mpz_init(roots[1]);    
    for(size_t i = 0; i < factor_base_length; i++)
      {
	if(mpz_cmp_ui(factor_base[i], 2) == 0)
	  {
	    roots_length = 1;
	    mpz_mod_ui(roots[0], composite, 2);
	  }
	else
	  {
	    mod_sqrt(roots[0], composite, factor_base[i]);
	    mpz_sub(roots[1], factor_base[i], roots[0]);
	    roots_length = 2;
	  }

	
      }
    
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


