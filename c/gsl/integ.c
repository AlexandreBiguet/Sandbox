#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h> // use of chdir
#include <ctype.h>
#include <getopt.h>
#include <execinfo.h>
#include <errno.h>
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
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

#define STR_MAXSIZE 1024
#define _GNU_UNUSED_ __attribute__((unused))


#define EP_C gsl_hypot(L,m)

#define EP		sqrt(p*p+m*m)
#define EP2		EP*EP
#define EP3		EP2*EP

#define EXPP	exp(  (EP - C)/T )
#define EXPPM	exp( -(EP - C)/T )

#define _FD_		1./(1. + EXPP  )

#define _GD_		1./(1. + EXPPM )

#define _FD2_		_FD_ * _FD_ 

#define _GD2_		_GD_ * _GD_

#define _DIF_FD_GD_	( _FD2_*_GD_ - _FD_ * _GD2_ )

#define M0	  njl->m0

#define GNcNf njl->G*njl->nc*njl->nf

typedef struct
{
	double er;				// relative error
	double ea;				// absolute error
	size_t max_iter;		// a max number for iteration
	size_t ws;				// workspace size

}parGSL;

typedef struct
{
	double nf;			// Nombre flavour
	double nc;			// Nombre couleur
	double G;			// Couplage
	double L;			// Lambda cut-off
	double m0;			// current mass in SU2 isospin sym. limit
	bool cutoff;
	
}parNJL;

/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/

static parGSL gsl = {1e-7, 1e-8 , 100 , 10000 };

/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/

double FD_T(double T , double C , double p , double m) ;
double FD( double T , double C , double p , double m) ;
int integ_qags ( double f(double) , double bmin , double bmax , double *res , double *err) ;
int integ_qagiu ( double f(double) , double bmin , double *res , double *err ) ;
int integ_d3p ( double f(double) , double bmax , double *res , double *err , bool cutoff ) ;

int mfe ( parNJL *njl , double T , double C , double m , double *res );
int PV_I1_a ( double L , double m , double *I ) ;
int Icut_a ( double L , double m , double *I ) ;
int Iinf_n ( double L , double T , double C , double m , double *I , double *e );

void test_integration(void);

int r1d_brent_method ( double f(double), double xlo , double xhi , double *zer , double *err );
int resMFE_m ( parNJL *njl , double T , double C , double mlo , double mhi, double *res );

void test_mfe_and_reso(void);

void test_fermi(void);

void test_precision(void);

void test_Temp_min ( void ) ;

/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/

int main(void){

	//
	// test_integration();
	//
	// Il est etonant de voir que les intégrands se comportent bien
	// meme à température faible, (T = 0.1 MeV). 
	// Il est de même étonnant que l'on puisse calculer les intégrales
	// avec qags, et qagiu, même à faible température (T = 0.1 MeV).
	
	// Pour voir, l'on trace ici m (solution de mfe), en fonction de T
	// pour plusieurs valeurs de mu, et on essaie de tirer à faible 
	// température
	
	//test_mfe_and_reso();
	
	test_integration();
	
	//test_Temp_min();
	
	// Il n'y a aucun problème lors du calcul de mfe, ce qui est normal
	// puisque ce calcul ne fait intervenir que le calculs des integrales.
	// Il n'y a pas non plus de problème lors de la recherche du zéro
	// de mfe. 
	
	
	
	return 0 ;
}

/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/

double FD_T(double T , double C , double p , double m){ return _FD_ ; }

