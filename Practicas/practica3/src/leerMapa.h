#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cassert>
#include "carretera.h"
#include "interseccion.h"

using namespace std;

#define MAX_INTERSECCIONES 900
#define MIN_INTERSECCIONES 3


/* 
 * Precondición:    
 * Postcondición:   devuelve MIN_INTERSECCIONES <= N <= MAX_INTERSECCIONES
 */
bool comprobar_numero_intersecciones(int N);

/* 
 * Precondición:    
 * Postcondición:   devuelve N/2 <= M <= N*(N-1)/2
 */
bool comprobar_numero_carreteras(int N, int M);

/* 
 * Precondición:    
 * Postcondición:   devuelve 0 <= I < N
 */
bool comprobar_interseccion(int I, int N);

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