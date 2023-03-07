#!/bin/bash

if [ $1 ]
then
    o=$1
else
    o=1
fi

cc=/usr/bin/clang

rm -rf test_omp
$cc -O$o -fopenmp -o test_omp test_omp_simd.c
./test_omp

rm test_omp
