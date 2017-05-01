#!/bin/bash
# set y2label "asdf"
# set yrange [1:250000]

gnuplot << EOP

set terminal png size 800,600
set output "$1".".png"
#set xrange[0:3.14]
#set yrange[0:1]
set style data boxes
#set xlabel "Num threads"
#set ylabel "Speedup"
#set logscale y 2


plot "$1" using 1:2 title "method reject"

# plot \\
# "$1" using 1:2 title "dgemm_omp" with lines axis x1y1,\\
# x title "Linear speedup"


EOP
