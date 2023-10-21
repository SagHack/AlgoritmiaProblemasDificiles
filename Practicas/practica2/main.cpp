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
using namespace std;


#define SEPARADOR ' '


struct CoordenadasCelda{
    int fila,columna;
};

struct CuadradoLatino{
    vector<CoordenadasCelda> celdasRellenar;
    vector<int> valoresFila;
    vector<int> valoresColumna;
    CuadradoLatino(int n) : valoresFila(n,(1<<n)-1), valoresColumna(n,(1<<n)-1), celdasRellenar(){}
};

void leerFichero(string ficheroEntrada,int n, vector<CuadradoLatino>& CL){
    ifstream entrada(ficheroEntrada);
    if(entrada.is_open()){
        string s;
        int vn = (1 << n) -1;
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
                    int num,mascara;
                    try{
                        num = stoi(s);
                    } catch (const invalid_argument& e){
                        cerr << "El elemento de la fila " << i+1 << " y columna " << j+1 << " no es * o un número\n";
                        exit(1);
                    }

                    if(num >= 1 || num <= n){
                        mascara = 1 << (num-1);

                        if(CL.valoresFila[i] & mascara) 
                        CL.valoresFila[i] &= ~mascara;
                        else{
                            cerr << "En la fila " << i+1 << " hay dos o más columnas con el número " << num << endl;
                            exit(1);
                        }
                        if(CL.valoresColumna[i] & mascara) 
                        CL.valoresColumna[i] &= ~mascara;
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



using KeyTuple = tuple<int,int,int>;



void numVariable(map<KeyTuple,int>& variables,int& numVariables,int i, int j, int k){
    
    KeyTuple key = make_tuple(i,j,k);
    auto iter = variables.find(key);
    int resul;
    if(iter == variables.end()){
        resul = numVariables;
        variables[key] = ++numVariables;
        
    }
    else resul = iter->second;
    return resul;
    
}

struct CuadradoLatinoClauses{
    vector<string> clausesFila;
    vector<string> clausesColumna;
    vector<string> clausesCeldas;
    CuadradoLatinoClauses(int n) : clausesFila(n*n,""), clausesColumna(n*n,""), clausesCeldas(){}
};

void elaborarClausesCL(string ficheroSalida,const vector<CuadradoLatino>& CL,map<KeyTuple,int>& variables,int& numVariables,vector<CuadradoLatinoClauses>& CLC){
    ofstream salida(ficheroSalida);
    if(salida.is_open()){
        int n = CL.celdasRellenar.size();
        for(int i = 0; i < n; i++){
            int fila = CL.celdasRellenar[i].fila;
            int columna = CL.celdasRellenar[i].columna;
            int nums = CL.valoresFila[fila] & CL.valoresColumna[columna];
            CL.clausesCeldas.push_back("");
            while(nums > 0){
                int k = log2(static_cast<double>(nums));
                int variable = numVariable(variables,numVariables,fila,columna,k);
                nums -= (2 << k);

            }
        }
    }
    else{
        exit(1);
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

    CuadradoLatino CL(n);

    leerFichero(ficheroEntrada,n,CL);

    vector<CuadradoLatinoClauses> CLC(n);

    elaborarClausesCL()
    
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
