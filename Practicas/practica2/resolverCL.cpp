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
/*                      Definición e implementación de estructuras de datos 
                        usadas en el solucionador de cuadrados latinos parciales                    */

struct CoordenadasCelda{
    int fila,columna;
};

struct CuadradoLatino{
    vector<CoordenadasCelda> celdasRellenar;
    vector<vector<uint64_t>> valoresFila;
    vector<vector<uint64_t>> valoresColumna;
    CuadradoLatino(int n) : celdasRellenar(){
        int componentes = ceil(n/64.0);
        vector<uint64_t> aux;
        for(int i = 1; i < componentes; i++){
            aux.push_back(UINT64_MAX);
        }
        
        int k = n%64;
        if(k != 0) aux.push_back(((uint64_t) (1) << n)-1);
        
        for(int i = 0; i < n; i++){
            valoresFila.push_back(aux);
            valoresColumna.push_back(aux);
        }
    }
};

struct CuadradoLatinoClauses{
    vector<vec<Lit>> clausesFila;
    vector<vec<Lit>> clausesColumna;
    vector<vec<Lit>> clausesCeldas;
    CuadradoLatinoClauses(int n,int nceldas) : clausesFila(n*n), clausesColumna(n*n), clausesCeldas(nceldas){
    }
};

/****************************************************************************************************/


/****************************************************************************************************/
/*                    Predefinición de funciones locales usadas para debuggear 
                      el contenido de las estructuras de datos                                      */

void mostrarVariables(map<KeyTuple,int>& variables);
void mostrarCL(vector<int>& CL, const int n);

/****************************************************************************************************/


/****************************************************************************************************/
/*  Predefinición de funciones locales usadas en el solucionador de cuadrados latinos parciales     */

void leerFichero(string ficheroEntrada,int n, CuadradoLatino& CL, vector<int>& v);

Var addVariable(map<KeyTuple,Var>& variables,Solver& s,int fila, int columna, int valor_posible);
Var numVariable(map<KeyTuple,Var>& variables,int fila, int columna, int valor_posible);
void simplificarCeldas(CuadradoLatino& CL,vector<int>& cl,int n);
void procesarUnaClausula(const CuadradoLatino& CL, vec<Lit>& clauses, Solver& s);
void elaborarClausesCL(const CuadradoLatino& CL,map<KeyTuple,Var>& variables,CuadradoLatinoClauses& CLC, Solver& s);
void escribirCL(const string ficheroSalida,vector<int>& CL, const int n);
bool valid_row_column(vector<int> v,int n);
bool validarSolucion(vector<int>& CL,int n);

/****************************************************************************************************/


/****************************************************************************************************/
/*                    Implementación de funcion que resuelve cuadrados latinos parciales            */

