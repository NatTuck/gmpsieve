#include <assert.h>
#include <mpi.h>
#include <gmp.h>
#include <stdio.h>

#include "utility.h"
#include "fermatfactor.h"


#define DEBUG 1

typedef unsigned int uint;




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


