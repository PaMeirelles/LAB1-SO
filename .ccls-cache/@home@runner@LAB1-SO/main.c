// Rafael Paladini Meirelles 2111538
// Felipe Mello 1811435

#include "sum.h"
#include "test.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#define NUM_PROCESSES 8

int main(void) {
  test_sum(1000, 'c', naive_vector_sum);
  test_sum(1000, 'c', fancy_vector_sum);

  return 0;
}