#!/bin/bash

make clean
make C=g++ && ./1 gcc
make clean
make C=clang++ && ./1 clang
./plot.sh gcc_acor gcc_acor.png
./plot.sh clang_acor clang_acor.png