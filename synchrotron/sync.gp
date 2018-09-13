#! /usr/bin/gnuplot

set logscale x 10
set format x "%L"
set xlabel "Log  E_{ph}   [eV]"
unset mxtics

set logscale y 10
set format y "%L"
set ylabel "Log  E_{ph} x L   [erg s^{-1}]"
unset mytics

unset key

set terminal pngcairo font "CMU Sans Serif" fontscale 1 size 640, 480 linewidth 1
set output "./sync.png"

plot "./sync.dat" u ($1/1.6e-12):($2*$1) w l lw 2
