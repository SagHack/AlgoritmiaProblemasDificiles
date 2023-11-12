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



int main(int argc, char* argv[]) {
    
    /*if(argc != 2){
        cerr << "Ejecución correcta: ./main <dimensión>";
        exit(1);
    }*/
    int n = stoi(argv[4]);
    int p = stoi(argv[5]);
    vector<string> CL(n*n,"");

    generarCuadradoLatinoCompleto(CL,n);
    cout << "Generado\n";
    escribirCuadradoLatinoParcial(CL,argv[1],n);

    generarCuadradoLatinoParcial(CL,n,p);
    cout << "Generado parcial\n";
    escribirCuadradoLatinoParcial(CL,argv[2],n);

    resolverCL(argv[2],argv[3],n,false);
}
