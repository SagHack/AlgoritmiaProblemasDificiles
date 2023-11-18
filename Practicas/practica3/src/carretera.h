/*
 * Fichero:   		carretera.h
 * Autores: 		Diego García Aranda 820506
                    Simón Alonso Gutiérrez 821038
 * Fecha entrega:	22/12/2023
 * Comentarios:     Fichero que define y especifica la estructura de datos que representa una carretera en un mapa
 *                  que conecta dos intersecciones y cuesta un tiempo recorrerla.
 *                  Perteneciente a la práctica 3 de la asignatura Algoritmia para problemas difíciles.
 */


/*
 * Estructura de datos que representa una carretera:
 *      u,v son las intersecciones que conecta la carretera
 *      tuv es el tiempo en minutos que cuesta recorrer la carretera
 */
struct Carretera {
    int u, v, tuv;
};


