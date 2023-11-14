/*
 * Fichero:   		resolverCL.h
 * Autores: 		Diego García Aranda 820506
                    Simón Alonso Gutiérrez 821038
 * Fecha entrega:	15/11/2023
 * Comentarios:     Fichero que define y especifica la función que resuelve el problema del 
 *                  cuadrado latino a partir de una reducción a SAT y usar el SAT solver
 *                  https://github.com/master-keying/minisat/ para resolverlo.
 */
#pragma once
#include <string>
using namespace std;


#define SEPARADOR_ENTRADA ' '

/*
 * Resuelve el cuadrado latino parcial  de dimensión n x n almacenado en el fichero ficheroEntrada y 
 * lo escribe en el fichero ficheroSalida. Para ello, realiza una reducción de cuadrado latino a SAT
 * y utiliza un SAT solver para resolver. Si se quiere realizar una simplificación de las cláusulas
 * que se pasan al SAT solver, el booleano deber ser true.
 */
void resolverCL(string ficheroEntrada, string ficheroSalida,vector<int>& CL_entero, int n,bool simplificar);


void leerCL_backtracking(string ficheroEntrada,vector<int>& CL_entero,int n);
void escribirCL_backtracking(const vector<int>& CL,const string ficheroSalida,const int n);
bool estaEnFila(const vector<int>& CL, int fila, int num,int n);
bool estaEnColumna(const vector<int>& CL, int columna, int num,int n);
bool puedeColocar(const vector<int>& square, int row, int col, int num,int n);
bool resolverCL_backtracking(vector<int>& CL,int n);