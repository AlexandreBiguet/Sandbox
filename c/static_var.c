#include <stdio.h>

static int nb_appel_func = 0;

void func(void) { nb_appel_func++; }

/* Si une fonction a besoin de savoir combien de fois elle a ete
 * appellée, alors, variable statique locale à la fonction
 * les autres procédures ne devant pas avoir accés à cette variable
 */

void func2(void) {
  static int nb_appel_func2 = 0;
  nb_appel_func2++;
  printf("%d \n", nb_appel_func2);
}

int main(void) {
  func();
  func();
  func();
  printf("%d \n", nb_appel_func);

  func2();  // 1
  func2();  // 2
  func2();  // 3

  return 0;
}
