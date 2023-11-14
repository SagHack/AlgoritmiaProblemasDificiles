/*
 * Fichero:   		resolverCL.cpp
 * Autores: 		Diego García Aranda 820506
                    Simón Alonso Gutiérrez 821038
 * Fecha entrega:	15/11/2023
 * Comentarios:     Fichero que implementa la función que resuelve el problema del 
 *                  cuadrado latino a partir de una reducción a SAT y usar el SAT solver
 *                  https://github.com/master-keying/minisat/ para resolverlo.
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

using namespace std;
using namespace Minisat;

// Tupla correspondiente al identificador generado por la tupla (fila,columna,valor_posible)
using KeyTuple = tuple<int,int,int>;


/****************************************************************************************************/
/*                      Definición e implementación de estructuras de datos 
                        usadas en el solucionador de cuadrados latinos parciales                    */

//  Estructura de las coordenadas de una celda a rellenar
struct CoordenadasCelda{
    int fila,columna;
};

/*  Estructura para almacenar las celdas a rellenar y los valores posibles de cada una.
    Para obtener las valores posibles, hay que realizar una intersección entre los valores posibles de 
    la fila en la que está la celda y los valores posibles de la columna en la que está la celda. 
    Los valores posibles están almacenador mediante una máscara de bit, la cual se guarda como un vector de
    enteros de 64 bits.                                                                                     */
struct CuadradoLatino{
    vector<CoordenadasCelda> celdasRellenar;
    vector<vector<uint64_t>> valoresFila;
    vector<vector<uint64_t>> valoresColumna;
    CuadradoLatino() : valoresFila(),valoresColumna(),celdasRellenar(){}
    CuadradoLatino(int n) : celdasRellenar(){
        int componentes = n/64;
        vector<uint64_t> aux;
        for(int i = 0; i < componentes; i++){
            aux.push_back(UINT64_MAX);
        }
        
        int k = n%64;
        if(k != 0) aux.push_back(((uint64_t) (1) << n)-1);
        
        for(int i = 0; i < n; i++){
            valoresFila.push_back(aux);
            valoresColumna.push_back(aux);
        }
    }
} CL;

//  Estructura para almacenar las cláusulas para pasarle a SAT.
struct CuadradoLatinoClauses{
    vector<vec<Lit>> clausesFila;
    vector<vec<Lit>> clausesColumna;
    vector<vec<Lit>> clausesCeldas;
    CuadradoLatinoClauses() : clausesFila(), clausesColumna(), clausesCeldas(){}
    CuadradoLatinoClauses(int n,int nceldas) : clausesFila(n*n), clausesColumna(n*n), clausesCeldas(nceldas){
    }
} CLC;

Solver solucionador;

map<KeyTuple,Var> mapa_variables;

/****************************************************************************************************/


/****************************************************************************************************/
/*                    Predefinición de funciones locales usadas para debuggear 
                      el contenido de las estructuras de datos                                      */

/*
 * Muestra las variables existentes y la tupla que tiene como clave
 */
void mostrarVariables(map<KeyTuple,Var>& variables);

/*
 * Muestra por salida estándar el cuadrado latino CL
 */
void mostrarCL(const int n);

/****************************************************************************************************/


/****************************************************************************************************/
/*  Predefinición de funciones locales usadas en el solucionador de cuadrados latinos parciales     */

/*
 * Lee el fichero ficheroEntrada, el cual almacena un cuadrado latino, completo o parcial, de dimensión 
 * n x n. Si el cuadrado latino almacenado es correcto, almacena en CL las celdas que hay que rellenar y 
 * sus valores posibles. También almacena en v el cuadrado latino leído, en el que las celdas a rellenar 
 * se almacenan como 0.
 */
void leerCL(string ficheroEntrada,vector<int>& CL_entero,int n);

/*
 * Escribe en el fichero ficheroSalida el cuadrado latino de dimensión n x n almacenado en CL.
 */
void escribirCL(const string ficheroSalida,vector<int>& CL_entero, const int n);

/*
 * Escribe en el fichero ficheroSalida el cuadrado latino de dimensión n x n almacenado en CL.
 */
void escribirCLC(const int n);

/*
 * Modifica el cuadrado latino de manera que las celdas a rellenar con único valor posible son rellenadas con 
 * ese valor, resultando que en CL sólo se almacenen celdas a rellenar que tienen al menos 2 valores posibles.
 */
void simplificarCeldas(int n,vector<int>& CL_entero);

