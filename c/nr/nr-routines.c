#include "nr-routines.h"
/*






*/
/*======================================================================
========================================================================
========================================================================
CHAPITRE 1 : PRELIMINARIES
========================================================================
========================================================================
======================================================================*/
/*






*/
/*======================================================================
========================================================================
========================================================================
CHAPITRE 2 : SOLUTION OF LINEAR ALGEBRAIC EQUATIONS
========================================================================
========================================================================
======================================================================*/
/*






*/
/*======================================================================
========================================================================
========================================================================
CHAPITRE 3 : INTERPOLATION AND EXTRAPOLATION
========================================================================
========================================================================
======================================================================*/
/*






*/
/*======================================================================
========================================================================
========================================================================
CHAPITRE 4 : INTEGRATION OF FUNCTIONS
========================================================================
========================================================================
======================================================================*/
/*






*/
/*======================================================================
========================================================================
========================================================================
CHAPITRE 5 : EVALUATION OF FUNCTIONS
========================================================================
========================================================================
======================================================================*/
/*






*/
/*======================================================================
========================================================================
========================================================================
CHAPITRE 6 : SPECIAL FUNCTIONS
========================================================================
========================================================================
======================================================================*/
/*






*/
double gammq(double a, double x) {
  /*======================================================================
          Routine adapted from gammq in Numerical Recipies C
          ---------------------------------------------------

          Returns the incomplete gamma function P(a,x).

  ======================================================================*/
  double gamser, gammcf, gln;

  if (x < 0.0 || a <= 0.0) {
    printf("\n Invalid arguments in routine gammq \nEXIT\n");
    exit(1);
  }
  if (x < (a + 1.0)) {
    gser(&gamser, a, x, &gln);
    return 1.0 - gamser;
  } else {
    gcf(&gammcf, a, x, &gln);
    return gammcf;
  }
}
/*






*/
void gcf(double *gammcf, double a, double x, double *gln) {
  /*======================================================================
          Routine adapted from gcf in Numerical Recipies C
          ---------------------------------------------------

          Returns the incomplete gamma function Q(a, x) evaluated by its
          continued fraction represen- tation as gammcf.
          Also returns lnΓ(a) as gln.

  ======================================================================*/
  int ITMAX = 100;
  double EPS = 3.0e-7;
  double FPMIN = 1.0e-30;
  int i;
  double an, b, c, d, del, h;

  *gln = gammln(a);
  b = x + 1.0 - a;
  c = 1.0 / FPMIN;
  d = 1.0 / b;
  h = d;
  for (i = 1; i <= ITMAX; i++) {
    an = -i * (i - a);
    b += 2.0;
    d = an * d + b;
    if (fabs(d) < FPMIN) d = FPMIN;
    c = b + an / c;
    if (fabs(c) < FPMIN) c = FPMIN;
    d = 1.0 / d;
    del = d * c;
    h *= del;
    if (fabs(del - 1.0) < EPS) break;
  }
  if (i > ITMAX) {
    printf("\n a too large, ITMAX too small in gcf routine \n EXIT \n");
    exit(1);
  }
  *gammcf = exp(-x + a * log(x) - (*gln)) * h;
}
/*






*/
void gser(double *gamser, double a, double x, double *gln) {
  /*======================================================================
          Routine adapted from gser in Numerical Recipies C
          ---------------------------------------------------

          Returns the incomplete gamma function P (a, x) evaluated by its
          series representation as gamser. Also returns lnΓ(a) as gln.

  ======================================================================*/
  int ITMAX = 100;
  double EPS = 3.0e-7;
  int n;
  double sum, del, ap;

  *gln = gammln(a);
  if (x <= 0.0) {
    if (x < 0.0) {
      printf("\n x less than 0 in routine gser \n EXIT \n");
      exit(1);
    }
    *gamser = 0.0;
    return;
  } else {
    ap = a;
    del = sum = 1.0 / a;
    for (n = 1; n <= ITMAX; n++) {
      ++ap;
      del *= x / ap;
      sum += del;
      if (fabs(del) < fabs(sum) * EPS) {
        *gamser = sum * exp(-x + a * log(x) - (*gln));
        return;
      }
    }
    printf("\n a too large, ITMAX too small in routine gser \n EXIT \n");
    exit(1);
    return;
  }
}
/*






*/
double gammln(double xx) {
  /*======================================================================
          Routine adapted from gammln in Numerical Recipies C
          ---------------------------------------------------

          Returns the value ln[Γ(xx)] for xx > 0.

  ======================================================================*/

  double x, y, tmp, ser;
  static double cof[6] = {76.18009172947146,     -86.50532032941677,
                          24.01409824083091,     -1.231739572450155,
                          0.1208650973866179e-2, -0.5395239384953e-5};
  int j;

  y = x = xx;
  tmp = x + 5.5;
  tmp -= (x + 0.5) * log(tmp);
  ser = 1.000000000190015;
  for (j = 0; j <= 5; j++) ser += cof[j] / ++y;
  return -tmp + log(2.5066282746310005 * ser / x);
}
/*






*/
/*======================================================================
========================================================================
========================================================================
CHAPITRE 7 : RANDOM NUMBERS
========================================================================
========================================================================
======================================================================*/
/*






*/
double ran0(int *idum) {
  /*======================================================================
          Routine adapted from ran0 in Numerical Recipies C
          ---------------------------------------------------

          “Minimal” random number generator of Park and Miller.
          Returns a uniform random deviate between 0.0 and 1.0.
          Set or reset idum to any integer value (except the unlikely value
  MASK) to initialize the sequence; idum must not be altered between calls for
  successive deviates in a sequence.
  ======================================================================*/
  //
  int k;
  double ans;
  int IA, IM, IQ, IR, MASK;
  double AM;
  IA = 16807;
  IM = 2147483647;
  AM = (1.0 / IM);
  IQ = 127773;
  IR = 2836;
  MASK = 123459876;
  //
  *idum ^= MASK;
  k = (*idum) / IQ;
  *idum = IA * (*idum - k * IQ) - IR * k;
  if (*idum < 0) {
    *idum += IM;
  }
  ans = AM * (*idum);
  *idum ^= MASK;
  return ans;
}
/*






*/
double ran1(int *idum) {
  /*======================================================================
          Routine adapted from ran1 in Numerical Recipies C
          ---------------------------------------------------

          “Minimal” random number generator of Park and Miller with
          Bays-Durham shuffle and added safeguards.
          Returns a uniform random deviate between 0.0 and 1.0
          (exclusive of the endpoint values).
          Call with idum a negative integer to initialize;
          thereafter, do not alter idum between successive deviates in a
  sequence. RNMX should approximate the largest floating value that is less
  than 1.
  ======================================================================*/
  //
  int IA, IM, IQ, IR, NTAB;
  double AM, NDIV, EPS, RNMX;
  IA = 16807;
  IM = 2147483647;
  AM = (1.0 / IM);
  IQ = 127773;
  IR = 2836;
  NTAB = 32;
  NDIV = (1 + (IM - 1) / NTAB);
  EPS = 1.e-16;
  RNMX = (1.0 - EPS);
  //
  int j, k, iy;
  int iv[NTAB];
  double temp;
  iy = 0;
  //
  if (*idum <= 0 || !iy) {
    if (-(*idum) < 1) {
      *idum = 1;
    } else {
      *idum = -(*idum);
    }
    for (j = NTAB + 7; j >= 0; j--) {
      k = (*idum) / IQ;
      *idum = IA * (*idum - k * IQ) - IR * k;
      if (*idum < 0) {
        *idum += IM;
      }
      if (j < NTAB) {
        iv[j] = *idum;
      }
    }
    iy = iv[0];
  }
  k = (*idum) / IQ;
  *idum = IA * (*idum - k * IQ) - IR * k;
  if (*idum < 0) {
    *idum += IM;
  }
  j = iy / NDIV;
  iy = iv[j];
  iv[j] = *idum;
  if ((temp = AM * iy) > RNMX) {
    return RNMX;
  } else {
    return temp;
  }
}
/*






*/
double ran2(int *idum) {
  /*======================================================================
          Routine adapted from ran2 in Numerical Recipies C
          ---------------------------------------------------

          Long period (> 2 × 1018) random number generator of L’Ecuyer
          with Bays-Durham shuffle and added safeguards.
          Returns a uniform random deviate between 0.0 and 1.0
          (exclusive of the endpoint values).
          Call with idum a negative integer to initialize;
          thereafter, do not alter idum between successive deviates
          in a sequence.
          RNMX should approximate the largest floating value that is less
  than 1.
  ======================================================================*/
  //
  int IM1, IM2, IMM1, IA1, IA2, IQ1, IQ2, IR1, IR2, NTAB;
  double AM, NDIV, EPS, RNMX;
  IM1 = 2147483563;
  IM2 = 2147483399;
  IMM1 = (IM1 - 1);
  IA1 = 40014;
  IA2 = 40692;
  IQ1 = 53668;
  IQ2 = 52774;
  IR1 = 12211;
  IR2 = 3791;
  NTAB = 32;
  AM = (1.0 / IM1);
  NDIV = (1 + IMM1 / NTAB);
  EPS = 1.e-16;
  RNMX = (1.0 - EPS);
  //
  int j, k, idum2, iy;
  idum2 = 123456789;
  iy = 0;
  int iv[NTAB];
  double temp;
  //
  if (*idum <= 0) {
    if (-(*idum) < 1) {
      *idum = 1;
    } else {
      *idum = -(*idum);
    }
    idum2 = (*idum);
    for (j = NTAB + 7; j >= 0; j--) {
      k = (*idum) / IQ1;
      *idum = IA1 * (*idum - k * IQ1) - k * IR1;
      if (*idum < 0) {
        *idum += IM1;
      }
      if (j < NTAB) {
        iv[j] = *idum;
      }
    }
    iy = iv[0];
  }
  k = (*idum) / IQ1;
  *idum = IA1 * (*idum - k * IQ1) - k * IR1;
  if (*idum < 0) {
    *idum += IM1;
  }
  k = idum2 / IQ2;
  idum2 = IA2 * (idum2 - k * IQ2) - k * IR2;
  if (idum2 < 0) {
    idum2 += IM2;
  }
  j = iy / NDIV;
  iy = iv[j] - idum2;
  iv[j] = *idum;
  if (iy < 1) {
    iy += IMM1;
  }
  if ((temp = AM * iy) > RNMX) {
    return RNMX;
  } else {
    return temp;
  }
}
/*






*/
double ran3(int *idum) {
  /*======================================================================
          Routine adapted from ran3 in Numerical Recipies C
          ---------------------------------------------------

          Returns a uniform random deviate between 0.0 and 1.0.
          Set idum to any negative value to initialize or reinitialize
          the sequence.
  ======================================================================*/
  //
  static int inext, inextp;
  static int ma[56];
  static int iff = 0;
  int mj, mk;
  int i, ii, k;
  //
  int MBIG = 1000000000;
  int MSEED = 161803398;
  int MZ = 0;
  double FAC = (1.0 / MBIG);
  //
  if (*idum < 0 || iff == 0) {
    iff = 1;
    mj = labs(MSEED - labs(*idum));
    mj %= MBIG;
    ma[55] = mj;
    mk = 1;
    for (i = 1; i <= 54; i++) {
      ii = (21 * i) % 55;
      ma[ii] = mk;
      mk = mj - mk;
      if (mk < MZ) mk += MBIG;
      mj = ma[ii];
    }
    for (k = 1; k <= 4; k++) {
      for (i = 1; i <= 55; i++) {
        ma[i] -= ma[1 + (i + 30) % 55];
        if (ma[i] < MZ) ma[i] += MBIG;
      }
    }
    inext = 0;
    inextp = 31;
    *idum = 1;
  }
  if (++inext == 56) {
    inext = 1;
  }
  if (++inextp == 56) {
    inextp = 1;
  }
  mj = ma[inext] - ma[inextp];
  if (mj < MZ) {
    mj += MBIG;
  }
  ma[inext] = mj;
  return mj * FAC;
}
/*






*/
double ran4(int *idum) {
  /*======================================================================
          Routine adapted from ran4 in Numerical Recipies C
          ---------------------------------------------------

          Returns a uniform random deviate in the range 0.0 to 1.0,
          generated by pseudo-DES (DES- like) hashing of the 64-bit word
          (idums,idum), where idums was set by a previous call with negative
          idum. Also increments idum.
          Routine can be used to generate a random sequence by successive
          calls, leaving idum unaltered between calls; or it can randomly
          access the nth deviate in a sequence by calling with idum = n.
          Different sequences are initialized by calls with differing
          negative values of idum.
  ======================================================================*/
  //
  unsigned int irword, itemp, lword;
  static int idums = 0;
#if defined(vax) || defined(_vax_) || defined(__vax__) || defined(VAX)
  static unsigned int jflone = 0x00004080;
  static unsigned int jflmsk = 0xffff007f;
#else
  static unsigned int jflone = 0x3f800000;
  static unsigned int jflmsk = 0x007fffff;
#endif

  if (*idum < 0) {
    idums = -(*idum);
    *idum = 1;
  }
  irword = (*idum);
  lword = idums;
  psdes(&lword, &irword);
  itemp = jflone | (jflmsk & irword);
  ++(*idum);
  return (*(double *)&itemp) - 1.0;
}
/*






*/
void psdes(unsigned int *lword, unsigned int *irword) {
  /*======================================================================
          Routine adapted from ran4 in Numerical Recipies C
          ---------------------------------------------------

          “Pseudo-DES” hashing of the 64-bit word (lword,irword).
          Both 32-bit arguments are re- turned hashed on all bits.
  ======================================================================*/
  //
  unsigned int NITER = 4;
  unsigned int i, ia, ib, iswap, itmph = 0, itmpl = 0;
  static unsigned int c1[4] = {0xbaa96887L, 0x1e17d32cL, 0x03bcdc3cL,
                               0x0f33d1b2L};
  static unsigned int c2[4] = {0x4b0f3b58L, 0xe874f0c3L, 0x6955c5a6L,
                               0x55a7ca46L};

  for (i = 0; i < NITER; i++) {
    ia = (iswap = (*irword)) ^ c1[i];
    itmpl = ia & 0xffff;
    itmph = ia >> 16;
    ib = itmpl * itmpl + ~(itmph * itmph);
    *irword = (*lword) ^ (((ia = (ib >> 16) | ((ib & 0xffff) << 16)) ^ c2[i]) +
                          itmpl * itmph);
    *lword = iswap;
  }
}
/*






*/
/*======================================================================
        dran* routines return a random number between min and max using
        the ran* routine as a random nb generator
======================================================================*/
double dran0(int *idum, double min, double max) {
  double rand = min + (max - min) * ran0(idum);
  return rand;
}
double dran1(int *idum, double min, double max) {
  double rand = min + (max - min) * ran1(idum);
  return rand;
}
double dran2(int *idum, double min, double max) {
  double rand = min + (max - min) * ran2(idum);
  return rand;
}
double dran3(int *idum, double min, double max) {
  double rand = min + (max - min) * ran3(idum);
  return rand;
}
double dran4(int *idum, double min, double max) {
  double rand = min + (max - min) * ran4(idum);
  return rand;
}
/*






*/
double NR_dist_exp(int *idum) {
  /*----------------------------------------------------------------------
          Routine from Numerical Recipes in C

          this routine returns an exponentially distributed, positive,
          random deviate of unit mean, using ran3(idum) as the source
          of uniform deviates.
  ----------------------------------------------------------------------*/
  double dum;
  do {
    dum = ran3(idum);
  } while (dum == 0.0);
  return -log(dum);
}
/*






*/
double NR_dist_gauss(int *idum) {
  /*----------------------------------------------------------------------
          Routine from Numerical Recipes in C

          this routine returns a normally distributed deviate with zero mean
          and unit variance, using ran3(idum) as the source of uniform deviates.
  ----------------------------------------------------------------------*/
  static int iset = 0;
  static double gset;
  double fac, rsq, v1, v2;

  if (*idum < 0) {
    iset = 0;
  }
  if (iset == 0) {
    do {
      v1 = 2.0 * ran3(idum) - 1.0;
      v2 = 2.0 * ran3(idum) - 1.0;
      rsq = v1 * v1 + v2 * v2;
    } while (rsq >= 1.0 || rsq == 0.0);
    fac = sqrt(-2.0 * log(rsq) / rsq);
    gset = v1 * fac;
    iset = 1;
    return v2 * fac;
  } else {
    iset = 0;
    return gset;
  }
}

