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
#include "generarCuadradoLatino.h"
using namespace std;

#define MIN_ARGS 3
#define MAX_ARGS 5


void mostrarEjeucionesCorrectas(){
    cerr << "Ejecuciones correctas:\n" 
    cerr << "\t./main <fichero_salida_CL_completo_original> <fichero_salida_CL_parcial> <fichero_salida_CL_resuelto> <dimensión> <porcentaje_celdas_sin_valor>\n";
    cerr << "\t./main <fichero_entrada_CL_parcial> <fichero_salida_CL_resuelto> <dimensión>\n";
}


int main(int argc, char* argv[]) {
    
    if(argc < MIN_ARGS || argc > MAX_ARGS){
       mostrarEjeucionesCorrectas();
       exit(1);
    }

    int n,p;
    if(argc == MAX_ARGS){
        n = stoi(argv[4]);
        p = stoi(argv[5]);
    }
    else if(argc == MIN_ARGS){
        n = stoi(argv[3]);
    }

    vector<string> CL(n*n,"");

    generarCuadradoLatinoCompleto(CL,n);
    cout << "Generado\n";
    escribirCuadradoLatinoParcial(CL,argv[1],n);

    generarCuadradoLatinoParcial(CL,n,p);
    cout << "Generado parcial\n";
    escribirCuadradoLatinoParcial(CL,argv[2],n);

    resolverCL(argv[2],argv[3],n,false);
}
