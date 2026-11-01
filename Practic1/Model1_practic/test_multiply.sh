#!/usr/bin/env bash

N=1000
P=3

gcc multiply_seq.c -o seq -lpthread -Wall
gcc rezolvare_test1.c -o parallel -lpthread -Wall

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
