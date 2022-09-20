#!/bin/bash

if [ ! $1 ]
then
    flag=1
else
    flag=$1
fi

rm *.exe

#sed 's/#pragma/\/\/#pragma/g' simd.cpp > serial.cpp
#g++ -O$flag -mavx2 -fopenmp -fopt-info-vec-optimized -ftree-vectorizer-verbose=2 -o a_serial.exe serial.cpp
#clang++ -O$flag -mavx2 -Rpass="loop|vect" -Rpass-missed="loop|vect" -Rpass-analysis="loop|vect" -fopenmp -o a_serial.exe serial.cpp
#rm serial.cpp

#g++ -O$flag -mavx2 -fopt-info-vec-optimized -ftree-vectorizer-verbose=2 -o a_serial.exe simd.cpp
clang++-16 -O$flag -mavx2 -Rpass="loop|vect" -Rpass-missed="loop|vect" -Rpass-analysis="loop|vect" -o a_serial.exe simd.cpp
#icpc -O$flag -mavx2 -D NOFUNCCALL -qopt-report=1 -qopt-report-phase=vec -o a_serial.exe simd.cpp

echo serial compiled

#g++ -O$flag -mavx2 -fopenmp -fopt-info-vec-optimized -ftree-vectorizer-verbose=2 -o a_simd.exe simd.cpp
clang++-16 -O$flag -mavx2 -Rpass="loop|vect" -Rpass-missed="loop|vect" -Rpass-analysis="loop|vect" -fopenmp -o a_simd.exe simd.cpp
#icpc -O$flag -mavx2 -D NOFUNCCALL -qopt-report=1 -qopt-report-phase=vec -qopenmp -o a_simd.exe simd.cpp

echo simd compiled


echo serial
./a_serial.exe
echo simd
./a_simd.exe
