#include <vector>
/*
 * Estructura de datos que representa una intersección:
 *      salidas son las carreteras que llegan/parten de la intersección
 *      limitesP almacenan los intervalo entre 0 y 1 que modela la probabilidad 
 *      de coger una salida determinada.
 *      Sea s una salida, el intervalo se obtiene por [ limitesP[s-1] , limitesP[s] )
 *      Para el caso de que s sea la primera componente, el intervalo se obtiene por
 *      [ 0 , limitesP[s] ).
 */
struct Interseccion{
    vector<int> salidas;
    vector<double> limitesP;
    //Interseccion() : salidas(), limitesP(){}
};