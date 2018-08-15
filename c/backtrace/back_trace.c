#include "utils.h"

/**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/

void print_location(FILE *f) {
  void *array[200];
  size_t size;
  char **strings;
  size_t i, c;
  size = backtrace(array, 200);
  int size_int = (int)size;
  strings = backtrace_symbols(array, size_int);

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
  fprintf(f, "location : ");
  // for ( i = size-1 ; i >= 0 ; i--)
  for (i = 1; i < size; i++) {
    fprintf(f, "%s / ", fcts[i]);
  }
  fprintf(f, "\n");
  free(strings);
}

/**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/

void get_location(char *loc) {
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

  // sizeof(char) = 1
  // sizeof(tab_of_char) = nb de case dans le tableau
  size_t slo = STR_MAXSIZE * sizeof(char);

  if (slo <= s) {
    ERROR(stdout, "Erreur allocation mémoire");
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

/**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/ /**/
