#include "radixsort.hpp"
#include "mergesort.hpp"
#include "quicksort.hpp"
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <random>
#include <chrono>
#include <iomanip>

#define NUM_CASOS_PRUEBA 7
#define CASO_ALEATORIOS_PEQUENOS 1
#define CASO_ALEATORIOS_GRANDES 2
#define CASO_ORDENADO_ASC 3
#define CASO_ORDENADO_DESC 4
#define CASO_PARC_ORDENADO 5
#define CASO_REPETIDOS 6
#define CASO_BOOKS 7

using namespace std;

// Overload the << operator for vector<int>
ostream& operator<<(ostream& os, const vector<int>& v) {
    for (int i = 0; i < v.size(); ++i) {
        os << v[i] << " ";
    }
    return os;
}

// Overload the << operator for vector<string>
ostream& operator<<(ostream& os, const vector<string>& v) {
    for (int i = 0; i < v.size(); ++i) {
        os << v[i] << " ";
    }
    return os;
}

void escribirVectorEnArchivo(const vector<int>& vector, const string& nombreArchivo) {
    ofstream archivo(nombreArchivo);

    if (archivo.is_open()) {
        for (int i = 0; i < vector.size(); i++) {
            archivo << vector[i];
            if (i < vector.size() - 1) {
                archivo << " ";
            }
        }
        archivo.close();
    } else {
        cerr << "No se pudo abrir el archivo para escritura." << endl;
    }
}



void leerNumerosDeArchivo(const string& nombreArchivo,vector<int>& numeros) {
    ifstream archivo(nombreArchivo);   
    if (!archivo.is_open()) {
        cerr << "Error: No se pudo abrir el archivo." << endl;
        return;
    }

    int numero;
    while (archivo >> numero) {
        numeros.push_back(numero);
    }
    archivo.close();
}

bool areEqual(const vector<int>& v_radixsort,const vector<int>& v_quicksort,const vector<int>& v_mergesort){
    bool areEqual = (v_radixsort == v_mergesort && v_radixsort == v_quicksort);
    if (!areEqual){
        if (v_radixsort == v_mergesort) {
            cout << "v_radixsort and v_mergesort are equal, but v_quicksort is different." << endl;
        } else if (v_radixsort == v_quicksort) {
            cout << "v_radixsort and v_quicksort are equal, but v_mergesort is different." << endl;
        } else if (v_mergesort == v_quicksort) {
            cout << "v_mergesort and v_quicksort are equal, but v_radixsort is different." << endl;
        } else {
            cout << "All three vectors are different." << endl;
        }
    }
    return areEqual;
}

void leerCSV(const string& archivoCSV, int columna_a_leer, vector<string>& v) {
    ifstream archivo(archivoCSV);
    
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo CSV." << std::endl;
        return;
    }

    string linea;
    bool skipFirstLine = true; // Add this flag to skip the first line
    while (getline(archivo, linea)) {
        if (skipFirstLine) {
            skipFirstLine = false; // Set the flag to false after skipping the first line
            continue;
        }

        stringstream ss(linea);
        string token;
        int columna = 1;

        while (std::getline(ss, token, ';')) { // Adjust the delimiter according to your CSV format
            if (columna == columna_a_leer) {
                v.push_back(token);
            }
            columna++;
        }
    }

    archivo.close();
}



void elegirCasoPrueba(int casoPrueba){
    vector<int> v, v_radixsort, v_quicksort, v_mergesort;
    vector<string> v_libros;
    switch(casoPrueba){
        case CASO_ALEATORIOS_PEQUENOS:
            leerNumerosDeArchivo("aleatoriosPequenos.txt", v);
            break;
        case CASO_ALEATORIOS_GRANDES:
            leerNumerosDeArchivo("aleatoriosGrandes.txt", v);
            break;
        case CASO_ORDENADO_ASC:
            leerNumerosDeArchivo("ordenadoAsc.txt", v);
            break;
        case CASO_ORDENADO_DESC:
            leerNumerosDeArchivo("ordenadoDesc.txt", v);
            break;
        case CASO_PARC_ORDENADO:
            leerNumerosDeArchivo("parcOrdenado.txt", v);
            break;
        case CASO_REPETIDOS:
            leerNumerosDeArchivo("repetidos.txt", v);
            break;
        case CASO_BOOKS:
            leerCSV("books.csv",3,v_libros);
            break;
        default:
            cerr << "Ejecución incorrecta.\nEjecución correcta: ./pruebas <num_prueba> siendo num_prueba un número entre 1 y " + to_string(NUM_CASOS_PRUEBA) + "\n";
            exit(-1);
            break;
    }

    if(casoPrueba < CASO_BOOKS){
        auto start = chrono::high_resolution_clock::now();
        radixsort(v_radixsort);
        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
        cout << "Radixsort: " << to_string(duration.count()) << " milisegundos" << endl;
        start = chrono::high_resolution_clock::now();  
        quicksort(v_quicksort);
        stop = chrono::high_resolution_clock::now();
        duration = chrono::duration_cast<chrono::microseconds>(stop - start);
        cout << "Quicksort: " << to_string(duration.count()) << " milisegundos" << endl;

        start = chrono::high_resolution_clock::now();
        mergesort(v_mergesort);
        stop = chrono::high_resolution_clock::now();
        duration = chrono::duration_cast<chrono::microseconds>(stop - start);
        cout << "Mergesort: " << to_string(duration.count()) << " milisegundos" << endl;
    }else if(casoPrueba == CASO_BOOKS){
        auto start = chrono::high_resolution_clock::now();  
        radixsort(v_libros);
        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
        cout << "Radixsort con strings: " << to_string(duration.count()) << " milisegundos" << endl;
    }

}


int main(int argc, char* argv[]) {

    int prueba;
    if(argc == 2){
        prueba = stoi(argv[1]);
        elegirCasoPrueba(prueba);
    }
    else{
        cerr << "Ejecución incorrecta.\nEjecución correcta: ./pruebas <num_prueba> siendo num_prueba un número entre 1 y " + to_string(NUM_CASOS_PRUEBA) + "\n";
        exit(-1);
    }


}