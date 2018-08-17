#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
  char w[1024];
  sprintf(w,
          "\\documentclass{report} \n\n"
          "\\usepackage{tikz}\n\n"
          "\\begin{document}\n\n"
          "\\end{document}\n");
  // printf ("%s",w);
  FILE* f = NULL;
  int i;
  for (i = 1; i < argc; i++) {
    f = fopen(argv[i], "w");
    if (f == NULL) {
      printf("Probleme ouverture fichier %s \n", argv[i]);
      exit(1);
    }
    fprintf(f, "%s", w);
    fclose(f);
  }

  return 0;
}
