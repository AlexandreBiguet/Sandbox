#include "test.h"

/*======================================================================
========================================================================
	Test of Random number generator from GSL 
========================================================================
======================================================================*/
//
void TEST_GSLran()
{
/*----------------------------------------------------------------------
	This routine tests the random number generator from GSL lib.

	PART 1 : (part1 = true)
	```````````````````````
			Simple test for the 4 previous routine, one random number
			is generated between min and max for each RNG.
	
	PART 2 : (part2 = true)
	```````````````````````
			Test of average of RNG.
			
	PART 3 : (part3 = true)
	```````````````````````
			Test of convergence true the theoretical mean for the 4
			RNG routines.
	PART 4 : (part4 = true)
	```````````````````````
			Test of GSLdran(gsl_rng*,double,double)
------------------------------------------------------------------------
----------------------------------------------------------------------*/
	bool part1,part2,part3,part4;
	part1 = true;
	part2 = true;
	part3 = true;
	part4 = true;
/*----------------------------------------------------------------------
	PART 0 : random numbers generators initialisation
----------------------------------------------------------------------*/
	gsl_rng *r1;
	gsl_rng *r2;
	gsl_rng *r3;
	gsl_rng *r4;
	unsigned long int seed = time(0);
	r1 = GSLinitran_mt19(seed);
	r2 = GSLinitran_lux1(seed);
	r3 = GSLinitran_lux2(seed);
	r4 = GSLinitran_taus(seed);
	
/*----------------------------------------------------------------------
	PART 1
----------------------------------------------------------------------*/
	if(part1)
	{
		printf("\n\n\t TEST GSL ran fcts : PART 1 \n \n");
		double ran;
		ran = GSLran(r1);
		printf("\n ran = %10f \n",ran);
		ran = GSLran(r2);
		printf("\n ran = %10f \n",ran);
		ran = GSLran(r3);
		printf("\n ran = %10f \n",ran);
		ran = GSLran(r4);
		printf("\n ran = %10f \n",ran);
	}
/*----------------------------------------------------------------------
	PART 2
----------------------------------------------------------------------*/
	if(part2)
	{
		printf("\n\n\t TEST GSL ran fcts : PART 2 \n \n");
		int tsmax = 50000;
		double tran[tsmax];
		for(int i=0;i<tsmax;i++)
		{
			tran[i] = GSLran(r1);
		}
		double ave = average(tran,tsmax);
		printf("\n ave = %f \n",ave);
	}
/*----------------------------------------------------------------------
	PART 3
----------------------------------------------------------------------*/
	if(part3)
	{
		printf("\n\n\t TEST GSL ran fcts : PART 3 \n \n");
		int nbpts,tsizemin,tsizemax,it;
		double ave;
		nbpts    = 100;
		tsizemin = 10;
		tsizemax = 50000;
		double tran[tsizemax];
		it = (tsizemax-tsizemin)/nbpts; 
		system("mkdir -p data/test/GSL-Random-Nb-Gen");
		FILE *f = fopen("data/test/GSL-Random-Nb-Gen/part2.dat","w");
		for(int tsize=tsizemin;tsize<tsizemax;tsize+=it)
		{
			fprintf(f,"%10d",tsize);
			for(int i=0;i<tsize;i++)
			{
				tran[i] = GSLran(r1);
			}
			ave = average(tran,tsize);
			fprintf(f,"%15f",ave);
			for(int i=0;i<tsize;i++)
			{
				tran[i] = GSLran(r2);
			}
			ave = average(tran,tsize);
			fprintf(f,"%15f",ave);
			for(int i=0;i<tsize;i++)
			{
				tran[i] = GSLran(r3);
			}
			ave = average(tran,tsize);
			fprintf(f,"%15f",ave);
			for(int i=0;i<tsize;i++)
			{
				tran[i] = GSLran(r4);
			}
			ave = average(tran,tsize);
			fprintf(f,"%15f %s \n",ave,"0.5");
		}
		fclose(f);
		f = fopen("data/test/GSL-Random-Nb-Gen/part2.gnu","w");
		char gc[1024];
		sprintf(gc,"set t pos eps enh col solid"                      "\n"
		           "set xlabel 'nb of iteration' "                    "\n"
				   "set ylabel 'mean value of random distribution' "  "\n"
				   "set yrange [0.495:0.505]"                         "\n"                      
				   "set title 'Convergence of the mean' "             "\n"
				   "set out 'data/test/GSL-Random-Nb-Gen/part2.eps' "	 "\n"
				   "plot 'data/test/GSL-Random-Nb-Gen/part2.dat' u 1:2 w lp title 'mt19' ,"
				   "     'data/test/GSL-Random-Nb-Gen/part2.dat' u 1:3 w lp title 'lux1' ,"
				   "     'data/test/GSL-Random-Nb-Gen/part2.dat' u 1:4 w lp title 'lux2' ,"              
				   "     'data/test/GSL-Random-Nb-Gen/part2.dat' u 1:5 w lp title 'taus' ,"
				   "     'data/test/GSL-Random-Nb-Gen/part2.dat' u 1:6 w l notitle"      "\n"
				  );
		fprintf(f,"%s",gc);
		fclose(f);
		system("gnuplot data/test/GSL-Random-Nb-Gen/part2.gnu");
		system("epstopdf data/test/GSL-Random-Nb-Gen/part2.eps");
		system("rm data/test/GSL-Random-Nb-Gen/part2.eps");
	}
/*----------------------------------------------------------------------
	PART 4
----------------------------------------------------------------------*/
	if(part4)
	{
		printf("\n\n\t TEST GSL ran fcts : PART 4 \n \n");
		int nbpts,tsizemin,tsizemax,it;
		double ave,min,max;
		nbpts    = 100;
		tsizemin = 10;
		tsizemax = 50000;
		min = -10.;
		max = 10.;
		double tran[tsizemax];
		it = (tsizemax-tsizemin)/nbpts; 
		system("mkdir -p data/test/GSL-Random-Nb-Gen");
		FILE *f = fopen("data/test/GSL-Random-Nb-Gen/part4.dat","w");
		for(int tsize=tsizemin;tsize<tsizemax;tsize+=it)
		{
			fprintf(f,"%10d",tsize);
			for(int i=0;i<tsize;i++)
			{
				tran[i] = GSLdran(r1,min,max);
			}
			ave = average(tran,tsize);
			fprintf(f,"%15f",ave);
			for(int i=0;i<tsize;i++)
			{
				tran[i] = GSLdran(r2,min,max);
			}
			ave = average(tran,tsize);
			fprintf(f,"%15f",ave);
			for(int i=0;i<tsize;i++)
			{
				tran[i] = GSLdran(r3,min,max);
			}
			ave = average(tran,tsize);
			fprintf(f,"%15f",ave);
			for(int i=0;i<tsize;i++)
			{
				tran[i] = GSLdran(r4,min,max);
			}
			ave = average(tran,tsize);
			fprintf(f,"%15f \n",ave);
		}
		fclose(f);
		f = fopen("data/test/GSL-Random-Nb-Gen/part4.gnu","w");
		char gc[1024];
		sprintf(gc,"set t pos eps enh col solid"                      "\n"
		           "set xlabel 'nb of iteration' "                    "\n"
				   "set ylabel 'mean value of random distribution' "  "\n"                    
				   "set title 'Convergence of the mean' "             "\n"
				   "set xzeroaxis \n"
				   "set out 'data/test/GSL-Random-Nb-Gen/part4_1.eps' "	 "\n"
				   "plot 'data/test/GSL-Random-Nb-Gen/part4.dat' u 1:2 w lp title 'mt19' ,"
				   "     'data/test/GSL-Random-Nb-Gen/part4.dat' u 1:3 w lp title 'lux1' ,"
				   "     'data/test/GSL-Random-Nb-Gen/part4.dat' u 1:4 w lp title 'lux2' ,"              
				   "     'data/test/GSL-Random-Nb-Gen/part4.dat' u 1:5 w lp title 'taus' \n"
				   "set out 'data/test/GSL-Random-Nb-Gen/part4_2.eps' \n"
				   "set yrange[-1:1] \n"
				   "replot \n"
				   "set out 'data/test/GSL-Random-Nb-Gen/part4_3.eps' \n"
				   "set yrange[-0.5:0.5] \n"
				   "replot \n"
				  );
		fprintf(f,"%s",gc);
		fclose(f);
		system("gnuplot data/test/GSL-Random-Nb-Gen/part4.gnu");
		system("epstopdf data/test/GSL-Random-Nb-Gen/part4_1.eps");
		system("rm data/test/GSL-Random-Nb-Gen/part4_1.eps");
		system("epstopdf data/test/GSL-Random-Nb-Gen/part4_2.eps");
		system("rm data/test/GSL-Random-Nb-Gen/part4_2.eps");
		system("epstopdf data/test/GSL-Random-Nb-Gen/part4_3.eps");
		system("rm data/test/GSL-Random-Nb-Gen/part4_3.eps");		
	}
/*----------------------------------------------------------------------
	END : random numbers generators free
----------------------------------------------------------------------*/
	GSLdealran(r1);
	GSLdealran(r2);
	GSLdealran(r3);
	GSLdealran(r4);
}

