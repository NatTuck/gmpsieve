#include <gmp.h>

typedef unsigned int uint;

void gep(mpf_t n)
{
  const uint precision = 6;
  gmp_printf ("%.*Ff\n", precision, n);
}

void gep(mpz_t n)
{
  gmp_printf ("%Zd\n", n);
}
