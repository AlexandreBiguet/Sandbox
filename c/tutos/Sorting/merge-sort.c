/* https://www.tutorialspoint.com/data_structures_algorithms/merge_sort_program_in_c.htm */

#include <stdio.h>
#define max 10

/* Complexity O ( n log(n) ) */


//int a[10] = { 10, 14, 19, 26, 27, 31, 33, 35, 42, 44 };

int a[10] = { 14, 10,  27, 19, 26,  31, 42, 33, 35,  44 };
int b[10] = {0,0,0,0, 0,0,0 ,0,0,0};

void display() {
  int i;
  printf("[");
	
  // navigate through all items 
  for(i = 0;i<max;i++) {
    printf("%d ", a[i]);
  }
  printf("]    [");
  for(i = 0;i<max;i++) {
    printf("%d ", b[i]);
  }
  printf("]\n");
}


void merging(int low, int mid, int high) {
  int l1, l2, i, iter = 0 ;

  for(l1 = low, l2 = mid + 1, i = low; l1 <= mid && l2 <= high; i++) {
    printf (" iter (%d) \n", iter ); 
    if(a[l1] <= a[l2])
      b[i] = a[l1++];
    else
      b[i] = a[l2++];
    display();
    iter++ ; 
  }

  printf ( "\n" ); 
  while(l1 <= mid) {   
    b[i++] = a[l1++];
    display();
  }

  printf ( "\n" );
  while(l2 <= high)   {
    b[i++] = a[l2++];
    display();
  }

  for(i = low; i <= high; i++)
    a[i] = b[i];
}

void sort(int low, int high) {
  int mid;
   
  if(low < high) {
    mid = (low + high) / 2;
    sort(low, mid);
    sort(mid+1, high);
    merging(low, mid, high);
  } else { 
    return;
  }   
}

int main() { 
  int i;

  printf("List before sorting\n");   
  display();
  printf("\n" ); 

  sort(0, max);
  
  printf("\n" ); 
  printf("\nList after sorting\n");
   
  display();
}
