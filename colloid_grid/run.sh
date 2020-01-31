#!/bin/bash
for itr in `seq 5 2 49`
do
    sed -e "s/ROOTNUM_VAL/$itr/g" main.template > main.cpp
    make clean
    make all
    ./coll >> timing_20.dat
    echo $itr
done 
