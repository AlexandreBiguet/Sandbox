#include <stdio.h>
#include <stdlib.h>
#include <time.h>

size_t fact(size_t n) {
  size_t i;
  size_t r = 1;
  for (i = 1; i <= n; i++) {
    r *= i;
  }
  return r;
}

size_t comb_1(size_t n, size_t p) {
  size_t r = fact(n);
  size_t d = fact(p);
  size_t e = n - p;
  e = fact(e);
  r = r / (d * e);
  return r;
}

/* Much much better way of calculating n! / (p!*(n-p)!) */

size_t comb_2(size_t n, size_t p) {
  size_t C = 1;

  size_t k;
  for (k = 1; k <= p; k++) {
    C *= (n - k + 1);
    C /= k;
  }

  return C;
}

int main(void) {
  size_t n = 30;
  size_t p = 15;

  size_t nf = fact(n);
  size_t pf = fact(p);

  printf("n  = %zu \t p  = %zu \n", n, p);
  printf("n! = %zu \t p! = %zu \n", nf, pf);

  clock_t ti1 = clock();

  size_t C_1 = comb_1(n, p);

  clock_t tf1 = clock();

  size_t C_2 = comb_2(n, p);

  clock_t tf2 = clock();

  printf("C_1 = %zu \t clock = %zu \n", C_1, tf1 - ti1);
  printf("C_2 = %zu \t clock = %zu \n", C_2, tf2 - tf1);

  return 0;
}
