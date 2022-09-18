#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include "test.h"
#include "sum.h"

#include <sys/shm.h>
#include <sys/stat.h>
#include <pthread.h>


#define NUM_PROCESSES 8
#define NUM_THREADS 8
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
void *wrapper(void *par){
  p * parametros = (p*)par;
  naive_vector_sum(parametros->vec_a, parametros->vec_b, parametros->vec_c, parametros->start, parametros->end);
  pthread_exit(0);
}
void thread_vector_sum(int * vec_a, int * vec_b, int * vec_c, int start, int end){
  pthread_t threads[NUM_THREADS];
  int *vetA, *vetB, *vetC;
  p *parametros[NUM_THREADS];
  int i;
  int size = end - start;

  for(i = 0; i < NUM_THREADS; i++){
    parametros[i] = (p*)malloc(sizeof(p));

    parametros[i]->vec_a = vec_a;
    parametros[i]->vec_b = vec_b;
    parametros[i]->vec_c = vec_c;
    parametros[i]->start = i*(size / NUM_THREADS);
    parametros[i]->end = (i+1)*(size / NUM_THREADS);

    pthread_create(&threads[i], NULL, wrapper, (void *)parametros[i]);
  }

  for(i = 0; i < NUM_THREADS; i++){
    pthread_join(threads[i], NULL);

    free(parametros[i]);
  }
}