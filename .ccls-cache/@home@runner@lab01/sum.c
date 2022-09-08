void naive_vector_sum(int * vec_a, int * vec_b, int * vec_c, int size, int index)
{
  for(int i = index; i < index + 124; i++)
  {
    vec_c[i] = vec_a[i] + vec_b[i];
  }
}