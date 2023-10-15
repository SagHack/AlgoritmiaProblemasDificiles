#include "radixsort.cpp"
#include "mergesort.cpp"
#include "quicksort.cpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <random>
#include <chrono>
#include <iomanip>

using namespace std;

const int MAX_RANGO = 2147483647;

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


void generarCasoNumerosAleatoriosGrandes(int maxRango,int n,vector<int>& v) {

    // mt19937_64 gen (random_device{}());
    // int numero;
    // for (int i = 0; i < n; i++) {
    //     numero = gen() % MAX_RANGO;
    //     v.push_back(numero);
    // }
    

    random_device rd;
    mt19937 gen(rd()); // Mersenne Twister es un generador de números aleatorios común
    uniform_int_distribution<int32_t> dis(INT32_MIN, INT32_MAX);

    for (int i = 0; i < n; i++) {
        // Generar un número decimal aleatorio en el rango [0, 1]
        int random_decimal = gen();
        v.push_back(random_decimal);
    }

}

void generarCasoNumerosAleatoriosPequenos(int n,vector<int>& v) {

    srand(time(NULL));
    int random;
    for (int i = 0; i < n; i++) {
        random = rand();
        v.push_back(random);
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


void generarCasoInversamenteOrdenado(int n,vector<int>& v){
    v.clear();
    for(int i = n-1;i>=0;i--){
        v.push_back(i);
    }
}

void generarCasoCasiOrdenado(int n,int n_desordenados, vector<int>& v) {
    v.clear();
    // Llenar el vector con números en orden ascendente
    for (int i = 1; i <= n; i++) {
        v.push_back(i);
    }

    // Introducir algunos elementos desordenados
    srand(time(nullptr));
    for (int i = 0; i < n_desordenados; i++) {
        int indice1 = rand() % n;
        int indice2 = rand() % n;
        swap(v[indice1], v[indice2]);
    }
}


void generarCasoDatosRepetidos(int n, int n_repetidos,vector<int>& v) {
    v.clear(); 

    generarCasoNumerosAleatoriosPequenos(n,v);

    // Introducir algunos elementos repetidos
    for (int i = 0; i < n_repetidos; i++) {
        int indice1 = rand() % n;
        int indice2 = rand() % n;
        v[indice2] = v[indice1];
    }
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


void leerCSV(string archivoCSV, int columna_a_leer, vector<string>& v) {
    ifstream archivo(archivoCSV);

    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo CSV." << endl;
        return;
    }

    string linea;

    // Ignoramos la primera línea que contiene los encabezados
    getline(archivo, linea);

    while (getline(archivo, linea)) {
        string token;
        size_t pos = 0;
        int columna = 1;

        while ((pos = linea.find(';')) != string::npos) {
            token = linea.substr(0, pos);
            
            if (columna == columna_a_leer) {
                v.push_back(token);
            }

            linea.erase(0, pos + 1);
            columna++;
        }
        
        if (columna == columna_a_leer) {
            v.push_back(linea);
        }
    }

    archivo.close();
}



void generarFicheros(int n,int n_repetidos,int n_desordenados){
    vector<int> v;
    generarCasoNumerosAleatoriosPequenos(n,v);
    escribirVectorEnArchivo(v,"aleatorios.txt");
    generarCasoInversamenteOrdenado(n,v);
    escribirVectorEnArchivo(v,"inversamenteOrdenados.txt");
    generarCasoCasiOrdenado(n,n_desordenados,v);
    escribirVectorEnArchivo(v,"casiOrdenado.txt");
    generarCasoDatosRepetidos(n,n_repetidos,v);
    escribirVectorEnArchivo(v,"datosRepetidos.txt");
}

void casosPrueba(ofstream& f,string nombreFichero,int N,int n_repetidos,int n_desordenados){
    f << "Caso de prueba con " << nombreFichero << ". N=" << N <<", N_repetidos=" << n_repetidos << ", N_desordenados=" << n_desordenados <<endl; 
    vector<int> v, v_radixsort, v_quicksort, v_mergesort;
    string r="radixsort: ",q="quicksort: ",m="mergesort: ";
    for (int n = 2; n <= N; n *= 2) {
        generarFicheros(n, n_repetidos, n_desordenados);
        leerNumerosDeArchivo(nombreFichero, v);
        v_radixsort = v;
        v_quicksort = v;
        v_mergesort = v;
        
        auto start = chrono::high_resolution_clock::now();
        radixsort(v_radixsort);
        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
        r += "(" + to_string(n) + "," + to_string(duration.count()) + "),";


        start = chrono::high_resolution_clock::now();  
        quicksort(v_quicksort);
        stop = chrono::high_resolution_clock::now();
        duration = chrono::duration_cast<chrono::microseconds>(stop - start);
        q += "(" + to_string(n) + "," + to_string(duration.count()) + "),";
        start = chrono::high_resolution_clock::now();
        mergesort(v_mergesort);
        stop = chrono::high_resolution_clock::now();
        duration = chrono::duration_cast<chrono::microseconds>(stop - start);
        m += "(" + to_string(n) + "," + to_string(duration.count()) + "),";
        if (!areEqual(v_radixsort, v_quicksort, v_mergesort)) {
            exit(-1);
        }
    }
    f << r << endl;
    f << q << endl;
    f << m << endl;
    f << endl;
}






//books.csv esta ya preprocesado, no hay espacios en blanco ni celdas raras
//TODO: cuando leamos del ficheor books.csv como sabemos que hay repetidos, podemos justificar cual de los algoritmos
// funciona mejor para este caso
int main(int argc, char* argv[]) {

    // if(argc == 1){

    //     int prueba = stoi(argv[1]);

    //     string fichero = "";
    //     switch(prueba){
    //         case 0:

    //     }

    // }
    // else{
    //     cerr << "Error en la ejecución del programa: faltan argumentos.\n\tEjemplo ejecución: pruebaAlgoritmos <numPrueba> siendo numPrueba número entre 0 y 9\n";
    //     return -1;
    // }


    ofstream f("resultados.txt");
    string fichAleatorios = "aleatorios.txt";
    string fichCasiOrdenados = "casiOrdenado.txt";
    string fichDatosRepetidos = "datosRepetidos.txt";
    string fichInversamenteOrdneado = "inversamenteOrdenados.txt";
    int max_n = 32768;
    int iter = 1;
    string cost_time = "";
    if (f.is_open()) {

        for (int n = 2; n <= max_n; n *= 2) {
            cost_time += "(" + to_string(n) + "," + to_string(n*log(n)) + "),";
        }
        f << "n log n: " << cost_time << endl;

        cost_time = "";
        for (int n = 2; n <= max_n; n *= 2) {
            cost_time += "(" + to_string(n) + "," + to_string(n*n) + "),";
        }
        f << "n^2: " << cost_time << endl;

        cout << "HOLA" << endl;
        casosPrueba(f,fichAleatorios,max_n,0,0);
        cout << "HOLA" << endl;
        casosPrueba(f,fichCasiOrdenados,max_n,0,max_n/10);
        cout << "HOLA" << endl;
        casosPrueba(f,fichCasiOrdenados,max_n,0,max_n/5);
        cout << "HOLA" << endl;
        casosPrueba(f,fichCasiOrdenados,max_n,0,max_n/2);
        cout << "HOLA" << endl;
        casosPrueba(f,fichDatosRepetidos,max_n,max_n/10,0);
        cout << "HOLA" << endl;
        casosPrueba(f,fichDatosRepetidos,max_n,max_n/5,0);
        cout << "HOLA" << endl;
        casosPrueba(f,fichDatosRepetidos,max_n,max_n/2,0);
        cout << "HOLA" << endl;
        casosPrueba(f,fichInversamenteOrdneado,max_n,0,0);
        cout << "HOLA" << endl;
        f.close();
    }else{
        cerr << "No se pudo abrir el archivo para escritura." << endl;
    }

    return 0;
}
