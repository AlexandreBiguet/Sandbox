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
#include <gsl/gsl_matrix.h>
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
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/

#define RETURN_IF_NULL(x) do{			\
    if (!x) {					\
      printf("\nreturn if null\n") ;		\
      return ;					\
    }						\
  } while (0)

// structures test 
typedef struct {
  double a ;
  double b ;
} Coord_2d ; // structure contenant un point sur une surface 2D

typedef struct {
  Coord_2d *c_2D ;
  double c ;
  double (*func)(double,double) ;
} F_Coord_2d ; 
// structure contenant un point sur une surface 2D et son ordonnée 
// calculée par la fonction func (pointeur sur fonction)

typedef struct {
  double a ; 
  bool test ;
} Struc_bool ;


//// pointeur sur structure

typedef struct {
  double a ;
  double b ;
  bool is_freed ;
} BF_param ;

typedef struct {
  double A ;
  BF_param * bf ;
  bool bf_is_freed ;
} BI_param ;


BF_param * BF_param_alloc (double a , double b )
{
  BF_param * p;
  p = (BF_param *) malloc ( sizeof ( BF_param ) ) ;
  if ( p == 0 )
    {
      printf("pb BF_param allocation \n"); exit(-1) ;
    }
  p->a = a ;
  p->b = b ;
  p->is_freed = false ;
  return p ;
}

void BF_param_free ( BF_param * p )
{
  RETURN_IF_NULL (p) ;
  free ( p );
	
}

void BF_param_set ( BF_param * p , double a , double b )
{
  p->a = a ;
  p->b = b ;
}


BI_param * BI_param_alloc ( BF_param *bf, double A )
{
  BI_param * p ;
  p = (BI_param *) malloc ( sizeof (BI_param) );
  if ( p == 0 )
    {
      printf("pb BI_param allocation \n"); exit(-1) ;
    }

  p->A = A ;
  p->bf = bf ;
  p->bf_is_freed = false ;
  return p ;
}

void BI_param_free ( BI_param *p )
{
  RETURN_IF_NULL (p) ;
  free(p);
  p=NULL ;
}


typedef struct
{
  double a ;
  double (*f) (double) ;
	
} struct_fct ;

typedef struct
{
  double a ;
  double b ;
} test_structure_argument_fct_a ;
typedef struct
{
  double a ;
  double b ;
} test_structure_argument_fct_b ;


/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/

void test_gsl_matrix(void);
void test_gsl_vector ( void );
void test_size (void) ;

void test_struct(void);
void test_ptr_struct ( void ) ;

void test_attribute_unused ( double a );
void test_nan_inf (void);

void test_sizet_ulong (void);

void test_return_in_void(void);

void test_free_non_allocated_gsl_vector ( void );

void test_reconnaissance_char ( char a ) ;

void test_fermi_dirac_generalise ( void ) ;

void test_exp_of_nan ( void );

void test_accolade ( void ) ;

void test_time_gsl_nan ( void );

void test_alloc_struct_fct ( void );

void test_struct_arg_fct (void );

void test_const_arg_struct ( void );

void test_multiplication_of_PI (void ); 

void test_rapidity_gsl_hypot ( void );

void test_writing_matrix_gsl ( void );

/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/


