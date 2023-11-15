/*
 * Fichero:   		main.cpp
 * Autores: 		Diego García Aranda 820506
                    Simón Alonso Gutiérrez 821038
 * Fecha entrega:	15/11/2023
 * Comentarios:     Fichero que implementa el programa que genera un cuadrado latino
 *                  parcial de determinada dimensión y determinado porcentaje de celdas 
 *                  sin valor, que resuelve cuadrados latinos mediante reducción a SAT y
 *                  un SAT Solver o Backtracking.
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
#include <chrono>
#include "minisat-master/minisat/core/Solver.h"
#include "resolverCL.h"
#include "generarCL.h"
using namespace std;
using namespace chrono;

#define NUM_ARGS_COMANDO_GENERAR 5
#define NUM_ARGS_COMANDO_RESOLVER 5
#define NUM_ARGS_COMANDO_RESOLVER_COMPARACION 7
#define NUM_ARGS_COMANDO_GENERAR_RESOLVER_COMPARACION 8

#define ARGS_COMANDO_GENERAR " <fichero_salida_CL_parcial> <dimensión> <porcentaje_celdas_a_rellenar>"
#define ARGS_COMANDO_RESOLVER " <fichero_entrada_CL_parcial> <fichero_salida_CL_resuelto> <dimensión>"
#define ARGS_COMANDO_RESOLVER_COMPARACION " <fichero_entrada_CL_parcial> <fichero_salida_CL_resuelto_SAT> <fichero_salida_CL_resuelto_SAT_simplificado> <fichero_salida_CL_resuelto_Backtracking> <dimensión>"
#define ARGS_COMANDO_GENERAR_RESOLVER_COMPARACION " <fichero_salida_CL_parcial> <fichero_salida_CL_resuelto_SAT> <fichero_salida_CL_resuelto_SAT_simplificado> <fichero_salida_CL_resuelto_Backtracking> <dimensión> <porcentaje_celdas_a_rellenar>"

#define COMANDO_GENERAR "generarCL"
#define COMANDO_RESOLVER_SAT "resolverCL_SAT"
#define COMANDO_RESOLVER_SAT_SIMPLIFICADO "resolverCL_simplificado_SAT"
#define COMANDO_RESOLVER_BACKTRACKING "resolverCL_Backtracking"
#define COMANDO_RESOLVER_COMPARACION "resolverCL_comparacion"
#define COMANDO_GENERAR_RESOLVER_COMPARACION "generar_resolverCL_comparacion"


void mostrarEjeucionesCorrectas(){
    cerr << "Ejecuciones correctas:\n" ;
    cerr << "\t./main " << COMANDO_GENERAR << ARGS_COMANDO_GENERAR << "\n";
    cerr << "\t./main " << COMANDO_RESOLVER_SAT << ARGS_COMANDO_RESOLVER << "\n";
    cerr << "\t./main " << COMANDO_RESOLVER_SAT_SIMPLIFICADO << ARGS_COMANDO_RESOLVER << "\n";
    cerr << "\t./main " << COMANDO_RESOLVER_BACKTRACKING << ARGS_COMANDO_RESOLVER << "\n";
    cerr << "\t./main " << COMANDO_RESOLVER_COMPARACION << ARGS_COMANDO_RESOLVER_COMPARACION << "\n";
    cerr << "\t./main " << COMANDO_GENERAR_RESOLVER_COMPARACION << ARGS_COMANDO_GENERAR_RESOLVER_COMPARACION << "\n";
}

vector<int> CL_entero;

int main(int argc, char* argv[]) {
    
    if(argc <= 1){
        cerr << "No hay parámetros\n";
        mostrarEjeucionesCorrectas();
        exit(1);
    }
    string comando = argv[1];



    if(comando == COMANDO_GENERAR){
        if(argc != NUM_ARGS_COMANDO_GENERAR){
            cerr << "Número de párametros de comando " << comando << " incorrecto.\n";
            mostrarEjeucionesCorrectas();
            exit(1);
        }
        int n,p;
        try{
            n = stoi(argv[3]);
        }
        catch(exception& e){
            cerr << "Dimensión no es número\n";
            mostrarEjeucionesCorrectas();
            exit(1);
        }

        try{
            p = stoi(argv[4]);
        }
        catch(exception& e){
            cerr << "Porcentaje de celdas a rellenar no es número\n";
            mostrarEjeucionesCorrectas();
            exit(1);
        }
        CL_entero = vector<int>(n*n,0);
        string ficheroSalida = argv[2];

        generarCLCompleto(CL_entero,n);
        cout << "Se ha generado correctamente el cuadrado latino completo de dimensión " << n << " x " << n << ".\n";

        generarCLParcial(CL_entero,n,p);
        cout << "Se ha generado correctamente el cuadrado latino parcial de dimensión " << n << " x " << n << " con un " << p << "% de celdas a rellenar.";

        escribirCL(CL_entero,ficheroSalida,n);
        cout << "Se ha guardado correctamente en el fichero " << ficheroSalida << "\n";
    }
    else if(comando == COMANDO_RESOLVER_SAT || comando == COMANDO_RESOLVER_SAT_SIMPLIFICADO || comando == COMANDO_RESOLVER_BACKTRACKING){
        if(argc != NUM_ARGS_COMANDO_RESOLVER){
            cerr << "Número de párametros de comando " << comando << " incorrecto.\n";
            mostrarEjeucionesCorrectas();
            exit(1);
        }
        int n;
        try{
            n = stoi(argv[4]);
        }
        catch(exception& e){
            cerr << "Dimensión no es número\n";
            mostrarEjeucionesCorrectas();
            exit(1);
        }
        CL_entero = vector<int>(n*n,0);
        string ficheroEntrada = argv[2];
        string ficheroSalida = argv[3];

        if(comando == COMANDO_RESOLVER_SAT){
            auto start_time = high_resolution_clock::now();
            resolverCL_SAT(ficheroEntrada,CL_entero,n,false);
            auto end_time = high_resolution_clock::now();

            auto duration = duration_cast<microseconds>(end_time - start_time);

            resolverCL_SAT(ficheroEntrada,CL_entero,n,false);
            cout << "\nSe ha resuelto correctamente el cuadrado latino parcial de dimensión " << n << " x " << n << " almacenado en el fichero " << ficheroEntrada << " mediante reducción a SAT y SAT solver.";
            escribirCL(CL_entero,ficheroSalida,n);
            cout << "\nSe ha guardado correctamente el cuadrado latino resuelto en el fichero" << ficheroSalida << "\n";

            cout << "\nCuadrado latino dimensión " << n << " x " << n << "\n";
            cout << "Resolución SAT: \t\t\t" << duration.count() << "\n\n";
        }
        else if(comando == COMANDO_RESOLVER_SAT_SIMPLIFICADO){

            auto start_time = high_resolution_clock::now();
            resolverCL_SAT(ficheroEntrada,CL_entero,n,true);
            auto end_time = high_resolution_clock::now();

            auto duration = duration_cast<microseconds>(end_time - start_time);
            
            cout << "\nSe ha resuelto correctamente el cuadrado latino parcial de dimensión " << n << " x " << n << " almacenado en el fichero " << ficheroEntrada << " mediante reducción simplificada a SAT y SAT solver.";
            escribirCL(CL_entero,ficheroSalida,n);
            cout << "\nSe ha guardado correctamente el cuadrado latino resuelto en el fichero" << ficheroSalida << "\n";
        
            cout << "\nCuadrado latino dimensión " << n << " x " << n << "\n";
            cout << "Resolución SAT con simplifcación: \t" << duration.count() << "\n\n";
        }
        else{
            auto start_time = high_resolution_clock::now();
            
            resolverCL_Backtracking(ficheroEntrada,CL_entero,n);
            auto end_time = high_resolution_clock::now();

            auto duration = duration_cast<microseconds>(end_time - start_time);
            
            cout << "\nSe ha resuelto correctamente el cuadrado latino parcial de dimensión " << n << " x " << n << " almacenado en el fichero " << ficheroEntrada << " mediante backtracking.";
            escribirCL(CL_entero,ficheroSalida,n);
            cout << "\nSe ha guardado correctamente el cuadrado latino resuelto en el fichero" << ficheroSalida << "\n";
        
            cout << "\nCuadrado latino dimensión " << n << " x " << n << "\n";
            cout << "Resolución Backtracking: \t\t" << duration.count() << "\n\n";
        }
    }
    else if(comando == COMANDO_RESOLVER_COMPARACION){
        if(argc != NUM_ARGS_COMANDO_RESOLVER_COMPARACION){
            cerr << "Número de párametros de comando " << comando << " incorrecto.\n";
            mostrarEjeucionesCorrectas();
            exit(1);
        }
        int n;
        try{
            n = stoi(argv[6]);
        }
        catch(exception& e){
            cerr << "Dimensión no es número\n";
            mostrarEjeucionesCorrectas();
            exit(1);
        }
        CL_entero = vector<int>(n*n,0);
        string ficheroEntrada = argv[2];
        string ficheroSalida1 = argv[3];
        string ficheroSalida2 = argv[4];
        string ficheroSalida3 = argv[5];

        auto start_time_SAT = high_resolution_clock::now();
        resolverCL_SAT(ficheroEntrada,CL_entero,n,false);
        auto end_time_SAT = high_resolution_clock::now();

        auto durationSAT = duration_cast<microseconds>(end_time_SAT - start_time_SAT);
        escribirCL(CL_entero,ficheroSalida1,n);
        cout << "Se ha guardado correctamente el cuadrado latino resuelto mediante SAT en el fichero " << ficheroSalida1 << "\n";
        
        
        auto start_time_SAT_simplificado = high_resolution_clock::now();
        resolverCL_SAT(ficheroEntrada,CL_entero,n,true);
        auto end_time_SAT_simplificado = high_resolution_clock::now();

        auto durationSAT_simplificado = duration_cast<microseconds>(end_time_SAT_simplificado - start_time_SAT_simplificado);
        escribirCL(CL_entero,ficheroSalida2,n);
        cout << "Se ha guardado correctamente el cuadrado latino resuelto mediante SAT simplificado en el fichero " << ficheroSalida2 << "\n";


        auto start_time_Backtracking = high_resolution_clock::now();
        resolverCL_Backtracking(ficheroEntrada,CL_entero,n);
        auto end_time_Backtracking = high_resolution_clock::now();

        auto durationBacktracking = duration_cast<microseconds>(end_time_Backtracking - start_time_Backtracking);
        
        escribirCL(CL_entero,ficheroSalida3,n);
        cout << "Se ha guardado correctamente el cuadrado latino resuelto mediante backtracking en el fichero " << ficheroSalida3 << "\n";


        cout << "Cuadrado latino dimensión " << n << " x " << n << "\n";
        cout << "Resolución SAT: \t\t\t" << durationSAT.count() << "\n";
        cout << "Resolución SAT con simplificación: \t" << durationSAT_simplificado.count() << "\n";
        cout << "Resolución Backtracking: \t\t" << durationBacktracking.count() << "\n";
    }
    else if(comando == COMANDO_GENERAR_RESOLVER_COMPARACION){
        if(argc != NUM_ARGS_COMANDO_GENERAR_RESOLVER_COMPARACION){
            cerr << "Número de párametros de comando " << comando << " incorrecto.\n";
            mostrarEjeucionesCorrectas();
            exit(1);
        }
        int n,p;
        try{
            n = stoi(argv[6]);
        }
        catch(exception& e){
            cerr << "Dimensión no es número\n";
            mostrarEjeucionesCorrectas();
            exit(1);
        }

        try{
            p = stoi(argv[7]);
        }
        catch(exception& e){
            cerr << "Porcentaje de celdas a rellenar no es número\n";
            mostrarEjeucionesCorrectas();
            exit(1);
        }

        CL_entero = vector<int>(n*n,0);
        string ficheroEntrada = argv[2];
        string ficheroSalida1 = argv[3];
        string ficheroSalida2 = argv[4];
        string ficheroSalida3 = argv[5];

        generarCLCompleto(CL_entero,n);
        cout << "Se ha generado correctamente el cuadrado latino completo de dimensión " << n << " x " << n << ".\n";

        generarCLParcial(CL_entero,n,p);
        cout << "Se ha generado correctamente el cuadrado latino parcial de dimensión " << n << " x " << n << " con un " << p << "% de celdas a rellenar.";

        escribirCL(CL_entero,ficheroEntrada,n);
        cout << "Se ha guardado correctamente en el fichero" << ficheroEntrada << "\n";

        auto start_time_SAT = high_resolution_clock::now();
        resolverCL_SAT(ficheroEntrada,CL_entero,n,false);
        auto end_time_SAT = high_resolution_clock::now();

        auto durationSAT = duration_cast<microseconds>(end_time_SAT - start_time_SAT);
        escribirCL(CL_entero,ficheroSalida1,n);
        cout << "Se ha guardado correctamente el cuadrado latino resuelto mediante SAT en el fichero " << ficheroSalida1 << "\n";
        
        
        auto start_time_SAT_simplificado = high_resolution_clock::now();
        resolverCL_SAT(ficheroEntrada,CL_entero,n,true);
        auto end_time_SAT_simplificado = high_resolution_clock::now();

        auto durationSAT_simplificado = duration_cast<microseconds>(end_time_SAT_simplificado - start_time_SAT_simplificado);
        escribirCL(CL_entero,ficheroSalida2,n);
        cout << "Se ha guardado correctamente el cuadrado latino resuelto mediante SAT simplificado en el fichero " << ficheroSalida2 << "\n";


        auto start_time_Backtracking = high_resolution_clock::now();
        resolverCL_Backtracking(ficheroEntrada,CL_entero,n);
        auto end_time_Backtracking = high_resolution_clock::now();

        auto durationBacktracking = duration_cast<microseconds>(end_time_Backtracking - start_time_Backtracking);
        
        escribirCL(CL_entero,ficheroSalida3,n);
        cout << "Se ha guardado correctamente el cuadrado latino resuelto mediante backtracking en el fichero " << ficheroSalida3 << "\n";


        cout << "Cuadrado latino dimensión " << n << " x " << n << "\n";
        cout << "Resolución SAT: \t\t\t" << durationSAT.count() << "\n";
        cout << "Resolución SAT con simplificación: \t" << durationSAT_simplificado.count() << "\n";
        cout << "Resolución Backtracking: \t\t" << durationBacktracking.count() << "\n";
    }    
    else{
        cerr << comando << ": comando no válido\n";
        mostrarEjeucionesCorrectas();
        exit(1);
    }

    
}

