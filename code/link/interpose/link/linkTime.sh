#!/bin/bash

gcc -DLINKTIME -c mymalloc.c -o link/mymalloc.o
gcc -c int.c -o link/int.o

gcc -Wl,--wrap,malloc -Wl,--wrap,free -o intl link/int.o link/mymalloc.o
