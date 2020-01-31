#!/usr/bin/env gnuplot
set style arrow 1 head filled size screen 0.03,10,85 ls 5


set terminal postscript eps enh color; set output "disp.eps"
#set terminal gif optimize size 1000, 1000 animate delay 20; set output "pos.gif"
unset key;

load 'moreland.pal'
set ylabel "Avg. Disp." font "Helvetica,24"
set xlabel "time" font "Helvetica,24"
set xtics font "Helvetica,20"
set ytics font "Helvetica,20"

plot for [i=0:22] sprintf('disp/d_%02d.dat',i*2+5) with lines lw 4
#do for [disp=0:22] {
#    print disp*2+5
#    infile = sprintf('disp/d_%02d.dat',disp*2+5)
#    tt = sprintf('t=04d', disp)
#        set label 1 tt at 0.5,1.05 
#        plot infile 
#        
#        #infile using  5:6:($1) with labels notitle  ,\
#        #infile using  5:6:($2) with labels offset 1 notitle 
#        
#}