/*






*/
/*======================================================================
========================================================================
========================================================================
CHAPITRE 8 : SORTING
========================================================================
========================================================================
======================================================================*/
/*






*/
/*======================================================================
========================================================================
========================================================================
CHAPITRE 9 : ROOT FINDING AND NONLINEAR SETS OF EQUATIONS
========================================================================
========================================================================
======================================================================*/
/*






*/
/*======================================================================
========================================================================
========================================================================
CHAPITRE 10 : MINIMIZATION OR MAXIMIZATION OF FUNCTIONS
========================================================================
========================================================================
======================================================================*/
/*






*/
/*======================================================================
========================================================================
========================================================================
CHAPITRE 11 : EIGENSYSTEMS
========================================================================
========================================================================
======================================================================*/
/*






*/
/*======================================================================
========================================================================
========================================================================
CHAPITRE 12 : FAST FOURIER TRANSFORM
========================================================================
========================================================================
======================================================================*/
/*






*/
/*======================================================================
========================================================================
========================================================================
CHAPITRE 13 : FOURIER AND SPECTRAL APPLICATIONS
========================================================================
========================================================================
======================================================================*/
/*






*/
/*======================================================================
========================================================================
========================================================================
CHAPITRE 14 : STATISTICAL DESCRIPTION OF DATA
========================================================================
========================================================================
======================================================================*/
/*






*/
void moment(double data[], int n, double *ave, double *adev, double *sdev,
            double *var, double *skew, double *curt) {
  /*======================================================================
          Routine adapted from moment in Numerical Recipies C
          ---------------------------------------------------

          Given an array of data data[0,...,n], this routine returns
                  its mean              : ave
                  its average deviation : adev
                  its standar deviation : sdev
                  its variance          : var
                  its skewness          : skew
                  its kurtosis          : curt
  ======================================================================*/
  int j;
  double ep = 0.0, s, p;
  if (n <= 0) {
    printf("\n n must be at least 2 in moment routine \n");
    exit(1);
  }
  s = 0.0;
  for (j = 0; j < n; j++) {
    s += data[j];
  }
  *ave = s / n;
  *adev = (*var) = (*skew) = (*curt) = 0.0;
  for (j = 0; j < n; j++) {
    *adev += fabs(s = data[j] - (*ave));
    ep += s;
    *var += (p = s * s);
    *skew += (p *= s);
    *curt += (p *= s);
  }
  *adev /= n;
  *var = (*var - ep * ep / n) / (n - 1);
  *sdev = sqrt(*var);
  if (*var)  // *var != 0.
  {
    *skew /= (n * (*var) * (*sdev));
    *curt = (*curt) / (n * (*var) * (*var)) - 3.0;
  } else {
    printf("No skew/kurtosis when variance = 0 (in moment routine)");
  }
}
/*======================================================================
======================================================================*/
double average(double data[], int n) {
  /*----------------------------------------------------------------------
          This routine returns the average of the data in data[0,...,n]
  ----------------------------------------------------------------------*/
  double s = 0.;
  for (int i = 0; i < n; i++) {
    s += data[i];
  }
  return (s / (1. * n));
}
/*======================================================================
======================================================================*/
/*






*/
/*======================================================================
========================================================================
========================================================================
CHAPITRE 15 : MODELING OF DATA
========================================================================
========================================================================
======================================================================*/
/*






*/
/*======================================================================
========================================================================
========================================================================
CHAPITRE 16 : INTEGRATION OF ORDINARY DIFFERENTIAL EQUATIONS
========================================================================
========================================================================
======================================================================*/
/*






*/
/*======================================================================
========================================================================
========================================================================
CHAPITRE 17 : TWO POINT BOUNDARY VALUE PROBLEMS
========================================================================
========================================================================
======================================================================*/
/*






*/
/*======================================================================
========================================================================
========================================================================
CHAPITRE 18 : INTEGRAL EQUATIONS AND INVERSE THEORY
========================================================================
========================================================================
======================================================================*/
/*






*/
/*======================================================================
========================================================================
========================================================================
CHAPITRE 19 : PARTIAL DIFFERENTIAL EQUATIONS
========================================================================
========================================================================
======================================================================*/
/*






*/
/*======================================================================
========================================================================
========================================================================
CHAPITRE 20 : LESS-NUMERICAL ALGORITHMS
========================================================================
========================================================================
======================================================================*/
/*






*/
/*======================================================================
========================================================================
========================================================================
NRUTIL-H ROUTINES
========================================================================
========================================================================
======================================================================*/
