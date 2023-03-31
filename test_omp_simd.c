#include <omp.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <immintrin.h>

int data_dep(int8_t *A, int N){
  int off = 32;
  #pragma omp simd simdlen(8)
  for(int i = off; i < N; i++)
  {
      A[i] += (A[i-off] > 0) * (A[i-off] - A[i]);
  }
  return 1;
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
  int i, off=32, result = 0; // initialize result to false
  printf("before result: %d\n", result);

  //#pragma omp simd
  for (i=0; i<N; i+=off) {
   
    //#pragma omp simd simdlen(32), reduction(|:tmp) //, aligned(A:32) // use logical OR reduction
    //#pragma omp simd reduction(|:result) aligned(A:64)
    #pragma omp simd simdlen(32), reduction(|:result) //, aligned(A:32) // use logical OR reduction
    for(int j=i; j<i+off; j++){
        result |= (A[i] == -1); // set result to true if any element is zero
    }
    result |= result;
    if(result != 0){
        //return result;
        break;
    }
  }

  printf("after result: %d %d\n", result, i);

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

//#pragma omp declare simd inbranch
int is_any_zero_3(int8_t *A, int N) {
  int i, off=64, result = 0; // initialize result to false
  printf("before result: %d\n", result);

  //#pragma omp simd
  for (i=0; i<N; i+=off) {
    // Use pragma omp simd with additional clauses
    #pragma omp simd simdlen(32), reduction(|:result), aligned(A:32), safelen(64)
    for(int j=i; j<i+off; j++){
        result |= (A[i] == -1); // set result to true if any element is zero
    }
    if(result != 0){
        //return result;
        break;
    }
  }

  printf("after result: %d %d\n", result, i);

  return result;
}

int is_any_zero_4(int8_t *A, int N) {
  int i, off=64, result = 0; // initialize result to false
  __m128i vresult, va, vcmp, flag=_mm_set1_epi8(-1);
  printf("before result: %d\n", result);

  for (i=0; i<N; i+=off) {
    vresult = _mm_set1_epi8(0); // initialize vresult to false

    for(int j=i; j<i+off; j+=16){
        //__m128i va = _mm_load_si128((__m128i const *)(A+j));
        va = _mm_load_si128((__m128i const *)(A+j));
        //__m128i vcmp = _mm_cmpeq_epi8(va, _mm_set1_epi8(-1));
        vcmp = _mm_cmpeq_epi8(va, flag);
        vresult = _mm_or_si128(vresult, vcmp);
    }

    result |= _mm_movemask_epi8(vresult); // set result to true if any element is -1

    if(result != 0){
        break;
    }
  }

  printf("after result: %d %d\n", result, i);

  return result;
}

int is_any_zero_5(int8_t *A, int N) {
  int i, off=32, result = 0; // initialize result to false
  printf("before result: %d\n", result);

  for (i=0; i<N; i+=off) {
    int partial_result = 0; // initialize partial result to false

    #pragma omp simd reduction(|:partial_result) aligned(A:64)
    for(int j=i; j<i+off; j++){
      partial_result |= (A[j] == -1); // set partial result to true if any element is -1
    }

    result |= partial_result; // set result to true if any element is -1
    if(result != 0) { // terminate outer loop if result is non-zero
      break;
    }
  }

  printf("after result: %d %d\n", result, i);
  return result;
}

//int is_any_zero_6(int8_t *A, int N) {
int test_6(int8_t *A, int N) {
  int i, result = 0; // initialize result to false
  __m128i va, vcmp, flag=_mm_set1_epi8(-1), vresult = _mm_set1_epi8(0); 
  printf("before result: %d\n", result);

  for(i=0; i<N; i+=16){
    va = _mm_load_si128((__m128i const *)(A+i));
    vcmp = _mm_cmpeq_epi8(va, flag);
    vresult = _mm_or_si128(vresult, vcmp);
    result |= _mm_movemask_epi8(vresult); // set result to true if any element is -1  
    if(result != 0){
        break;
    }
  }

  printf("after result: %d %d\n", result, i);

  return result;
}

int test_7(int8_t *A, int N) {
    int i, j, flag = 0;
    __m256i vecA, cmpr, minus_one = _mm256_set1_epi8(-1);

    for (i = 0; i < N; i += 32) {
        vecA = _mm256_loadu_si256((__m256i *)(A + i));
        cmpr = _mm256_cmpeq_epi8(vecA, minus_one);
        flag = _mm256_movemask_epi8(cmpr);
        if (flag != 0) {
            break;
        }
        j+=1;
    }

    printf("after result: %d %d %d\n", flag, i, j);
    return flag;
}


int set_test(){
    // Declare an array of 32 integers
    int arr[32];
    // Create a vector with all elements set to 42
    __m128i vec = _mm_set1_epi32(42);
    // Store the vector into the array using a loop
    for (int i = 4; i < 32; i += 4) {
    // Cast the array pointer to __m128i*
    //_mm_store_si128((__m128i*)&arr[i], _mm_set1_epi32(42));
    _mm_store_si128((__m128i*)&arr[i], _mm_setr_epi32(1,2,3,4));
    return 0;
    }
}

int main() {

  int N = 1280000000; // size of the array
  int8_t *A = aligned_alloc(32, N * sizeof(int8_t)); // the array to check
  int k; // flag to indicate if all elements are nonzero

  clock_t s0, e0;

  // initialize the array with some values
  #pragma omp simd
  for (int i = 0; i < N; i++) {
    A[i] = rand() % 0xf;
  }

  printf("%ld %d\n", CLOCKS_PER_SEC, N);

  s0 = clock(); // get the start time
  is_any_zero_1(A, N);
  //k = data_dep(A, N);
  e0 = clock(); // get the start time
  printf("fuc 1 %ld %ld The simd took %f seconds to execute. %d\n", s0, e0, (double) (e0 - s0)/1000000, N);

  s0 = clock(); // get the start time
  is_any_zero_3(A, N);
  e0 = clock(); // get the start time
  printf("fuc 3 %ld %ld The simd took %f seconds to execute. %d\n", s0, e0, (double) (e0 - s0)/1000000, N);

  s0 = clock(); // get the start time
  is_any_zero_4(A, N);
  e0 = clock(); // get the start time
  printf("fuc 4 %ld %ld The simd took %f seconds to execute. %d\n", s0, e0, (double) (e0 - s0)/1000000, N);

  s0 = clock(); // get the start time
  is_any_zero_5(A, N);
  e0 = clock(); // get the start time
  printf("fuc 5 %ld %ld The simd took %f seconds to execute. %d\n", s0, e0, (double) (e0 - s0)/1000000, N);

  s0 = clock(); // get the start time
  //is_any_zero_6(A, N);
  test_6(A, N);
  e0 = clock(); // get the start time
  printf("fuc 6 %ld %ld The simd took %f seconds to execute. %d\n", s0, e0, (double) (e0 - s0)/1000000, N);

  s0 = clock(); // get the start time
  //is_any_zero_6(A, N);
  test_7(A, N);
  e0 = clock(); // get the start time
  printf("fuc 7 %ld %ld The simd took %f seconds to execute. %d\n", s0, e0, (double) (e0 - s0)/1000000, N);

  return 0;
}