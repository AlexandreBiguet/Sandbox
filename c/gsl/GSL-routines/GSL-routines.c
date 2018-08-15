#include "GSL-routines.h"
/*



*/
/*======================================================================
========================================================================
                             RANDOM NUMBER GENERATOR ROUTINES
========================================================================
======================================================================*/
/*----------------------------------------------------------------------
PRELIMINARY REMARK :
````````````````````
        The use of a gsl random number generator (RNG) is the following :

        1) declaration of a type of genrator
        const gsl_rng_type *T;

        2) declaration of an instance of a generator
        gsl_rng *r;

        3) choice for the generator
        T = gsl_rng_mt19937;
        r = gsl_rng_alloc(T);

        4) initialsiation of the instance with a determined seed
        gsl_rng_set(r,seed);

        5) having a random number
        double rand = gsl_rng_uniform(r);

        6) deallocate the instance.
        gsl_rng_free(r);

It not possible to write a routine that contains all the previous steps
because of the seed choice.
Since this routine would create an instance of a generator, initialize it
with the seed, deallocate the instance and return a random number, each time
the routine is called, a new instance of the same T type is created with the
same seed. Conclusion, the returned number is each time the same !!

The way of doing is the following :

        A routine returns an instance of a given T type, and a given seed.
        This routine must be called once time a the begenning of the program

        A routine take the created instance and returns a random number

        At the end of the program a routine deallocate the instance.
----------------------------------------------------------------------*/
gsl_rng *GSLinitran_mt19(unsigned long int seed) {
  const gsl_rng_type *T;
  gsl_rng *r;
  T = gsl_rng_mt19937;
  r = gsl_rng_alloc(T);
  gsl_rng_set(r, seed);
  return r;
}
/*----------------------------------------------------------------------
----------------------------------------------------------------------*/
gsl_rng *GSLinitran_lux1(unsigned long int seed) {
  const gsl_rng_type *T;
  gsl_rng *r;
  T = gsl_rng_ranlxd1;
  r = gsl_rng_alloc(T);
  gsl_rng_set(r, seed);
  return r;
}
/*----------------------------------------------------------------------
----------------------------------------------------------------------*/
gsl_rng *GSLinitran_lux2(unsigned long int seed) {
  const gsl_rng_type *T;
  gsl_rng *r;
  T = gsl_rng_ranlxd2;
  r = gsl_rng_alloc(T);
  gsl_rng_set(r, seed);
  return r;
}
/*----------------------------------------------------------------------
----------------------------------------------------------------------*/
gsl_rng *GSLinitran_taus(unsigned long int seed) {
  const gsl_rng_type *T;
  gsl_rng *r;
  T = gsl_rng_taus2;
  r = gsl_rng_alloc(T);
  gsl_rng_set(r, seed);
  return r;
}
/*----------------------------------------------------------------------
----------------------------------------------------------------------*/
double GSLran(gsl_rng *r) {
  double rand = gsl_rng_uniform(r);
  return rand;
}
/*----------------------------------------------------------------------
----------------------------------------------------------------------*/
double GSLdran(gsl_rng *r, double min, double max) {
  if (max > 4294967295) {
    printf(
        "/n max must be < 4294967295 in '%s' "
        " random number generator \n",
        gsl_rng_name(r));
  }
  double rand = min + (max - min) * gsl_rng_uniform(r);
  return rand;
}
/*----------------------------------------------------------------------
----------------------------------------------------------------------*/
void GSLdealran(gsl_rng *r) { gsl_rng_free(r); }

/*======================================================================
========================================================================
        RANDOM NUMBER DISTRIBUTION ROUTINES
========================================================================
======================================================================*/

/*======================================================================
        G A U S S I A N     D I S T R I B U T I O N
======================================================================*/

