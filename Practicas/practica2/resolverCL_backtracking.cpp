#include <iostream>
#include <fstream>
#include <vector>
#include<string>
#include <sstream>
using namespace std;

#define SEPARADOR_ENTRADA ' '
/*
 * Lee el fichero ficheroEntrada, el cual almacena un cuadrado latino, completo o parcial, de dimensión 
 * n x n. Si el cuadrado latino almacenado es correcto, almacena en CL las celdas que hay que rellenar y 
 * sus valores posibles. También almacena en v el cuadrado latino leído, en el que las celdas a rellenar 
 * se almacenan como 0.
 */
void leerCL_backtracking(string ficheroEntrada,vector<int>& CL_entero,int n){
    ifstream entrada(ficheroEntrada);
    if(entrada.is_open()){
        string s;
        int i = 0, j = 0;

        while(getline(entrada,s)){
            stringstream linea(s);
            while(getline(linea,s,SEPARADOR_ENTRADA)){
                if(s == "*"){
                    CL_entero[i*n+j] = 0;
                }
                else{
                    int num;
                    try{
                        num = stoi(s);
                    } catch (const invalid_argument& e){
                        cerr << "El elemento de la fila " << i+1 << " y columna " << j+1 << " no es * o un número\n";
                        exit(1);
                    }

                    if(num >= 1 || num <= n){
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
 *  Escribe en el fichero ficheroSalida el cuadrado latino de dimensión 
 *  n x n almacenado en CL.
 */
void escribirCL_backtracking(const vector<int>& CL,const string ficheroSalida,const int n){
    ofstream salida(ficheroSalida);
    if(salida.is_open()){

        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                int aux = CL[i*n+j];
                if(aux == 0){
                    salida << "* ";
                }
                else{
                    salida << aux <<" ";
                }
                
            }
            salida << endl;
        }   
        
        salida.close();
    }
}

// Devuelve true si el numero esta presente en la fila especificada
bool estaEnFila(const vector<int>& CL, int fila, int num,int n) {
    for (int j = 0; j < n; ++j) {
        if (CL[fila*n + j] == num) {
            return true;
        }
    }
    return false;
}

// Devuelve true si el numero esta presente en la columna especificada
bool estaEnColumna(const vector<int>& CL, int columna, int num,int n) {
    for (int i = 0; i < n; ++i) {
        if (CL[i*n + columna] == num) {
            return true;
        }
    }
    return false;
}

// Devuelve true si se puede colocar el número en la posición especificada
bool puedeColocar(const vector<int>& square, int row, int col, int num,int n) {
    return !estaEnFila(square, row, num,n) && !estaEnColumna(square, col, num,n);
}


// Backtracking function to solve the Latin square
bool resolverCL_backtracking(vector<int>& CL,int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            // Check if the cell is empty
            if (CL[i*n + j] == 0) {
                for (int num = 1; num <= n; ++num) {
                    if (puedeColocar(CL, i, j, num,n)) {
                        // Place the number in the cell
                        CL[i*n + j] = num;
                        // Recursively try to fill the rest of the square
                        if (resolverCL_backtracking(CL,n)) {
                            return true;  // Solution found
                        }

                        // If placing the number doesn't lead to a solution, backtrack
                        CL[i*n + j] = 0;
                    }
                }

                // If no number can be placed in the current cell, backtrack
                return false;
            }
        }
    }

    // If all cells are filled, the Latin square is solved
    return true;
}
