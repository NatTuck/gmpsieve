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

// find x^2 = q mod n
// return
// -1 q is quadratic non-residue mod n
//  1 q is quadratic residue mod n
//  0 q is congruent to 0 mod n
//
int mod_sqrt(mpz_t x,mpz_t q,mpz_t n)
// copied exactly from
// http://permalink.gmane.org/gmane.comp.lib.gmp.general/4322
{
  int                        leg;
  mpz_t                        tmp,ofac,nr,t,r,c,b;
  unsigned int            mod4;
  mp_bitcnt_t                twofac=0,m,i,ix;

  mod4=mpz_tstbit(n,0);
  if(!mod4) // must be odd
    return 0;

  mod4+=2*mpz_tstbit(n,1);

  leg=mpz_legendre(q,n);
  if(leg!=1)
    return leg;

  mpz_init_set(tmp,n);

  if(mod4==3) // directly, x = q^(n+1)/4 mod n
    {
      mpz_add_ui(tmp,tmp,1UL);
      mpz_tdiv_q_2exp(tmp,tmp,2);
      mpz_powm(x,q,tmp,n);
      mpz_clear(tmp);
    }
  else // Tonelli-Shanks
    {
      mpz_inits(ofac,t,r,c,b,NULL);

      // split n - 1 into odd number times power of 2 ofac*2^twofac
      mpz_sub_ui(tmp,tmp,1UL);
      twofac=mpz_scan1(tmp,twofac); // largest power of 2 divisor
      if(twofac)
	mpz_tdiv_q_2exp(ofac,tmp,twofac); // shift right

      // look for non-residue
      mpz_init_set_ui(nr,2UL);
      while(mpz_legendre(nr,n)!=-1)
	mpz_add_ui(nr,nr,1UL);

      mpz_powm(c,nr,ofac,n); // c = nr^ofac mod n

      mpz_add_ui(tmp,ofac,1UL);
      mpz_tdiv_q_2exp(tmp,tmp,1);
      mpz_powm(r,q,tmp,n); // r = q^(ofac+1)/2 mod n

      mpz_powm(t,q,ofac,n);
      mpz_mod(t,t,n); // t = q^ofac mod n

      if(mpz_cmp_ui(t,1UL)!=0) // if t = 1 mod n we're done
	{
	  m=twofac;
	  do
	    {
	      i=2;
	      ix=1;
	      while(ix<m)
		{
		  // find lowest 0 < ix < m | t^2^ix = 1 mod n
		  mpz_powm_ui(tmp,t,i,n); // repeatedly square t
		  if(mpz_cmp_ui(tmp,1UL)==0)
		    break;
		  i<<=1; // i = 2, 4, 8, ...
		  ix++; // ix is log2 i
		}
	      mpz_powm_ui(b,c,1<<(m-ix-1),n); // b = c^2^(m-ix-1) mod n
	      mpz_mul(r,r,b);
	      mpz_mod(r,r,n); // r = r*b mod n
	      mpz_mul(c,b,b);
	      mpz_mod(c,c,n); // c = b^2 mod n
	      mpz_mul(t,t,c);
	      mpz_mod(t,t,n); // t = t b^2 mod n
	      m=ix;
	    }while(mpz_cmp_ui(t,1UL)!=0); // while t mod n != 1
	}
      mpz_set(x,r);
      mpz_clears(tmp,ofac,nr,t,r,c,b,NULL);
    }

  return 1;
}
