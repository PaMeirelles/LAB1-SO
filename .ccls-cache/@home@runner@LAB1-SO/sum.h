struct parametros{
  int *vec_a;
  int *vec_b;
  int *vec_c;
  int start;
  int end;
} typedef p;
void naive_vector_sum(int * vec_a, int * vec_b, int * vec_c, int start, int end);
void fancy_vector_sum(int * vec_a, int * vec_b, int * vec_c, int start, int end);
void thread_vector_sum(int * vec_a, int * vec_b, int * vec_c, int start, int end);