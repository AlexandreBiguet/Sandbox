#include "test.h"


/*======================================================================
========================================================================
	Test of Random number generator from Numerical Recipies 
========================================================================
======================================================================*/
/*





*/
/*======================================================================
========================================================================
======================================================================*/
void TEST_NRrand()
{
/*----------------------------------------------------------------------
	This routine tests the random number genrators ran0,ran1,ran2,ran3,
	ran4 from Numerical Recipes C.
	
	Remark :
	````````
			If the seed is not changed between a run and another, the 
			random numbers calculated will be the same. This is why
			the time(0) function is used.
			However, it may be some times interesting to have the same 
			distribution, to make a comparison or whatever. In that case, 
			the seed must be registered somewhere, in order to have the
			same random sequence.
	
	Part 1 : (part1 = true)
	```````````````````````
			one random number is calculated using ran0,ran1,ran2,ran3.
	
	Part 2 : (part2 = true)
	```````````````````````
			1000 random numbers are calculated using ran0,ran1,ran2,ran3.
			The result is plotted into 8 files in : 
			data/test/NR_C-Random-Nb-Gen/ran*.pdf
		
	  ! --> We got a problem with ran1, at each iteration, the same number
			is calculated... This problem comes from a wrong utilisation
			of the routine, but for now i don't know what's wrong.
	
	Part 3 : (part3 = true)
	```````````````````````
			The same work is done as in part 1 and 2 but using the ran4
			routine, which is expected to give the best results, but 
			expected to cost time.
		
	  ! --> We also got a problem using ran4, the random numbers generated
			are between -1 and +inf ...
			don't know why...
			
	Part 4 : (part4 = true)
	```````````````````````
			The "moment" routine is used to compute mean, variance, aso,
			of the distribution computed using ran* routines.
			The used generator are ran0,ran2,ran3, since we don't know
			how to use ran1 and ran4...
			
	Part 5 : (part5 = true)
	```````````````````````
			The average of the distribution of random numbers generated
			by ran0,ran2,ran3 must be 0.5.
			We look here for the convergence of the average, ie, we 
			compute the average of the distribution for a number of 
			ramdom numbers growing, from 10 to 1e6. 
			The bigger the number of iteration is, the closer the average 
			of the distribution is form the expected average. What we 
			want to know here is which routine converge faster.

	Part 6 : (part6 = true)
	```````````````````````
			The method used in part 5 is not enought to test the random
			number generators, because the number of double that can be
			stocked in an array is limited to 10^5 (why ?).
			The idea in this part is to do exactly the same thing as in 
			part5, but using another way in order to have more iteration
			
	Part 7 : (part7 = true)
	```````````````````````
			Some tests using the dran* routines. dran* routine returns 
			a random number in min and max using ran* routine.
----------------------------------------------------------------------*/
//
	printf("\n TEST NR-C ran fcts \n ");
//
	bool part1,part2,part3,part4,part5,part6,part7;
	part1 = true;
	part2 = true;
	part3 = true;
	part4 = true;
	part5 = true;
	part6 = true;
	part7 = true;
//
	int idum0,idum1,idum2,idum3;
	double rran0,rran1,rran2,rran3;
	idum0 = -1*time(0);
	idum1 = -1*time(0);
	idum2 = -1*time(0);
	idum3 = -1*time(0);
/*----------------------------------------------------------------------
	PART 1
----------------------------------------------------------------------*/
	if(part1)
	{
		printf("\n TEST NR-C ran fcts : PART 1 \n \n");
		rran0 = ran0(&idum0);
		rran1 = ran1(&idum1);
		rran2 = ran2(&idum2);
		rran3 = ran3(&idum3);
		printf("rran0 = %f \n",rran0);
		printf("rran1 = %f \n",rran1);
		printf("rran2 = %f \n",rran2);
		printf("rran3 = %f \n",rran3);
	}
/*----------------------------------------------------------------------
	PART 2
----------------------------------------------------------------------*/
	if(part2)
	{
		printf("\n TEST NR-C ran fcts : PART 2 \n ");
		int tsize = 1000;
		double tran0[tsize],tran1[tsize],tran2[tsize],tran3[tsize];
		for(int i=0;i<tsize;i++)
		{
			tran0[i] = ran0(&idum0);
			tran1[i] = ran1(&idum1);
			tran2[i] = ran2(&idum2);
			tran3[i] = ran3(&idum3);
		}
		printf("\n tran1[0] = %f \n",tran1[0]);
		char Scomm[1024],wayfile[1024],Dfile[1024],Gfile[1024],Efile[1024];
		char Efile0[1024],Efile1[1024],Efile2[1024],Efile3[1024];
		char Efile4[1024],Efile5[1024],Efile6[1024],Efile7[1024];
		sprintf(wayfile,"data/test/NR_C-Random-Nb-Gen");
		sprintf(Dfile,"%s/ran.dat",wayfile);
		sprintf(Gfile,"%s/ran.gnu",wayfile);
		sprintf(Efile,"%s/ran.eps",wayfile);
		sprintf(Efile0,"%s/ran0.eps",wayfile);
		sprintf(Efile1,"%s/ran1.eps",wayfile);
		sprintf(Efile2,"%s/ran2.eps",wayfile);
		sprintf(Efile3,"%s/ran3.eps",wayfile);
		sprintf(Efile4,"%s/ran4.eps",wayfile);
		sprintf(Efile5,"%s/ran5.eps",wayfile);
		sprintf(Efile6,"%s/ran6.eps",wayfile);
		sprintf(Efile7,"%s/ran7.eps",wayfile);
		sprintf(Scomm,"mkdir -p %s",wayfile);
		system(Scomm);
		FILE *f;
		f = fopen(Dfile,"w");
		fprintf(f,"#iter \t ran0 \t ran1 \t ran2 \t ran3 \n");
		for(int i=0;i<tsize;i++)
		{
			fprintf(f,"%3d %14f %14f %14f %14f \n",
					i,tran0[i],tran1[i],tran2[i],tran3[i]);
		}
		fclose(f);
		f = fopen(Gfile,"w");
		char Gcomm[2048];
		sprintf(Gcomm,"set t pos eps enh col"                 "\n"
					  "set xlabel 'numero of iteration'"      "\n"
					  "set ylabel 'random number'"            "\n"
					  "set title 'NR-C random nb generator'"  "\n"
					  "set out '%s' "                         "\n"
					  "set yrange[0:1.2]"                     "\n"
					  "set xrange[0:10]"                      "\n"
					  "plot '%s' u 1:2 w lp title 'ran0',"
				      "     '%s' u 1:3 w lp title 'ran1',"
				      "     '%s' u 1:4 w lp title 'ran2'," 
				      "     '%s' u 1:5 w lp title 'ran3'"     "\n"
					  "set out '%s'"                 "\n"
					  "plot '%s' u 1:2 w lp title 'ran0' "    "\n"
					  "set out '%s'"                 "\n"
					  "plot '%s' u 1:3 w lp title 'ran1' "    "\n"
					  "set out '%s'"                 "\n"
					  "plot '%s' u 1:4 w lp title 'ran2' "    "\n"
					  "set out '%s'"                 "\n"
					  "plot '%s' u 1:5 w lp title 'ran3' "    "\n"
					  "set xlabel 'random number'"            "\n"
					  "set ylabel 'number of iteration' "     "\n"
					  "set xrange[0:1.2]"                     "\n"
					  "set yrange[0:1000]"                    "\n"
					  "set out '%s'"                 "\n"
					  "plot '%s' u 2:1 w p title 'ran0' "    "\n"
					  "set out '%s'"                 "\n"
					  "plot '%s' u 3:1 w p title 'ran1' "    "\n"
					  "set out '%s'"                 "\n"
					  "plot '%s' u 4:1 w p title 'ran2' "    "\n"
					  "set out '%s'"                 "\n"
					  "plot '%s' u 5:1 w p title 'ran3' "    "\n"
					  
					  ,Efile,Dfile,Dfile,Dfile,Dfile,Efile0,Dfile,
					  Efile1,Dfile,Efile2,Dfile,Efile3,Dfile,
					  Efile4,Dfile,Efile5,Dfile,Efile6,Dfile,Efile7,
					  Dfile);
		fprintf(f,"%s",Gcomm);
		fclose(f);
		char Gsys[1024];
		sprintf(Gsys,"gnuplot %s ; epstopdf %s ; rm %s ; "
					 "epstopdf %s ; "
					 "epstopdf %s ; " 
					 "epstopdf %s ; "
					 "epstopdf %s ; "
					 "epstopdf %s ; "
					 "epstopdf %s ; " 
					 "epstopdf %s ; "
					 "epstopdf %s ; "
					 "rm %s %s %s %s %s %s %s %s"
					 ,Gfile,Efile,Efile,Efile0,Efile1,Efile2,Efile3
					 ,Efile4,Efile5,Efile6,Efile7
					 ,Efile0,Efile1,Efile2,Efile3,Efile4,Efile5,Efile6
					 ,Efile7);
		system(Gsys);
	}
/*----------------------------------------------------------------------
	PART 3
----------------------------------------------------------------------*/
	if(part3)
	{
		printf("\n TEST NR-C ran fcts : PART 3 \n \n");
		int idum = -1*time(0);
		double rr=ran4(&idum);
		printf("rr = %f \n",rr);
		
		char wayf[1024],Scom[1024],Efil[1024],Efi1[1024],Gfil[1024];
		char Dfil[1024],Gcom[1024],Gsys[1024];
		sprintf(wayf,"data/test/NR_C-Random-Nb-Gen");
		sprintf(Scom,"mkdir -p %s",wayf);
		sprintf(Efil,"%s/NRran4.eps",wayf);
		sprintf(Efi1,"%s/NRran4_1.eps",wayf);
		sprintf(Dfil,"%s/NRran4.dat",wayf);
		sprintf(Gfil,"%s/NRran4.gnu",wayf);
		system(Scom);
		int tsize = 1000;
		double tran4[tsize];
		FILE *f = fopen(Dfil,"w");
		fprintf(f,"# iter \t ran4 \n#\n");
		for(int i=0;i<tsize;i++)
		{
			tran4[i] = ran4(&idum);
			fprintf(f,"%4d %15f \n",i,tran4[i]);
		}
		fclose(f);
		f = fopen(Gfil,"w");
		sprintf(Gcom,"set t pos eps enh col"                 "\n"
					 "set xlabel 'numero of iteration'"      "\n"
					 "set ylabel 'random number'"            "\n"
					 "set title 'NR-C rn (ran4) generator'"  "\n"
					 "set out '%s' "                         "\n"
					 "set yrange[0:1.2]"                     "\n"
					 "set xrange[0:10]"                      "\n"
					 "plot '%s' u 1:2 w lp title 'ran4' "    "\n"
					 "set out '%s' "                         "\n"
					 "set ylabel 'numero of iteration'"      "\n"
					 "set xlabel 'random number'"            "\n"
					 "set xrange[0:1.2]"                     "\n"
					 "set yrange[0:1000]"                    "\n"
					 "plot '%s' u 1:2 w p title 'ran4' "     "\n"
					 ,Efil,Dfil,Efi1,Dfil);
		fprintf(f,"%s",Gcom);
		fclose(f);
		sprintf(Gsys,"gnuplot %s ; epstopdf %s ; epstopdf %s ; rm %s %s;"
							,Gfil,Efil,Efi1,Efil,Efi1);
		system(Gsys);
	}
/*----------------------------------------------------------------------
	PART 4
----------------------------------------------------------------------*/
	if(part4)
	{
		printf("\n TEST NR-C ran fcts : PART 4 \n \n");
		int idum = -1*time(0);
		int tsize = 10000;
		double tran3[tsize],tran0[tsize],tran2[tsize];
		for(int i=0;i<tsize;i++)
		{
			tran0[i] = ran0(&idum);
			tran2[i] = ran2(&idum);
			tran3[i] = ran3(&idum);
		}
		double ave,adev,sdev,var,skew,curt;
		moment(tran0,tsize,&ave,&adev,&sdev,&var,&skew,&curt);
		printf("\n\t RAN0 Routine : (nb of iteration = 10000) \n");
		printf("ave   =  %10f \n",ave);
		printf("adev  =  %10f \n",adev);
		printf("sdev  =  %10f \n",sdev);
		printf("var   =  %10f \n",var);
		printf("skew  =  %10f \n",skew);
		printf("curt  =  %10f \n",curt);
		moment(tran2,tsize,&ave,&adev,&sdev,&var,&skew,&curt);
		printf("\n\t RAN2 Routine : (nb of iteration = 10000) \n");
		printf("ave   =  %10f \n",ave);
		printf("adev  =  %10f \n",adev);
		printf("sdev  =  %10f \n",sdev);
		printf("var   =  %10f \n",var);
		printf("skew  =  %10f \n",skew);
		printf("curt  =  %10f \n",curt);
		moment(tran3,tsize,&ave,&adev,&sdev,&var,&skew,&curt);
		printf("\n\t RAN3 Routine : (nb of iteration = 10000) \n");
		printf("ave   =  %10f \n",ave);
		printf("adev  =  %10f \n",adev);
		printf("sdev  =  %10f \n",sdev);
		printf("var   =  %10f \n",var);
		printf("skew  =  %10f \n",skew);
		printf("curt  =  %10f \n",curt);
	}
/*----------------------------------------------------------------------
	PART 5
----------------------------------------------------------------------*/
	if(part5)
	{
		printf("\n TEST NR-C ran fcts : PART 5 \n \n");
		double averan0[101],averan2[101],averan3[101];
		double a,b,c,d,e;
		int iave = 0;
		double tran0[100000];
		double tran2[100000];
		double tran3[100000];
		printf("\n TEST 1 PP \n");
		char Gf[1024],Df[1024],Wf[1024],Ef[1024],sc[1024],gc[1024];
		char scc[1024];
		sprintf(Wf,"data/test/NR_C-Random-Nb-Gen");
		sprintf(Gf,"%s/conv.gnu",Wf);
		sprintf(Df,"%s/conv.dat",Wf);
		sprintf(Ef,"%s/conv.eps",Wf);
		sprintf(sc,"mkdir -p %s",Wf);
		system(sc);
		FILE *f = fopen(Df,"w");
		for(int tsize=10;tsize<=100000;tsize+=990)
		{
			int idum = time(0);
			for(int i=0;i<tsize;i++)
			{
				tran0[i] = ran0(&idum);
				tran2[i] = ran2(&idum);
				tran3[i] = ran3(&idum);
			}
			moment(tran0,tsize,&averan0[iave],&a,&b,&c,&d,&e);
			moment(tran2,tsize,&averan2[iave],&a,&b,&c,&d,&e);
			moment(tran3,tsize,&averan3[iave],&a,&b,&c,&d,&e);
			fprintf(f,"%8d %15f %15f %15f \t %s \n",tsize,averan0[iave],averan2[iave],averan3[iave],"0.5");
			iave++;
		}
		fclose(f);
		sprintf(gc,"set t pos eps enh col"                            "\n"
		           "set xlabel 'nb of iteration' "                    "\n"
				   "set ylabel 'mean value of random distribution' "  "\n"
				   "set yrange [0.48:0.52]"                           "\n"                      
				   "set title 'Convergence of the mean' "             "\n"
				   "set out '%s' "									  "\n"
				   "plot '%s' u 1:2 w lp title 'ran0' ,"
				   "     '%s' u 1:3 w lp title 'ran2' ,"
				   "     '%s' u 1:4 w lp title 'ran3' ,"              
				   "     '%s' u 1:5 w l notitle"                      "\n"
				  ,Ef,Df,Df,Df,Df);
		f = fopen(Gf,"w");
		fprintf(f,"%s",gc);
		fclose(f);
		sprintf(scc,"gnuplot %s ; epstopdf %s ; rm %s",Gf,Ef,Ef);
		system(scc);
	}
/*----------------------------------------------------------------------
	PART 6
----------------------------------------------------------------------*/
	if(part6)
	{
		printf("\n TEST NR-C ran fcts : PART 6 \n \n");
		int nbpts,tsizemin,tsizemax,it;
		nbpts    = 100;
		tsizemin = 10;
		tsizemax = 500000;
		it = (tsizemax-tsizemin)/nbpts; 
		double ave;
		double tran[tsizemax];
		system("mkdir -p data/test/NR_C-Random-Nb-Gen");
		FILE *f = fopen("data/test/NR_C-Random-Nb-Gen/conv_1.dat","w");
		for(int tsize=tsizemin;tsize<tsizemax;tsize+=it)
		{
			int idum = time(0);
			fprintf(f,"%10d",tsize);
			for(int i=0;i<tsizemax;i++)
			{
				tran[i] = ran0(&idum);
			}
			ave = average(tran,tsize);
			fprintf(f,"%15f",ave);
			for(int i=0;i<tsizemax;i++)
			{
				tran[i] = ran2(&idum);
			}
			ave = average(tran,tsize);
			fprintf(f,"%15f",ave);
			for(int i=0;i<tsizemax;i++)
			{
				tran[i] = ran3(&idum);
			}
			ave = average(tran,tsize);
			fprintf(f,"%15f %s \n",ave,"0.5");
		}
		fclose(f);
		f = fopen("data/test/NR_C-Random-Nb-Gen/conv_1.gnu","w");
		char gc[1024];
		sprintf(gc,"set t pos eps enh col"                            "\n"
		           "set xlabel 'nb of iteration' "                    "\n"
				   "set ylabel 'mean value of random distribution' "  "\n"
				   "set yrange [0.495:0.505]"                           "\n"                      
				   "set title 'Convergence of the mean' "             "\n"
				   "set out 'data/test/NR_C-Random-Nb-Gen/conv_1.eps' "	 "\n"
				   "plot 'data/test/NR_C-Random-Nb-Gen/conv_1.dat' u 1:2 w lp title 'ran0' ,"
				   "     'data/test/NR_C-Random-Nb-Gen/conv_1.dat' u 1:3 w lp title 'ran2' ,"
				   "     'data/test/NR_C-Random-Nb-Gen/conv_1.dat' u 1:4 w lp title 'ran3' ,"              
				   "     'data/test/NR_C-Random-Nb-Gen/conv_1.dat' u 1:5 w l notitle"      "\n"
				  );
		fprintf(f,"%s",gc);
		fclose(f);
		system("gnuplot data/test/NR_C-Random-Nb-Gen/conv_1.gnu");
		system("epstopdf data/test/NR_C-Random-Nb-Gen/conv_1.eps");
		system("rm data/test/NR_C-Random-Nb-Gen/conv_1.eps");
	}
/*----------------------------------------------------------------------
	PART 7
----------------------------------------------------------------------*/
	if(part7)
	{
		printf("\n TEST NR-C ran fcts : PART 7 \n \n");
		int tsize = 1000;
		double randmin = -2.;
		double randmax = 10.;
		double tdran[tsize];
		int idum = -1*time(0);
		double ave,adev,sdev,var,skew,curt;
		for(int i=0;i<tsize;i++)
		{
			tdran[i] = dran3(&idum,randmin,randmax);
		}
		moment(tdran,tsize,&ave,&adev,&sdev,&var,&skew,&curt);
		system("mkdir -p data/test/NR_C-Random-Nb-Gen/Part7");
		FILE *f = fopen("data/test/NR_C-Random-Nb-Gen/Part7/rtest.dat","w");
		fprintf(f,"# routine used : dran3, min = %.2f   max = %.2f \n",randmin,randmax);
		fprintf(f,"# tsize =  %d   \n",tsize);
		fprintf(f,"# ave   =  %10f \n",ave);
		fprintf(f,"# adev  =  %10f \n",adev);
		fprintf(f,"# sdev  =  %10f \n",sdev);
		fprintf(f,"# var   =  %10f \n",var);
		fprintf(f,"# skew  =  %10f \n",skew);
		fprintf(f,"# curt  =  %10f \n",curt);
		for(int i=0;i<tsize;i++)
		{
			fprintf(f,"%4d %15f \n",i,tdran[i]);
		}
		fclose(f);
		f = fopen("data/test/NR_C-Random-Nb-Gen/Part7/rtest.gnu","w");
		char gc[1024];
		sprintf(gc,"set t pos eps enh col \n"
				   "set xlabel 'numero of iteration' \n"
				   "set ylabel 'random number' \n"
				   "set out 'data/test/NR_C-Random-Nb-Gen/Part7/rtest1.eps' \n"
				   "plot 'data/test/NR_C-Random-Nb-Gen/Part7/rtest.dat' u 1:2 w lp notitle \n"
				   "set xlabel 'random number' \n"
				   "set ylabel 'numero of iteration' \n"
				   "set yrange[0:50] \n"
				   "set out 'data/test/NR_C-Random-Nb-Gen/Part7/rtest2.eps' \n"
				   "plot 'data/test/NR_C-Random-Nb-Gen/Part7/rtest.dat' u 2:1 w lp notitle \n"
				);
		fprintf(f,"%s",gc);
		fclose(f);
		system("gnuplot data/test/NR_C-Random-Nb-Gen/Part7/rtest.gnu");
		system("epstopdf data/test/NR_C-Random-Nb-Gen/Part7/rtest1.eps");
		system("rm data/test/NR_C-Random-Nb-Gen/Part7/rtest1.eps");
		system("epstopdf data/test/NR_C-Random-Nb-Gen/Part7/rtest2.eps");
		system("rm data/test/NR_C-Random-Nb-Gen/Part7/rtest2.eps");
	}
}
/*======================================================================
========================================================================
======================================================================*/
void TEST_NRrand_dist()
{
	int ntsize,nhsize,idum;
	double xmin,xmax,space;
	ntsize = 10000; // nb de rand nb
	nhsize = 100;   // nb de bin dans l'histo
	xmin   = -5.;
	xmax   = 5.;
	space  = (xmax-xmin)/nhsize;
	idum   = time(0);
	double tgau[ntsize],texp[ntsize],hgau[nhsize],hexp[nhsize];
	FILE *f = fopen("data/test/NR_C-Random-Nb-Gen/dist.dat","w");
	FILE *f1 = fopen("data/test/NR_C-Random-Nb-Gen/ran.dat","w");
	for(int i=0;i<ntsize;i++)
	{
		tgau[i] = NR_dist_gauss(&idum);
		texp[i] = NR_dist_exp(&idum);
		int nhgbin = (tgau[i] - xmin)/space ;
		int nhebin = (texp[i] - xmin)/space ;
		hgau[nhgbin]++;
		hexp[nhebin]++;
		fprintf(f1,"%5d %15f %15f \n",i,tgau[i],texp[i]);
	}
	for(int i=0;i<nhsize;i++)
	{
		fprintf(f,"%5f %15f %15f \n",xmin+i*space,hgau[i],hexp[i]);
	}
	fclose(f);
	f = fopen("data/test/NR_C-Random-Nb-Gen/dist.gnu","w");
	char gc[1024];
	sprintf(gc,"set t pos eps enh col \n"
				"set ylabel 'numero of iteration' \n"
				"set xlabel 'random number' \n"
				"set out 'data/test/NR_C-Random-Nb-Gen/dist.eps' \n"
				"plot 'data/test/NR_C-Random-Nb-Gen/dist.dat' u 1:2 w boxes title 'gauss-dist' ,"
				"     'data/test/NR_C-Random-Nb-Gen/dist.dat' u 1:3 w boxes title 'exp-dist'\n"
			);
	fprintf(f,"%s",gc);
	fclose(f);
	system("gnuplot data/test/NR_C-Random-Nb-Gen/dist.gnu");
	system("epstopdf data/test/NR_C-Random-Nb-Gen/dist.eps");
	system("rm data/test/NR_C-Random-Nb-Gen/dist.eps");
}