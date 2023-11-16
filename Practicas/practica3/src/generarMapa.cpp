#include <iostream>
#include <fstream>
#include <random>
#include "carretera.h"
#include "interseccion.h"
using namespace std;


void generarFichero(const string ficheroEntrada) {

    ofstream entrada(ficheroEntrada); // Nombre del archivo donde se escribirán los datos
    if (!entrada) {
        cerr << "Error al abrir el archivo." << endl;
        exit(1);
    }

    random_device rd;
    mt19937 gen(rd()); // Generador de números aleatorios

    uniform_int_distribution<int> distN(3, 900); // Rango para N
    int N = distN(gen);

    uniform_int_distribution<int> distM(N/2, N*(N-1)/2); // Rango para M

    uniform_int_distribution<int> distInter(0, N-1); // Rango para intersecciones
    uniform_real_distribution<double> distProb(0.0001, 1.0); // Rango para probabilidades

    int M = distM(gen);
    int C = distInter(gen);
    int A = distInter(gen);
    int B = distInter(gen);

    

    // Escribir la primera línea con N, M, C, A y B
    entrada << N << " " << M << " " << C << " " << A << " " << B << endl;

    // Generar M carreteras aleatorias
    for (int i = 0; i < M; ++i) {

        Carretera c;
        c.u = distInter(gen);
        c.v = distInter(gen);
        c.tuv = distInter(gen) % 100 + 1; // Tiempo aleatorio entre 1 y 100 minutos
        c.puv = distProb(gen); // Probabilidad aleatoria entre 0 y 1
        c.pvu = 1 - c.puv;

        entrada << c.u << " " << c.v << " " << c.tuv << " " << c.puv << " " << c.pvu << endl;
    }

    entrada.close(); // Cerrar el archivo

    cout << "Archivo generado exitosamente." << endl;
}
