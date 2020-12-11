#!/bin/bash

PWD_M="/home/mocai/CS/code/link/interpose"
TARGET_M="/home/mocai/CS/code/link/interpose/run"

gcc -DRUNTIME -shared -fpic -o $TARGET_M/mymalloc.so $PWD_M/mymalloc.c -ldl
gcc -o $TARGET_M/intr $PWD_M/int.c $TARGET_M/mymalloc.so

echo "LD_PRELOAD=\"./mymalloc.so\" ./intr"
