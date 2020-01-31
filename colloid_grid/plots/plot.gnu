#!/usr/bin/env gnuplot
set style arrow 1 head filled size screen 0.03,10,85 ls 5

set terminal postscript eps enh color; set output "pos.eps"
#set terminal gif optimize size 1000, 1000 animate delay 20; set output "pos.gif"
unset key;

load 'moreland.pal'

set size square
set xrange [0:1]
set yrange [0:1]
set xtics 0, 0.1, 1
set ytics 0, 0.1, 1
set grid

unset colorbox
do for [t=0:9] {
    infile = sprintf('../positions/%06d.dat',t*10)
    tt = sprintf('t=04d',t*10)
    outfile = sprintf('pos_%06d.eps',t*10)
    set output outfile 
        #set label 1 tt at 0.5,1.05 
        plot \
        infile using  5:6:(0.01):(int($1+$2)%2*100) with circles lc palette lw 2 notitle 
        #infile using  7:8:(0.01) with circles lc "black" notitle
        
        #infile using  5:6:($1) with labels notitle  ,\
        #infile using  5:6:($2) with labels offset 1 notitle 
        
}
! ps2pdf -dEPSCrop pos*.eps