int main (void)
{
  // test_size();
  // test_gsl_vector();
  // test_gsl_matrix();
	
  //test_struct();
	
	
	
  // test_ptr_struct(); // ATTENTION PROVOQUE ERROR MALLOC
	
  // CONCLUSION :
  // Le plus sécurisé est de free chaque objet précédement alloué 
  // par la routine de désallocation qui correspond.
  // Dans le cas ou deux structures (A et B) peuvent vivrent 
  // sépérament, mais B->b_A existe. Le mieux est de faire une copie 
  // de A lors de la création de B. 
  // Pour la désallocation, on free B->b_A, on free B. Et evidement
  // on free A.


  // test_attribute_unused(5.);
	
  // CONCLUSION : même un argument d'une fonction passé avec
  // __attribute__((unused)) peut être utilisé par la fonction, 
  // et modifié par la fonction. Donc c'est juste un mot clef qui 
  // dit à gcc de laissé tombé un quelconque warning-parameter-unused
  // pour cet argument.
		
		
  //test_nan_inf();
	
	
  // test_sizet_ulong();
	
  // CONCLUSION : Pas de problème à la compilation pour 'caster' des 
  // size_t avec des unsigned long. (voir test_size(), le nombre de 
  // bit est le même -8- . ) 
  // Cela dit pas de problème non plus pour caster un int dans un 
  // unsigned long. Les erreurs de compilations viennent en fait du
  // format d'affichage : %d (int) %lu(ulong) %zu(size_t). %d pour un 
  // ulong provoque un warning. 
	
  //printf("Avant\n");
  //test_return_in_void();
  //printf("Apres\n");
	
  // CONCLUSION : On peut utiliser return dans une fonction void, 
  // A l'exécution, on sort de la routine, mais pas du programme. A la
  // différence de exit(1) qui sort du programme.
	
	
	
  //test_free_non_allocated_gsl_vector();
	
  // CONCLUSION :
  // free ( NULL ) est ok chez moi, mais 
  // free ( -un truc pas initialiser- ) => seg fault.
  // ==> apres free ( ptr ) ; ptr = NULL ; 
  // ==> apres deallocaiton, faire pointer sur NULL.
	
  //test_reconnaissance_char('z');
	
  // CONCLUSION : 
  // on peut faire des tests d'égalité avec des chars, sans problème
  // de même, on peut assigner des valeurs à des chars sans pbs.
	
	
  //test_fermi_dirac_generalise();
	
  //CONCLUSION : ok c'est bon


  // test_exp_of_nan();
	
  // CONCLUSION : Pour tester si un nombre est NaN, il faut utilser
  // la routine gsl_isnan. Le test if ( a == 0./0. ) ne marche pas.
	
  //test_accolade();

  // CONCLUSION : On peut utiliser des accolades dans une fonction
  // et les variables déclarées à l'intérieur des accolades ne vivent
  // que dans les accolades.
	
	
  // test_time_gsl_nan();
	
  // CONCLUSION : visiblement, la macro GSL_NAN donne de meilleur 
  // resultat quant à la vitesse d'assignement de la valeur nan
  // à une variable

  //test_alloc_struct_fct();

  // CONCLUSION : Si une structure prend un pointeur sur fonction,
  // il peut être initialisé à NULL lors de l'allocation de mémoire
  // pour une instance de la structure.

  //test_struct_arg_fct();
	
  // CONCLUSION : La question que l'on se posait était la suivante :
  // Soient deux structures qui pesent le même poid (en bit).
  // Soit une fonction qui prend en argument deux instances de ces
  // deux structure.
  // GCC fait-il la différence entre les deux structures puisqu'elles
  // ne diffère que par leur nom. (ou autre chose mais j'en sais rien)
  // REPONSE : OUI => donc c'est cool.

  //test_const_arg_struct();
	
  // CONCLUSION : La question que l'on s'est posé est en fait hors
  // sujet. 
  // On se demande si une fonction, qui prend en argument un argument
  // const, peut prendre un attribut d'une structure déclarée const.
  // En fait c'est hors sujet car : Une fonction qui prend un argument
  // const est juste une syntaxe qui permet de savoir si l'argument
  // est changé ou pas. 
  // Donc le fait que la structure soit déclarée const ne change rien,
  // elle peut être déclarée pas const. 

  // test_multiplication_of_PI();
	
  // CONCLUSION : Ce n'etait pas vraiment un test, on voulait juste
  // comparer les résultats le pi donnée par M_PI et le pi calculé
  // avec bc scale = 20 comme pi = 4 * arctan (1) (en bc : 4*a(1) )
  // Dans le fichier integrals.c on a définit des constantes calculees
  // avec bc scale = 20.
	
  //test_rapidity_gsl_hypot();
	
  // CONCLUSION : (output) 
  //	N =      10000
  //	dt (gsl_hypot) : 749, 508 , 555
  //	dt (normal) : 1, 2 , 2
  // les dt en clock() (en temps ordi quoi)
  // Incroyablement plus long avec gsl_hypot !

  //test_writing_matrix_gsl();
  
  // CONCLUSION :
  // Comme prévu, le frpintf de gsl matrix print en une colonne et on 
  // ne visualise pas très bien la matrice.


  return 0 ;

}
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/

void test_writing_matrix_gsl ( void )
{
  gsl_matrix * M = gsl_matrix_calloc ( 5 , 5 );
  FILE * file = fopen ("test_ecriture_binaire.bin","w");
  gsl_matrix_fprintf ( stdout , M , "%f" );
  gsl_matrix_fwrite ( file , M ); 

  fclose ( file );
}

/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/

