#include <iostream>
#include <cstdlib>
#include <string>
#include "quicksort.hpp"
using namespace std;

/****************************************************************************************************/
/* Predefinición de funciones locales usadas en el algoritmo de ordenación quicksort implementado   */


/* CAMBIAR
 * Precondición:    el número de elementos de v tiene que ser mayor que 0.
 * Postcondición:   devuelve el máximo de los números del vector.
 */
void quicksortRec(vector<int>& v, int inicio, int final);

/* 
 * Precondición:    el número de elementos de v tiene que ser mayor que 0.
 * Postcondición:   devuelve la longitud máxima de las cadenas del vector.
 */

/* 
 * Precondición:    el número de elementos de v tiene que ser mayor que 0.
 * Postcondición:   ordena el vector v de forma ascendente según el valor de una 
 *                  cifra de los números del vector.
 *                  La cifra con la que ordenar en la iteración es igual al 
 *                  logaritmo en base 10 de exp.
 */

/* 
 * Precondición:    el número de elementos de v tiene que ser mayor que 0 y los 
 *                  elementos del vector v son cadenas que representan
 *                  números en formato entero.
 * Postcondición:   ordena el vector v de forma ascendente según el valor de la 
 *                  cifra de los números del vector.
 */


/****************************************************************************************************/


/****************************************************************************************************/
/*                Implementación de las funciones de ordenación según algoritmo quicksort           */


/* 
 * Precondición:
 * Postcondición:   ordena el vector v de forma ascendente 
 *                  mediante el algoritmo de ordenación quicksort.
 */
void quicksort(vector<int>& v)
{
    int n = v.size();
    if(n > 1){
        quicksortRec(v,0,n-1);
    }
        
}


int mediana(int primero, int segundo , int tercero){
    if(primero >= segundo){
        if(segundo >= tercero){
            return 3;
        }
        else{
            return 2;
        }
    }
    else{
        if(primero >= tercero){
            return 3;
        }
        else{
            return 1;
        }
    }
}

int elegirPivote(vector<int> v, int inicio, int final){

    int n = v.size();

    if((final - inicio) >= 3){
        int countNums = 0;
        int nums[3] = {-1,-1,-1};
        srand(time(nullptr));

        while(countNums < 3){
            int random = rand() % (final - inicio + 1) + inicio;
            if(nums[0] == random || nums[1] == random || nums[2] == random) continue;
            else nums[countNums++] = random;
        }

        int m = mediana(v[nums[0]],v[nums[1]],v[nums[2]]);
        return nums[m-1];
        
    }
    else{
        return final;
    }
}


int particion(vector<int>& v, int inicio, int final){


    int pivote = elegirPivote(v,inicio,final);
    int nPivote = v[pivote];

    int index = inicio;
    for(int i = inicio; i < final; i++){
        if(v[i] < nPivote) swap(v[i],v[index++]);
    }
    swap(v[index],v[pivote]);
    return index;

}


void quicksortRec(vector<int>& v, int inicio, int final){
    if(final > inicio){
        int pPivote = particion(v,inicio,final);
        quicksortRec(v,inicio,pPivote-1);
        quicksortRec(v,pPivote+1,final);
    }
}