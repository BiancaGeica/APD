#!/usr/bin/env bash

N=1000
P=2

gcc dem_seq.c -o seq -lpthread -Wall
gcc dem_parallel.c -o parallel -lpthread -Wall

if [ ! -f "seq" ]
then
    echo "Nu exista binarul seq"
    exit
fi

if [ ! -f "parallel" ]
then
    echo "Nu exista binarul parallel"
    exit
fi

./seq $N > seq.txt
./parallel $N $P > rez.txt

diff seq.txt rez.txt

rm -rf seq.txt rez.txt