/*
 * Añade una variable al solver de SAT que representa si valor_posible es el valor que debe tener la celda
 * con fila y columna y devuelve esa variable.
 */
Var addVariable(map<KeyTuple,Var>& variables,Solver& s,int fila, int columna, int valor_posible);

/*
 * Devuelve la variable del solver de SAT que representa si valor_posible es el valor que debe tener la celda
 * con fila y columna. Si no existe esa variable, devuelve variable no definida.
 */
Var numVariable(map<KeyTuple,Var>& variables,int fila, int columna, int valor_posible);

/*
 * Si clauses almacena una cláusula, entonces la añade en el SAT solver s. Una vez añadida, elimina la cláusula
 * para que no se vuelva a añadir.
 */
void procesarUnaClausula(vec<Lit>& clauses, Solver& s);

/*
 * Realiza la reducción de Cuadrado Latino a SAT. Para ello, a partir de las celdas a rellenar y sus valores posibles
 * almacenados en CL, elabora variables que se guardan en el map y a partir de estas genera los literales que forman
 * las cláusulas que habrá que pasar al SAT solver s y que son almacenadas en CLC.
 */
void elaborarClausesCL(map<KeyTuple,Var>& variables, Solver& s);

/*
 * Devuelve true si una fila o columna del cuadrado latino es válida, para ello la frecuencia de cada 
 * número entre 1 y n en ese fila o columan debe ser igual a 1. v almacena estas frecuencias
 */
bool validarFilaColumna(vector<int> v,int n);

/*
 * Devuelve true si el cuadrado latino almacenado en CL es válido.
 */
bool validarCL(vector<int>& CL_entero,int n);

/****************************************************************************************************/


/****************************************************************************************************/
/*                    Implementación de función que resuelve cuadrados latinos parciales            */
/*
 * Resuelve el cuadrado latino parcial  de dimensión n x n almacenado en el fichero ficheroEntrada y 
 * lo escribe en el fichero ficheroSalida. Para ello, realiza una reducción de cuadrado latino a SAT
 * y utiliza un SAT solver para resolver. Si se quiere realizar una simplificación de las cláusulas
 * que se pasan al SAT solver, el booleano deber ser true.
 */
