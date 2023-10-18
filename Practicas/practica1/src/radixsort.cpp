/*
 * Fichero:   		radixsort.cpp
 * Autores: 		Diego García Aranda 820506
                    Simón Alonso Gutiérrez 821038
 * Fecha entrega:	18/10/2023
 * Comentarios:     Fichero que implementan las funciones que componen las dos funciones 
 *                  que ordenan vectores de números mediante el algoritmo de ordenación
 *                  radixsort. 
 *                  La primera de las funciones de ordenación radixsort es usada para números 
 *                  representables en formato entero y la segunda es para número no representables 
 *                  en formato entero, por lo que se utilizan strings para representar 
 *                  los números.
 */

#include "radixsort.hpp"
#include <cmath>
using namespace std;

/****************************************************************************************************/
/* Predefinición de funciones locales usadas en el algoritmo de ordenación radixsort implementado   */


/*
 * Precondición:    el número de elementos de v tiene que ser mayor que 0.
 * Postcondición:   devuelve el máximo de los números del vector.
 */
int obtenerNumeroMaximo(vector<int> v);

/* 
 * Precondición:    el número de elementos de v tiene que ser mayor que 0.
 * Postcondición:   devuelve la longitud máxima de las cadenas del vector.
 */
int obtenerLongitudMaxima(vector<string> v);

/* 
 * Precondición:    el número de elementos de v tiene que ser mayor que 0.
 * Postcondición:   ordena el vector v de forma ascendente según el valor de una 
 *                  cifra de los números del vector.
 *                  La cifra con la que ordenar en la iteración es igual al 
 *                  logaritmo en base 10 de exp.
 */
void iteracionRadixsort(vector<int>& v, int exp);

/* 
 * Precondición:    el número de elementos de v tiene que ser mayor que 0 y los 
 *                  elementos del vector v son cadenas que representan
 *                  números en formato entero.
 * Postcondición:   ordena el vector v de forma ascendente según el valor de la 
 *                  cifra de los números del vector.
 */
void iteracionRadixsort(vector<string>& v, int cifra);

/* 
 * Precondición:    
 * Postcondición:   almacena en neg los números negativos de original y en pos los 
 *                  números positivos de original. Tanto en neg como en pos los números 
 *                  se almacenan como positivos.
 */
void separarNegativosPositivos(const vector<int>& original, vector<int>& neg, vector<int>& pos);

/* 
 * Precondición:    los elementos de original son cadenas que representan
 *                  números en formato entero.
 * Postcondición:   almacena en neg los números negativos de original y en pos los 
 *                  números positivos de original. Tanto en neg como en pos los números 
 *                  se almacenan como positivos.
 */
void separarNegativosPositivos(const vector<string>& original, vector<string>& neg, vector<string>& pos);


/****************************************************************************************************/


/****************************************************************************************************/
/*                Implementación de las funciones de ordenación según algoritmo radixsort           */


/* 
 * Precondición:    
 * Postcondición:   ordena el vector v de forma ascendente 
 *                  mediante el algoritmo de ordenación radixsort.
 */
void radixsort(vector<int>& v)
{
    vector<int> neg, pos;
    int n = v.size();
    if(n > 1){
        
        separarNegativosPositivos(v,neg,pos);

        if(pos.size() > 1){
            // Obtenemos el máximo de los números del vector de positivos.
            int max_pos = obtenerNumeroMaximo(pos);

            // Vamos realizando las iteraciones del algoritmo de ordenación radixsort.
            for (int exp = 1; max_pos / exp > 0; exp *= 10){
                iteracionRadixsort(pos, exp);
            }
        }

        if(neg.size() > 1){
            int max_neg = obtenerNumeroMaximo(neg);
            // Vamos realizando las iteraciones del algoritmo de ordenación radixsort.
            for (int exp = 1; max_neg / exp > 0; exp *= 10){
                iteracionRadixsort(neg, exp);
            }
        }


        // Juntamos los negativos y positivos 
        v.clear();
        for (int i = neg.size() - 1; i >= 0; i--) {
            v.push_back(-neg[i]);
        }
    
        for (int num : pos) {
            v.push_back(num);
        }

    }

    
        
}

