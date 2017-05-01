cd out
files=( $(ls *.out) )
for file in ${files[*]};
do
	out=$(echo $file | sed s/.out//g )
	#echo ${distr[*]}
	gnuplot <<- EOP

	set terminal png size 800, 600 
	set title "Strategy $out" font "Arial, 17"
	set output "${out}.png"
	set xlabel "Mx sigma"
	set ylabel "Mx omega"
	#set label "Strategy $name" at 1,2 font "Arial, 20" 
	
	plot "$file" using 1:2 title "0.1 Mx tau" with linespoints ls 1,\
	     "$file" using 1:3 title "0.2 Mx tau" with linespoints ls 2,\
		"$file" using 1:4 title "0.3 Mx tau" with linespoints ls 3,\
		"$file" using 1:5 title "0.4 Mx tau" with linespoints ls 4,\
		"$file" using 1:6 title "0.5 Mx tau" with linespoints ls 5,\
		"$file" using 1:7 title "0.6 Mx tau" with linespoints ls 6,\
		"$file" using 1:8 title "0.7 Mx tau" with linespoints ls 7,\
		"$file" using 1:9 title "0.8 Mx tau" with linespoints ls 8,\
		"$file" using 1:10 title "0.9 Mx tau" with linespoints ls 9
	EOP
done