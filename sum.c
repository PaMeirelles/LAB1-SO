void naive_vector_sum(int * vec_a, int * vec_b, int * vec_c, int size){
  for(int i=0; i < size; i++){
    vec_c[i] = vec_a[i] + vec_b[i];
  }
}