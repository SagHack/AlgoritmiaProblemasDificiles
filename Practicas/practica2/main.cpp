#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <random>
#include <stdio.h>
using namespace std;

#define SEPARADOR ' '

class VectorOcurrencias{
    public: 
        vector<int> v;
        VectorOcurrencias(int n, int valor) : v(n,valor) {}
};

struct OcurrenciasValor{
    int OcurrenciasColumnas, OcurrenciasFilas;
    OcurrenciasValor(int num) : OcurrenciasColumnas(num), OcurrenciasFilas(num){}
};

void leerFichero(string ficheroEntrada,int n, vector<OcurrenciasValor>& ocurrenciasNum){
    ifstream entrada(ficheroEntrada);
    if(entrada.is_open()){
        string s;
        VectorOcurrencias v(n,0);
        int vn = (1 << n) -1;
        vector<int> valores_posibles(2*n,vn);
        vector<VectorOcurrencias> ocurrencias(2*n,v);
        int i = 0, j = 0;

        while(getline(entrada,s)){
            stringstream linea(s);
            while(getline(linea,s,SEPARADOR)){
                if(s == "*"){
                }
                else{
                    int num,mascaraFila,mascaraColumna;
                    try{
                        num = stoi(s);
                    } catch (const invalid_argument& e){
                        cerr << "El elemento de la fila " << i+1 << " y columna " << j+1 << " no es * o un número\n";
                        exit(1);
                    }

                    if(num >= 1 || num <= n){
                        mascaraFila = (1 << i);
                        mascaraColumna = (1 << j);

                        if(ocurrenciasNum[num-1].OcurrenciasFilas & mascaraFila) 
                        ocurrenciasNum[num-1].OcurrenciasFilas &= ~mascaraFila;
                        else{
                            cerr << "En la fila " << i+1 << " hay dos o más columnas con el número " << num << endl;
                            exit(1);
                        }
                        if(ocurrenciasNum[num-1].OcurrenciasColumnas & mascaraColumna) 
                        ocurrenciasNum[num-1].OcurrenciasColumnas &= ~mascaraColumna;
                        else{
                            cerr << "En la columna " << j+1 << " hay dos o más filas con el número " << num << endl;
                            exit(1);
                        }

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
            cout << i;
            cerr << "No hay " << n << " filas\n";
            exit(1);
        }

    }
}



void printBinary(int number,int n){
    if (number == 0) {
        printf("0");
        return;
    }
    int maskMax = (1<<n);
    int mask = 1; // Máscara para el bit más significativo de un entero de 32 bits

    while (mask < maskMax) {
        if (number & mask) {
            printf("1");
        } else {
            printf("0");
        }
        mask <<= 1;
    }
}

void printOcurrencias(vector<OcurrenciasValor>& ocurrenciasNum){
    int n = ocurrenciasNum.size();
    for(int i = 0; i < n; i++){
        cout << "Número : " << i+1 << endl;
        cout << "\tfilas: ";
        printBinary(ocurrenciasNum[i].OcurrenciasFilas,n);
        cout << "\n\tfilas: ";
        printBinary(ocurrenciasNum[i].OcurrenciasColumnas,n);
        cout << endl;
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

int main(int argc, char* argv[]) {
    
    if(argc != 3){
        cerr << "Ejecución correcta: ./main <fichero_entrada> <dimensión>";
        exit(1);
    }

    string ficheroEntrada = argv[1];
    int n = stoi(argv[2]);

    vector<OcurrenciasValor> ocurrenciasNum(n,OcurrenciasValor((1 << n)-1));

    leerFichero(ficheroEntrada,n,ocurrenciasNum);
    printOcurrencias(ocurrenciasNum);
    
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
