#include <omp.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int data_dep(int8_t *A, int N){
  int off = 32;
  #pragma omp simd simdlen(8),order(concurrent)
  for(int i = off; i < N; i++)
  {
      A[i] += (A[i-off] > 0) * (A[i-off] - A[i]);
  }
}

int is_any_zero(int8_t *array, int size) {
  int result = 0; // initialize result to false
  printf("before result: %d\n", result);
  #pragma omp simd reduction(|:result) // use logical OR reduction
  for (int i = 0; i < size; i++) {
    result = result | (array [i] == 1); // set result to true if any element is zero
  }
  printf("after result: %d\n", result);

  return result;
}

//#pragma omp declare simd inbranch
int is_any_zero_1(int8_t *A, int N) {
  int off=128, result = 0; // initialize result to false
  printf("before result: %d\n", result);

  //#pragma omp simd
  for (int i=0; i<N; i+=off) {
    #pragma omp simd simdlen(8), reduction(|:result) // use logical OR reduction
    for(int j=i; j<i+off; j++){
        result |= (A[i] == -1); // set result to true if any element is zero
    }
    if(result != 0){
        return result;
    }
  }

  printf("after result: %d\n", result);

  return result;
}

int is_any_zero_2(int8_t *array, int size) {
  int i, flag, result = 0; // initialize result to false
  printf("before result: %d\n", result);
  #pragma omp simd reduction(|:result) // use logical OR reduction
  for (i = 0; i < size; i++) {
    result = result | (array [i] == 1); // set result to true if any element is zero
    if(result != 0)
    {
        flag = 1;
    }
  }
  printf("after result: %d %d\n", result, i);

  return result;
}




int main() {
  int N = 1280000000; // size of the array
  int8_t *A = malloc(N * sizeof(int)); // the array to check
  int k; // flag to indicate if all elements are nonzero

  clock_t s0, e0;

  // initialize the array with some values
  #pragma omp simd order(concurrent)
  for (int i = 0; i < N; i++) {
    A[i] = rand() % 0xf;
  }

  printf("%ld %d\n", CLOCKS_PER_SEC, N);

  s0 = clock(); // get the start time

  is_any_zero_1(A, N);
  //k = data_dep(A, N);

  e0 = clock(); // get the start time
  printf("%ld %ld The simd took %f seconds to execute. %d\n", s0, e0, (double) (e0 - s0)/1000000, N);

  return 0;
}