double FD( double T , double C , double p , double m)
{
	//return _FD_ ;
	double ep = gsl_hypot(p,m);
	double P = 0.5 ;
	//return exp(-(ep-C) / T) / (1. + exp(-(ep-C) / T) ) ;
	//return exp(-3.*(ep-C) / T) / (1. + exp(-3.*(ep-C) / T) ) ; 
	//return 1. / (1 +exp(3.*(ep-C) / T) ) ;
	
	/*
	// Forme Arianna
	double exp1 = exp(-1.*(ep-C) / T) ;
	double exp2 = exp(-2.*(ep-C) / T) ;
	double exp3 = exp(-3.*(ep-C) / T) ;

	double num = P*exp1 + 2.*P*exp2 + exp3 ;
	double den = 1. + 3.*P*exp1 + 3.*P*exp2 + exp3 ;
	*/
	
	// Forme simplifiée par facteur exp(-3X) où X = B(Ep - mu)
	double exp1 = exp(1.*(ep-C) / T) ;
	double exp2 = exp(2.*(ep-C) / T) ;
	double exp3 = exp(3.*(ep-C) / T) ;
	
	double num = P * exp2 + 2.*P*exp1 + 1. ;
	double den = exp3 + 3.*P*exp2 + 3.*P*exp1 + 1. ;
	
	return num/den ;
}

/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/

int integ_qags ( double f(double) , double bmin , double bmax , double *res , double *err)
{
/*
 * Méthode intégration : 
 * QAGS : Gauss-K adaptative with (integrable) singularities
 *
 */
	void my_handler ( const char *reason , const char *file , int line , int gsl_errno)
	{
		fprintf(stderr , "QAGS ::\n"
		                 "Err : %d \n"
						 "Sig : %s \n"
						 "Fic : %s (l : %d)\n"
						 ,gsl_errno,reason,file,line);
	}
	gsl_error_handler_t * old_handler;
	old_handler = gsl_set_error_handler (&my_handler);
	double faux ( double x , void *p _GNU_UNUSED_ ){return f(x);}
	gsl_integration_workspace *w = gsl_integration_workspace_alloc ( gsl.ws );
	gsl_function F;
	F.function = &faux ;
	int status = gsl_integration_qags(&F , bmin , bmax , gsl.ea , gsl.er , gsl.ws , w , res , err );
	gsl_integration_workspace_free ( w ); 
	gsl_set_error_handler (old_handler);
	return status ;
}

/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/

int integ_qagiu ( double f(double) , double bmin , double *res , double *err )
{
/*
 * Méthode intégration : 
 * QAGIU : Gauss-K adaptative, integration to Up Infty
 *
 */
	void my_handler ( const char *reason , const char *file , int line , int gsl_errno)
	{
		fprintf(stderr , "QAGIU ::\n"
		                 "Err : %d \n"
						 "Sig : %s \n"
						 "Fic : %s (l : %d)\n"
						 ,gsl_errno,reason,file,line);
	}
	gsl_error_handler_t * old_handler;
	old_handler = gsl_set_error_handler (&my_handler);
	double faux ( double x , void *p _GNU_UNUSED_ ){return f(x);}
	gsl_integration_workspace *w = gsl_integration_workspace_alloc ( gsl.ws );
	gsl_function F;
	F.function = &faux ;
	int status = gsl_integration_qagiu ( &F , bmin , gsl.ea , gsl.er , gsl.ws , w , res , err );
	gsl_integration_workspace_free ( w ); 
	gsl_set_error_handler (old_handler);
	return status ;
}

/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/

int integ_d3p ( double f(double) , double bmax , double *res , double *err , bool cutoff )
{
/* 
 * Integration de la fonction f entre 0 et bmax si cutoff = true, 
 * entre 0 et Infty sinon.
 *
 * int_0^\Lambda_t  d3p / (2\pi)^3  f(p)  
 *
 */
	double faux ( double p){return p*p/(2.*M_PI*M_PI) * f(p) ;}
	int status ;
	if (cutoff)
		status = integ_qags ( faux , 0. , bmax , res , err );
	else
		status = integ_qagiu(faux , 0. , res , err );
	return status ;
}

/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/

