#!/usr/bin/gnuplot -persist

unset errorbars 
set xlabel "ID Station"
set ylabel "Moeyenne Température "
plot 'FinalWeather.csv' using 1:2:3 with title "minmax",'' using 1:3 with line title "moyenne" 
