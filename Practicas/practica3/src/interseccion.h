/*
 * Fichero:   		intersección.h
 * Autores: 		Diego García Aranda 820506
                    Simón Alonso Gutiérrez 821038
 * Fecha entrega:	22/12/2023
 * Comentarios:     Fichero que define y especifica la estructura de datos que representa una intersección en 
 *                  un mapa. Esta intersección tiene carreteras que la conectan con otras intersecciones y que
 *                  tienen una cierta probabilidad de salir por ella.
 *                  Perteneciente a la práctica 3 de la asignatura Algoritmia para problemas difíciles.
 */

#include <vector>

/*
 * Estructura de datos que representa una intersección:
 *      salidas son las carreteras que llegan/parten de la intersección
 *      limitesP almacenan los intervalos entre 0 y 1 que modelan la probabilidad 
 *      de coger una carretera de salida determinada. 
 *      Sea s una salida, el intervalo se obtiene por [ limitesP[s-1] , limitesP[s] )
 *      Para el caso de que s sea la primera componente, el intervalo se obtiene por
 *      [ 0 , limitesP[s] ).
 * 
 *      Restricciones limitesP:
 *          Para 0 <= i < |limitesP|-1, limitesP[i] < limitesP[i+1].
 *          limitesP[0] > 0
 *          limitesP[|limitesP|-1] == 1
 *
 */
struct Interseccion{
    vector<int> salidas;
    vector<double> limitesP;
    //Interseccion() : salidas(), limitesP(){}
};