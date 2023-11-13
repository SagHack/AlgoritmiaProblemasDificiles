/*
 * Fichero:   		generarCL.h
 * Autores: 		Diego García Aranda 820506
                    Simón Alonso Gutiérrez 821038
 * Fecha entrega:	15/11/2023
 * Comentarios:     Fichero que define y especifica las funciones que generan cuadrados
 *                  latinos completos, cuadrados latinos parciales y que los escriben 
 *                  en un fichero de salida.
 */
#pragma once
#include <vector>
#include <string>
using namespace std;

/*
 *  Se almacena en CL un cuadrado latino completo de dimensión n x n.
 */
void generarCLCompleto(vector<int>& CL, int n);

/*
 *  Se modifica el cuadrado latino completo de dimensión n x n almacenado en CL,
 *  generando un cuadrado latino parcial de dimensión n x n, siendo
 *  porcentaje el porcentaje de casillas a rellenar.
 */
void generarCLParcial(vector<int>& CL,const int n,const double porcentaje);

/*
 *  Escribe en el fichero ficheroSalida el cuadrado latino de dimensión 
 *  n x n almacenado en CL.
 */
void escribirCL(const vector<int>& CL,const string ficheroSalida,const int n);