/* 
 * Precondición:    los elementos de v son cadenas que representan
                    números en formato entero.
 * Postcondición:   ordena el vector v de forma ascendente 
 *                  mediante el algoritmo de ordenación radixsort.
 */
void radixsort(vector<string>& v)
{
    vector<string> neg, pos;
    int n = v.size();
    if(n > 1){
        
        separarNegativosPositivos(v,neg,pos);

        if(pos.size() > 1){
            // Obtenemos el máximo de cifras de los números del vector de positivos.
            int max_pos = obtenerLongitudMaxima(pos);

            // Vamos realizando las iteraciones del algoritmo de ordenación radixsort.
            for (int c = 1; c <= max_pos; c++){
                iteracionRadixsort(pos, c);
            }
        }

        if(neg.size() > 1){

            // Obtenemos el máximo de cifras de los números del vector de negativos.
            int max_neg = obtenerLongitudMaxima(neg);
            
            // Vamos realizando las iteraciones del algoritmo de ordenación radixsort.
            for (int c = 1; c <= max_neg; c++){
                iteracionRadixsort(neg, c);
            }
        }

        // Juntamos los negativos y positivos 
        v.clear();
        for (int i = neg.size() - 1; i >= 0; i--) {
            v.push_back('-' + neg[i]);
        }
    
        for (string num : pos) {
            v.push_back(num);
        }

    }

    
        
}


/****************************************************************************************************/



/****************************************************************************************************/
/* Implementación de funciones locales usadas en el algoritmo de ordenación radixsort implementado  */


/*
 * Precondición:    el número de elementos de v tiene que ser mayor que 0.
 * Postcondición:   devuelve el máximo de los números del vector.
 */
int obtenerNumeroMaximo(vector<int> v)
{
    int mx = v[0];
    for (int i: v){
        if (i > mx){
            mx = i;
        }
    }
    return mx;
}

/* 
 * Precondición:    el número de elementos de v tiene que ser mayor que 0.
 * Postcondición:   devuelve la longitud máxima de las cadenas del vector.
 */
int obtenerLongitudMaxima(vector<string> v)
{
    string mx = v[0];
    for (string elem: v){
        string aux = elem;
        if (aux.length() > mx.length()){
            mx = elem;
        }
    }
    return mx.length();
    
}

/* 
 * Precondición:    el número de elementos de v tiene que ser mayor que 0.
 * Postcondición:   ordena el vector v de forma ascendente según el valor de una 
 *                  cifra de los números del vector.
 *                  La cifra con la que ordenar en la iteración es igual al 
 *                  logaritmo en base 10 de exp.
 */
void iteracionRadixsort(vector<int>& v, int exp)
{
   
    // Obtenemos el número de elementos del vector.
    int n = v.size();

    // Generamos el vector donde guardaremos el vector ordenado tras la iteración
    vector<int> v_ordenado;
    for(int j = 0; j < n; j++){
        v_ordenado.push_back(0);
    }
  
    int i; // iterador de bucles
    int ocurrencias[10] = {0};  // vector donde guardamos las ocurrencias de cada posible
                                // valor de la cifra.
                                // Posibles valores: [-9,9] 
    
    // Acumulamos las ocurrencias de cada cifra.
    for (i = 0; i < n; i++){
        int index = (v[i] / exp) % 10;
        ocurrencias[(v[i] / exp) % 10]++;
        // (v[i] / exp) % 10 es igual que si seleccionasemos el valor de la cifra a coger del número.
    }
   
    
    // Hacemos que el vector ocurrencias pase a indicarnos las posiciones que deberían ocupar los números 
    // con cada valor de la cifra en esa iteración en el vector ordenado.
    for (i = 1; i < 10; i++){
        ocurrencias[i] += ocurrencias[i - 1];
    }

    // Creamos el vector ordenado
    for (i = n - 1; i >= 0; i--) {
        int index = (v[i] / exp) % 10;
        ocurrencias[index]--;
        v_ordenado[ocurrencias[(v[i] / exp) % 10]] = v[i];
    }

    // Hacemos que v pase a ser el vector ordenado.
    for (i = 0; i < n; i++){
        v[i] = v_ordenado[i];
    }
  
}

