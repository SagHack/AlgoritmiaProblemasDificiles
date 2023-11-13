/*
 * Fichero:   		generarCL.cpp
 * Autores: 		Diego García Aranda 820506
                    Simón Alonso Gutiérrez 821038
 * Fecha entrega:	15/11/2023
 * Comentarios:     Fichero que implementa las funciones que generan cuadrados
 *                  latinos completos, cuadrados latinos parciales y que los escriben 
 *                  en un fichero de salida.
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <random>
#include <algorithm>
#include "generarCL.h"
using namespace std;


/****************************************************************************************************/
/*                    Implementación de función que resuelve cuadrados latinos parciales            */

/*
 *  Se almacena en CL un cuadrado latino completo de dimensión n x n.
 */
void generarCLCompleto(vector<string>& CL, int n){
    
    
        mt19937 gen(time(nullptr));
        vector<int> available_indices(n);
        for (int i = 0; i < n; i++) {
            available_indices[i] = i;
        }
        shuffle(available_indices.begin(), available_indices.end(), gen);
        
        for (int i=0;i<n;i+=1) {
            for (int j = 0; j < n; j++) {
                CL[i*n+j] = to_string((available_indices[i] + j) % n + 1);
            }
        }

}


/*
 *  Se modifica el cuadrado latino completo de dimensión n x n almacenado en CL,
 *  generando un cuadrado latino parcial de dimensión n x n, siendo
 *  porcentaje el porcentaje de casillas a rellenar.
 */
void generarCLParcial(vector<string>& CL,const int n,const double porcentaje){
    
    int fila = 0, columna = 0, asteriscos = ((n * n)*porcentaje) / 100.0;
    srand(time(NULL));
    for(int i = 0; i < asteriscos; i++){
        fila = rand() % n;
        columna = rand() % n;
        CL[fila*n + columna] = "*";
    }

}

/*
 *  Escribe en el fichero ficheroSalida el cuadrado latino de dimensión 
 *  n x n almacenado en CL.
 */
void escribirCL(const vector<string>& CL,const string ficheroSalida,const int n){
    ofstream salida(ficheroSalida);
    if(salida.is_open()){

        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                salida << CL[i*n+j] << " ";
            }
            salida << endl;
        }   

    }
}

/****************************************************************************************************/