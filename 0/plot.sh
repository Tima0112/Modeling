#!/bin/bash
# set y2label "asdf"
# set yrange [1:250000]

gnuplot << EOP

set terminal png size 800,600
set output "$2"
set yrange[-0.07:0.07]
set xlabel "Шаг"
set ylabel "Автокорреляция"
#set logscale y 2

plot \\
"$1" using 1:2 with lines axis x1y1
#x title "Linear speedup"

EOP
