#!/bin/bash

# Compilamos el programa
g++ -o codigo/pruebaAlgoritmos codigo/pruebaAlgoritmos.cpp -std=c++11


if [ $? -eq 0 ]; then
  # Ejecutamos el programa
  ./codigo/pruebaAlgoritmos
else
  echo "Fallo en compilación. Compruebe los errores"
fi