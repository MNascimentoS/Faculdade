set title "Grafico de memoria livre durante a multiplicacao de matrizes quadradas" 

set xlabel "Tempo(segundos)"
set ylabel "Uso memoria (em Kbytes)"

set xtics nomirror
set ytics nomirror
set key top left
set key box
set style data lines

set style line 1 linetype 1 linewidth 1 linecolor rgb "red" pointtype 7 pointsize 1
set style line 2 linetype 1 linewidth 1 linecolor rgb "blue" pointtype 7 pointsize 1

# Aqui seta a fonte
#set terminal postscript eps enhanced color "arial" 14
set terminal postscript eps enhanced color
set output 'graphicUsoMemoriaMult.eps'

plot "saidaUsoMemoriaComPrograma.txt" using 1:2 title "Uso Memoria com programa" ls 1 with linespoints
