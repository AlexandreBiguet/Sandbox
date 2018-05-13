#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include <gsl/gsl_math.h>
#include <gsl/gsl_integration.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_roots.h>
#include <gsl/gsl_multiroots.h>
#include <gsl/gsl_multimin.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_deriv.h>
#include <gsl/gsl_min.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_cdf.h>
#include <gsl/gsl_histogram.h>
#include <gsl/gsl_sort_double.h>
#include <gsl/gsl_statistics_double.h>




#define MALLOC(_p,_t,_n) do{ \
(_p) = malloc ( (_n) * sizeof( (_t) )); \
if( (_p) == NULL ) \
{ \
     fprintf(stderr,"Allocation impossible dans le fichier :%s ligne : %s",__FILE__,__LINE__);\
     exit(EXIT_FAILURE); \
} \
}while(0)



#define CALLOC(_p,_t,_n) do{ \
(_p) = calloc ( (_n) , sizeof( (_t) ) ); \
if( (_p) == NULL ) \
{ \
     fprintf(stderr,"Allocation impossible dans le fichier :%s ligne : %s",__FILE__,__LINE__);\
     exit(EXIT_FAILURE); \
} \
}while(0)



#define REALLOC(_p,_t,_n) do{ \
(_t) * temp; \
temp = realloc ( (_p) , (_n) * sizeof( (_t) ) ); \
if( temp == NULL ) \
{ \
     fprintf(stderr,"Allocation impossible dans le fichier :%s ligne : %s",__FILE__,__LINE__);\
     free( (_p) ); \
	 exit(EXIT_FAILURE); \
} \
else \
{ \
     (_p) = temp; \
} \
}while(0)


#define FREE(_p) do{ \
	 free( (_p) ); \
     (_p) = NULL; \
}while(0)





/* TEST DE MACROS POUR CONSTRUIRE DES MATRICES : NE MARCHE PAS POUR LE MOMENT */

#define MATRIX_ALLOC( _p , _tp , _t , _n1 , _n2 )	\
MALLOC(_p , _tp , _n1 ); \
for ( int i = 0 ; i < _n1 ; i++ ) \
{	\
	CALLOC ( _p[i] , _t , _n2 );	\
}


#define MATRIX_FREE( _p , _n1 , _n2 ) \
for ( int i = 0 ; i < _n1 ; i++ )	\
{	\
	FREE( _p[i]) ;	\
}	\
FREE( _p) ;	

/* FIN :  TEST DE MACROS POUR CONSTRUIRE DES MATRICES : NE MARCHE PAS POUR LE MOMENT */




/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/

void matrix_char_set_str ( char *in , size_t strlenght , size_t numero_ligne , gsl_matrix_char *out )
{
	for ( size_t i = 0 ; i < strlenght+1 ; i++ )
	{
		gsl_matrix_char_set ( out , numero_ligne , i , in[i] ) ;
	}
}

/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/

void matrix_char_cpy ( char *dest ,  size_t numero_ligne ,  gsl_matrix_char *in )
{
	for ( size_t i = 0 ; i < in->size2 ; i++ )
	{
		dest[i] = gsl_matrix_char_get ( in , numero_ligne , i );
	}
}


/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/

void plot_fcts_2 ( double (*f[])(double) , size_t nbfct  , size_t nbpts , gsl_matrix_char *tit )
{
	double xlo = 0. ;
	double xhi = 5. ;

	double it = (xhi - xlo)/(double) nbpts ;
	
	FILE *file = fopen ("data.dat" , "w" );
	if ( file == NULL )
	{
		printf("problème ouverture data\n");
		exit(-1);
	}
	
	gsl_matrix *m = gsl_matrix_alloc( nbpts , nbfct +1 );
	
	double x;
	
	for ( size_t l = 0; l < nbpts ; l++ )
	{
		x = xlo + it * l ;
		gsl_matrix_set ( m , l , 0 , x ); 
		
		for ( size_t c = 0 ; c < nbfct  ; c++ )
		{
			gsl_matrix_set ( m , l , c+1 , f[c](x) );
		} 
	}
	
	for ( size_t l = 0 ; l < nbpts ; l++ )
	{
		for ( size_t c = 0 ; c < nbfct + 1 ; c++ )
		{
			fprintf( file , "%20.15f " , gsl_matrix_get ( m , l , c ) );
		}
		fprintf ( file , "\n" );
	}
	
	gsl_matrix_free ( m ); 
	fclose ( file );
	
	
	file = fopen ("com.gnu" , "w");
	if ( file == NULL )
	{
		printf("problème ouverture gnu com \n");
		exit(-1);
	}
	fprintf(file,"set term pos eps col enh \n");
	fprintf(file,"set out 'plot.eps' \n");
	
	char title[1024] ;
	
	matrix_char_cpy ( title , (size_t) 0 ,  tit ) ;
	
	fprintf(file,"plot 'data.dat' u 1:2 w l title '%s' ,\\\n" , title );
	size_t ind = 1; 
	for (size_t i = 3 ; i < nbfct + 1 ; i++ )
	{
		matrix_char_cpy ( title , ind ,  tit ) ;
		fprintf ( file , "'data.dat' u 1:%zu w l title '%s' ,\\\n" , i , title);
		ind++; 
	}
	
	matrix_char_cpy ( title , (size_t) nbfct-1 ,  tit ) ;
	
	fprintf ( file, "'data.dat' u 1:%zu w l title '%s' \n", nbfct+1 , title );
	fprintf(file,"!epstopdf plot.eps \n");
	fprintf(file,"!rm plot.eps \n");
	
	/*fprintf(file,"plot 'data.dat' u 1:2 w l title '0' ,\\\n" );
	int ind = 1; 
	for (size_t i = 3 ; i < nbfct  ; i++ )
	{
		 fprintf ( file , "'data.dat' u 1:%zu w l title '%d' ,\\\n" , i , ind );
		 ind++; 
	}
	fprintf ( file, "'data.dat' u 1:%zu w l title '%zu' \n", nbfct+1 , nbfct - (size_t)1 );
	fprintf(file,"!epstopdf plot.eps \n");
	fprintf(file,"!rm plot.eps \n");*/
	
	fclose ( file );
	
	system ("gnuplot com.gnu");
}





