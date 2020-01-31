#!/bin/bash
rm positions/*.dat
wait
make clean
make
./coll > log
wait
cd plots
gnuplot plot.gnu
cd ..