void test_integration(void)
{
	double T , C , m ;
	size_t N ;
	
	T = 1. ;
	C = 50. ;
	m = 20. ;
	
	N = 100  ;
	
	double fd(double p){ return FD (T, C,p,m) ;}
	double fb(double p){ return FD (T,-C,p,m) ;}
	double int_cut(double p){ return p*p / EP ; }
	double int_inf(double p){ return -1.*int_cut(p) * ( fd(p) + fb(p) ) ; } 
	double integrand(double p){ return int_cut(p) + int_inf(p) ; }
	
	double p , p2 , pmin , pmax , pmax2 , it , it2 ;
	
	pmin = 0. ;
	pmax = 700. ;
	pmax2= 100. ;
	it = (pmax-pmin) / (double) N ;
	it2 = (pmax2-pmin) / (double) N ;
	
	FILE *f = fopen("out.dat" , "w" );
	fprintf(f,"#T = %20.15f\n",T);
	fprintf(f,"#p	p2		fd(p2)		I_cut(p)	I_inf(p2)	Integrand\n");
	for ( size_t i = 0 ; i <= N ; i++ )
	{
		p = pmin + i*it ;
		p2 = pmin + i*it2 ;
		fprintf(f,"%20.15f %20.15f %20.15f %20.15f %20.15f %20.15f \n" 
			, p , p2 , fd(p2) , int_cut(p) , int_inf(p2), integrand(p));
	}
	fclose(f);
	
	f = fopen("Temp.dat" , "w") ;
	
	size_t NT = 10 ;
	
	double fdt (double p,double t){ return FD(t, C,p,m) ;}
	double fbt (double p,double t){ return FD(t,-C,p,m) ;}
	double Iin (double p,double t){ return -1.0*int_cut(p)*( fdt(p,t) + fbt(p,t) ) ; }
	double Int (double p,double t){ return int_cut(p) + Iin(p,t); }
	
	double Tmin = T , Tmax = 50. , itT = (Tmax - Tmin) / (double) NT ;
	T = 0. ;
	fprintf (f , "#p	I_inf(p,T)		Integrand(p,T) \n");
	for ( size_t i = 0 ; i <= NT ; i++ )
	{
		T = Tmin + i*itT ;
		fprintf(f,"\"T = %10.3f\" \n",T);
		for ( size_t j = 0 ; j <= N ; j++ )
		{
			p2 = pmin + j*it2 ;
			fprintf(f,"%20.15f %20.15f %20.15f\n" , p2 , Iin(p2,T) , Int(p2,T) ); 
		}
		fprintf(f,"\n\n");
	}
	fclose(f);
	
	f = fopen ("Integ.dat","w");
	T = 0. ;
	
	double resint , resint_inf , errint , errint_inf , Lambda , nolimit;
	double resint_cut , errint_cut ;
	int staint , staint_inf , staint_cut;
	
	Lambda = 650. ;
	
	for ( size_t i = 0 ; i < NT ; i++ )
	{
		T = Tmin + i*itT ;
		double Ii ( double p ) { return Iin (p,T) ; }
		double Integ(double p){ return Int(p,T); }
		staint = integ_d3p ( Integ , Lambda , &resint , &errint , true ) ;
		//staint_inf = integ_d3p(Ii, nolimit , &resint_inf , &errint_inf , false );
		staint_inf = integ_d3p(Ii, Lambda , &resint_inf , &errint_inf , true ); 
		staint_cut = integ_d3p(int_cut,Lambda,&resint_cut , &errint_cut , true );		
		const char *cint = gsl_strerror(staint);
		const char *cint_inf = gsl_strerror(staint_inf);
		const char *cint_cut = gsl_strerror(staint_cut);
		fprintf(f,"%30.15f %30.15f %30.15f %30.15f %30.15f %30.15f %30.15f %15s %15s %15s\n"
			   , T , resint , resint_inf , resint_cut 
			   , errint , errint_inf , errint_cut 
			   , cint , cint_inf , cint_cut);
	}
	fclose(f);
}

/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/

int PV_I1_a ( double L , double m , double *I )
{		
	*I= 1./(8.*M_PI*M_PI)* ( L*EP_C - m*m*log ( EP_C + L ) + m*m*log(m) ) ;  
	
	if ( gsl_isinf ( *I ) || gsl_isnan (*I) )
	{
		return GSL_FAILURE ;
	}
	else return GSL_SUCCESS ;
}

