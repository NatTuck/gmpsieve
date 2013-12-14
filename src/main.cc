#include <assert.h>
#include <gmp.h>
#include <limits.h>
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include "fermatfactor.h"
#include "quadraticsieve.h"
#include "utility.h"

#define BUFFLEN 1024
#define FERMAT 0 
#define QUADRATICSIEVENOGMP 1
	  
#if FERMAT == 1
int main(int argc, char *argv[])
{
  int err;

  char input[BUFFLEN];
  mpz_t n; 
  { // Read input and float
    if (DEBUG)
      printf("Enter your number: ");

    fgets(input, BUFFLEN, stdin);
    for(size_t i = 0; i < BUFFLEN; i++)
      {
	if ('\n' == input[i])
	  {
	    input[i] = '\0';
	    break;
	  }
      }

    err = mpz_init_set_str(n, input, 10);
    assert (err == 0);

  }
  mpz_t result;
  mpz_init(result);
  mpz_fermat(result, n);
  return 0;
}
#endif
#if QUADRATICSIEVENOGMP == 1
int main(int argc, char *argv[])
{
  char input[BUFFLEN];
  mpz_t n; 
  { // Initialize n, and read input
	  
    if (DEBUG)
      printf("Enter your number: ");

    fgets(input, BUFFLEN, stdin);
    for(size_t i = 0; i < BUFFLEN; i++)
      {
	if ('\n' == input[i])
	  {
	    input[i] = '\0';
	    break;
	  }
      }
    
    { // atoll is garbage. Try to find strtonum from FreeBSD
      int err = mpz_init_set_str(n, input, 10);
      assert(err == 0);
    }
  }
  { // Factor using the quadratic sieve and print a factor,
    // provided that there is no error
	  
    mpz_t result;
    mpz_init(result);
    {
      int err = 0;
      err = quadratic_sieve(result, n);
      assert(err == 0);
    }
    gep(result);
    mpz_clear(result);
  }
  mpz_clear(n);
  return 0;
}
#endif
