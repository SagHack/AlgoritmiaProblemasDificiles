#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

std::vector<std::vector<int>> generarCuadradoLatinoParcial(int n) {
    if (n < 2) {
        std::vector<std::vector<int>> cuadrado_vacio;
        return cuadrado_vacio;
    }

    // Crear una matriz vacía
    std::vector<std::vector<int>> cuadrado(n, std::vector<int>(n, 0));

    // Llenar la primera fila con valores aleatorios
    for (int i = 0; i < n; i++) {
        cuadrado[0][i] = i + 1;
    }

    // Llenar las filas restantes de manera que sea un cuadrado latino parcial
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::vector<int> opciones_disponibles;
            for (int num = 1; num <= n; num++) {
                opciones_disponibles.push_back(num);
            }
            for (int k = 0; k < i; k++) {
                int valor = cuadrado[k][j];
                opciones_disponibles.erase(valor);
            }
            int indice_aleatorio = rand() % opciones_disponibles.size();
            cuadrado[i][j] = opciones_disponibles[indice_aleatorio];
        }
    }

    return cuadrado;
}

void imprimirCuadradoLatino(const std::vector<std::vector<int>>& cuadrado) {
    for (const auto& fila : cuadrado) {
        for (int valor : fila) {
            std::cout << valor << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    int n = 4; // Puedes cambiar n para ajustar el tamaño del cuadrado
    std::srand(std::time(0)); // Inicializar la semilla aleatoria

    std::vector<std::vector<int>> cuadrado_parcial = generarCuadradoLatinoParcial(n);
    if (!cuadrado_parcial.empty()) {
        std::cout << "Cuadrado Latino Parcial de orden " << n << ":\n";
        imprimirCuadradoLatino(cuadrado_parcial);
    } else {
        std::cout << "No se pudo generar un cuadrado latino parcial de orden " << n << std::endl;
    }

    return 0;
}
