#!/bin/bash
rm positions/*.dat
make clean
make
./coll > log
wait
cd plots
gnuplot plot.gnu
cd ..
