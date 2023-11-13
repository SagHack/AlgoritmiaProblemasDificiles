/*
 * Fichero:   		main.cpp
 * Autores: 		Diego García Aranda 820506
                    Simón Alonso Gutiérrez 821038
 * Fecha entrega:	15/11/2023
 * Comentarios:     Fichero que implementa el programa que genera un cuadrado latino
 *                  parcial de determinada dimensión y determinado porcentaje de celdas 
 *                  sin valor, resuelve este cuadrado latino parcial mediante una reducción
 *                  a SAT y un SAT solver
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <tuple>
#include <map> 
#include <math.h>
#include "minisat-master/minisat/core/Solver.h"
#include "resolverCL.h"
#include "generarCL.h"
using namespace std;

#define MIN_ARGS 4
#define MAX_ARGS 6


void mostrarEjeucionesCorrectas(){
    cerr << "Ejecuciones correctas:\n" ;
    cerr << "\t./main <fichero_salida_CL_completo_original> <fichero_salida_CL_parcial> <fichero_salida_CL_resuelto> <dimensión> <porcentaje_celdas_sin_valor>\n";
    cerr << "\t./main <fichero_entrada_CL_parcial> <fichero_salida_CL_resuelto> <dimensión>\n";
}

vector<int> CL_entero;

int main(int argc, char* argv[]) {
    
    if(argc < MIN_ARGS || argc > MAX_ARGS){
       mostrarEjeucionesCorrectas();
       exit(1);
    }

    int n,p;
    
    if(argc == MAX_ARGS){
        n = stoi(argv[4]);
        p = stoi(argv[5]);
        CL_entero = vector<int>(n*n,0);
        generarCLCompleto(CL_entero,n);
        cout << "Generado\n";
        escribirCL(CL_entero,argv[1],n);

        generarCLParcial(CL_entero,n,p);
        cout << "Generado parcial\n";
        escribirCL(CL_entero,argv[2],n);

        resolverCL(argv[2],argv[3],CL_entero,n,false);
        cout << "Resuelto\n";
    }
    else if(argc == MIN_ARGS){
        CL_entero = vector<int>(n*n,0);
        n = stoi(argv[3]);
        resolverCL(argv[1],argv[2],CL_entero,n,false);
        cout << "Resuelto\n";
    }

    

    

    
}