/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/

int Icut_a ( double L , double m , double *I )
{
/*			I = int_0^L d3p/(2PI^3)   m/(2EP)       */

	int s = PV_I1_a ( L , m , I );
	
	if ( s!= GSL_SUCCESS  ) return GSL_FAILURE ;

	*I = m*(*I) ;
	
	return GSL_SUCCESS ;
}

/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/

int Iinf_n ( double L , double T , double C , double m , double *I , double *e )
{
/*			int_0^infty  d3p/(2PI^3)     m/(2EP) * ( f + fbar )			*/
	
	double fp,fa ;
	
	double intinf ( double p )
	{
		fp = FD(T,C,p,m);
		fa = FD(T,-C,p,m);
		return m*(fp + fa)/(2.*EP);
	}
	
	int s = integ_d3p ( intinf , L , I , e , false );
	
	return s ;
}

/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/

int mfe ( parNJL *njl , double T , double C , double m , double *res )
{
	if ( T == 0. )
	{
		double Ic ;
		int s1 = Icut_a ( njl->L , m , &Ic );
		if ( s1 == GSL_SUCCESS )
		{
			*res = - m + M0 + 8. * GNcNf *  Ic ;
			return GSL_SUCCESS ;
		}
		else return GSL_FAILURE ;
	}
	
	double Ic , Ii , ei ;
		
	int s1 = Icut_a ( njl->L , m , &Ic );
	int s2 = Iinf_n ( njl->L , T , C , m , &Ii , &ei );
	
	if ( s1 == GSL_SUCCESS && s2 == GSL_SUCCESS )
	{
		*res = - m + M0 + 8. * GNcNf * ( - Ii + Ic );
		return GSL_SUCCESS ;
	} 
	else return GSL_FAILURE ;
}

/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/

int r1d_brent_method ( double f(double), double xlo , double xhi , double *zer , double *err )
{
	int status ;
	void my_handler ( const char *reason , const char *file , int line , int gsl_errno )
	{		
		double flo = f(xlo);
		double fhi = f(xhi);
		fprintf ( stderr , 
		         "ROOT1D_BRENT ::\n"
				 "Err : %d \n"
				 "Sig : %s \n"
				 "Fic : %s (l : %d)\n"
				 "x_lo = %20.15f \t\t f(x_lo) = %20.15f \n" 
				 "x_hi = %20.15f \t\t f(x_hi) = %20.15f \n"
				 ,gsl_errno,reason,file,line,xlo,flo,xhi,fhi);
	}
	gsl_error_handler_t * old_handler;
	old_handler = gsl_set_error_handler (&my_handler);
	double faux ( double x , void *p _GNU_UNUSED_ ){return f(x);}
	size_t iter = 0;
	const gsl_root_fsolver_type *T;
	gsl_root_fsolver *s;
	gsl_function F;
	F.function = &faux;
	T = gsl_root_fsolver_brent;
	s = gsl_root_fsolver_alloc (T);
	gsl_root_fsolver_set (s, &F, xlo, xhi);
	do
    {
		iter++;
		status = gsl_root_fsolver_iterate (s);
		*zer = gsl_root_fsolver_root (s);
		xlo = gsl_root_fsolver_x_lower (s);
		xhi = gsl_root_fsolver_x_upper (s);
		status = gsl_root_test_interval (xlo, xhi, 0. , gsl.er);	
	}
	while (status == GSL_CONTINUE && iter < gsl.max_iter);
	*err = xhi - xlo ;
	gsl_root_fsolver_free ( s );
	gsl_set_error_handler (old_handler);
	return status ;
}

/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/

int resMFE_m ( parNJL *njl , double T , double C , double mlo , double mhi, double *res )
{
/* Resolution of Mean Field eq => get mass */	
	double mfe_aux ( double m )
	{
		double mfe_res ;
		mfe ( njl, T , C , m , &mfe_res );
		return mfe_res ;
	}
	double err ;
	int status = r1d_brent_method(mfe_aux,mlo,mhi,res,&err);
	return status;
}

