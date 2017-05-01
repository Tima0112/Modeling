#!/bin/bash
cd out
fnames=( $(ls ksi* | sed /.png/d ) )
i=0
gnuplot <<- EOP

set terminal png size 1300,700
set output "ksi.png"

plot "${fnames[0]}" using 1:2 title "Матрица 1" with line,\
	"${fnames[1]}" using 1:2 title "Матрица 2" with line

EOP
