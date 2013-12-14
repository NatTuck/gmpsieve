#include <assert.h>
#include <gmp.h>
#include <limits.h>
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include "fermatfactor.h"
#include "utility.h"

#define BUFFLEN 1024
#define DEBUG 1
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
  long long n; 
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
    
    {// atoll is garbage. Try to find strtonum from FreeBSD
      n = atoll(input); 
    }
  }
  printf("%lld\n", n);
  return 0;
}
#endif
