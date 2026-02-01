#!/bin/bash

numLoop=${1:-100}
doComp=${2:-1}

if [ "$doComp" -eq 1 ]; then
  echo "Compiling solution, gen, brute..."

  g++ -std=c++17 gen.cpp -o gen.exe
  g++ -std=c++17 solution.cpp -o solution.exe
  g++ -std=c++17 brute.cpp -o brute.exe

  echo "Done compiling."
fi

diff_found=""

for ((x = 1; x <= numLoop; x++)); do
  echo $x

  ./gen.exe > input.in
  ./solution.exe < input.in > output.out
  ./brute.exe < input.in > output2.out

  # Normalize CRLF → LF
  tr -d '\r' < output.out  > out1.tmp
  tr -d '\r' < output2.out > out2.tmp

  # Compare ignoring whitespace
  if ! diff -wB out1.tmp out2.tmp > diagnostics; then
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

rm -f input.in output.out output2.out brute.exe gen.exe solution.exe diagnostics out1.tmp out2.tmp