void GSLgauss_dist(double *tgaus, unsigned long int seed, int nbpts,
                   double mean, double sigma) {
  /*----------------------------------------------------------------------
          This routine 'return' an array tgaus[0,...,nbpts], of nbpts random
          numbers that verify a gaussian distribution of mean 'mean' and
          variance 'sigma'.
          The random numbers are generated using GSLinitran_mt19(seed) routine.

          Algorithm used : Box-Muller  (same algo in NR_dist_gaus)
  ----------------------------------------------------------------------*/
  if (nbpts < 0) {
    error("nbpts must be > 0 in GSLgauss_dist routine");
  }
  if (sigma < 0) {
    error("sigma must be > 0 in GSLgauss_dist routine");
  }
  gsl_rng *r;
  r = GSLinitran_mt19(seed);
  for (int i = 0; i < nbpts; i++) {
    tgaus[i] = mean + gsl_ran_gaussian(r, sigma);
  }
  GSLdealran(r);
}
/*----------------------------------------------------------------------
----------------------------------------------------------------------*/
void GLSgauss_zig_dist(double *tgaus, unsigned long int seed, int nbpts,
                       double mean, double sigma) {
  /*----------------------------------------------------------------------
          This routine 'returns' an array tgaus[0,...,nbpts], of nbpts random
          numbers that verify a gaussian distribution of mean 'mean' and
          variance 'sigma'.
          The random numbers are generated using GSLinitran_mt19(seed) routine.

          Algorithm used : Marsaglia-Tsang ziggurat

          Remark : Le nom de cette méthode provient du fait qu'elle couvre
          la densité de la loi avec des segments rectangulaires empilés
          par ordre de taille décroissant, ce qui ressemble donc à une
          ziggourat (Wiki). (un ziggourat est un édifice religieux)
  ----------------------------------------------------------------------*/
  if (nbpts < 0) {
    error("nbpts must be > 0 in GLSgauss_zig_dist routine");
  }
  if (sigma < 0) {
    error("sigma must be > 0 in GLSgauss_zig_dist routine");
  }
  gsl_rng *r;
  r = GSLinitran_mt19(seed);
  for (int i = 0; i < nbpts; i++) {
    tgaus[i] = mean + gsl_ran_gaussian_ziggurat(r, sigma);
  }
  GSLdealran(r);
}
/*----------------------------------------------------------------------
----------------------------------------------------------------------*/
double GSLgauss_pdf(double x, double sigma) {
  /*----------------------------------------------------------------------
          This function computes the probability density p(x) at x
          for a Gaussian distribution with standard deviation sigma.
  ----------------------------------------------------------------------*/
  return gsl_ran_gaussian_pdf(x, sigma);
}
//
/*======================================================================
        G A U S S I A N   T A I L   D I S T R I B U T I O N
======================================================================*/
//
void GSLgauss_tail_dist(double *tab, unsigned long int seed, int nbpts,
                        double min, double mean, double sigma) {
  /*----------------------------------------------------------------------
          This routine 'returns' an array tab[0,...,nbpts], of nbpts random
          numbers that verify a gaussian tail distribution of mean 'mean' and
          variance 'sigma'.

          This function provides random variates from the upper tail of a
          Gaussian distribution with standard deviation sigma.
          The values returned are larger than the lower limit min,
          which must be positive.
  ----------------------------------------------------------------------*/
  if (nbpts < 0) {
    error("nbpts must be > 0 in GSLgauss_tail_dist routine");
  }
  if (sigma < 0) {
    error("sigma must be > 0 in GSLgauss_tail_dist routine");
  }
  gsl_rng *r;
  r = GSLinitran_mt19(seed);
  for (int i = 0; i < nbpts; i++) {
    tab[i] = mean + gsl_ran_gaussian_tail(r, min, sigma);
  }
  GSLdealran(r);
}
/*----------------------------------------------------------------------
----------------------------------------------------------------------*/
double GSLgauss_tail_pdf(double x, double min, double sigma) {
  return gsl_ran_gaussian_tail_pdf(x, min, sigma);
}

