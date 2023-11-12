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

using namespace std;
using namespace Minisat;
using KeyTuple = tuple<int,int,int>;


/****************************************************************************************************/
/*       Predefinición de estructuras de datos usadas en el solucionador de cuadrados latinos          */


struct CoordenadasCelda{
    int fila,columna;
};

struct CuadradoLatino{
    vector<CoordenadasCelda> celdasRellenar;
    vector<uin64_t> valoresFila;
    vector<uin64_t> valoresColumna;
    CuadradoLatino(int n) : valoresFila(n,((uin64_t) (1)<<n)-1), valoresColumna(n,((uin64_t) (1)<<n)-1), celdasRellenar(){}
};

/****************************************************************************************************/
/*       Predefinición de funciones locales usadas en el solucionador de cuadrados latinos          */

void leerFichero(string ficheroEntrada,int n, CuadradoLatino& CL, vector<int>& v);

Var addVariable(map<KeyTuple,Var>& variables,Solver& s,int fila, int columna, int valor_posible):
Var numVariable(map<KeyTuple,Var>& variables,int fila, int columna, int valor_posible)



/****************************************************************************************************/

void leerFichero(string ficheroEntrada,int n, CuadradoLatino& CL, vector<int>& v){
    ifstream entrada(ficheroEntrada);
    if(entrada.is_open()){
        string s;
        int i = 0, j = 0;
        CoordenadasCelda c;

        while(getline(entrada,s)){
            stringstream linea(s);
            while(getline(linea,s,SEPARADOR_ENTRADA)){
                if(s == "*"){
                    c.fila = i;
                    c.columna = j;
                    CL.celdasRellenar.push_back(c);
                }
                else{
                    int num;
                    uin64_t mascara;
                    try{
                        num = stoi(s);
                    } catch (const invalid_argument& e){
                        cerr << "El elemento de la fila " << i+1 << " y columna " << j+1 << " no es * o un número\n";
                        exit(1);
                    }

                    if(num >= 1 || num <= n){
                        
                        int componenteValores = num/64;
                        int k = num-64*componenteValores; // k = num mod 64
                        mascara = (uin64_t) (1) << (k-1);
                        
                        if(CL.valoresFila[i][componenteValores] & mascara) 
                            CL.valoresFila[i][componenteValores] &= ~mascara;
                        else{
                            cerr << "En la fila " << i+1 << " hay dos o más columnas con el número " << num << endl;
                            exit(1);
                        }

                        if(CL.valoresColumna[j][componenteValores] & mascara) 
                            CL.valoresColumna[j][componenteValores] &= ~mascara;
                        else{
                            cerr << "En la columna " << j+1 << " hay dos o más filas con el número " << num << endl;
                            exit(1);
                        }

                       v[i*n+j] = num;

                    }
                    else{
                        cerr << "El número de la fila " << i+1 << " y columna " << j+1 << " no es número entre 1 y " << n << endl;
                        exit(1);
                    }
                }
                j++;
                
            }
            if(j!=n){
                cerr << "La fila " << i+1 << " no tiene " << n << " columnas\n";
                exit(1);
            }
            i++;
            j = 0;
        
        }

        if(i!=n){
            cerr << "No hay " << n << " filas\n";
            exit(1);
        }

    }
}


using namespace Minisat;
using KeyTuple = tuple<int,int,int>;


Var addVariable(map<KeyTuple,Var>& variables,Solver& s,int fila, int columna, int valor_posible){
    KeyTuple key = make_tuple(i,j,k);
    Var v = s.newVar();
    variables[key] = v;
    return v;
}

Var numVariable(map<KeyTuple,Var>& variables,int fila, int columna, int valor_posible){
    KeyTuple key = make_tuple(i,j,k);
    auto iter = variables.find(key);
    if(iter != variables.end()) return iter->second;
    return -1;
    
}


struct CuadradoLatinoClauses{
    vector<vec<Lit>> clausesFila;
    vector<vec<Lit>> clausesColumna;
    vector<vec<Lit>> clausesCeldas;
    CuadradoLatinoClauses(int n,int nceldas) : clausesFila(n*n), clausesColumna(n*n), clausesCeldas(nceldas){
    }
};



void procesarUnaClausula(const CuadradoLatino& CL, vec<Lit>& clauses, Solver& s) {
    int nClauses = clauses.size();
    if (nClauses > 0) {
        s.addClause(clauses);
        clauses.clear();
    }
}

