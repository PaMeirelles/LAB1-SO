#include <stdio.h>
#include "test.h"
#include "sum.h"
// Rafael Paladini Meirelles 2111538
// Felipe Mello --Tua matrícula--

int main(void) {
  test_sum(100000000, 'z', naive_vector_sum);
  return 0;
}