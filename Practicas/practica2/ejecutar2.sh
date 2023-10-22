#!/bin/bash

p=20.0
n=6

./gCL "CL.txt" "$n" "$p"

if [ "$?" -ne 0 ]; then
    exit 1
fi

./main "CL.txt" "$n"

if [ "$?" -ne 0 ]; then
    exit 1
fi
./minisat-master/build/minisat "clauses.txt" "resultado.txt"
./mostrarResultado "$n"