#include <omp.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main() {
  int N = 1000000000; // size of the array
  int *A = malloc(N * sizeof(int)); // the array to check
  int nonzero; // flag to indicate if all elements are nonzero

  clock_t start, end;
  double cpu_time_used;

  // initialize the array with some values
  for (int i = 0; i < N; i++) {
    A[i] = i + 1;
  }

  start = clock(); // get the start time

  for (int j = 0; j < 10; j++) {

      nonzero = 1;
      // use omp simd to check each element in parallel
      // #pragma omp simd reduction(&:nonzero)
      for (int i = 0; i < N; i++) {
        nonzero &= (A[i] != 0); // bitwise and with the flag
      }

  }

  end = clock(); // get the end time
  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC; // calculate the elapsed time in seconds
  printf("The work took %f seconds to execute.\n", cpu_time_used);

  // print the result
  if (nonzero) {
    printf("All elements are nonzero\n");
  } else {
    printf("Some elements are zero\n");
  }

  return 0;
}
