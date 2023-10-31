#! /bin/bash
make clean && make monte_carlo
./monte_carlo -n 1000 -r $RANDOM > monte_carlo.dat
./monte_carlo -n 65536 -r $RANDOM > monte_carlo_err1.dat
./monte_carlo -n 65536 -r $RANDOM > monte_carlo_err2.dat
./monte_carlo -n 65536 -r $RANDOM > monte_carlo_err3.dat
./monte_carlo -n 65536 -r $RANDOM > monte_carlo_err4.dat
gnuplot <<END
    set terminal pdf
    set output "monte_carlo.pdf"
    set size square
    set style function linespoints
    set style line 7
    set pointsize 0.5
    set nokey
    plot "monte_carlo.dat" using 3:4:5 with points pt 20 palette, \
         [x=0:1] sqrt(1-x**2) lt rgb "violet"
    
    set output "monte_error.pdf"
    set nokey
    set xrange [1:]
    set yrange [-1:1]
    set logscale x 2
    set grid xtics
    set grid ytics
    set grid mxtics
    set grid mytics
    set grid back ls 0
    set xlabel "iterations"
    set ylabel "Estimation Error"
    plot 'monte_carlo_err1.dat' u 1:(\$2-pi) w l, 'monte_carlo_err2.dat' u 1:(\$2-pi) w l, 'monte_carlo_err3.dat' u 1:(\$2-pi) w l, 'monte_carlo_err4.dat' u 1:(\$2-pi) w l		
END
