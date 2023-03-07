#!/bin/bash

gcc -O1 -fopenmp -o test_omp test_omp_simd.c && ./test_omp