/*======================================================================
        B I V A R I A T E   G A U S S I A N    D I S T R I B U T I O N
======================================================================*/
//
void GSLbiv_gauss_dist(double *xtab, double *ytab, unsigned long int seed,
                       int nbpts, double mean_x, double mean_y, double sigma_x,
                       double sigma_y, double corr) {
  /*----------------------------------------------------------------------
          This routine 'returns' two arrays xtab[0,...,nbpts], ytab[0,...,nbpts]
          of nbpts random numbers following two gaussian distribution correlated
          using -1 < corr < 1

          This function generates a pair of correlated Gaussian variates,
          correlation coefficient corr and standard deviations sigma_x and
          sigma_y in the x and y directions.
  ----------------------------------------------------------------------*/
  if (nbpts < 0) {
    error("nbpts must be > 0 in GSLbiv_gauss_dist routine");
  }
  if (sigma_x < 0. || sigma_y < 0.) {
    error("sigma must be > 0 in GSLbiv_gauss_dist routine");
  }
  if (corr > 1. || corr < -1.) {
    error("correlation coefficient must be -1 < corr < 1 ");
  }
  gsl_rng *r;
  r = GSLinitran_mt19(seed);
  for (int i = 0; i < nbpts; i++) {
    double ranx, rany;
    gsl_ran_bivariate_gaussian(r, sigma_x, sigma_y, corr, &ranx, &rany);
    xtab[i] = mean_x + ranx;
    ytab[i] = mean_y + rany;
  }
  GSLdealran(r);
}
/*----------------------------------------------------------------------
----------------------------------------------------------------------*/
double GSLbiv_gauss_pdf(double x, double y, double sigma_x, double sigma_y,
                        double corr) {
  return gsl_ran_bivariate_gaussian_pdf(x, y, sigma_x, sigma_y, corr);
}

/*======================================================================
        E X P O N E N T I A L    D I S T R I B U T I O N
======================================================================*/
//
void GSLexp_dist(double *tab, unsigned long int seed, int nbpts, double mean) {
  /*----------------------------------------------------------------------
          This routine 'returns' an array tab[0,...,nbpts] of nbpts random
          numbers following an exponential distribution of mean mean.
  ----------------------------------------------------------------------*/
  if (nbpts < 0) {
    error("nbpts must be > 0 in GSLexp_dist routine");
  }
  gsl_rng *r;
  r = GSLinitran_mt19(seed);
  for (int i = 0; i < nbpts; i++) {
    tab[i] = gsl_ran_exponential(r, mean);
  }
  GSLdealran(r);
}
/*----------------------------------------------------------------------
----------------------------------------------------------------------*/
double GSLexp_pdf(double x, double mean) {
  return gsl_ran_exponential_pdf(x, mean);
}

/*======================================================================
        L A P L A C E   D I S T R I B U T I O N
======================================================================*/
//
void GSLlaplace_dist(double *tab, unsigned long int seed, int nbpts,
                     double width) {
  /*----------------------------------------------------------------------
          This routine 'returns' an array tab[0,...,nbpts] of nbpts random
          numbers following an exponential distribution of mean mean.
  ----------------------------------------------------------------------*/
  if (nbpts < 0) {
    error("nbpts must be > 0 in GSLlaplace_dist routine");
  }
  if (width < 0.) {
    error("width must be > 0. in GSLlaplace_dist routine");
  }
  gsl_rng *r;
  r = GSLinitran_mt19(seed);
  for (int i = 0; i < nbpts; i++) {
    tab[i] = gsl_ran_laplace(r, width);
  }
  GSLdealran(r);
}
/*----------------------------------------------------------------------
----------------------------------------------------------------------*/
double GSLlaplace_pdf(double x, double width) {
  return gsl_ran_laplace_pdf(x, width);
}
