#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main ( int argc , char * argv[] )
{
  if ( argc < 2 ) 
    {
      printf ("exit");
      return 1;
    }
  int i ;
  int N = atoi ( argv[1] ) ;
  double m = 0. , M = 5. , x , it ,fx ;
  it = (M - m)/(double)N ;
  for ( i = 0  ; i < N ; i++ )
    {
      x = m + i * it ;
      fx = sin (x) ;
      printf ("%15.5f %15.5f\n" , x , fx );
    }
  return 0 ;
}



