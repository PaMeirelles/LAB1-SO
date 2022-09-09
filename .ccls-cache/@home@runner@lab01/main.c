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

  int index = 0, status, id;

  for (int i = 0; i < NUM_PROCESSES; ++i) {
    
    if((id =fork()) < 0) 
    {
      exit(0);
    }
    else if(id == 0)
    {
    test_sum(1000, index, 'c', naive_vector_sum);
    }
  
    index += 125;
  }
    waitpid (-1, &status, 0);

  return 0;
}