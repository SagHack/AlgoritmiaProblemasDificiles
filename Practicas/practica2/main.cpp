#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <random>
using namespace std;

#define SEPARADOR ' '

class VectorOcurrencias{
    public: 
        vector<int> v;
        VectorOcurrencias(int n, int valor) : v(n,valor) {}
};

void generarCuadradoLatino(string ficheroSalida,int n, double porcentaje){
    ofstream salida(ficheroSalida);
    if(salida.is_open()){

        int i = 0, j = 0;
        vector<int> valores_posibles(2*n,(1<<n)-1);
        
        random_device nd;
        mt19937 genP(nd());
        uniform_int_distribution<int> distribucionN(1,n);

        random_device pd;
        mt19937 genN(pd());
        uniform_real_distribution<double> distribucionP(1.0,100.0);


        while(i < n){
            double random = distribucionP(genP);
            string s;
            if(random < porcentaje){
                s = "*";
            }
            else{
                int valido;
                int num;
                int mascara;
                do{
                    num = distribucionN(genN);
                    mascara = 1 << (num-1);
                    valido = valores_posibles[i] & mascara & valores_posibles[n+j];
                } while(valido == 0);
                valores_posibles[i] &= ~mascara;
                s = to_string(num);
            }

            if(++j == n){
                salida << s << endl;
                i++;
                j = 0;
            }
            else{
                salida << s << " ";
            }
        }

    }
}

void leerFichero(string ficheroEntrada,int n, vector<int>& vals_filas,vector<int>& vals_columnas){
    ifstream entrada(ficheroEntrada);
    if(entrada.is_open()){
        string s;
        VectorOcurrencias v(n,0);
        int vn = (1 << n) -1;
        vector<int> valores_posibles(2*n,vn);
        vector<VectorOcurrencias> ocurrencias(2*n,v);
        int i = 0, j = 0;

        while(getline(entrada,s,SEPARADOR)){
            stringstream linea(s);
            while(getline(linea,s,SEPARADOR)){
                if(s == "*"){
                    cout << s;
                }
                else{
                    int num;
                    try{
                        num = stoi(s);
                    } catch (const invalid_argument& e){

                    }
                    if(num >= 1 || num <= n){
                        if(++ocurrencias[i].v[num] > 1){
                            cerr << "";
                            exit(1);
                        }
                        if(++ocurrencias[n+j].v[num] > 1){
                            cerr << "";
                            exit(1);
                        }

                        valores_posibles[i] &= ~(1 << num-1);
                        valores_posibles[n+j] &= ~(1 << num-1);

                    }
                    else{
                        cerr << "";
                        exit(1);
                    }
                }
                j++;
                
            }
            i++;
            j = 0;
        
        }

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
    cout << "Antes";
    if(argc != 4){
        cerr << "Mal";
        exit(1);
    }
    cout << "Bien";

    string ficheroSalida = argv[1];
    int n = stoi(argv[2]);
    double p = stod(argv[3]);

    generarCuadradoLatino(ficheroSalida,n,p);
    
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
