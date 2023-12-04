/*
 * Fichero:   		entregarPaquete.h
 * Autores: 		Diego García Aranda 820506
                    Simón Alonso Gutiérrez 821038
 * Fecha entrega:	22/12/2023
 * Comentarios:     Fichero que define y especifica la función que resuelve el problema de la entrega de paquetes.
 *                  Perteneciente a la práctica 3 de la asignatura Algoritmia para problemas difíciles.
 */

#pragma once

#include <iostream>
#include <fstream>
#include <random>
#include "carretera.h"
#include "interseccion.h"
using namespace std;



/* 
 * Precondición:    
 * Postcondición:   devuelve aleatoriamente la carretera por la que salir de la intersección i o -1 si la 
 *                  intersección i no tiene ninguna carretera de salida.
 */
int carreteraSalida(const Interseccion& i);

/* 
 * Precondición:    0 <= IA,IC < |intersecciones|
 * Postcondición:   devuelve el tiempo en minutos que ha costado realizar la entrega del paquete desde la 
 *                  intersección IA hasta la intersección IC en el mapa representado por carreteras e 
 *                  intersecciones o -1 si la entrega no se ha realizado antes del límite de tiempo.
 */
int entregarPaquete(const vector<Carretera>& carreteras, const vector<Interseccion>& intersecciones, int IC, int IA);