/*======================================================================
======================================================================*/

void TEST_gaus_dist()
{
	printf("\n Gaussian Distribution \n ");

	double xmin,xmax,sigma;
	char c1[256],c2[256];

	sigma = 1.;
	xmin = -10.;
	xmax = 10.;

	double gd_aux(double x)
	{
		return GSLgauss_pdf(x,sigma);
	}
	system("mkdir -p data/test/GSL-Random-Nb-Gen/pdf");
	sprintf(c1,"data/test/GSL-Random-Nb-Gen/pdf/gaus_pdf");
	sprintf(c2,"pdf gauss {/Symbol s} = 1.");
//	
	PlotCFct(gd_aux,xmin,xmax,400,c1,c2,"x","p(x)","set xzeroaxis");
}

/*======================================================================
======================================================================*/

void TEST_gaus_tail_dist()
{
	printf("\n Gaussian-Tail Distribution \n ");

	double xmin,xmax,lomin,sigma;
	char c1[512],c2[512],namedir[256];

	sigma = 1.;
	lomin = 0.6;
	xmin = -0.1;
	xmax = 10.;

	double gt_aux(double x)
	{
		return GSLgauss_tail_pdf(x,lomin,sigma);
	}
	sprintf(namedir,"mkdir -p data/test/GSL-Random-Nb-Gen/pdf");
	system(namedir);
	sprintf(c1,"data/test/GSL-Random-Nb-Gen/pdf/gaus_tail_pdf");
	sprintf(c2,"pdf gauss-tail {/Symbol s} = %.2f lower bound = %.2f",sigma,lomin);

	PlotCFct(gt_aux,xmin,xmax,400,c1,c2,"x","p(x)","set xzeroaxis");
}

