#include "sum.h"
#include <stdlib.h>
#include <stdio.h>

void print_vector(int * vector, int size){
  for(int i=0; i < size; i++){
    printf("%d ", vector[i]);
  }
  printf("\n");
}

void random_filler(int size, int * vector, int bound){
  for(int i=0; i < size; i++){
    vector[i] = rand() % bound;
  }
}

void fill_vector(int size, int * vector, int filler){
  for(int i=0; i < size; i++){
    vector[i] = filler;
  }
}


void test_sum(int size, char mode, void (*sum)(int *, int *, int *, int)){
  int * vec_a = malloc(sizeof(int) * size);
  int * vec_b = malloc(sizeof(int) * size);
  int * vec_c = malloc(sizeof(int) * size);

  fill_vector(size, vec_c, 0);

  switch(mode){
    case 'z':{
      fill_vector(size, vec_a, 0);
      fill_vector(size, vec_b, 0);
      break;
    }
    case 'c':{
      fill_vector(size, vec_a, rand() % 10);
      fill_vector(size, vec_b, rand() % 10);
      break;
    }
    case 's':{
      random_filler(size, vec_a, rand() % 10);
      random_filler(size, vec_b, rand() % 10);
      break;
    }
    case 'b':{
      random_filler(size, vec_a, RAND_MAX / 2);
      random_filler(size, vec_b, RAND_MAX / 2);
    }
  }

  sum(vec_a, vec_b, vec_c, size);

  print_vector(vec_a, size);
  print_vector(vec_b, size);
  print_vector(vec_c, size);
}