#include <omp.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main() {
  int N = 500000000; // size of the array
  int *A = malloc(N * sizeof(int)); // the array to check
  int nonzero; // flag to indicate if all elements are nonzero

  clock_t s0, e0, s1, e1;
  double t0, t1;

  // initialize the array with some values
  for (int i = 0; i < N; i++) {
    A[i] = i + 1;
  }

  printf("%ld %d\n", CLOCKS_PER_SEC, N);


  s0 = clock(); // get the start time

  for (int j = 0; j < 10; j++) {

      nonzero = 1;
      // use omp simd to check each element in parallel
      // #pragma omp simd reduction(&:nonzero)
      for (int i = 0; i < N; i++) {
        nonzero &= (A[i] != 0); // bitwise and with the flag
      }

  }

  e0 = clock(); // get the end time
  t0 = ((double) (e0 - s0)) / CLOCKS_PER_SEC; // calculate the elapsed time in seconds
  printf("%ld %ld The simd took %f seconds to execute.\n", s0, e0, t0);


  s1 = clock(); // get the start time

  for (int j = 0; j < 10; j++) {

      // break;
      nonzero = 1;
      for (int i = 0; i < N; i++) {
        nonzero &= (A[i] != 0); // bitwise and with the flag
      }

  }

  e1 = clock(); // get the end time
  t1 = ((double) (e1 - s1)) / CLOCKS_PER_SEC; // calculate the elapsed time in seconds
  printf("%ld %ld  No simd took %f seconds to execute.\n", s1, e1, t1);



  // print the result
  if (nonzero) {
    printf("All elements are nonzero\n");
  } else {
    printf("Some elements are zero\n");
  }

  return 0;
}