/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/

void test_mfe_and_reso(void)
{
	parNJL njl ;
	njl.L = 650. ;
	njl.nc = 3. ;
	njl.nf = 2. ;
	njl.G = 2.14 / (njl.L * njl.L) ;
	njl.cutoff = false ;
	njl.m0 = 5.2 ;
	
	FILE *f = fopen ("mfe.dat","w");
	
	double Tmin,Tmax,Cmin,Cmax,Mmin,Mmax ;
	size_t N = 100 , NT = 10 , NC = 10 ;
	double itT,itC,itM ;
	
	Tmax = 10. ;
	Tmin = 0. ;
	Cmin = 0.1 ;
	Cmax = 350. ;
	Mmin = njl.m0 ;
	Mmax = 340. ;
	
	itT = (Tmax - Tmin) / (double) NT ;
	itC = (Cmax - Cmin) / (double) NC ;
	itM = (Mmax - Mmin) / (double) N ;
	
	double T,C,M,mfeM ;
	for ( size_t i = 0 ; i <= NT ; i++ )
	{
		T = Tmin + i*itT ;
		for ( size_t j = 0 ; j <= NC ; j++ )
		{
			C = Cmin + j*itC ;
			fprintf(f,"\"T = %.2f ; {/Symbol m} = %.2f\" \n",T,C);
			
			double mfe_aux ( double m ) 
			{ 
				double res ; 
				mfe ( &njl , T , C , m , &res ) ; 
				return res ; 
			}
			
			for ( size_t k = 0 ; k<= N ; k++ )
			{
				M = Mmin + k*itM ; 
				mfeM = mfe_aux(M) ;
				fprintf(f,"%20.15f %20.15f \n",M , mfeM );
			}
			fprintf(f,"\n\n");
		}
	}
	
	fclose(f);
	
	f = fopen ("res_mfe.dat","w");
	
	size_t NT2 = 50 ;
	double Tmax2 = 200. ;
	double itT2 = (Tmax2 - Tmin) / (double) NT2 ;
	
	for ( size_t i = 0 ; i <=NC ; i++ )
	{
		C = Cmin + i*itC ;
		fprintf(f,"\"{/Symbol m} = %.2f\"\n",C);
		for ( size_t j = 0 ; j <= NT2 ; j++ )
		{
			T = Tmin + j*itT2 ;
			double mres ;
			resMFE_m(&njl,T,C,Mmin,Mmax,&mres);
			fprintf(f,"%20.15f %20.15f \n",T,mres);
		}
		fprintf(f,"\n\n");
	}
	
	size_t NC2 = 100 ;
	double itC2 = (Cmax - Cmin ) / (double) NC2 ;
	
	for ( size_t i = 0 ; i <= NT ; i++ )
	{
		T = Tmin + i*itT ;
		fprintf(f,"\" T=%.2f\"\n",T);
		for ( size_t j = 0 ; j <= NC2 ; j++ )
		{
			C = Cmin + j*itC2 ;
			double mres ;
			resMFE_m(&njl,T,C,Mmin,Mmax,&mres);
			fprintf(f,"%20.15f %20.15f \n",C,mres);
		}
		fprintf(f,"\n\n");
	}
	fclose(f);
}

/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/

void test_fermi(void)
{
	double T = 10. ;
	double C = 40. ;
	double m = 20. ;
	double pmin = 0. ;
	double pmax = 300. ;
	size_t N = 100 ;
	double itp = (pmax - pmin) / (double) N ;
	double p;
	
	FILE *f = fopen ("test_fd.dat","w");
	for (size_t i = 0 ; i <= N ; i++ )
	{
		p = pmin + i*itp ;
		double f1 = FD_T(T,C,p,m);
		double f2 = FD(T,C,p,m);
		double f3 = f2 - f1 ;
		double f4 = (f2-f1)/f2 ;
		fprintf(f,"%20.15f %20.15f %20.15f %20.15f %20.15f \n", p,f1,f2,f3,f4 );
	}
	fclose(f);
}

