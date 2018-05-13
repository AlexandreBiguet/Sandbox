#ifndef __utils_H__
#define __utils_H__
/**********************************************************************/
/**********************************************************************/
#include "GSL-routines.h"
/**********************************************************************/
/**********************************************************************/
//
//
/*======================================================================
	tabular initialization
======================================================================*/
//
void dtabinit  ( double *dtab , int size , double initial);
//
void itabinit  ( int *itab    , int size , int initial);
// 
//
/*======================================================================
	Error message
======================================================================*/
//
void error(char *errormessage);
//
//
/*======================================================================
	Warning message
======================================================================*/
//
void warning(char *warningmessage);
//
//
/*======================================================================
	Histogram maker
======================================================================*/
//
void makeHisto(double *tab,int tsize,double *histo,int nbin,double xmin,double xmax);
//
/*======================================================================
	Histogram writer
======================================================================*/
void writeHisto(FILE *f,double *histo,int nbin,double xmin,double xmax);
//
//
/*======================================================================
	Histogram gnuplot command
======================================================================*/
void gnuplotHisto(FILE *f,int nbpts,char *filename,char *histoname);
//
//
/*======================================================================
	Average of an array
======================================================================*/
double average(double data[],int n);
//
/*======================================================================
	Plot fct
======================================================================*/
void PlotCFct(double f(double),double xmin,double xmax,int n, char *nameFile, 
			  char *nameGraph, char *nameXaxis, char *nameYaxis , char *command);
//
void Plot3DCFct(double f(double,double),double xmin,double xmax,double ymin,
				double ymax,int nx,int ny,char *nameFile , char *nameGraph , 
				char *nameXaxis , char *nameYaxis ,char *nameZaxis, char *command , 
				bool keepdata);
/**********************************************************************/
#endif
