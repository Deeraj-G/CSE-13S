#!/usr/bin/env bash

make clean && make

# Split each line using comma as the delimiter.
# Then extract x, the computed value, and the library value from each line.
# Output to `sine()` results to `/tmp/computed.dat`.
# Output to `sin()` results to `/tmp/library.dat`.
./mathlib-test -g | awk -F, '{
    split($1, computed, " ");
    split(computed[1], x, "[()]")
    split($2, library, " ");
    print x[2], computed[3] > "/tmp/computed.dat"
    print x[2], library[3] > "/tmp/library.dat"
}'

echo -n "Plotting... "
gnuplot <<EOF
set terminal pdf
set key outside
set zeroaxis

set output "e.c-comparison.pdf"
set title "sqrt\\\_newton() vs. sqrt()"

plot "/tmp/computed.dat" with linespoints title "e.c", \
    "/tmp/library.dat" with linespoints title "M_E"
EOF
echo "done."

