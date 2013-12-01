#include <assert.h>
#include <mpi.h>
#include <gmp.h>
#include <stdio.h>

#define BUFFLEN 1024
#define DEBUG 1

typedef unsigned int uint;

void mpz_fermat(mpz_t result, mpz_t input);
void gep(mpf_t n);
void gep(mpz_t n);

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
	    input[i] == '\0';
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

void mpz_fermat(mpz_t result, mpz_t input)
 // PRECONDITION:                             
 // result has been initialized with mpz_init 
 // input is non-negative and odd             
 // POSTCONDITION:                            
 // result contains a number that divides input
{
  mpz_t a, b; // a and b should be freed. 
  
  {
    mpz_init(a);
    { // a = ceil(sqrt(n))
      mpz_sub_ui(a, input, 1);
      mpz_sqrt(a, a);
      mpz_add_ui(a, a, 1);
    }    
    { 
      mpz_init(b);

      { // b = a^2 - input
	mpz_mul(b, a, a); 
	mpz_sub(b, b, input);
      }
      while(!mpz_perfect_square_p(b))
	{
	  mpz_add_ui(a, a, 1);
	  { // b = a^2 - input
	    mpz_mul(b, a, a); 
	    mpz_sub(b, b, input);
	  }
	}
    }
  }
  mpz_sqrt(result, b);
  mpz_sub(result, a, result);

  mpz_clear(a);
  mpz_clear(b);
  if(DEBUG)
    {
      printf("In mpz_fermat(mpz_t): ");
      gep(result);
    }
}

void gep(mpf_t n)
{ // Stands for good enough print. The printf supplied by gmp is too
  // verbose.
  const uint precision = 6;
  gmp_printf ("%.*Ff\n", precision, n);
}

void gep(mpz_t n)
{
  gmp_printf ("%Zd\n", n);
}
