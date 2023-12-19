#pragma once

#include <vector>
#include "entregarPaquete.h"
#include "interseccion.h"
#include "carretera.h"

using namespace std;


#define N_BOOTSTRAPS 500



/* 
 * Precondición:    
 * Postcondición:   Realiza N_BOOTSTRAPS bootstraps, obteniendo un intervalo de confianza
 *                  donde el limite inferior se almacena en L y el superior en R.
 *                  Las N_BOOTSTRAPS se realizan para el almacen <I_almacen>.
 *                  
 */
void realizar_bootstraps(const vector<Carretera>& carreteras, const vector<Interseccion>& intersecciones,int IC,
                         int I_almacen,int n,float& L,float& R,const int limiteTiempo);












