#ifndef __nr_routines_H__
#define __nr_routines__
/**********************************************************************/
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
/**********************************************************************/
//
/*======================================================================
========================================================================
========================================================================
CHAPITRE 1 : PRELIMINARIES
========================================================================
========================================================================
======================================================================*/

/*======================================================================
========================================================================
========================================================================
CHAPITRE 2 : SOLUTION OF LINEAR ALGEBRAIC EQUATIONS
========================================================================
========================================================================
======================================================================*/

/*======================================================================
========================================================================
========================================================================
CHAPITRE 3 : INTERPOLATION AND EXTRAPOLATION
========================================================================
========================================================================
======================================================================*/

/*======================================================================
========================================================================
========================================================================
CHAPITRE 4 : INTEGRATION OF FUNCTIONS
========================================================================
========================================================================
======================================================================*/

/*======================================================================
========================================================================
========================================================================
CHAPITRE 5 : EVALUATION OF FUNCTIONS
========================================================================
========================================================================
======================================================================*/

/*======================================================================
========================================================================
========================================================================
CHAPITRE 6 : SPECIAL FUNCTIONS
========================================================================
========================================================================
======================================================================*/
double gammq(double a, double x);
//
void gcf(double *gammcf, double a, double x, double *gln);
//
void gser(double *gamser, double a, double x, double *gln);
//
double gammln(double xx);
//
/*======================================================================
========================================================================
========================================================================
CHAPITRE 7 : RANDOM NUMBERS
========================================================================
========================================================================
======================================================================*/
//
double ran0(int *idum);
//
double ran1(int *idum);
//
double ran2(int *idum);
//
double ran3(int *idum);
//
double ran4(int *idum);
//
void psdes(unsigned int *lword, unsigned int *irword);
//
double dran0(int *idum,double min,double max);
//
double dran1(int *idum,double min,double max);
//
double dran2(int *idum,double min,double max);
//
double dran3(int *idum,double min,double max);
//
double dran4(int *idum,double min,double max);
//
double NR_dist_exp(int *idum);
//
double NR_dist_gauss(int *idum);
//
/*======================================================================
========================================================================
========================================================================
CHAPITRE 8 : SORTING
========================================================================
========================================================================
======================================================================*/

/*======================================================================
========================================================================
========================================================================
CHAPITRE 9 : ROOT FINDING AND NONLINEAR SETS OF EQUATIONS
========================================================================
========================================================================
======================================================================*/

/*======================================================================
========================================================================
========================================================================
CHAPITRE 10 : MINIMIZATION OR MAXIMIZATION OF FUNCTIONS
========================================================================
========================================================================
======================================================================*/

/*======================================================================
========================================================================
========================================================================
CHAPITRE 11 : EIGENSYSTEMS
========================================================================
========================================================================
======================================================================*/

/*======================================================================
========================================================================
========================================================================
CHAPITRE 12 : FAST FOURIER TRANSFORM
========================================================================
========================================================================
======================================================================*/

/*======================================================================
========================================================================
========================================================================
CHAPITRE 13 : FOURIER AND SPECTRAL APPLICATIONS
========================================================================
========================================================================
======================================================================*/

/*======================================================================
========================================================================
========================================================================
CHAPITRE 14 : STATISTICAL DESCRIPTION OF DATA
========================================================================
========================================================================
======================================================================*/
//
void moment(double data[], int n, double *ave, double *adev, double *sdev, double *var, double *skew, double *curt);
//
double average(double data[],int n);
//
/*======================================================================
========================================================================
========================================================================
CHAPITRE 15 : MODELING OF DATA
========================================================================
========================================================================
======================================================================*/

/*======================================================================
========================================================================
========================================================================
CHAPITRE 16 : INTEGRATION OF ORDINARY DIFFERENTIAL EQUATIONS
========================================================================
========================================================================
======================================================================*/

/*======================================================================
========================================================================
========================================================================
CHAPITRE 17 : TWO POINT BOUNDARY VALUE PROBLEMS
========================================================================
========================================================================
======================================================================*/

/*======================================================================
========================================================================
========================================================================
CHAPITRE 18 : INTEGRAL EQUATIONS AND INVERSE THEORY
========================================================================
========================================================================
======================================================================*/

/*======================================================================
========================================================================
========================================================================
CHAPITRE 19 : PARTIAL DIFFERENTIAL EQUATIONS
========================================================================
========================================================================
======================================================================*/

/*======================================================================
========================================================================
========================================================================
CHAPITRE 20 : LESS-NUMERICAL ALGORITHMS
========================================================================
========================================================================
======================================================================*/

/*======================================================================
========================================================================
========================================================================
NRUTIL-H ROUTINES
========================================================================
========================================================================
======================================================================*/

/**********************************************************************/
#endif