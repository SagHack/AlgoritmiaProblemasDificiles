#include "radixsort.cpp"
#include "mergesort.cpp"
#include "quicksort.cpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <random>
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


void generarCasoNumerosAleatorios(int maxRango,int n,vector<int>& v) {

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

    generarCasoNumerosAleatorios(MAX_RANGO,n,v);

    // Introducir algunos elementos repetidos
    for (int i = 0; i < n_repetidos; i++) {
        int indice1 = rand() % n;
        int indice2 = rand() % n;
        v[indice2] = v[indice1];
    }
}



void areEqual(const vector<int>& v_radixsort,const vector<int>& v_quicksort,const vector<int>& v_mergesort){
    bool areEqual = (v_radixsort == v_mergesort && v_radixsort == v_quicksort);
    if (areEqual) {
        cout << "All three vectors are equal." << endl;
    } else {
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
}


// void leerCSV(string archivoCSV, vector<string>& v) {
//     ifstream archivo(archivoCSV);

//     if (!archivo.is_open()) {
//         cerr << "No se pudo abrir el archivo CSV." << endl;
//         return;
//     }

//     string linea;

//     // Ignoramos la primera línea que contiene los encabezados
//     getline(archivo, linea);

//     while (getline(archivo, linea)) {
//         istringstream ss(linea);
//         string token;

//         // Usamos ';' como delimitador para separar las columnas
//         int columna = 1;
//         while (getline(ss, token, ';')) {
//             if (columna == 3) {  // La tercera columna contiene el ISBN
//                 v.push_back(token);
//             }
//             columna++;
//         }
//     }

//     archivo.close();
// }



void generarFicheros(){
    vector<int> v;
    int n = 100000; //Cantidad de números a generar
    int n_repetidos = n/10; //Cantidad de números repetidos
    int n_desordenados = n/10; //Cantidad de números que van a estar desordenados
    generarCasoNumerosAleatorios(MAX_RANGO,n,v);
    escribirVectorEnArchivo(v,"aleatorios.txt");
    generarCasoInversamenteOrdenado(n,v);
    escribirVectorEnArchivo(v,"inversamenteOrdenados.txt");
    generarCasoCasiOrdenado(n,n_desordenados,v);
    escribirVectorEnArchivo(v,"casiOrdenado.txt");
    generarCasoDatosRepetidos(n,n_repetidos,v);
    escribirVectorEnArchivo(v,"datosRepetidos.txt");

}


//books.csv esta ya preprocesado, no hay espacios en blanco ni celdas raras
//TODO: cuando leamos del ficheor books.csv como sabemos que hay repetidos, podemos justificar cual de los algoritmos
// funciona mejor para este caso
int main() {
    int cantidadNumeros = 10;
    generarFicheros();
    vector<int> v,v_radixsort,v_quicksort,v_mergesort;
    leerNumerosDeArchivo("aleatorios.txt",v);
    v_radixsort = v;
    v_quicksort = v;
    v_mergesort = v;
    radixsort(v_radixsort);
    quicksort(v_quicksort);
    mergeSort(v_mergesort,0,v_mergesort.size()-1);
    // cout << "Radixsort: " << v_radixsort << endl;
    // cout << "Quicksort: " <<  v_quicksort << endl;
    // cout << "Mergesort: " <<  v_mergesort << endl;
    areEqual(v_radixsort,v_quicksort,v_mergesort);
    return 0;
}







// int main(){  
//     vector<int> v_desord_int_radixsort = {4, 822, 732, 40, 50, 6, 2, 1, 9, 73};
//     //TODO: El quicksort falla, si lo ejecutas muchas veces lo mismo da distintos resultados
//     vector<int> v_desord_int_quicksort = {4, 822, 732, 40, 50, 6, 2, 1, 9, 73};
//     vector<int> v_desord_int_mergesort = {4, 822, 732, 40, 50, 6, 2, 1, 9, 73};
    
//     radixsort(v_desord_int_radixsort);
//     cout << v_desord_int_radixsort << endl; 
//     quicksort(v_desord_int_quicksort);
//     cout << v_desord_int_quicksort << endl;

//     mergeSort(v_desord_int_mergesort,0,v_desord_int_mergesort.size()-1);
//     cout << v_desord_int_mergesort << endl;



//     // cout << "Ahora el que va con strings" << endl;

//     // vector<string> v_desord = {"32", "822", "732", "40", "50", "5", "2", "1", "9", "73"};
//     // radixsort(v_desord);
//     // cout << v_desord << endl;


    
// }