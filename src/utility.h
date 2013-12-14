#ifndef __UTILITY_H__
#define __UTILITY_H__

// Stands for good enough print. The printf supplied by gmp is too
// verbose.

void gep(mpf_t n);
void gep(mpz_t n);

#endif