#define STR_MAXSIZE 1024

/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/

int main ( void )
{
	
	size_t nbfct = 4  ;
	size_t nbpts = 50 ;
	
	double f1 ( double x) { return x + 1. ; }
	double f2 ( double x) { return 2.*x   ; }
	double f3 ( double x) { return x*x    ; }
	double f4 ( double x) { return 2 + f3(x) ; }
	
	double (*F[4]) ( double ) = { f1 , f2 , f3 , f4 } ;
	
	gsl_matrix_char *tc = gsl_matrix_char_alloc( nbfct , STR_MAXSIZE );
	
	char str_1 [] = "x + 1" ;
	char str_2 [] = "2 * x" ;
	char str_3 [] = "x * x" ;
	char str_4 [] = "2 + x * x" ;
	
	size_t str_len = strlen ( str_1 );
	
	matrix_char_set_str ( str_1 , str_len , (size_t) 0 , tc ) ;
	
	str_len = strlen ( str_2 );
	
	matrix_char_set_str ( str_2 , str_len , (size_t) 1 , tc ) ;
	
	str_len = strlen ( str_3 );
	
	matrix_char_set_str ( str_3 , str_len , (size_t) 2 , tc ) ;
	
	str_len = strlen ( str_4 );
	
	matrix_char_set_str ( str_4 , str_len , (size_t) 3 , tc ) ;
	
	
	/*char str_out [ STR_MAXSIZE ] ;
	
	matrix_char_cpy ( str_out , (size_t) 0 , tc ) ;
	
	printf("%s \n" , str_out);
	
	matrix_char_cpy ( str_out , (size_t) 1 , tc ) ;
	
	printf("%s \n" , str_out);*/
	
	
	
	plot_fcts_2 ( F ,  nbfct  ,  nbpts , tc ) ;

	
	gsl_matrix_char_free ( tc );
	
	/*
	
	
	size_t nbfct = 2 ;
	size_t nbpts = 50 ;
	
	
	
	char **tit ;
	
	MATRIX_ALLOC(tit , char* , char , 2 , 50 );
	
	//tit = malloc ( 2*sizeof(char*)) ;
	sprintf ( tit[0] , "x + 1" );
	sprintf ( tit[1] , "2x" );
	
	plot_fcts ( F , nbfct , nbpts , tit );
	
	MATRIX_FREE( tit , 2 , 50);
	*/
	
	
	return 0;
}











/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/


void plot_fcts ( double (*f[])(double) , size_t nbfct  , size_t nbpts , char **tit )
{
	double xlo = 0. ;
	double xhi = 5. ;

	double it = (xhi - xlo)/(double) nbpts ;
	
	FILE *file = fopen ("data.dat" , "w" );
	if ( file == NULL )
	{
		printf("problème ouverture data\n");
		exit(-1);
	}
	
	gsl_matrix *m = gsl_matrix_alloc( nbpts , nbfct +1 );
	
	double x;
	
	for ( size_t l = 0; l < nbpts ; l++ )
	{
		x = xlo + it * l ;
		gsl_matrix_set ( m , l , 0 , x ); 
		
		for ( size_t c = 0 ; c < nbfct  ; c++ )
		{
			gsl_matrix_set ( m , l , c+1 , f[c](x) );
		} 
	}
	
	for ( size_t l = 0 ; l < nbpts ; l++ )
	{
		for ( size_t c = 0 ; c < nbfct + 1 ; c++ )
		{
			fprintf( file , "%20.15f " , gsl_matrix_get ( m , l , c ) );
		}
		fprintf ( file , "\n" );
	}
	
	gsl_matrix_free ( m ); 
	fclose ( file );
	
	
	file = fopen ("com.gnu" , "w");
	if ( file == NULL )
	{
		printf("problème ouverture gnu com \n");
		exit(-1);
	}
	
	fprintf(file,"set term pos eps col enh \n");
	fprintf(file,"set out 'plot.eps' \n");
	fprintf(file,"plot 'data.dat' u 1:2 w l title '%s' ,\\\n" , tit[0] );
	int ind = 1; 
	for (size_t i = 3 ; i < nbfct+1  ; i++ )
	{
		 fprintf ( file , "'data.dat' u 1:%zu w l title '%s' ,\\\n" , i , tit[ind] );
		 ind++; 
	}
	fprintf ( file, "'data.dat' u 1:%zu w l title '%s' \n", nbfct , tit[nbfct - 1] );
	fprintf(file,"!epstopdf plot.eps \n");
	fprintf(file,"!rm plot.eps \n");
	
	/*fprintf(file,"plot 'data.dat' u 1:2 w l title '0' ,\\\n" );
	int ind = 1; 
	for (size_t i = 3 ; i < nbfct  ; i++ )
	{
		 fprintf ( file , "'data.dat' u 1:%zu w l title '%d' ,\\\n" , i , ind );
		 ind++; 
	}
	fprintf ( file, "'data.dat' u 1:%zu w l title '%zu' \n", nbfct+1 , nbfct - (size_t)1 );
	fprintf(file,"!epstopdf plot.eps \n");
	fprintf(file,"!rm plot.eps \n");*/
	
	fclose ( file );
	
	system ("gnuplot com.gnu");
}