void test_rapidity_gsl_hypot ( void )
{
  double p = 4. , m = 5. ; 
  double p2, m2 ;
  int N = 10000 ;
	
  double res_gsl_hypot ;
  double res ;
	
  clock_t ti = clock();
  for ( int i = 0 ; i < N ; i++ )
    {
      res_gsl_hypot = gsl_hypot ( p , m );
    }
  clock_t tf = clock (); 
  clock_t dt = tf - ti ;
  printf("N = %10d \n",N);
  printf("dt (gsl_hypot) : %zu \n", dt);
  ti = clock();
  for ( int i = 0 ; i < N ; i++ )
    {
      p2 = p*p ;
      m2 = m*m ;
      res = sqrt ( p2 + m2 );
    }
  tf = clock();
  dt = tf - ti ;
  printf("dt (normal) : %zu \n", dt);
  printf("%d \n", CLOCKS_PER_SEC);
	
}

/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/

void test_multiplication_of_PI (void )
{
  printf("M_PI   = %25.20f \n", M_PI);
  printf("M_PI^2 = %25.20f \n",M_PI * M_PI);
}

/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/

void test_const_arg_struct ( void )
{
  typedef struct
  {
    double a ;
    double b ;
  } A_str ;
	
  void print_a ( const double *a ) { printf( "a = %f \n" , *a ); }
	
  A_str A ;
  A.a = 2. ;
	
  print_a ( &A.a );
}

/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/

void test_struct_arg_fct (void )
{
  test_structure_argument_fct_a A ;
  test_structure_argument_fct_b B ;
	
  A.a = 1. ;
  B.b = 2. ;
	
  double test ( test_structure_argument_fct_a a , 
		test_structure_argument_fct_b b )
  {
    return a.a + b.b ;
  }
	
  size_t sA = sizeof(A);
  size_t sB = sizeof(B);
	
  double t = 0. ;
  // t = test (B,A) ;
	
  printf("size(A) = %zu \n", sA);
  printf("size(B) = %zu \n", sB);
  printf("t = %f \n",t);
}

/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/

void test_alloc_struct_fct ( void )
{
  double func(double x) { return x + 1. ;}
	
  struct_fct A ;
  A.f = NULL ;
  A.f = func ;
  A.a = A.f(2.) ;
  printf("a = %f \n",A.a);
}

/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/

void test_time_gsl_nan ( void )
{
  size_t N = 100000000000 ;
  printf("N = %zu \n",N); fflush(stdout);
	
  clock_t ti = clock();
  for ( size_t i = 0 ; i < N ; i++)
    {
      //double x = 0. / 0. ;
    }
  clock_t tf = clock();
	
  clock_t dt = tf - ti ;
	
  printf("clock 0. /0. : %zu \n",dt) ;fflush(stdout);
	
	
  ti = clock();
  for ( size_t i = 0 ; i < N ; i++)
    {
      //double x = GSL_NAN ;
    }
  tf = clock();
  dt = tf - ti ;
	
  printf("clock GSL_NAN : %zu \n",dt) ;fflush(stdout);
}

/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/

void test_accolade ( void )
{
  {
    double a = 10. ;
    printf("a = %f \n" , a);
  }
  {
    double a = 5. ;
    printf("a = %f \n" , a);
  }
}

/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/

void test_exp_of_nan ( void )
{
  double a = GSL_NAN ;
  double b = exp(a);
  double c = 0. / 0. ;
  printf("b = %f \n",b);
  printf("c = %f \n",c);
  if ( b == c )
    printf("coucou \n");
}

/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/

void test_fermi_dirac_generalise ( void )
{
  double fd_1 ( double x )
  {
    double num = exp(-x) + 2. * exp (-2.*x ) + exp (-3.*x ) ;
    double den = 1.+ 3.*exp(-x)+3.*exp(-2.*x) + exp(-3.*x) ;
    return num / den ; 
  }
	
  double fd_2 ( double x )
  {
    double num = exp(2.*x) + 2.*exp ( x ) + 1.; 
    double den = 1.+exp(3.*x)+3.*exp(2.*x)+3.*exp(x) ;
    return num / den ; 
  }
  FILE *file = fopen ("test_fermi_dirac_generalise.dat","w");
	
  double xl = -100. ;
  double xh = 100. ;
  double it = 1. ;
	
  double f1x , f2x , del ;
	
  for ( double x = xl ; x <= xh ; x+=it )
    {
      f1x = fd_1 ( x );
      f2x = fd_2 ( x );
      del = (f2x - f1x)/f2x ;
      fprintf( file , "%25.15f %25.15f %25.15f %25.15f \n" 
	       , x , f1x , f2x , del );
    }
  fclose ( file );
}

/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/

void test_reconnaissance_char ( char a )
{	
  if ( a == 'a' ) 
    printf("coucou - a \n");
  else if ( a == 'b' ) 
    printf("coucou - b \n");
  else{
    printf("don't knwo what to do !\n");
    a = 'a' ;
    test_reconnaissance_char(a) ;
  }
}

/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/

