#!/usr/bin/env bash

clang++ -std=c++11 billions.cpp -o ./build/billions && pushd build && ./billions "$@"

# | tee ./build/out.txt

# 1 billion values output to file =  161.63s user 10.03s system 99% cpu 2:52.51 total
# 9 GB file
