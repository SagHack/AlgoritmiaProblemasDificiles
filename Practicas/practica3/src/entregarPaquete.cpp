/*
 * Fichero:   		entregarPaquete.cpp
 * Autores: 		Diego García Aranda 820506
                    Simón Alonso Gutiérrez 821038
 * Fecha entrega:	22/12/2023
 * Comentarios:     Fichero que implementa la función que resuelve el problema de la entrega de paquetes.
 *                  Perteneciente a la práctica 3 de la asignatura Algoritmia para problemas difíciles.
 */
#include <iostream>
#include <fstream>
#include <random>
#include <chrono>

#include "entregarPaquete.h"
using namespace std;


/***********************************************************************************************************/
/*         Definición e implementación de función local usada en la función de entrega de paquetes         */

/* 
 * Precondición:    
 * Postcondición:   devuelve aleatoriamente la carretera por la que salir de la intersección i o -1 si la 
 *                  intersección i no tiene ninguna carretera de salida.
 */

int carreteraSalida(const Interseccion& i){
    // Elegimos un numero aleatorio
    float num_random = static_cast<float>(rand()) / RAND_MAX;
    int n = i.salidas.size();
    for(int x = 0; x < n; x++){
        double limite = i.limitesP[x];
        if(num_random <= limite){
            return i.salidas[x];
        }
    }
    return -1;
}

/***********************************************************************************************************/


/***********************************************************************************************************/
/*                     Definición e implementación de la función de entrega de paquetes                    */

/* 
 * Precondición:    0 <= IA,IC < |intersecciones|
 * Postcondición:   devuelve el tiempo en minutos que ha costado realizar la entrega del paquete desde la 
 *                  intersección IA hasta la intersección IC en el mapa representado por carreteras e 
 *                  intersecciones o -1 si la entrega no se ha realizado antes del límite de tiempo.
 */
int entregarPaquete(const vector<Carretera>& carreteras, const vector<Interseccion>& intersecciones, int IC, int IA){
    int tiempo = 0;
    int interseccionActual = IA;
    int n_intersecciones_visitadas = 0;
    
    // En caso de superar 2 * intersecciones, podemos decir que ha excedido el limite de tiempo
    int max_intersecciones = intersecciones.size() * 2; 

    // Mientras no supere el limite de tiempo, es decir, no visite más de 2 * intersecciones
    while(n_intersecciones_visitadas <= max_intersecciones ){
        //cout << "Visitando intersección: " << interseccionActual << endl;

        /* 
         * Si hemos llegado a la intersección donde vive el cliente, entregamos el paquete y devolvemos el
         * tiempo en minutos que nos ha costado realizar la entrega.
         */
        if(interseccionActual == IC) return tiempo;

        // Elegimos una carretera de salida de la intersección interseccionActual
        int cS = carreteraSalida(intersecciones[interseccionActual]);
        
        // Error: la intersección no tiene carretera de salida.
        if(cS == -1){
            cout << "ERROR: La interseccion no tiene carretera de salida" << endl;
            exit(1);
        }

        // Vamos a la intersección a la que se llega por la carretera cS.
        interseccionActual = (carreteras[cS].u == interseccionActual) ? carreteras[cS].v : carreteras[cS].u;
        n_intersecciones_visitadas++;

        // Sumamos el tiempo en minutos que nos ha costado recorrer la carretera.
        tiempo += carreteras[cS].tuv;
    }
    cout << "Intentamos entregar tu paquete, pero no estabas" << endl;
    // Si se ha superado el límite del tiempo de entrega, ha entrado en un bucle, devolver -1.
    return -1;

}

/***********************************************************************************************************/
