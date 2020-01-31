#!/usr/bin/env gnuplot
set style arrow 1 head filled size screen 0.03,10,85 ls 5

set terminal gif animate delay 5
set output "pos.gif"
#set terminal postscript eps enh color
#set output "pos.eps"
unset key;


set size square
set xrange [0:1]
set yrange [0:1]

do for [t=0:299] {
    infile = sprintf('../positions/%06d.dat',t)
        set label 1 infile at 0.5,0.95 
        plot \
        infile using  1:2:(0.02) with circles notitle #,\
        #infile using  1:2:($0+1) with labels notitle 
}
