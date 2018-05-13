#include "utils.h"
//
//
/*======================================================================
	tabular initialization
======================================================================*/
//
void dtabinit  ( double *dt  , int ts , double in)
{
	for(int i=0;i<ts;i++)
	{
		dt[i] = in ;
	}
}
//
void itabinit  ( int *it  , int ts , int in)
{
	for(int i=0;i<ts;i++)
	{
		it[i] = in;
	}
}
/*======================================================================
	Error message
======================================================================*/
//
void error(char *errormessage)
{
	printf("\nERROR :  %s   \n   EXIT \n\n",errormessage);
	exit(1);
}
//
//
/*======================================================================
	Warning message
======================================================================*/
//
void warning(char *warningmessage)
{
	printf("\n WARNING : %s \n",warningmessage);
}
//
//
/*======================================================================
	Histogram maker
======================================================================*/
//
void makeHisto(double *tab,int tsize,double *histo,int nbin,double xmin,double xmax)
{
/*----------------------------------------------------------------------
	From a tabular 'tab' [0,...,tsize], this routine build an histogram
	'histo' [0,...,nbin].
		nbin      : nb of bin in histo
		xmin,xmax : min and max of tab
		tsize     : size of tab
----------------------------------------------------------------------*/
	error("makeHisto does not work properly");
	double space = (xmax - xmin)/nbin ;
	int in;
	for(int i=0;i<tsize;i++)
	{
		in = (tab[i] - xmin) / space ;
		if(in < 0)
		{
			error("in makeHisto routine : xmin to high");
		}
		histo[in]++;
	}
}
//
//
/*======================================================================
	Histogram writer
======================================================================*/
void writeHisto(FILE *f,double *histo,int nbin,double xmin,double xmax)
{
	double space = (xmax - xmin)/nbin;
	for(int i=0;i<nbin;i++)
	{
		fprintf(f,"%5f %15f \n",xmin + i*space,histo[i]);
	}
}
//
/*======================================================================
	Histogram gnuplot command
======================================================================*/
void gnuplotHisto(FILE *f,int nbpts,char *filename,char *histoname)
{
	char gc[1024];
	sprintf(gc,"set t pos eps enh col \n"
				"set ylabel 'iteration' \n"
				"set xlabel 'random number' \n"
				"set title '%s for N = %d random numbers' \n"
				"set out '%s.eps' \n"
				"plot '%s.dat' u 1:2 w boxes title '%s' "
			,histoname,nbpts,filename,filename,histoname);
	fprintf(f,"%s",gc);
}
//
/*======================================================================
	Average of an array
======================================================================*/
double average(double data[],int n)
{
/*----------------------------------------------------------------------
	This routine returns the average of the data in data[0,...,n]
----------------------------------------------------------------------*/
	double s = 0.;
	for(int i=0;i<n;i++)
	{
		s+=data[i];
	}
	return (s/(1.*n));
}
//
/*======================================================================
	Plot fct
======================================================================*/
void PlotCFct(double f(double),double xmin,double xmax,int n, char *nameFile, char *nameGraph, char *nameXaxis, char *nameYaxis , char *command)
{	
	char Dname[1024];
	char Gname[1024];
	sprintf(Dname,"%s.dat",nameFile);
	sprintf(Gname,"%s.gnu",nameFile);
//
	FILE *file = fopen(Dname,"w");
	double h = (xmax-xmin)/ (double) n;
	double x,fx;
	for(int i=0;i<=n;i++)
	{
		x = xmin + i*h;
		fx = f(x);
		fprintf(file,"%f \t %f \n",x,fx);
	}
	fclose(file);
//
	file = fopen(Gname,"w");
//
	#if __gnu_linux__
		fprintf(file,"set t wxt enh \n");
		fprintf(file,"set title '%s' \n",nameGraph);
		fprintf(file,"set xlab '%s'  \n ",nameXaxis);
		fprintf(file,"set ylab '%s'  \n ",nameYaxis);
		fprintf(file,"%s \n",command);
		fprintf(file,"plot '%s' u 1:2 w l notitle \n",Dname);
		fprintf(file,"pause-1 \n");
		fprintf(file,"set term pos eps col enh \n");
		fprintf(file,"set out '%s.eps'  \n", nameFile);
		fprintf(file,"replot \n");
	#endif
//	
	#if __APPLE__ && __MACH__
		fprintf(file,"set title '%s' \n ",nameGraph);
		fprintf(file,"set xlab '%s'  \n ",nameXaxis);
		fprintf(file,"set ylab '%s'  \n ",nameYaxis);
		fprintf(file,"%s \n",command);
		fprintf(file,"set term pos eps col enh \n");
		fprintf(file,"set out '%s.eps'  \n", nameFile);
		fprintf(file,"plot '%s' u 1:2 w l notitle \n",Dname);
	#endif
//
	fclose(file);
	char Syscom[1024],epstopdf[1024],rmFile[1024],Ename[1024];
	sprintf(Syscom,"gnuplot %s",Gname);
	sprintf(Ename,"%s.eps",nameFile);
	sprintf(epstopdf,"epstopdf %s",Ename);
	sprintf(rmFile,"rm %s %s %s",Gname,Dname,Ename);
	system(Syscom);
	system(epstopdf);
	system(rmFile);
}
/*======================================================================
========================================================================
	 C O M P L E T E     3 D  -  P L O T      F U N C T I O N
========================================================================
======================================================================*/
//
void Plot3DCFct(double f(double,double),double xmin,double xmax,double ymin,double ymax,int nx,int ny,char *nameFile , char *nameGraph , char *nameXaxis , char *nameYaxis ,char *nameZaxis, char *command , bool keepdata)
{
	double itx,ity;
	char df[1024],gf[1024],ef[1024];
	char comm[2048];
	sprintf(df,"%s.dat",nameFile);
	sprintf(gf,"%s.gnu",nameFile);
	sprintf(ef,"%s.eps",nameFile);
	itx = (xmax-xmin)/nx;
	ity = (ymax-ymin)/ny;
	FILE *fi = fopen(df,"w");
	for(int i=0;i<=nx;i++)
	{
		for(int j=0;j<=ny;j++)
		{
			fprintf(fi,"%15.7f %15.7f %15.7f \n",xmin+i*itx,ymin+j*ity,f(xmin+i*itx,ymin+j*ity));
		}
		fprintf(fi,"\n");
	}
	fclose(fi);
	fi = fopen(gf,"w");
	fprintf(fi,"set title '%s' \n",nameGraph);
	fprintf(fi,"set xlabe '%s' \n",nameXaxis);
	fprintf(fi,"set ylabe '%s' \n",nameYaxis);
	fprintf(fi,"set zlabe '%s' \n",nameZaxis);
	fprintf(fi,"set hidden3d \n");
	fprintf(fi,"%s \n",command);
	fprintf(fi,"set t pos eps enh col \n");
	fprintf(fi,"set out '%s' \n",ef);
	fprintf(fi,"splot '%s' u 1:2:3 w l notitle \n",df);
	fprintf(fi,"set contour \n");
	fprintf(fi,"set cntrparam levels 20 \n");
	//fprintf(fi,"set data style line \n");
	fprintf(fi,"set key outside \n");
	fprintf(fi,"set out '%s_1.eps' \n",nameFile);
	fprintf(fi,"replot \n");
	fprintf(fi,"set out '%s_2.eps' \n",nameFile);
	fprintf(fi,"set view 0,0 \n");
	fprintf(fi,"set nozlabel \n");
	fprintf(fi,"set view map \n");
	fprintf(fi,"set nosurface \n");
	fprintf(fi,"set key outside \n");
	fprintf(fi,"replot \n");
	fclose(fi);
	if(!keepdata)
	{
		sprintf(comm,"gnuplot %s ; epstopdf %s ; epstopdf %s_1.eps ;"
				" epstopdf %s_2.eps ; rm %s %s %s %s_1.eps %s_2.eps  "
				,gf,ef,nameFile,nameFile,gf,df,ef,nameFile,nameFile);
		system(comm);
	}
	else
	{
		sprintf(comm,"gnuplot %s ; epstopdf %s ; epstopdf %s_1.eps ;"
				" epstopdf %s_2.eps ; rm %s %s_1.eps %s_2.eps"
				,gf,ef,nameFile,nameFile,ef,nameFile,nameFile);
		system(comm);
	}
}




