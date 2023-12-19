#include "bootstraps.h"
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <algorithm>
#include <random>
#include <iostream>

/* 
 * Precondición:    El vector de tiempos no debe estar vacio 
 * Postcondición:   Devuelve el promedio de los tiempo del vector.
 *                  
 */
float calcularMedia(const vector<int>& tiempos){
    float total_tiempos = 0.0;
    int n = tiempos.size();
    for(float tiempo: tiempos){
        total_tiempos += tiempo;
    }
    return (n > 0) ? (total_tiempos / n) : 0.0;
}


/* 
 * Precondición:    
 * Postcondición:   Realiza la tecnica de bootstrap, devolviendo la media 
 *                  de los n tiempos pasados, pero elegidos al azar y con reemplazo.
 *                  
 */


float bootstrap(const vector<int> tiempos){
    int n = tiempos.size();
    vector<int> tiempos_aleatorios;
    int indice_aleatorio = 0;
    for(int i=0;i<n;i++){
        indice_aleatorio = rand() % n; // [0,n-1]
        tiempos_aleatorios.push_back(tiempos[indice_aleatorio]);
    }

    return calcularMedia(tiempos_aleatorios);
}


/* 
 * Precondición:    
 * Postcondición:   Realiza N_BOOTSTRAPS bootstraps, obteniendo un intervalo de confianza
 *                  donde el limite inferior se almacena en L y el superior en R.
 *                  Las N_BOOTSTRAPS se realizan para el almacen <I_almacen>.
 *                  
 */
void realizar_bootstraps(const vector<Carretera>& carreteras, const vector<Interseccion>& intersecciones,
                         int IC, int I_almacen,int n,float& L,float& R, const int limiteTiempo){
    
    // Para hacer completamente aleatoria la secuencia, necesitamos utilizar
    // una semilla que cambie aunque las ejecuciones sean muy seguidas
    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    srand(static_cast<unsigned>(seed));  // Seed for rand()                       

    vector<int> tiempos; // Vector con los n tiempos de realizar las n simulaciones
    vector<float> medias_bootstraps; // Vector con las medias de cada bootstrap
    float media_tiempos,tiempo;

    // Realizamos las n simulaciones y guardamos el tiempo de cada una
    for(int i=0;i<n;i++){
        tiempo = entregarPaquete(carreteras,intersecciones,IC,I_almacen,limiteTiempo);
        tiempos.push_back(tiempo);
    }

    // Media real de las n simulaciones
    media_tiempos = calcularMedia(tiempos);

    // Obtiene la media de las N_BOOTSTRAPS
    for(int i=0;i<N_BOOTSTRAPS;i++){
        medias_bootstraps.push_back(bootstrap(tiempos));
    }

    //Ordenamos las medias de menor a mayor
    sort(medias_bootstraps.begin(), medias_bootstraps.end());

    L = 2 * media_tiempos - (medias_bootstraps[475] + medias_bootstraps[476]) / 2;
    R = 2 * media_tiempos - (medias_bootstraps[25] + medias_bootstraps[26]) / 2;
}