/*======================================================================
======================================================================*/

void TEST_biv_gaus_dist()
{
	printf("\n Bivariate Gaussian Distribution \n ");
}

/*======================================================================
======================================================================*/

void TEST_exp_dist()
{
	printf("\n Exponential Distribution \n ");

	double xmin,xmax,mean;
	char c1[512],c2[512],namedir[256];

	xmin = -0.1;
	xmax = 10.;
	mean = 2.;

	double faux(double x)
	{
		return GSLexp_pdf(x,mean);
	}
	sprintf(namedir,"mkdir -p data/test/GSL-Random-Nb-Gen/pdf");
	system(namedir);
	sprintf(c1,"data/test/GSL-Random-Nb-Gen/pdf/exp_pdf");
	sprintf(c2,"pdf exp dist mean = %.2f",mean);

	PlotCFct(faux,xmin,xmax,400,c1,c2,"x","p(x)","set xzeroaxis");
}

/*======================================================================
======================================================================*/

void TEST_laplace_dist()
{
	printf("\n Laplace Distribution \n ");

	double xmin,xmax,width;
	char c1[512],c2[512],namedir[256];

	xmin = -10.;
	xmax = 10.;
	width = 1.0;

	double faux(double x)
	{
		return GSLlaplace_pdf(x,width);
	}
	sprintf(namedir,"mkdir -p data/test/GSL-Random-Nb-Gen/pdf");
	system(namedir);
	sprintf(c1,"data/test/GSL-Random-Nb-Gen/pdf/laplace_pdf");
	sprintf(c2,"pdf laplace dist width = %.2f",width);

	PlotCFct(faux,xmin,xmax,400,c1,c2,"x","p(x)","set xzeroaxis");
}
