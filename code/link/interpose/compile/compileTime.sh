#!/bin/bash

PWD_M="/home/mocai/CS/code/link/interpose"
echo $PWN_M
TARGET_M="/home/mocai/CS/code/link/interpose/compile"

gcc -DCOMPILETIME -c $PWD_M/mymalloc.c -o $TARGET_M/mymalloc.o
gcc -I. -o $TARGET_M/intc $PWD_M/int.c $TARGET_M/mymalloc.o

#bash ./compile/intc
