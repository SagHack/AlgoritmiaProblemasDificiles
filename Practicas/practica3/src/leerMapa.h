/*
 * Fichero:   		leerMapa.h
 * Autores: 		Diego García Aranda 820506
                    Simón Alonso Gutiérrez 821038
 * Fecha entrega:	22/12/2023
 * Comentarios:     Fichero que define y especifica la función que lee la entrada del problema de la entrega de paquetes.
 *                  Perteneciente a la práctica 3 de la asignatura Algoritmia para problemas difíciles.
 */
#pragma once

#include <vector>
#include "carretera.h"
#include "interseccion.h"

using namespace std;

#define MAX_INTERSECCIONES 900
#define MIN_INTERSECCIONES 3

/* 
 * Precondición:    
 * Postcondición:   Si el fichero <ficheroEntrada> tiene el formato correcto y cumple todas las condiciones devolverá True:
 *                  carreteras = Todas las carreteras
 *                  intersecciones = Todas las intersecciones 
 *                  C = Interseccion en la que vivo
 *                  A = Interseccion del primer almacen
 *                  B = Interseccion del segundo almacen
 *                  En caso de no tener el formato correcto, o no cumplir alguna de las condiciones devolverá False.
 */
bool leerMapa(const string ficheroEntrada, vector<Carretera>& carreteras,
              vector<Interseccion>& intersecciones, int& C, int& A, int& B);