#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include "test.h"
#include <sys/shm.h>
#include <sys/stat.h>

#define NUM_PROCESSES 8
void naive_vector_sum(int * vec_a, int * vec_b, int * vec_c, int start, int end)
{
  for(int i = start; i < end; i++)
  {
    vec_c[i] = vec_a[i] + vec_b[i];
  }
}

void fancy_vector_sum(int * vec_a, int * vec_b, int * vec_c, int start, int end)
{
  int size = end - start, status, id, pid;
  int * temp_vec;
  for (int i = 0; i < NUM_PROCESSES; i++) {
    if ((id = fork()) < 0)
      {
      printf("Erro na criação do novo processo");
      exit (-2);
      }
      else if (id == 0)
      {
      naive_vector_sum(vec_a, vec_b, vec_c, i * (size / NUM_PROCESSES), (i+1) * (size / NUM_PROCESSES));
      }
      else
      {
      pid = wait (&status);
      exit(-1);
      }
    }
}