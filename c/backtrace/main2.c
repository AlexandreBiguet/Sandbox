#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_MAXSIZE 1024

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

void be_located(char *loc) {
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

  char temp[100];

  size_t s = 0, st = 0;
  for (size_t i = 0; i < size - 1; i++) {
    st = strlen(fcts[i]);
    s += st;
  }

  size_t slo = strlen(loc);

  if (slo <= s) {
    printf("probleme taille");
    exit(-1);
  }

  for (i = 1; i < size - 1; i++) {
    if (i == 1)
      sprintf(loc, "%s / ", fcts[i]);
    else {
      sprintf(temp, "%s / ", fcts[i]);
      strcat(loc, temp);
    }
  }
  free(strings);
}

void f(void) {
  char loc[5];
  be_located(loc);
  puts(loc);
}

void g(void) { f(); }

void h(void) { g(); }

void i(void) { h(); }

void j(void) { print_location(); }

int main(void) {
  i();

  j();
  return 0;
}
