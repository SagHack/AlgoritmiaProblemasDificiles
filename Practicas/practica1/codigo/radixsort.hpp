/*
 * Fichero:   		radixsort.hpp
 * Autores: 		Diego García Aranda 820506
                    Simón Alonso Gutiérrez 821038
 * Fecha entrega:	18/10/2023
 * Comentarios:     Fichero que define y especifica dos funciones que ordenan
 *                  vectores de números mediante el algoritmo de ordenación
 *                  radixsort. 
 *                  La primera función es usada para números representables en 
 *                  formato entero y la segunda es para número no representables 
 *                  en formato entero, por lo que se utilizan strings para representar 
 *                  los números.
 */
#include <vector>
using namespace std;

/* 
 * Precondición:
 * Postcondición:   ordena el vector v de forma ascendente 
 *                  mediante el algoritmo de ordenación radixsort.
 */
void radixsort(vector<int>& v);

/* 
 * Precondición:    los elementos del vector v son cadenas que representan
                    números en formato entero.
 * Postcondición:   ordena el vector v de forma ascendente 
 *                  mediante el algoritmo de ordenación radixsort.
 */
void radixsort(vector<string>& v);
