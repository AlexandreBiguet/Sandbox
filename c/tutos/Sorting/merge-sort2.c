/* https://www.tutorialspoint.com/data_structures_algorithms/merge_sort_program_in_c.htm */

#include <stdio.h>
#define max 10

/* Complexity O ( n log(n) ) */


//int a[10] = { 10, 14, 19, 26, 27, 31, 33, 35, 42, 44 };

int a[10] = { 14, 10,  27, 19, 26,  31, 42, 33, 35,  44 };

int count_merge = 0 ; 
int count_sort = 0 ; 

void merging ( int low, int mid, int high ){

  printf ( "count_merge = %d \n", count_merge );
  fflush ( stdout ); 
  count_merge++ ; 
}
					  


void sort(int low, int high) {
  int mid;

  
  printf ( "count_sort = %d \n", count_sort );
  fflush ( stdout );
  count_sort++ ;
  int i ;
  
  if(low < high) {
    mid = (low + high) / 2;
    sort(low, mid);
    printf ( "1: " );
    for ( i = 0 ; i < high ; i++ )
      printf ("%d ", a[i] ) ; 
    printf ( "\n" );
    fflush(stdout);

    sort(mid+1, high);
    printf ( "2: " );
    for ( i = 0 ; i < high ; i++ )
      printf ("%d ", a[i] ) ; 
    printf ( "\n" );
    fflush(stdout);
    merging(low, mid, high);
  } else { 
    return;
  }   
}

int main ( void ){

  sort ( 0, max ); 

  return 0 ; 
}

