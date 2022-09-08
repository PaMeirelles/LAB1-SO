// Rafael Paladini Meirelles 2111538
// Felipe Mello 1811435

#include "sum.h"
#include "test.h"
#include <stdio.h>
#include <unistd.h>
#define NUM_PROCESSES 8

int main(void) {

  int index = 0, status;

  for (int i = 0; i < NUM_PROCESSES; ++i) {
    
    if(fork() == 0) 
      exit(0);
    
    for (int i = 0; i < NUM_PROCESSES; ++i) {
      test_sum(1000, index, 'c', naive_vector_sum);

      // Adicionei esse index pra fazer o controle de operação de cada processo
      // O primeiro pega de 0 a 124, o segundo de 125 a 249
      index += 125;
  		waitpid (-1, &status, 0);
  	}
  }

  return 0;
}