/*
 * Fichero:   		resolverCL.h
 * Autores: 		Diego García Aranda 820506
                    Simón Alonso Gutiérrez 821038
 * Fecha entrega:	15/11/2023
 * Comentarios:     Fichero que define y especifica las funciones que resuelven el problema del 
 *                  cuadrado latino a partir de una reducción a SAT y usar el SAT solver
 *                  https://github.com/master-keying/minisat/ o bien a través de un algoritmo de 
 *                  backtracking.
 */
#pragma once
#include <string>
using namespace std;


#define SEPARADOR_ENTRADA ' '

/*
 * Resuelve el cuadrado latino parcial de dimensión n x n almacenado en el fichero ficheroEntrada.
 * Para ello, realiza una reducción de cuadrado latino a SAT y utiliza un SAT solver para resolver. 
 * Si se quiere realizar una simplificación de las cláusulas que se pasan al SAT solver, el 
 * booleano deber ser true.
 */
void resolverCL_SAT(string ficheroEntrada,vector<int>& CL_entero, int n,bool simplificar);

/*
 * Devuelve true si se resuelve el cuadrado latino parcial  de dimensión n x n almacenado en 
 * el fichero ficheroEntrada. Para ello, utiliza un algoritmo de backtracking.
 */
bool resolverCL_Backtracking(string ficheroEntrada,vector<int>& CL_entero, int n);
