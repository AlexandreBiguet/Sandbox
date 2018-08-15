#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int t, n, p;
  double x, y, z;
} Stest;

int main(void) {
  double t[100];
  printf("sizeof ( int  ) = %zu \n", sizeof(int));
  printf("sizeof ( int* ) = %zu \n", sizeof(int *));
  printf("sizeof ( dbl  ) = %zu \n", sizeof(double));
  printf("sizeof ( dbl* ) = %zu \n", sizeof(double *));
  printf("sizeof ( Ste  ) = %zu \n", sizeof(Stest));
  printf("sizeof ( tab  ) = %zu \n", sizeof(t));

  return 0;
}
