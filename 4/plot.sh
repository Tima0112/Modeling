#!/bin/bash
cd out
fnames=( $(ls hist* | sed /.png/d ) )
for fname in ${fnames[*]};
do
	mas=( Event Value )
	i=2
	for x in ${mas[*]};
	do
		gnuplot <<- EOP

		set yrange [0:]
		set terminal png size 800,600
		set output "${fname}$x.png"
		set style data boxes
		set style fill solid border 0
		set xlabel "$x"
		set ylabel "Count"
		n=$i-1
		plot "$fname" using 1:${i} title "Матрица ".n lt rgb "grey"


		EOP
		let i++
	done
done