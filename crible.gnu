set title "Performance comparison between naive implementations and Eratosthene sieve to compute prime list"
set xlabel "Size of the list"
set ylabel "Time taken to compute the list (s)"
set key top box
plot 'crible.txt' using 2 title "Exhaustive search (Euclidian division)" with lines, \
		'crible.txt' using 3 title "Optimized search (Euclidian division below sqrt(n))" with lines, \
		'crible.txt' using 4 title "Eratosthene sieve" with lines, \

pause -1 "Hit any key to continue"