void test_free_non_allocated_gsl_vector ( void )
{
  gsl_vector *p = NULL ;
  gsl_vector_free (p);
}


/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/

void test_return_in_void(void)
{
  double a = 1. ;
  if ( a > 0. )
    return;
  else
    printf("coucou\n");
}	


/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/

void test_sizet_ulong (void)
{
  size_t nt = 100 ;
  unsigned long t ;
  t = nt ;
  int N ;
  N = t ;
  printf("nt = %zu \nt = %lu\nN = %d\n",nt,t,N);
}

/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/

void test_nan_inf (void)
{
  double x = log ( 0. );
	
  printf("x = log ( 0 ) = %f \n", x);

  x = sqrt ( -1. );

  printf("x = sqrt ( -1. ) = %f \n", x);
}

/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/

void test_attribute_unused ( double a __attribute__((unused)))
{
  a += 2. ;
  printf("a = %f \n" , a);
}

/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/

void test_ptr_struct ( void )
{
  double a = 3. , b = 5. , A = 10. ;
	
  BF_param * bf = BF_param_alloc ( a , b );
  BI_param * bi = BI_param_alloc ( bf , A );

  printf("BF_PARAM : \n a = %f , b = %f \n", bf->a , bf->b);
  printf("BI_PARAM : \n A = %f , bf->a = %f , bf->b = %f \n" ,
	 bi->A , bi->bf->a , bi->bf->b);
  printf("\nChange values of bf \n");
  BF_param_set ( bf , 25. , 35. );
  printf("BF_PARAM : \n a = %f , b = %f \n", bf->a , bf->b);
  printf("BI_PARAM : \n A = %f , bf->a = %f , bf->b = %f \n" ,
	 bi->A , bi->bf->a , bi->bf->b);
	
  BF_param_free ( bf );
  BI_param_free ( bi );
	
}

/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/

void test_struct(void)
{
  Coord_2d c_2D ;
  c_2D.a = 1. ;
  c_2D.b = 2. ;
	
  F_Coord_2d f_2D ;
  f_2D.c_2D = &c_2D ;
	
  double f(double x,double y) { return x + y ;}
	
  f_2D.func = f ;
	
  f_2D.c = f_2D.func(f_2D.c_2D->a , f_2D.c_2D->b) ;
	
  printf("a = %f \t b = %f \t c = f(a,b) = %f \n",f_2D.c_2D->a , f_2D.c_2D->b , f_2D.c );
	
  double ff ( double x , double y ) { return f_2D.func(x,y) ; }
  for ( double x = 0. ; x < 10 ; x+=5. )
    printf("x = %f \t f(x,x) = %f \n",x,ff(x,x));
	
  Struc_bool B ;
  B.test = true ;
  printf("%d\n",B.test);
	
}

/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/

void test_gsl_matrix(void)
{
  size_t nl = 5 ;
  size_t nc = 5 ;
	
  gsl_matrix *m = gsl_matrix_calloc ( nl, nc );
	
  gsl_matrix_set_all ( m , 1. );
	
  gsl_matrix_fprintf ( stdout , m , "%10.6f" ); 
  gsl_matrix_fwrite( stdout, m );
	
  gsl_matrix_free ( m ) ;
}

/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/


void test_gsl_vector ( void )
{
  size_t vs = 10 ;
  size_t vss = 5 ;
  gsl_vector *v = gsl_vector_calloc ( vs ) ;
  for ( size_t i = 0  ; i < vss ; i++ )
    {
      gsl_vector_set(v,i,1.);
    }
  for ( size_t i = 0  ; i < v->size ; i++ )
    {
      printf("%20.15f  ",gsl_vector_get(v,i));
    }
  printf("\n\n");
  gsl_vector_fprintf(stdout,v,"%20.15f");
  gsl_vector_free ( v );
  printf("\n\n");
  gsl_vector_int *vi = gsl_vector_int_calloc ( vs ) ;
  gsl_vector_int_set_all ( vi , 1 );
  gsl_vector_int_fprintf(stdout, vi , "%20d");
  gsl_vector_int_free(vi);
}


/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/

#define PRINT_SIZE(_t) do{				\
    printf("size of %-20s : %zu \n",#_t,sizeof(_t));	\
  } while(0)

void test_size (void)
{
  PRINT_SIZE(double) ;
  PRINT_SIZE(int) ;
  PRINT_SIZE(long);
  PRINT_SIZE(long int);
  PRINT_SIZE(unsigned int);
  PRINT_SIZE(unsigned long int);
  PRINT_SIZE(long double);
  PRINT_SIZE(size_t);
  PRINT_SIZE(long long);
}

#undef PRINT_SIZE

/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
