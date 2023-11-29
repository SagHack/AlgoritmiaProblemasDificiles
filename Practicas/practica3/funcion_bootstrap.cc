

## NO ESTA COMPROBADA

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

// Función para calcular la media de un vector
double calcularMedia(const std::vector<double>& valores) {
    double suma = 0.0;
    for (double valor : valores) {
        suma += valor;
    }
    return suma / valores.size();
}

// Función para realizar un bootstrap y calcular la media
double bootstrap(const std::vector<double>& tiempos) {
    std::vector<double> muestra;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distribucion(0, tiempos.size() - 1);

    for (size_t i = 0; i < tiempos.size(); ++i) {
        muestra.push_back(tiempos[distribucion(gen)]);
    }

    return calcularMedia(muestra);
}

int main() {
    // Número de simulaciones y tamaño de la muestra
    int numSimulaciones = 500;
    int tamanoMuestra = 100; // Puedes ajustar el tamaño de la muestra según tus necesidades

    // Vector para almacenar los tiempos
    std::vector<double> tiempos;

    // Llenar tiempos con datos de tu simulación
    // Aquí debes implementar la lógica para obtener los tiempos
    // Puedes leerlos desde un archivo, generarlos aleatoriamente, etc.

    // Vector para almacenar las medias de los bootstraps
    std::vector<double> mediasBootstraps;

    // Realizar 500 bootstraps
    for (int i = 0; i < numSimulaciones; ++i) {
        double mediaBootstrap = bootstrap(tiempos);
        mediasBootstraps.push_back(mediaBootstrap);
    }

    // Ordenar las medias de menor a mayor
    std::sort(mediasBootstraps.begin(), mediasBootstraps.end());

    // Calcular la estimación de la media
    double estimacionMedia = calcularMedia(tiempos);

    // Calcular los límites del intervalo del 90%
    double L = 2 * estimacionMedia - (mediasBootstraps[475] + mediasBootstraps[476]) / 2;
    double R = 2 * estimacionMedia - (mediasBootstraps[25] + mediasBootstraps[26]) / 2;

    // Imprimir resultados
    std::cout << "Estimación de la media: " << estimacionMedia << std::endl;
    std::cout << "Intervalo del 90%: [" << L << ", " << R << "]" << std::endl;

    return 0;
}