void elaborarClausesCL(const CuadradoLatino& CL,map<KeyTuple,Minisat::Var>& variables,CuadradoLatinoClauses& CLC, Solver& s){
    
    int n = CL.valoresFila.size();
    int nceldas = CL.celdasRellenar.size();
    for(int i = 0; i < nceldas; i++){
        int fila = CL.celdasRellenar[i].fila;
        int columna = CL.celdasRellenar[i].columna;

        for(int w=0;w<)

        uin64_t nums = CL.valoresFila[fila] & CL.valoresColumna[columna];
        vec<Var> v;
        int vLits = 0;
        vec<Lit> vl;

        if(nums == 0){
            cout << "El cuadrado latino es unsatisfiable.\nLa celda (" << fila+1 << "," << columna+1 << ")\n no pueder tener ningún valor posible.\n";
            exit(1);
        }
        while(nums > 0){
            int k = log2(static_cast<double>(nums));
            //cout << "Celda fila: " << fila << " columna: " << columna << " k: " << k << endl;
            Var variable = addVariable(variables,s,fila,columna,k);

            Lit l = mkLit(variable);
            CLC.clausesFila[fila*n + k].push(l);
            //cout << " \t clausesFila\n ";
            CLC.clausesColumna[columna*n + k].push(l);
            //cout << " \t clausesColumna\n ";
            CLC.clausesCeldas[i].push(l);
            //cout << " \t clausesCelda\n ";
            
            // Añadimos clasulas para que no haya más de un valor en la misma celda
            for(int j = 0; j < v.size(); j++){
                Var aux = v[j];
                s.addClause(~mkLit(aux),~mkLit(variable));
            }
            
            v.push(variable);
            nums -= (1 << k);
        }
    }
    //cout << "\nAñadir clauses\n";
    for(int i = 0; i < nceldas; i++){

        int fila = CL.celdasRellenar[i].fila,
            columna = CL.celdasRellenar[i].columna;
        uin64_t nums = CL.valoresFila[fila] & CL.valoresColumna[columna];

        while(nums > 0){
            int k = log2(static_cast<double>(nums));
            // Clausula de las filas
            //cout << " \t clausesFila\n ";
            procesarUnaClausula(CL, CLC.clausesFila[fila * n + k], s);
            // Clausula de las columnas
             //cout << " \t clausesColumna\n ";
            procesarUnaClausula(CL, CLC.clausesColumna[columna * n + k], s);

            nums -= (1 << k);
        }

        //cout << " \t clausesColumna\n ";
        s.addClause(CLC.clausesCeldas[i]);
    }
}

void mostrarVariables(map<KeyTuple,int>& variables){
    cout << endl;
    for(const auto& e: variables){
        KeyTuple k = e.first;
        Var v = e.second;
        cout << "Variable : " << v << ",celda fila: " << get<0>(k) << " columna: " << get<1>(k) << " k: " << get<2>(k) << endl;
    }
    cout << endl;
}

void mostrarCL(vector<int>& CL, const int n){
    cout << endl;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(CL[i*n+j] == 0) cout << "* ";
            else cout << CL[i*n+j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void resolverCL(string ficheroEntrada, string ficheroSalida, int n){
    
    if(argc != 3){
        cerr << "Ejecución correcta: ./main <fichero_entrada> <dimensión>";
        exit(1);
    }

    string ficheroEntrada = argv[1];
    int n = stoi(argv[2]);
    vector<int> cl(n*n,0);

    CuadradoLatino CL(n);
    leerFichero(ficheroEntrada,n,CL,cl);

    int nceldas = CL.celdasRellenar.size();
    CuadradoLatinoClauses CLC(n,nceldas);
    map<KeyTuple,int> variables;
    Solver s;


    elaborarClausesCL(CL,variables,CLC,s);
    bool resuelto = s.solve();

    if(resuelto){
        KeyTuple kt;
        mostrarCL(cl,n);

        for(int x = 0; x < s.nVars();x++){
            if(s.model[x] != l_Undef && s.model[x] == l_True){
                Var variable = x;
                for (const auto& a : variables) {
                    if (a.second == variable) {
                        kt = a.first;
                        break;
                    }
                }
                int i = get<0>(kt);
                int j = get<1>(kt);
                int k = get<2>(kt);
                if(cl[i*n+j] == 0){
                    cl[i*n+j] = k+1;
                }
                else{
                    cerr << "En la solución a la celda (" << i+1 << "," << j+1 << ") hay varios valores solución\n";
                    exit(1);
                }
            }
        }
    }
    else{
        cerr << "No hay solución\n";
        exit(1);
    }

    mostrarCL(cl,n);
}
