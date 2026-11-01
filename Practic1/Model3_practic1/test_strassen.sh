#!/usr/bin/env bash

N=1000
P=3

if [ ! -f "strassen" ]
then
    echo "Nu exista binarul strassen"
    exit
fi

if [ ! -f "strassen_seq" ]
then
    echo "Nu exista binarul strassen_seq"
    exit
fi

./strassen $N $P > parallel.txt
./strassen_seq $N > strassen_seq.txt

diff parallel.txt strassen_seq.txt

rm -rf parallel.txt strassen_seq.txt