void resolverCL(string ficheroEntrada, string ficheroSalida, int n,bool simplificar){
    

    vector<int> cl(n*n,0);

    CuadradoLatino CL(n);
    leerFichero(ficheroEntrada,n,CL,cl);

    int nceldas = CL.celdasRellenar.size();
    CuadradoLatinoClauses CLC(n,nceldas);
    map<KeyTuple,int> variables;
    Solver s;

    if(simplificar) simplificarCeldas(CL,cl,n);
    elaborarClausesCL(CL,variables,CLC,s);
    bool resuelto = s.solve();

    if(resuelto){
        KeyTuple kt;

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
    
    
    if(!validarSolucion(cl,n)){
        cerr << "Solución no válida\n";
    }
    escribirCL(ficheroSalida,cl,n);
}

/****************************************************************************************************/



/****************************************************************************************************/
/*                    Implementación de funciones locales usadas para debuggear 
                      el contenido de las estructuras de datos                                      */

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

/****************************************************************************************************/


/****************************************************************************************************/
/*       Implementación de funciones locales usadas en el solucionador de cuadrados latinos         */

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
                    uint64_t mascara;
                    try{
                        num = stoi(s);
                    } catch (const invalid_argument& e){
                        cerr << "El elemento de la fila " << i+1 << " y columna " << j+1 << " no es * o un número\n";
                        exit(1);
                    }

                    if(num >= 1 || num <= n){
                        
                        int componenteValores = num/64;
                        int k = num-64*componenteValores; // k = num mod 64
                        mascara = (uint64_t) (1) << (k-1);
                        
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



Var addVariable(map<KeyTuple,Var>& variables,Solver& s,int fila, int columna, int valor_posible){
    KeyTuple key = make_tuple(fila,columna,valor_posible);
    Var v = s.newVar();
    variables[key] = v;
    return v;
}

Var numVariable(map<KeyTuple,Var>& variables,int fila, int columna, int valor_posible){
    KeyTuple key = make_tuple(fila,columna,valor_posible);
    auto iter = variables.find(key);
    if(iter != variables.end()) return iter->second;
    return -1;
    
}

void simplificarCeldas(CuadradoLatino& CL,vector<int>& cl,int n){
    while(1){
        bool no_simplificado = true;
        int nCeldas = CL.celdasRellenar.size();
        for(int i = 0; i < nCeldas; i++){
            int fila = CL.celdasRellenar[i].fila;
            int columna = CL.celdasRellenar[i].columna;

            vector<uint64_t> v_nums;
            int nComponentes = CL.valoresFila[0].size();
            
            // Se obtiene la mascara con el resultado de 
            for(int w=0;w<nComponentes;w++){
                v_nums.push_back(CL.valoresFila[fila][w] & CL.valoresColumna[columna][w]);
            }
            int nums = 0, count = nComponentes -1;
            uint64_t lastNum, lastK;

            while(count >= 0){
                if(v_nums[count] <=0){
                    count--;
                    continue;
                }

                int k = log2(static_cast<double>(v_nums[count]));


                lastNum = k + count*64;
                lastK = k;
                nums++;
                v_nums[count] -= (1 << k);
            }

            if(nums == 1){
                cl[n*fila + columna] = lastNum+1;
                CL.valoresFila[fila][lastK] &= ~((uint64_t) (1) << (lastK-1));
                CL.valoresColumna[columna][lastK] &= ~((uint64_t) (1) << (lastK-1));
                CL.celdasRellenar.erase(CL.celdasRellenar.begin()+i);
                no_simplificado = false;
                break;
            }
            else if(nums == 0) break;
        }

        

        if (no_simplificado) break;
    }
}

void procesarUnaClausula(vec<Lit>& clauses, Solver& s) {
    int nClauses = clauses.size();
    if (nClauses > 0) {
        s.addClause(clauses);
        clauses.clear();
    }
}

void elaborarClausesCL(const CuadradoLatino& CL,map<KeyTuple,Var>& variables,CuadradoLatinoClauses& CLC, Solver& s){
    
    int n = CL.valoresFila.size();
    int nceldas = CL.celdasRellenar.size();
    for(int i = 0; i < nceldas; i++){
        int fila = CL.celdasRellenar[i].fila;
        int columna = CL.celdasRellenar[i].columna;
            
        vector<uint64_t> v_nums;
        int nComponentes = CL.valoresFila[0].size();
        
        // Se obtiene la mascara con el resultado de 
        for(int w=0;w<nComponentes;w++){
            v_nums.push_back(CL.valoresFila[fila][w] & CL.valoresColumna[columna][w]);
        }

        vec<Var> v;
        vec<Lit> vl;
        int vLits = 0;
        bool cero = true;

        for(int w=0;w<v_nums.size();++w){
            if(cero) cero = v_nums[w] == 0;
        }
        if(cero){
            cout << "El cuadrado latino es unsatisfiable.\nLa celda (" << fila+1 << "," << columna+1 << ")\n no pueder tener ningún valor posible.\n";
            exit(1);
        }

        int count = v_nums.size()-1;

        while(count >= 0){
            if(v_nums[count] <=0){
                count--;
                continue;
            }

            int k = log2(static_cast<double>(v_nums[count]));
            Var variable = addVariable(variables,s,fila,columna,(k+count*64));
            Lit l = mkLit(variable);
            CLC.clausesFila[fila*n + (k+count*64)].push(l);
            //cout << " \t clausesFila\n ";
            CLC.clausesColumna[columna*n + (k+count*64)].push(l);
            //cout << " \t clausesColumna\n ";
            CLC.clausesCeldas[i].push(l);
            //cout << " \t clausesCelda\n ";
            // Añadimos clasulas para que no haya más de un valor en la misma celda
            for(int j = 0; j < v.size(); j++){
                Var aux = v[j];
                s.addClause(~mkLit(aux),~mkLit(variable));
            }
            
            v.push(variable);
            
            
            v_nums[count] -= (1 << k);
            
        }
    }
    //cout << "\nAñadir clauses\n";
    for(int i = 0; i < nceldas; i++){

        int fila = CL.celdasRellenar[i].fila,
            columna = CL.celdasRellenar[i].columna;
        
        

        vector<uint64_t> v_nums;
        int nComponentes = CL.valoresFila[0].size();
        
        // Se obtiene la mascara con el resultado de 
        for(int w=0;w<nComponentes;w++){
            v_nums.push_back(CL.valoresFila[fila][w] & CL.valoresColumna[columna][w]);
        }

        int count = nComponentes-1;

        while(count >= 0){
            if(v_nums[count] <=0){
                count--;
                continue;
            }
            int k = log2(static_cast<double>(v_nums[count]));
            // Clausula de las filas
            //cout << " \t clausesFila\n ";
            procesarUnaClausula(CLC.clausesFila[fila * n + (k+count*64)], s);
            // Clausula de las columnas
             //cout << " \t clausesColumna\n ";
            procesarUnaClausula(CLC.clausesColumna[columna * n + (k+count*64)], s);

            v_nums[count] -= (1 << k);
        }

        //cout << " \t clausesColumna\n ";
        s.addClause(CLC.clausesCeldas[i]);
    }
}

void escribirCL(const string ficheroSalida,vector<int>& CL, const int n){
    ofstream entrada(ficheroSalida);
    if(entrada.is_open()){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(CL[i*n+j] == 0) entrada << "* ";
                else entrada << CL[i*n+j] << " ";
            }
            entrada << endl;
        }
        entrada << endl;
    }
    else{
        cerr << "No se ha podido escribir el CL en el fichero: " << ficheroSalida << endl;
        exit(1);
    }
}


bool valid_row_column(vector<int> v,int n){
    for(int i =0;i<n;i++){
        if(v[i] != 1){
            return false;
        }
    }
    return true;
}


bool validarSolucion(vector<int>& CL,int n){
    for(int i = 0; i < n; i++){
        vector<int> v_reps(n,0);
        for(int j = 0; j < n; j++){
            v_reps[CL[i*n + j]-1]++;
        }        
        if(!valid_row_column(v_reps,n)){
            return false;
        }
    }

    for(int i = 0; i < n; i++){
        vector<int> v_reps(n,0);
        for(int j = 0; j < n; j++){
            v_reps[CL[j*n + i]-1]++;
        }        
        if(!valid_row_column(v_reps,n)){
            return false;
        }
    }
    return true;
}