/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/

void test_precision(void) 
{
	parNJL njl ;
	njl.L = 650. ;
	njl.nc = 3. ;
	njl.nf = 2. ;
	njl.G = 2.14 / (njl.L * njl.L) ;
	njl.cutoff = false ;
	njl.m0 = 5.2 ;
	
	double Tmin = 1. ;
	double Tmax = 101. ;
	double Cmin = 0. ;
	double Cmax = 360. ;
	double Mmin = njl.m0 ;
	double Mmax = 340. ;
	
	size_t NT = 20 ;
	size_t NC = 20 ;
	
	double itT = (Tmax - Tmin) / (double) NT ;
	double itC = (Cmax - Cmin) / (double) NC ;
	
	FILE *f = fopen ("test_precision_m_T_mu.dat","w");
	
	double T , C ;
	
	fprintf(f,
			"# Run :			\n#\n"
			"# data en MeV		\n#\n"
			"# param njl :		\n#\n"
			"# L    = %20.15f	\n"
			"# GL2  = %20.15f	\n"
			"# m0   = %20.15f	\n#\n"
			"# Tmin = %20.15f	\n"
			"# Tmax = %20.15f	\n"
			"# Cmin = %20.15f	\n"
			"# Cmax = %20.15f	\n"
			"# Mmin = %20.15f	(bornes recherche root)\n"
			"# Mmax = %20.15f	\n#\n"
			"# NT   = %20zu		\n"
			"# NC   = %20zu		\n#\n"
			"# itT  = %20.15f (Tmax-Tmin)/NT \n"
			"# itC  = %20.15f	\n"
			, njl.L , njl.L*njl.L*njl.G , njl.m0 , Tmin , Tmax , Cmin 
			, Cmax , Mmin , Mmax , NT , NC , itT , itC );
	
	fprintf(f,"\n#\n# %20s %20s %20s \n", "T      ", "C      " ,"m(T,C)      "	);
	
	for ( size_t i = 0 ; i<=NT ; i++ )
	{
		T = Tmin + i*itT ;
		for ( size_t j = 0 ; j <=NC ; j++ )
		{
			C = Cmin + j*itC ;
			double mres ;
			resMFE_m(&njl,T,C,Mmin,Mmax,&mres);
			fprintf(f,"%20.15f %20.15f %20.15f \n",T,C,mres);
		}
		fprintf(f,"\n");
	}
	fclose(f);
}

/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/

void test_Temp_min ( void )
{
	parNJL njl ;
	njl.L = 650. ;
	njl.nc = 3. ;
	njl.nf = 2. ;
	njl.G = 2.14 / (njl.L * njl.L) ;
	njl.cutoff = false ;
	njl.m0 = 5.2 ;
	
	int N = 8 ;
	
	double T[] = {1. , 0.1 , 0.01 , 0.001 , 0.0001 , 0.00001 , 0.000001 , 0. } ;
	double Mmin = njl.m0 ;
	double Mmax = 340. ;
	double C = 250. ;
	
	FILE *f = fopen ("test_min_temperature_fd_dist.dat","w");
	
	fprintf(f,
			"# Run :			\n#\n"
			"# data en MeV		\n#\n"
			"# param njl :		\n#\n"
			"# L    = %20.15f	\n"
			"# GL2  = %20.15f	\n"
			"# m0   = %20.15f	\n#\n",
			njl.L,njl.L*njl.L*njl.G , njl.m0 );
	
	fprintf ( f , "C = %20.15f \n" , C );
	
	for ( int i = 0 ; i < N ; i++ )
	{
		double mres ;
		int status = resMFE_m(&njl,T[i],C,Mmin,Mmax,&mres) ;
		fprintf(f,"%d %25.15f %25.15f \n",status , T[i] , mres );
	}
	
	fclose (f);
}


