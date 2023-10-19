#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

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

int main() {
    std::ifstream inputFile("entrada.txt");
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

    return 0;
}
