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
    random_device rd;
    mt19937 generador(rd());
    uniform_real_distribution<double> distribucion(0.0,1.0);
    double num_random = distribucion(generador);
    int n = i.salidas.size();
    for(int x = 0; x < n; x++){
        double limite = i.limitesP[x];
        if(num_random < limite){
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
int entregarPaquete(const vector<Carretera>& carreteras, const vector<Interseccion>& intersecciones, int IC, int IA, int limiteTiempo){
    int tiempo = 0;
    int interseccionActual = IA;

    // Mientras el tiempo en minutos que llevamos realizando la entrega no supere el límite de tiempo.
    while(tiempo <= limiteTiempo ){

        /* 
         * Si hemos llegado a la intersección donde vive el cliente, entregamos el paquete y devolvemos el
         * tiempo en minutos que nos ha costado realizar la entrega.
         */
        if(interseccionActual == IC) return true;

        // Elegimos una carretera de salida de la intersección interseccionActual
        int cS = carreteraSalida(intersecciones[interseccionActual]);

        
        // Error: la intersección no tiene carretera de salida.
        if(cS == -1){
            exit(1);
        }

        // Vamos a la intersección a la que se llega por la carretera cS.
        interseccionActual = (carreteras[cS].u == interseccionActual) ? carreteras[cS].v : carreteras[cS].u;

        // Sumamos el tiempo en minutos que nos ha costado recorrer la carretera.
        tiempo += carreteras[cS].tuv;
    }

    // Si se ha superado el límite del tiempo de entrega, devolver -1.
    return -1;

}

/***********************************************************************************************************/
