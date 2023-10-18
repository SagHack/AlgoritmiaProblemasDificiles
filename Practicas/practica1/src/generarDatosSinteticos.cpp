#include <vector>
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <random>

using namespace std;

#define NUM_CASOS_PRUEBA 6
#define CASO_ALEATORIOS_PEQUENOS 1
#define CASO_ALEATORIOS_GRANDES 2
#define CASO_ORDENADO_ASC 3
#define CASO_ORDENADO_DESC 4
#define CASO_PARC_ORDENADO 5
#define CASO_REPETIDOS 6


#define MAX_RANGO 1000032767
#define MIN_RANGO 1000000000


#define MAX_N 32769


/* 
 * Precondición:    
 * Postcondición:   se genera un fichero de nombre nombreArchivo que contiene los 
 *                  elementos de v separados por espacios.
 */
void escribirVectorEnArchivo(const vector<int>& v, const string& nombreArchivo) {
    ofstream archivo(nombreArchivo);

    if (archivo.is_open()) {
        int n = v.size();
        for (int i = 0; i < n; i++) {
            archivo << v[i];
            if (i < n-1) {
                archivo << " ";
            }
        }
        archivo.close();
    } else {
        cerr << "No se pudo abrir el archivo para escritura." << endl;
    }
}


/**********************************************************************************/
// Casos de prueba

//                          CASO 1 O DEFAULT
/* 
 * Precondición:    
 * Postcondición:   v pasa a ser un vector donde v[i] <= 32767 con 0 <= i < n.
 */
void generarCaso_NumerosAleatoriosPequenos(vector<int>& v,int n) {
    srand(time(NULL));
    int random;
    for (int i = 0; i < n; i++) {
        random = rand();
        v.push_back(random);
    }

}

//                          CASO 2
/* 
 * Precondición:    
 * Postcondición:   v pasa a ser un vector donde 1000000000 <= v[i] <= 1000032767 con 0 <= i < n.
 */
void generarCaso_NumerosAleatoriosGrandes(vector<int>& v,int n) {
    v.clear();
    srand(time(NULL));
    int random;
    for (int i = 0; i < n; i++) {
        random = MIN_RANGO + rand();
        v.push_back(random);
    }

}

//                          CASO 3
/* 
 * Precondición:    
 * Postcondición:   v pasa a ser un vector donde v[i] == i con 0 <= i < n.
 */
void generarCaso_OrdenadoAscendentemente(vector<int>& v, int n){
    v.clear();
    for (int i = 0; i < n; i++) {
        v.push_back(i);
    }
}

//                          CASO 4
/* 
 * Precondición:    
 * Postcondición:   v pasa a ser un vector donde v[i] == n-i-1 con 0 <= i < n.
 */
void generarCaso_OrdenadoDescendentemente(vector<int>& v, int n){
    v.clear();
    for (int i = n-1; i >= 0; i--) {
        v.push_back(i);
    }
}


//                          CASO 5
/* 
 * Precondición:    
 * Postcondición:   v pasa a ser un vector donde n_desordenados es el número de elementos
 *                  que están descolocados de la que sería su posición real.
 */
void generarCaso_ParcialmenteOrdenado(vector<int>& v,int n,int n_desordenados) {
    v.clear();
    for (int i = 1; i <= n; i++) {
        v.push_back(i);
    }

    // Introducir algunos elementos desordenados
    srand(time(nullptr));
    for (int i = 0; i < n_desordenados/2; i++) {
        int indice1 = rand() % n;
        int indice2 = rand() % n;
        swap(v[indice1], v[indice2]);
    }
}

//                          CASO 6
/* 
 * Precondición:    
 * Postcondición:   v pasa a ser un vector donde n_repetidos es el número de elementos
 *                  que están repetidos.
 */
void generarCaso_DatosRepetidos(vector<int>& v,int n, int n_repetidos) {
    v.clear(); 
    if(n_repetidos==n){
        for (int i = 0; i < n_repetidos; i++) {
            v.push_back(1);
        }

    }
    else{
        generarCaso_NumerosAleatoriosPequenos(v,n);
        // Introducir algunos elementos repetidos
        for (int i = 0; i < n_repetidos; i++) {
            int indice1 = rand() % n;
            int indice2 = rand() % n;
            v[indice2] = v[indice1];
        }
    }
    
}


int main(int argc, char* argv[]){
    
    if(argc == 2){
        int caso = stoi(argv[1]);
        vector<int> v;
        int ordenados[] = {10,20,50}; 
        int repetidos[] = {10,20,50,100};
        switch(caso){
            case CASO_ALEATORIOS_PEQUENOS:
                for(int i = 2; i < MAX_N; i*=2){
                    generarCaso_NumerosAleatoriosPequenos(v,i);
                    escribirVectorEnArchivo(v,"AleatoriosPequenos_" + to_string(i) + ".txt");
                }
                break;
            case CASO_ALEATORIOS_GRANDES:
                for(int i = 2; i < MAX_N; i*=2){
                    generarCaso_NumerosAleatoriosGrandes(v,i);
                    escribirVectorEnArchivo(v,"AleatoriosGrandes_" + to_string(i) + ".txt");
                }
                break;
            case CASO_ORDENADO_ASC:
                for(int i = 2; i < MAX_N; i*=2){
                    generarCaso_OrdenadoAscendentemente(v,i);
                    escribirVectorEnArchivo(v,"OrdenadoAsc_" + to_string(i) + ".txt");
                }
                break;
            case CASO_ORDENADO_DESC:
                for(int i = 2; i < MAX_N; i*=2){
                    generarCaso_OrdenadoDescendentemente(v,i);
                    escribirVectorEnArchivo(v,"OrdenadoDesc_" + to_string(i) + ".txt");
                }
                break;
            case CASO_PARC_ORDENADO:
                
                for(int j = 0; j < 3; j++){
                    int o = ordenados[j];
                    for(int i = 2; i < MAX_N; i*=2){
                        int nDesordenados = (int32_t) (((int64_t) i)*o/100);
                        generarCaso_ParcialmenteOrdenado(v,i,nDesordenados);
                        escribirVectorEnArchivo(v,"ParcOrdenado_" + to_string(o) + "%_" + to_string(i) + ".txt");
                    }
                }
                break;
            case CASO_REPETIDOS:
                for(int j = 0; j < 4; j++){
                    int r = repetidos[j];
                    for(int i = 2; i < MAX_N; i*=2){
                        int nRepetidos = (int32_t) (((int64_t) i)*r/100);
                        generarCaso_DatosRepetidos(v,i,nRepetidos);
                        escribirVectorEnArchivo(v,"Repetidos_" + to_string(r) + "%_" + to_string(i) + ".txt");
                    }
                }

                break;
            default:
                cerr << "Ejecución incorrecta\n";
                break;
        }
    }
    else{
        cerr << "Ejecución incorrecta\n";
        return -1;
    }

}



