#ifndef __GSL_ROUTINES_H__
#define __GSL_ROUTINES_H__
/**********************************************************************/
/**********************************************************************/
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
/**********************************************************************/
/**********************************************************************/
#include <gsl/gsl_math.h>
#include <gsl/gsl_integration.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_roots.h>
#include <gsl/gsl_multiroots.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_deriv.h>
#include <gsl/gsl_min.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_cdf.h>
#include <gsl/gsl_histogram.h>
#include <gsl/gsl_sort_double.h>
/**********************************************************************/
/**********************************************************************/
#include "utils.h"
/**********************************************************************/
/**********************************************************************/

//
//==================================
// RANDOM NUMBER GENERATORS ROUTINES
//==================================
// initialization of rng routines
//
gsl_rng* GSLinitran_mt19(unsigned long int seed);
gsl_rng* GSLinitran_lux1(unsigned long int seed);
gsl_rng* GSLinitran_lux2(unsigned long int seed);
gsl_rng* GSLinitran_taus(unsigned long int seed);
//
// rand. nb. output routine
//
double GSLran (gsl_rng *r);
double GSLdran(gsl_rng *r,double min,double max);
//
// deallocation routine
//
void GSLdealran(gsl_rng *r);
//
//
//====================================
// RANDOM NUMBER DISTRIBUTION ROUTINES
//====================================
//
// RANDOM GAUSSIAN DISTRIBUTION
//
void GSLgauss_dist    (double *disttab,unsigned long int seed, int nbpts, double mean, double sigma);
void GLSgauss_zig_dist(double *disttab,unsigned long int seed, int nbpts, double mean, double sigma);
// PDF GAUSSIAN DISTRIBUTION
double GSLgauss_pdf(double x,double sigma);
//
//	GAUSSIAN TAIL DISTRIBUTION
//
void GSLgauss_tail_dist(double *tab,unsigned long int seed,int nbpts,double min,double mean,double sigma);
double GSLgauss_tail_pdf(double x,double min,double sigma);
//
// BIVARIATE GAUSSIAN DISTRIBUTION
//
void GSLbiv_gauss_dist(double *xtab,double *ytab,unsigned long int seed,int nbpts,double mean_x,double mean_y,double sigma_x,double sigma_y,double corr);
double GSLbiv_gauss_pdf(double x,double y, double sigma_x, double sigma_y, double corr);
//
// EXPONENTIAL DISTRIBUTION
//
void GSLexp_dist(double *tab,unsigned long int seed,int nbpts,double mean);
double GSLexp_pdf(double x,double mean);
//
// LAPLACE DISTRIBUTION
//
void GSLlaplace_dist(double *tab,unsigned long int seed,int nbpts,double width);
double GSLlaplace_pdf(double x,double width);

#endif
