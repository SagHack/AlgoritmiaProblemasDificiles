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
using namespace std;


#define SEPARADOR ' '


struct CoordenadasCelda{
    int fila,columna;
};

struct CuadradoLatino{
    vector<CoordenadasCelda> celdasRellenar;
    vector<unsigned long long> valoresFila;
    vector<unsigned long long> valoresColumna;
    CuadradoLatino(int n) : valoresFila(n,((unsigned long long) (1)<<n)-1), valoresColumna(n,((unsigned long long) (1)<<n)-1), celdasRellenar(){}
};

void leerFichero(string ficheroEntrada,int n, CuadradoLatino& CL, vector<int>& v){
    ifstream entrada(ficheroEntrada);
    if(entrada.is_open()){
        string s;
        int i = 0, j = 0;
        CoordenadasCelda c;

        while(getline(entrada,s)){
            stringstream linea(s);
            while(getline(linea,s,SEPARADOR)){
                if(s == "*"){
                    c.fila = i;
                    c.columna = j;
                    CL.celdasRellenar.push_back(c);
                }
                else{
                    int num;
                    unsigned long long mascara;
                    try{
                        num = stoi(s);
                    } catch (const invalid_argument& e){
                        cerr << "El elemento de la fila " << i+1 << " y columna " << j+1 << " no es * o un número\n";
                        exit(1);
                    }

                    if(num >= 1 || num <= n){
                        mascara = (unsigned long long) (1) << (num-1);

                        if(CL.valoresFila[i] & mascara) 
                        CL.valoresFila[i] &= ~mascara;
                        else{
                            cerr << "En la fila " << i+1 << " hay dos o más columnas con el número " << num << endl;
                            exit(1);
                        }
                        if(CL.valoresColumna[j] & mascara) 
                        CL.valoresColumna[j] &= ~mascara;
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


Var addVariable(map<KeyTuple,Var>& variables,Solver& s,int i, int j, int k){
    KeyTuple key = make_tuple(i,j,k);
    Var v = s.newVar();
    variables[key] = v;
    return v;
}

Var numVariable(map<KeyTuple,Var>& variables,int i, int j, int k){
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


void elaborarClausesCL(const CuadradoLatino& CL,map<KeyTuple,Minisat::Var>& variables,CuadradoLatinoClauses& CLC, Solver& s){
    
    int n = CL.valoresFila.size();
    int nceldas = CL.celdasRellenar.size();
    for(int i = 0; i < nceldas; i++){
        int fila = CL.celdasRellenar[i].fila;
        int columna = CL.celdasRellenar[i].columna;
        unsigned long long nums = CL.valoresFila[fila] & CL.valoresColumna[columna];
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
        unsigned long long nums = CL.valoresFila[fila] & CL.valoresColumna[columna];

        while(nums > 0){
            int k = log2(static_cast<double>(nums));
            //cout << "Celda fila: " << fila << " columna: " << columna << " k: " << k << endl;

            int nClauses = CLC.clausesFila[fila*n+k].size();
            if(nClauses > 0){
                //cout << " \t clausesFila\n ";
                s.addClause(CLC.clausesFila[fila*n+k]);
                CLC.clausesFila[fila*n+k].clear();
            }

            nClauses = CLC.clausesColumna[columna*n+k].size();
            if(nClauses > 0){
                //cout << " \t clausesColumna\n ";
                s.addClause(CLC.clausesColumna[columna*n+k]);
                CLC.clausesColumna[columna*n+k].clear();
            }

            nums -= (1 << k);
        }

        //cout << " \t clausesColumna\n ";
        s.addClause(CLC.clausesCeldas[i]);
        
    }
}



bool isValid(std::vector<std::vector<char>>& square, int row, int col, char num) {
    // Verifica que 'num' no se repita en la misma fila o columna
    for (int i = 0; i < 9; i++) {
        if (square[row][i] == num || square[i][col] == num) {
            return false;
        }
    }
    return true;
}

bool solveLatinSquare(std::vector<std::vector<char>>& square) {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if (square[row][col] == '*') {
                for (char num = '1'; num <= '9'; num++) {
                    if (isValid(square, row, col, num)) {
                        square[row][col] = num;
                        if (solveLatinSquare(square)) {
                            return true;
                        }
                        square[row][col] = '*'; // Backtrack
                    }
                }
                return false;
            }
        }
    }
    return true; // Se ha llenado el cuadrado sin asteriscos
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

int main(int argc, char* argv[]) {
    
    if(argc != 3){
        cerr << "Ejecución correcta: ./main <fichero_entrada> <dimensión>";
        exit(1);
    }

    string ficheroEntrada = argv[1];
    int n = stoi(argv[2]);
    vector<int> cl(n*n,0);

    CuadradoLatino CL(n);
    //cout << "Inicio Leer Fichero\n";
    leerFichero(ficheroEntrada,n,CL,cl);
    //cout << "Fin Leer Fichero\n";

    int nceldas = CL.celdasRellenar.size();
    CuadradoLatinoClauses CLC(n,nceldas);
    map<KeyTuple,int> variables;
    Solver s;

    //cout << "Inicio Elaborar Clauses\n";

    elaborarClausesCL(CL,variables,CLC,s);
    //cout << "Fin Elaborar Clauses\n";
    bool resuelto = s.solve();

    //mostrarVariables(variables);

    if(resuelto){
        KeyTuple kt;
        mostrarCL(cl,n);

        for(int x = 0; x < s.nVars();x++){
            /*cout << "Variable : " << x << ",resultado : ";
            
            if (s.model[x] == l_Undef){
                cout << "false";
            }
            else if (s.model[x] == l_True){
                cout << "true";
            }
            cout << endl;*/
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
                //mostrarCL(cl,n);
            }
        }
    }
    else{
        cerr << "No hay solución\n";
        exit(1);
    }

    mostrarCL(cl,n);
    
    /*std::ifstream inputFile("entrada.txt");
    std::ofstream outputFile("salida.txt");
    std::vector<std::vector<char>> latinSquare(9, std::vector<char>(9));

    if (inputFile.is_open() && outputFile.is_open()) {
        // Leer la entrada
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                inputFile >> latinSquare[i][j];
            }
        }

        // Resolver el cuadrado latino
        if (solveLatinSquare(latinSquare)) {
            // Escribir la solución en el archivo de salida
            for (int i = 0; i < 9; i++) {
                for (int j = 0; j < 9; j++) {
                    outputFile << latinSquare[i][j] << ' ';
                }
                outputFile << '\n';
            }
            std::cout << "Solución encontrada y escrita en salida.txt." << std::endl;
        } else {
            std::cout << "No se encontró una solución válida." << std::endl;
        }

        inputFile.close();
        outputFile.close();
    } else {
        std::cerr << "Error al abrir los archivos de entrada o salida." << std::endl;
    }

    return 0;*/
}
