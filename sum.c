#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
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
  int size = end - start, status, id;

  for (int i = 0; i < NUM_PROCESSES; i++) {
  
    id =fork();
    if(id == 0)
    {
    naive_vector_sum(vec_a, vec_b, vec_c, i * ((size) / NUM_PROCESSES), i * ((size / NUM_PROCESSES) + 1));
    }
    else{
    waitpid (-1, &status, 0);
    exit(1);
    }
  }
}