void resolverCL(string ficheroEntrada, string ficheroSalida,vector<int>& CL_entero, int n,bool simplificar){
    
    CL_entero = vector<int>(n*n,0);
    CL = CuadradoLatino(n);
    //cout << "Voy a leer\n";
    leerCL(ficheroEntrada,CL_entero,n);
    //cout << "Leer";

    int nceldas = CL.celdasRellenar.size();
    CLC = CuadradoLatinoClauses(n,nceldas);

    if(simplificar) simplificarCeldas(n,CL_entero);
    //cout << "eCL" <<  flush;
    elaborarClausesCL(mapa_variables,solucionador);
    cout << "Solucionar\n" << flush;
    bool resuelto = solucionador.solve();
    cout << "Solucionado\n" << flush;
    if(resuelto){
        KeyTuple kt;

        for(int x = 0; x < solucionador.nVars();x++){
            if(solucionador.model[x] != l_Undef && solucionador.model[x] == l_True){
                Var variable = x;
                for (const auto& a : mapa_variables) {
                    if (a.second == variable) {
                        kt = a.first;
                        break;
                    }
                }
                int i = get<0>(kt);
                int j = get<1>(kt);
                int k = get<2>(kt);
                if(CL_entero[i*n+j] == 0){
                    CL_entero[i*n+j] = k+1;
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
    cout << "Final\n" << flush;
    
    
    if(!validarCL(CL_entero,n)){
        cerr << "Solución no válida\n";
    }
    escribirCL(ficheroSalida,CL_entero,n);
}

/****************************************************************************************************/



/****************************************************************************************************/
/*                    Implementación de funciones locales usadas para debuggear 
                      el contenido de las estructuras de datos                                      */

/*
 * Muestra las variables existentes y la tupla que tiene como clave
 */
void mostrarVariables(map<KeyTuple,int>& variables){
    cout << endl;
    for(const auto& e: variables){
        KeyTuple k = e.first;
        Var v = e.second;
        cout << "Variable : " << v << ",celda fila: " << get<0>(k) << " columna: " << get<1>(k) << " k: " << get<2>(k) << endl;
    }
    cout << endl;
}
/*
 * Muestra por salida estándar el cuadrado latino CL
 */
void mostrarCL(const int n){
    cout << endl;
    int nceldas = CL.celdasRellenar.size();
    cout << "Celdas rellenar: " << nceldas << "\n";

    for(int i = 0; i < nceldas; i++){
        cout << "\tCelda: (" << CL.celdasRellenar[i].fila+1 << "," << CL.celdasRellenar[i].columna+1 << ")\n";
    }

    cout << "Valores posibles fila:\n";
    for(int i = 0; i < n; i++){
        cout << "\tFila " << i+1 << "\n\t\t";
        vector<uint64_t> aux = CL.valoresFila[i];
        for(int j = aux.size()-1; j >= 0 ; j--){
            cout << aux[j] << " ";
        }
        cout << endl;
    }

    cout << "Valores posibles columna:\n";
    for(int i = 0; i < n; i++){
        cout << "\tColumna " << i+1 << "\n\t\t";
        vector<uint64_t> aux = CL.valoresColumna[i];
        for(int j = aux.size()-1; j >= 0 ; j--){
            cout << aux[j] << " ";
        }
        cout << endl;
    }
}


/*
 * Muestra por salida estándar el cuadrado latino CL
 */
void mostrarCLentero(vector<int>& CL_entero,const int n){
    cout << endl;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){

            if(CL_entero[i*n+j] == 0) cout << "* ";
            else cout << CL_entero[i*n+j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

/****************************************************************************************************/


/****************************************************************************************************/
/*       Implementación de funciones locales usadas en el solucionador de cuadrados latinos         */

/*
 * Lee el fichero ficheroEntrada, el cual almacena un cuadrado latino, completo o parcial, de dimensión 
 * n x n. Si el cuadrado latino almacenado es correcto, almacena en CL las celdas que hay que rellenar y 
 * sus valores posibles. También almacena en v el cuadrado latino leído, en el que las celdas a rellenar 
 * se almacenan como 0.
 */
void leerCL(string ficheroEntrada,vector<int>& CL_entero,int n){
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
                        int componenteValores = (num-1)/64;
                        int k = (num-1)-64*componenteValores; // k = num mod 64
                        mascara = (uint64_t) (1) << k;
                        
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

                       CL_entero[i*n+j] = num;

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
        entrada.close();
    }
}

/*
 * Escribe en el fichero ficheroSalida el cuadrado latino de dimensión n x n almacenado en CL.
 */
void escribirCL(const string ficheroSalida,vector<int>& CL_entero,const int n){
    ofstream entrada(ficheroSalida);
    if(entrada.is_open()){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(CL_entero[i*n+j] == 0) entrada << "* ";
                else entrada << CL_entero[i*n+j] << " ";
            }
            entrada << endl;
        }
        entrada << endl;
        entrada.close();
    }
    else{
        cerr << "No se ha podido escribir el CL en el fichero: " << ficheroSalida << endl;
        exit(1);
    }
}

/*
 * Modifica el cuadrado latino de manera que las celdas a rellenar con único valor posible son rellenadas con 
 * ese valor, resultando que en CL sólo se almacenen celdas a rellenar que tienen al menos 2 valores posibles.
 */
void simplificarCeldas(int n,vector<int>& CL_entero){
    while(1){
        bool no_simplificado = true;
        int nCeldas = CL.celdasRellenar.size();
        for(int i = 0; i < nCeldas; i++){
            int fila = CL.celdasRellenar[i].fila;
            int columna = CL.celdasRellenar[i].columna;

            vector<uint64_t> v_nums;
            int nComponentes = CL.valoresFila[0].size();
    
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
                v_nums[count] -= ((uint64_t)(1) << k);
            }

            if(nums == 1){
                CL_entero[n*fila + columna] = lastNum+1;
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

/*
 * Añade una variable al solver de SAT que representa si valor_posible es el valor que debe tener la celda
 * con fila y columna y devuelve esa variable.
 */
Var addVariable(map<KeyTuple,Var>& variables,Solver& s,int fila, int columna, int valor_posible){
    KeyTuple key = make_tuple(fila,columna,valor_posible);
    Var v = s.newVar();
    variables[key] = v;
    return v;
}

/*
 * Devuelve la variable del solver de SAT que representa si valor_posible es el valor que debe tener la celda
 * con fila y columna. Si no existe esa variable, devuelve variable no definida.
 */
Var numVariable(map<KeyTuple,Var>& variables,int fila, int columna, int valor_posible){
    KeyTuple key = make_tuple(fila,columna,valor_posible);
    auto iter = variables.find(key);
    if(iter != variables.end()) return iter->second;
    return -1;
    
}

/*
 * Si clauses almacena una cláusula, entonces la añade en el SAT solver s. Una vez añadida, elimina la cláusula
 * para que no se vuelva a añadir.
 */
 inline void procesarUnaClausula(vec<Lit>& clauses, Solver& s) {
    int nClauses = clauses.size();
    if (nClauses > 0) {
        s.addClause(clauses);
        clauses.clear();
    }
}

/*
 * Realiza la reducción de Cuadrado Latino a SAT. Para ello, a partir de las celdas a rellenar y sus valores posibles
 * almacenados en CL, elabora variables que se guardan en el map y a partir de estas genera los literales que forman
 * las cláusulas que habrá que pasar al SAT solver s y que son almacenadas en CLC.
 */
void elaborarClausesCL(map<KeyTuple,Var>& variables, Solver& s){
    
    int n = CL.valoresFila.size();
    int nceldas = CL.celdasRellenar.size();
    for(int i = 0; i < nceldas; i++){
        
        int fila = CL.celdasRellenar[i].fila;
        int columna = CL.celdasRellenar[i].columna;
        
        vector<uint64_t> v_nums;
        int nComponentes = CL.valoresFila[0].size();
        bool cero = true;
        for(int w=0;w<nComponentes;w++){
            uint64_t mascaraAux = CL.valoresFila[fila][w] & CL.valoresColumna[columna][w];
            if(cero) cero = mascaraAux == 0;
            v_nums.push_back(mascaraAux);
        }
        if(cero){
            cout << "El cuadrado latino es unsatisfiable.\nLa celda (" << fila+1 << "," << columna+1 << ")\n no pueder tener ningún valor posible.\n";
            exit(1);
        }
        int count = nComponentes-1;
        while(count >= 0){
            if(v_nums[count] <=0){
                count--;
                continue;
            }

            int k = log2(static_cast<double>(v_nums[count]));
            Var variable = addVariable(variables,s,fila,columna,(k+count*64));
            Lit l = mkLit(variable);
            CLC.clausesFila[fila*n + (k+count*64)].push(l);
            CLC.clausesColumna[columna*n + (k+count*64)].push(l);
            CLC.clausesCeldas[i].push(l);
            
            v_nums[count] -= ((uint64_t)(1) << k);
        }
    }

    for(int i = 0; i < nceldas; i++){

        int fila = CL.celdasRellenar[i].fila,
            columna = CL.celdasRellenar[i].columna;
        
        vector<uint64_t> v_nums;
        int nComponentes = CL.valoresFila[0].size();
        
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
            // Clausula de la fila
            procesarUnaClausula(CLC.clausesFila[fila * n + (k+count*64)], s);
            // Clausula de la columna
            procesarUnaClausula(CLC.clausesColumna[columna * n + (k+count*64)], s);

            v_nums[count] -= ((uint64_t)(1) << k);
        }
        
        int nlits = CLC.clausesCeldas[i].size();
        for(int lit1 = 0; lit1 < nlits;lit1++ ){
            for(int lit2 = 0; lit2 < lit1;lit2++ ){
                s.addClause(~CLC.clausesCeldas[i][lit1],~CLC.clausesCeldas[i][lit2]);
            }
        }

        s.addClause(CLC.clausesCeldas[i]);
    }
}

/*
 * Devuelve true si una fila o columna del cuadrado latino es válida, para ello la frecuencia de cada 
 * número entre 1 y n en ese fila o columan debe ser igual a 1. v almacena estas frecuencias
 */
bool validarFilaColumna(vector<int> v,int n){
    for(int i =0;i<n;i++){
        if(v[i] != 1){
            return false;
        }
    }
    return true;
}

/*
 * Devuelve true si el cuadrado latino almacenado en CL es válido.
 */
bool validarCL(vector<int>& CL_entero,int n){
    for(int i = 0; i < n; i++){
        vector<int> v_reps(n,0);
        for(int j = 0; j < n; j++){
            v_reps[CL_entero[i*n + j]-1]++;
        }        
        if(!validarFilaColumna(v_reps,n)){
            return false;
        }
    }

    for(int i = 0; i < n; i++){
        vector<int> v_reps(n,0);
        for(int j = 0; j < n; j++){
            v_reps[CL_entero[j*n + i]-1]++;
        }        
        if(!validarFilaColumna(v_reps,n)){
            return false;
        }
    }
    return true;
}






