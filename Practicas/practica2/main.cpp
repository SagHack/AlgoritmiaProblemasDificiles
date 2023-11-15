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

#define NUM_ARGS_COMANDO_GENERAR 5
#define NUM_ARGS_COMANDO_RESOLVER 5
#define NUM_ARGS_COMANDO_RESOLVER_COMPARACION 5
#define NUM_ARGS_COMANDO_GENERAR_RESOLVER_COMPARACION 6

#define ARGS_COMANDO_GENERAR " <fichero_salida_CL_parcial> <dimensión> <porcentaje_celdas_a_rellenar>"
#define ARGS_COMANDO_RESOLVER " <fichero_entrada_CL_parcial> <fichero_salida_CL_resuelto> <dimensión>"
#define ARGS_COMANDO_RESOLVER_COMPARACION " <fichero_entrada_CL_parcial> <fichero_salida_CL_resuelto> <dimensión>"
#define ARGS_COMANDO_GENERAR_RESOLVER_COMPARACION "<fichero_salida_CL_parcial> <fichero_salida_CL_resuelto> <dimensión> <porcentaje_celdas_a_rellenar>"

#define COMANDO_GENERAR "generarCL"
#define COMANDO_RESOLVER_SAT "resolverCL_SAT"
#define COMANDO_RESOLVER_SAT_SIMPLIFICADO "resolverCL_simplificado_SAT"
#define COMANDO_RESOLVER_BACKTRACKING "resolverCL_BACKTRACKING"
#define COMANDO_RESOLVER_COMPARACION "resolverCL_comparacion"
#define COMANDO_GENERAR_RESOLVER_COMPARACION "generar_resolverC_comparacion"


void mostrarEjeucionesCorrectas(){
    cerr << "Ejecuciones correctas:\n" ;
    cerr << "\t./main " + COMANDO_GENERAR + ARGS_COMANDO_GENERAR + "\n";
    cerr << "\t./main " + COMANDO_RESOLVER_SAT + ARGS_COMANDO_RESOLVER + "\n";
    cerr << "\t./main " + COMANDO_RESOLVER_SAT_SIMPLIFICADO + ARGS_COMANDO_RESOLVER + "\n";
    cerr << "\t./main " + COMANDO_RESOLVER_BACKTRACKING + ARGS_COMANDO_RESOLVER + "\n";
    cerr << "\t./main " + COMANDO_RESOLVER_COMPARACION + ARGS_COMANDO_RESOLVER_COMPARACION + "\n";
    cerr << "\t./main " + COMANDO_GENERAR_RESOLVER_COMPARACION + ARGS_COMANDO_GENERAR_RESOLVER_COMPARACION + "\n";
}

vector<int> CL_entero;

int main(int argc, char* argv[]) {
    
    if(argc < 1){
        cerr << "No hay parámetros\n";
        mostrarEjeucionesCorrectas();
        exit(1);
    }
    string comando = argv[1];

    switch(comando){
        case COMANDO_GENERAR:
            if(argc != NUM_ARGS_COMANDO_GENERAR){
                cerr << "Número de párametros de comando " << comando << " incorrecto.\n";
                mostrarEjeucionesCorrectas();
                exit(1);
            }
            int n,p;
            try{
                n = stoi(argv[3]);
            }
            catch(Exception& e){
                cerr << "Dimensión no es número\n";
                mostrarEjeucionesCorrectas();
                exit(1);
            }

            try{
                p = stoi(argv[4]);
            }
            catch(Exception& e){
                cerr << "Porcentaje de celdas a rellenar no es número\n";
                mostrarEjeucionesCorrectas();
                exit(1);
            }
            CL_entero = vector<int>(n*n,0);
            
            string ficheroSalida = argv[2];

            generarCLCompleto(CL_entero,n);
            cout << "Se ha generado correctamente el cuadrado latino completo de dimensión " << n << " x " << n << ".";

            generarCLParcial(CL_entero,n,p);
            cout << "Se ha generado correctamente el cuadrado latino parcial de dimensión " << n << " x " << n << " con un " << p << "% de celdas a rellenar.";

            escribirCL(CL_entero,ficheroSalida,n);
            cout << "Se ha guardado correctamente en el fichero" << ficheroSalida << "\n";
            break;

        case COMANDO_RESOLVER_SAT:
        case COMANDO_RESOLVER_SAT_SIMPLIFICADO:
        case COMANDO_RESOLVER_BACKTRACKING:
            if(argc != NUM_ARGS_RESOLVER){
                cerr << "Número de párametros de comando " << comando << " incorrecto.\n";
                mostrarEjeucionesCorrectas();
                exit(1);
            }
            int n;
            try{
                n = stoi(argv[4]);
            }
            catch(Exception& e){
                cerr << "Dimensión no es número\n";
                mostrarEjeucionesCorrectas();
                exit(1);
            }
            string ficheroEntrada = argv[2];
            string ficheroSalida = argv[3];

            if(comando == COMANDO_RESOLVER_SAT){
                resolverCL_SAT(ficheroEntrada,ficheroSalida,CL_entero,n,false);
                cout << "Se ha resuelto correctamente el cuadrado latino parcial de dimensión " << n << " x " << n << " almacenado en el fichero " << ficheroEntrada << " mediante reducción a SAT y SAT solver.";
                escribirCL(CL_entero,ficheroSalida,n);
                cout << "Se ha guardado correctamente el cuadrado latino resuelto en el fichero" << ficheroSalida << "\n";
            }
            else if(comando == COMANDO_RESOLVER_SAT_SIMPLIFICADO){
                resolverCL_SAT(ficheroEntrada,ficheroSalida,CL_entero,n,true);
                cout << "Se ha resuelto correctamente el cuadrado latino parcial de dimensión " << n << " x " << n << " almacenado en el fichero " << ficheroEntrada << " mediante reducción simplificada a SAT y SAT solver.";
                escribirCL(CL_entero,ficheroSalida,n);
                cout << "Se ha guardado correctamente el cuadrado latino resuelto en el fichero" << ficheroSalida << "\n";
            }
            else{
                resolverCL_Backtracking(ficheroEntrada,CL_entero,n);
                cout << "Se ha resuelto correctamente el cuadrado latino parcial de dimensión " << n << " x " << n << " almacenado en el fichero " << ficheroEntrada << " mediante backtracking.";
                escribirCL(CL_entero,ficheroSalida,n);
                cout << "Se ha guardado correctamente el cuadrado latino resuelto en el fichero" << ficheroSalida << "\n";
            }
            break;

        case COMANDO_RESOLVER_COMPARACION:
            if(argc == NUM_ARGS_COMANDO_RESOLVER_COMPARACION){

            }
            else{
                cerr << "Número de párametros de comando " << comando << " incorrecto.\n";
                mostrarEjeucionesCorrectas();
                exit(1);
            }
            break;
        case COMANDO_GENERAR_RESOLVER_COMPARACION:
            if(argc == NUM_ARGS_COMANDO_GENERAR_RESOLVER_COMPARACION){

            }
            else{
                cerr << "Número de párametros de comando " << comando << " incorrecto.\n";
                mostrarEjeucionesCorrectas();
                exit(1);
            }
            break;

        default:
            cerr << comando << ": comando no válido\n";
            mostrarEjeucionesCorrectas();
            exit(1);
            break;
    }

    
}
