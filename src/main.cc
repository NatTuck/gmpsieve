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
    for(int i = 0; i < BUFFLEN; i++)
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
  long long n = 0; 
  { // Read input and float
	  
    if (DEBUG)
      printf("Enter your number: ");

    fgets(input, BUFFLEN, stdin);
    for(int i = 0; i < BUFFLEN; i++)
      {
	if ('\n' == input[i])
	  {
	    input[i] = '\0';
	    break;
	  }
      }
    
    { // atoll is garbage. Try to find strtonum from FreeBSD
      n = atoll(input); 
      
    }
  }
  { // Factor using the quadratic sieve and print a factor,
    // provided that there is no error
	  
    long long result = 0;
    int err = 0;
    quadratic_sieve(result, n, err);
    printf("%lld\n", result);
  }
  return 0;
}
#endif
