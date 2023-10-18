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



#define MAX_N 32768


/* 
 * Precondición:    
 * Postcondición:   se genera un fichero de nombre nombreArchivo que contiene los 
 *                  elementos de v separados por espacios.
 */
void escribirVectorEnArchivo(const vector<int>& v, const string& nombreArchivo) {
    ofstream archivo(nombreArchivo);

    if (archivo.is_open()) {
        int size = vector.size();
        for (int i = 0; i < n; i++) {
            archivo << vector[i];
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
 * Postcondición:   v pasa a ser un vector donde v[i] <= 32767 con 0 <= i < n.
 */
void generarCaso_NumerosAleatoriosGrandes(vector<int>& v,int n,int maxRango) {
    random_device rd;
    mt19937 gen(rd()); // Mersenne Twister es un generador de números aleatorios común
    uniform_int_distribution<int32_t> dis(INT32_MIN, INT32_MAX);
    for (int i = 0; i < n; i++) {
        // Generar un número decimal aleatorio en el rango [0, 1]
        int random_decimal = gen();
        v.push_back(random_decimal);
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
 *                  que están duplicados.
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
    generarCasoNumerosAleatoriosPequenos(n,v);

    // Introducir algunos elementos repetidos
    for (int i = 0; i < n_repetidos; i++) {
        int indice1 = rand() % n;
        int indice2 = rand() % n;
        v[indice2] = v[indice1];
    }
}


int main(int argc, char* argv[]){
    
    if(argc == 1){
        int caso = argv[1];
        vector<int> v;
        switch(caso){
            case CASO_ALEATORIOS_PEQUENOS:
                for(int i = 0; i < MAX_N; i*=2){
                    generarCaso_NumerosAleatoriosPequenos(v,n);
                    escribirVectorEnArchivo(v,"AleatoriosPequenos_" + to_string(n) + ".txt");
                }
                break;
            case CASO_ALEATORIOS_GRANDES:
                for(int i = 0; i < MAX_N; i*=2){
                    generarCaso_NumerosAleatoriosGrandes(v);
                    escribirVectorEnArchivo(v,"AleatoriosGrandes_" + to_string(n) + ".txt");
                }
                break;
            case CASO_ORDENADO_ASC:
                for(int i = 0; i < MAX_N; =i*=2){
                    generarCaso_OrdenadoAscendentemente(v);
                    escribirVectorEnArchivo(v,"OrdenadoAsc_" + to_string(n) + ".txt");
                }
                break;
            case CASO_ORDENADO_DESC:
                for(int i = 0; i < MAX_N; i*=2){
                    generarCaso_OrdenadoAscendentemente(v,n);
                    escribirVectorEnArchivo(v,"OrdenadoDesc_" + to_string(n) + ".txt");
                }
                break;
            case CASO_PARC_ORDENADO:
                int ordenados[3] = {10,20,50}
                for(int j = 0; i < 3; j++){
                    int o = ordenados[j];
                    for(int i = 0; i < MAX_N; i*=2){
                        int nDesordenados = (int32_t) (((int64_t) n)*o/100);
                        generarCaso_OrdenadoAscendentemente(v,n,nDesordenados);
                        escribirVectorEnArchivo(v,"ParcOrdenado_" + to_string(nDesordenados) + "%_" + to_string(n) + ".txt");
                    }
                }
                break;
            case CASO_REPETIDOS:
                int repetidos[4] = {10,20,50,100}
                for(int j = 0; i < 4; j++){
                    int r = repetidos[j];
                    for(int i = 0; i < MAX_N; i*=2){
                        int nRepetidos = (int32_t) (((int64_t) n)*r/100);
                        generarCaso_OrdenadoAscendentemente(v,n,nRepetidos);
                        escribirVectorEnArchivo(v,"Repetidos_" + to_string(nRepetidos) + "%_" + to_string(n) + ".txt");
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




