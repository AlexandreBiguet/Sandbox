#include "GSL-routines.h"
#include "test.h"
#include "utils.h"

int main(void) {
  // TEST_GSLran();
  TEST_gaus_dist();
  TEST_gaus_tail_dist();
  TEST_biv_gaus_dist();
  TEST_exp_dist();
  TEST_laplace_dist();
  return 0;
}
