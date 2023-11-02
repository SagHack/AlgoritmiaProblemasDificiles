#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <set>
#include <time.h>
#include <algorithm>
using namespace std;

// Se pasa el cuadrado latino completo, y se devuelve un cuadrado latino parcial, con un número de *
// equivalente al porcentaje
void generatePartialLatinSquare(int n, double porcentaje, vector<vector<int>>& square) {
    int k = n * n * porcentaje / 100;

    mt19937 gen(time(nullptr));

    vector<int> available_indices(n * n);
    for (int i = 0; i < n * n; i++) {
        available_indices[i] = i;
    }

    shuffle(available_indices.begin(), available_indices.end(), gen); // Mezcla con un generador aleatorio

    for (int i = 0; i < k; ++i) {
        int linear_index = available_indices[i];
        int row = linear_index / n;
        int col = linear_index - row * n;
        square[row][col] = -1;
    }
}




// Genera un cuadrado latino solamente con permutacione, siempre es el mismo
void generateCompleteLatinSquare(int n,vector<vector<int>>& square) {
    mt19937 gen(time(nullptr));
    vector<int> available_indices(n);
    for (int i = 0; i < n; i++) {
        available_indices[i] = i;
    }
    shuffle(available_indices.begin(), available_indices.end(), gen);
    
    for (int i=0;i<n;i+=1) {
        for (int j = 0; j < n; j++) {
            square[i][j] = (available_indices[i] + j) % n + 1;
        }
    }
}


void writeLatinSquareToFile(const vector<vector<int>>& square, const string& filename) {
    ofstream file(filename);

    if (file.is_open()) {
        for (const vector<int>& row : square) {
            for (int num : row) {
                if(num == -1){
                    file << "* ";
                }else{
                    file << num << ' ';
                }
                
            }
            file << '\n';
        }
        file.close();
    } else {
        cerr << "No se pudo abrir el archivo para escritura." << endl;
    }
}


// Funcion que comprueba que el cuadrado latino generado se puede satisfacer o no.
bool isValidLatinSquare(const vector<vector<int>>& square) {
    int n = square.size();
    
    // Check if it's a square matrix
    for (const auto& row : square) {
        if (row.size() != n) {
            return false;
        }
    }
    
    // Check if values are unique in rows
    for (const auto& row : square) {
        set<int> unique_values;
        for (int value : row) {
            if (value < 1 || value > n || !unique_values.insert(value).second) {
                return false; // Invalid value or duplicate in row
            }
        }
    }
    
    // Check if values are unique in columns
    for (int col = 0; col < n; ++col) {
        set<int> unique_values;
        for (int row = 0; row < n; ++row) {
            int value = square[row][col];
            if (!unique_values.insert(value).second) {
                return false; // Duplicate value in column
            }
        }
    }
    
    return true; // If it passes all checks, it's a valid Latin square
}



int main(int argc, char* argv[]) {
    if (argc != 4) {
        cerr << "Uso: " << argv[0] << " <n> <porcentaje> <filename>" << endl;
        return 1;
    }

    int n = atoi(argv[1]);
    double porcentaje = atof(argv[2]);
    string filename = argv[3];

    if (n < 1) {
        cerr << "El orden del cuadrado latino debe ser mayor >=2" << endl;
        return 1;
    }
    
    if (porcentaje < 0 || porcentaje > 100) {
        cerr << "El porcentaje debe estar en el rango [0,100]" << endl;
        return 1;
    }

    vector<vector<int>> latinSquare(n, vector<int>(n));
    generateCompleteLatinSquare(n, latinSquare);
    if (isValidLatinSquare(latinSquare)) {
        cout << "Cuadrado latino valido" << endl;
    } else {
        cout << "Cuadrado latino NO valido" << endl;
    }

    // Generamos el cuadrado latino con el porcentaje de *
    generatePartialLatinSquare(n,porcentaje,latinSquare);

    writeLatinSquareToFile(latinSquare, filename);
    cout << "Cuadrado latino de orden " << n << " con un porcentaje " << porcentaje << "% de *, generado y guardado en " << filename << endl;

    return 0;
}
