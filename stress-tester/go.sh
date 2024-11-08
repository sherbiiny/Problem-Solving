#!/bin/bash

numLoop=${1:-100}
doComp=${2:-1}

if [ "$doComp" -eq 1 ]; then
  echo "Compiling solution, gen, brute..."

  g++ -std=c++17 gen.cpp -o gen
  g++ -std=c++17 solution.cpp -o solution
  g++ -std=c++17 brute.cpp -o brute

  echo "Done compiling."
fi

diff_found=""

for ((x = 1; x <= numLoop; x++)); do
  echo $x
  ./gen >input.in
  ./solution < input.in > output.out
  ./brute < input.in > output2.out
  # Compare the outputs ignoring trailing whitespaces
  if ! diff -q output.out output2.out >diagnostics; then
    diff_found="y"
    break
  fi
done

if [ "$diff_found" ]; then
  echo "A difference has been found."
  echo "Input:"
  cat input.in
  echo
  echo "Output:"
  cat output.out
  echo
  echo "Expected:"
  cat output2.out
  echo
else
  echo "All tests passed :D"
fi

rm input.in output.out output2.out brute gen solution diagnostics
