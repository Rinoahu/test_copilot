#!/bin/bash

if [ $1 ]
then
    flag=$1
else
    flag=1
fi

if [ $2 ]
then
    cc=$2
else
    cc='gcc'
fi

echo $flag $cc
ln -sf simd_list.cpp simd.cpp
rm -f *.exe


if [ $cc == "gcc" ]
then
    /usr/bin/g++ -O$flag -mavx2 -fopt-info-vec-optimized -ftree-vectorizer-verbose=2 -o a_serial.exe simd.cpp &> log.txt
    /usr/bin/g++ -O$flag -mavx2 -fopenmp -fopt-info-vec-optimized -ftree-vectorizer-verbose=2 -o a_simd.exe simd.cpp &>> log.txt

elif [ $cc == "clang" ]
then
    clang++-16 -O$flag -mavx2 -Rpass="loop|vect" -Rpass-missed="loop|vect" -Rpass-analysis="loop|vect" -o a_serial.exe simd.cpp &> log.txt
    #echo serial compiled
    clang++-16 -O$flag -mavx2 -Rpass="loop|vect" -Rpass-missed="loop|vect" -Rpass-analysis="loop|vect" -fopenmp -o a_simd.exe simd.cpp &>> log.txt
    #echo simd compiled
else
    icpc -O$flag -mavx2 -D NOFUNCCALL -qopt-report=1 -qopt-report-phase=vec -o a_serial.exe simd.cpp && mv simd.optrpt serial.optrpt
    icpc -O$flag -mavx2 -D NOFUNCCALL -qopt-report=1 -qopt-report-phase=vec -qopenmp -o a_simd.exe simd.cpp
    cat *.optrpt
fi

echo serial
./a_serial.exe
echo simd
./a_simd.exe

rm -f simd.cpp *.exe *.optrpt log*.txt