// /* 
//  * Precondición:    el número de elementos de v tiene que ser mayor que 0. 
//  * Postcondición:   ordena el vector v de forma ascendente según el valor de 
//  *                  cifra de los números del vector.
//  */
void iteracionRadixsort(vector<string>& v, int cifra)
{   
    // Obtenemos el número de elementos del vector.
    int n = v.size();
    

    // Generamos el vector donde guardaremos el vector ordenado tras la iteración
    vector<string> v_ordenado;
    for(int j = 0; j < n; j++){
        v_ordenado.push_back("");
    }

    int i;  // iterador de bucles
    int ocurrencias[10] = {0};  // vector donde guardamos las ocurrencias de cada posible
                                // valor de la cifra.
                                // Posibles valores: [0,9] 

    
    // Acumulamos las ocurrencias de cada cifra.
    for (i = 0; i < n; i++){
        
        // Obtenemos el número de cifras del número.
        int l = v[i].length();

        char c;
        
        // Si la cifra a buscar es mayor que la longitud de palabra, entonces la cifra es 0.
        if (l < cifra){
            c = '0';
        }
        // Sino, obtenemos el carácter que representa el valor de esa cifra.
        else{
            string saux = v[i];
            c = saux[l-cifra];
        }
        int numero = c - '0';   // Obtenemos el valor de la cifra del número a partir del carácter 
                                    // que lo representa.
        ocurrencias[numero]++;
        
        
    }

    // Hacemos que el vector ocurrencias pase a indicarnos las posiciones que deberían ocupar los números 
    // con cada valor de la cifra en esa iteración en el vector ordenado.
    for (i = 1; i < 10; i++){
        ocurrencias[i] += ocurrencias[i - 1];
    }

    // Creamos el vector ordenado
    for (i = n - 1; i >= 0; i--) {
        int l = v[i].length();
        string saux = v[i];
        char c;

        // Si la cifra a buscar es mayor que la longitud de palabra, entonces la cifra es 0.
        if (l < cifra){
            c = '0';
        }
        // Sino, obtenemos el carácter que representa el valor de esa cifra.
        else{
            string saux = v[i];
            c = saux[l-cifra];
        }
        int numero = c - '0';   // Obtenemos el valor de la cifra del número a partir del carácter 
                                // que lo representa.
        ocurrencias[numero]--;
        v_ordenado[ocurrencias[numero]] = v[i];
    }
    // Hacemos que v pase a ser el vector ordenado.
    for (i = 0; i < n; i++){
        v[i] = v_ordenado[i];
    }
}

/* 
 * Precondición:    
 * Postcondición:   almacena en neg los números negativos de original y en pos los 
 *                  números positivos de original. Tanto en neg como en pos los números 
 *                  se almacenan como positivos.
 */
void separarNegativosPositivos(const vector<int>& original, vector<int>& neg, vector<int>& pos){
    for (int num : original) {
        if (num < 0) {
            neg.push_back(abs(num)); 
        } else {
            pos.push_back(num); 
        }
    }
}

/* 
 * Precondición:    los elementos de original son cadenas que representan
 *                  números en formato entero.
 * Postcondición:   almacena en neg los números negativos de original y en pos los 
 *                  números positivos de original. Tanto en neg como en pos los números 
 *                  se almacenan como positivos.
 */
void separarNegativosPositivos(const vector<string>& original, vector<string>& neg, vector<string>& pos){
    for (string num : original) {
        if (num[0] == '-') {
            neg.push_back(num.substr(1)); // Eliminamos el primer caracter, el signo negativo
        } else {
            pos.push_back(num); 
        }
    }
}


/****************************************************************************************************/

