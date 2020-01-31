#!/usr/bin/env gnuplot
set style arrow 1 head filled size screen 0.03,10,85 ls 5


set terminal postscript eps enh color; set output "timing.eps"
#set terminal gif optimize size 1000, 1000 animate delay 20; set output "pos.gif"
set key spacing 4 font "Helvetica,24" top center
load 'moreland.pal'
set ylabel "T" font "Helvetica,24"
set xlabel "N" font "Helvetica,24"
set xtics font "Helvetica,18"
set ytics font "Helvetica,18"

plot \
"timing_10.dat" using ($1*$1):2 with linespoints lw 5 pt 7 ps 3.5 lc rgb '#0000ff'  title "10x10",\
"timing_15.dat" using ($1*$1):2 with linespoints lw 5 pt 15 ps 3.5 lc rgb '#d2691e' title "15x15",\
"timing_20.dat" using ($1*$1):2 with linespoints lw 5 pt 9 ps 3.5 lc rgb '#002002'  title "20x20"
