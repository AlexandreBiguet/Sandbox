#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Obtain a backtrace and print it to stdout. */
void print_trace(void) {
  void *array[200];
  size_t size;
  char **strings;
  size_t i;

  size = backtrace(array, 200);
  strings = backtrace_symbols(array, size);

  printf("Obtained %zd stack frames.\n", size);

  for (i = 0; i < size; i++) printf("%5lu %s\n", i, strings[i]);

  // for ( i = size -1 ; i>=0 ; i--)
  //	printf ("%s\n\t", strings[i]);

  free(strings);
}

void print_trace2(void) {
  void *array[200];
  size_t size;
  char **strings;
  size_t i;
  size = backtrace(array, 200);
  strings = backtrace_symbols(array, size);

  // printf("splitting \t  ' %s ' into tokens \n",strings[0] );
  char *pch;
  char *buf;
  // buf = strdup ( strings[0] );
  // pch = strtok ( buf , " " ) ;
  pch = strtok(strings[0], " ");
  int count = 0;
  while (pch != NULL) {
    count++;
    if (count == 4) printf("%s \n", pch);
    pch = strtok(NULL, " ");
  }

  free(strings);
}

void print_location(void) {
  void *array[200];
  size_t size;
  char **strings;
  size_t i, c;
  size = backtrace(array, 200);
  strings = backtrace_symbols(array, size);

  char *pch;
  char fcts[size][100];
  for (i = 0; i < size; i++) {
    c = 0;
    pch = strtok(strings[i], " ");
    while (pch != NULL) {
      c++;
      if (c == 4) {
        sprintf(fcts[i], "%s", pch);
      }
      pch = strtok(NULL, " ");
    }
  }
  printf("location : ");
  // for ( i = size-1 ; i >= 0 ; i--)
  for (i = 1; i < size - 2; i++) {
    printf("%s / ", fcts[i]);
  }
  printf("\n");
  free(strings);
}

/* A dummy function to make the backtrace more interesting. */
void dummy_function(void) { print_trace(); }

void test_function1(void) { dummy_function(); }

void test_function1_prime() { print_trace(); }

void test_function2(void) {
  test_function1();
  test_function1_prime();
}

void test_function3(void) { test_function2(); }

void test_function4(void) { test_function3(); }

void test_function5(void) { test_function4(); }

void test_function6(void) { test_function5(); }

void test_function7(void) { test_function6(); }

void test_function8(void) { test_function7(); }

void f1(void) { print_trace(); }

void f2(void) {
  print_trace();
  f1();
}

void f3(void) {
  print_trace2();
  f2();
}

void g1(void) { print_location(); }

void g2(void) {
  print_location();
  g1();
}

void g3(void) {
  print_location();
  g2();
}

int main(void) {
  // dummy_function ();
  // test_function8();
  // test_function8();
  // print_trace();
  // f3();
  g3();
  // int i=10;
  // while( i>=0 ) {printf("%d ",i); i--;}
  return 0;
}
