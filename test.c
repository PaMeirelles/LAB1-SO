#include "sum.h"
#include "timer.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/stat.h>

void print_vector(int *vector, int size) {
  for (int i = 0; i < size; i++) {
    if (i < 5 || i > size - 5) {
      printf("%*d ", 10, vector[i]);
    } else if (i == 5) {
      printf(". . . ");
    }
  }
  printf("\n");
}

void random_filler(int size, int *vector, int bound) {
  
  for (int i = 0; i < size; i++) {
    //printf("%d %d %d\n", i, bound, size);
    vector[i] = rand() % bound;
  }
}

void fill_vector(int size, int *vector, int filler) {
  for (int i = 0; i < size; i++) {
    vector[i] = filler;
  }
}

void test_sum(int size, char mode, void (*sum)(int *, int *, int *, int, int), char type_of_sum) {
  struct timeval start, stop;
  gettimeofday(&start, NULL);


  int segmento;
  int *vec_a = malloc(sizeof(int) * size);
  int *vec_b = malloc(sizeof(int) * size);
  int *vec_c;
  if(type_of_sum == 'l'){
    vec_c = malloc(sizeof(int) * size);
  }
  else{
    segmento = shmget (IPC_PRIVATE, sizeof (int) * size, IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
    vec_c = (int *) shmat (segmento, 0, 0); 
  }
  
  if(vec_a == NULL || vec_b == NULL || vec_c == NULL){
    printf("Falha na alocação de memória\n");
    exit(-3); 
  }

  fill_vector(size, vec_c, 0);
  
  switch (mode) {
    case 'z': {
      fill_vector(size, vec_a, 0);
      fill_vector(size, vec_b, 0);
      break;
    }
    case 'c': {
      fill_vector(size, vec_a, rand() % 5);
      fill_vector(size, vec_b, rand() % 5);
      break;
    }
    case 's': {
      random_filler(size, vec_a, rand() % 10 + 1);
      random_filler(size, vec_b, rand() % 10 + 1);
      break;
    }
    case 'b': {
      random_filler(size, vec_a, RAND_MAX / 2);
      random_filler(size, vec_b, RAND_MAX / 2);
    }
  }

  sum(vec_a, vec_b, vec_c, 0, size);
  
  print_vector(vec_a, size);
  print_vector(vec_b, size);
  print_vector(vec_c, size);

  gettimeofday(&stop, NULL);
  printf("Process finished in %.3fms\n", timedifference_msec(start, stop));

  free(vec_a);
  free(vec_b);
  if (type_of_sum == 'l'){
  free(vec_c);
  }
  else{
      // libera a memória compartilhada do processo
      shmdt (vec_c);
      // libera a memória compartilhada
      shmctl (segmento, IPC_RMID, 0);
  }

  
}

void complete_test(int size){
  char modes[4] = {'z', 'c', 's', 'b'};
  printf("\n\n\n\nTestando para vetores de tamanho %d\n========================================\n", size);

  for(int i = 0; i < 4; i++){
  printf("\nTeste %d: \n-----------\n\n\n", i+1);
  
  printf("Soma tradicional: \n");
  test_sum(size, modes[i], naive_vector_sum, 'l');

  printf("\nSoma paralela: \n");
  test_sum(size, modes[i], fancy_vector_sum, 'p');
  
    printf("\nSoma com threads: \n");
  test_sum(size, modes[i], thread_vector_sum, 'p');
  }
  

}