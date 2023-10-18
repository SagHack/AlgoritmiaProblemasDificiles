/*
 * Fichero:   		quicksort.cpp
 * Autores: 		Diego García Aranda 820506
                    Simón Alonso Gutiérrez 821038
 * Fecha entrega:	18/10/2023
 * Comentarios:     Fichero que implementa las funciones que componen la función 
 *                  que ordena vectores de números mediante el algoritmo de ordenación
 *                  quicksort.
 */
#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include "quicksort.hpp"
using namespace std;


/****************************************************************************************************/
/* Predefinición de funciones locales usadas en el algoritmo de ordenación quicksort implementado   */


/*
 * Precondición:    0 <= inicio <= fin <= |v|-1.
 * Postcondición:   ordena el vector v entre los índices inicio y fin
                    de forma ascendente mediante el algoritmo de ordenación quicksort.
 */
void quicksortRec(vector<int>& v, int inicio, int fin);

/* 
 * Precondición:    0 <= inicio <= fin <= |v|-1.
 * Postcondición:   devuelve el índice, entre inicio y fin, del pivote elegido para particionar v,
                    es decir, deja v con los números menores que el pivote entre inicio y el índice
                    devuelto menos uno y con los números mayores o iguales que el pivote entre el
                    índice devuelto más uno y fin.
 */
int particion(vector<int>& v, int inicio, int fin);

/* 
 * Precondición:    0 <= inicio <= fin <= |v|-1.
 * Postcondición:   devuelve el índice del pivote del vector v según el número de componentes entre 
                    los índices inicio y fin:
                        Si (fin-inicio) < 2, devuelve el indice fin.
                        Si (fin-inicio) >= 2, se eligen tres índices aleatorios diferentes entre los 
                        índices inicio y fin y devuelve el índice cuyo valor es la mediana de entre
                        los valores de los tres índices.
 */
int elegirPivote(vector<int> v, int inicio, int fin);

/* 
 * Precondición:    
 * Postcondición:   devuelve un valor según cuál de los tres valores es la mediana de ellos:
                        1 si la mediana es primero
                        2 si la mediana es segundo
                        3 si la mediana es tercero
 */
int mediana(int primero, int segundo , int tercero);


/****************************************************************************************************/


/****************************************************************************************************/
/*                Implementación de las funciones de ordenación según algoritmo quicksort           */


/* 
 * Precondición:    
 * Postcondición:   ordena el vector v de forma ascendente 
 *                  mediante el algoritmo de ordenación quicksort.
 */
void quicksort(vector<int>& v){
    int n = v.size();
    if(n > 1){
        quicksortRec(v,0,n-1);
    }
}


/****************************************************************************************************/


/****************************************************************************************************/
/* Implementación de funciones locales usadas en el algoritmo de ordenación radixsort implementado  */


/*
 * Precondición:    0 <= inicio <= fin <= |v|-1.
 * Postcondición:   ordena el vector v entre los índices inicio y fin
                    de forma ascendente mediante el algoritmo de ordenación quicksort.
 */
void quicksortRec(vector<int>& v, int inicio, int fin){

    if(fin > inicio){

        // Deja los valores menores que v[pPivote] desde inicio a pPivote-1 y
        // los valores mayores o iguales desde pPivote+1 a fin.
        int pPivote = particion(v,inicio,fin);

        // ordenamos los valores menores de v[pPivote]
        quicksortRec(v,inicio,pPivote-1);

        // ordenamos los valores mayores de v[pPivote]
        quicksortRec(v,pPivote+1,fin);
    }
}

/* 
 * Precondición:    0 <= inicio <= fin <= |v|-1.
 * Postcondición:   devuelve el índice, entre inicio y fin, del pivote elegido para particionar v,
                    es decir, deja v con los números menores que el pivote entre inicio y el índice
                    devuelto menos uno y con los números mayores o iguales que el pivote entre el
                    índice devuelto más uno y fin.
 */
int particion(vector<int>& v, int inicio, int fin){

    int pivote = elegirPivote(v,inicio,fin);
    int numPivote = v[pivote];
    int index = inicio;
    for(int i = inicio; i <= fin; i++){
        
        if(i != pivote && v[i] < numPivote){
            if(index == pivote) pivote = i;
            swap(v[i],v[index++]);
        }
    }
    if(index != pivote) swap(v[index],v[pivote]);
    return index;

}

/* 
 * Precondición:    0 <= inicio <= fin <= |v|-1.
 * Postcondición:   devuelve el índice del pivote del vector v según el número de componentes entre 
                    los índices inicio y fin:
                        Si (fin-inicio) < 2, devuelve el indice fin.
                        Si (fin-inicio) >= 2, se eligen tres índices aleatorios diferentes entre los 
                        índices inicio y fin y devuelve el índice cuyo valor es la mediana de entre
                        los valores de los tres índices.
 */
int elegirPivote(vector<int> v, int inicio, int fin){

    int n = v.size();

    if((fin - inicio) >= 2){
        int countNums = 0;
        int indices[3] = {-1,-1,-1};
        srand(time(nullptr));

        while(countNums < 3){
            int random = rand() % (fin - inicio + 1) + inicio;
            if(indices[0] == random || indices[1] == random || indices[2] == random) continue;
            else{
                indices[countNums++] = random;
            }
        }
        int m = mediana(v[indices[0]],v[indices[1]],v[indices[2]]);
        return indices[m-1];
    }
    return fin;
}

/* 
 * Precondición:    
 * Postcondición:   devuelve un valor según cuál de los tres valores es la mediana de ellos:
                        1 si la mediana es primero
                        2 si la mediana es segundo
                        3 si la mediana es tercero
 */
int mediana(int primero, int segundo , int tercero){
    if(primero >= segundo){
        if(segundo >= tercero){
            return 2;
        }
        return (primero >= tercero) ? 3 : 1;
    }
    else{
        if(primero >= tercero){
            return 1;
        }
        return (segundo >= tercero) ? 3 : 2;
    }
}


/****************************************************************************************************/