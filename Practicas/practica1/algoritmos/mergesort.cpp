/*
 * Fichero:   		mergesort.cpp
 * Autores: 		Diego García Aranda 820506
                    Simón Alonso Gutiérrez 821038
 * Fecha entrega:	18/10/2023
 * Comentarios:     Fichero que implementa las funciones que componen la función 
 *                  que ordena vectores de números mediante el algoritmo de ordenación
 *                  mergesort.
 */
#include "mergesort.hpp"

using namespace std;


/****************************************************************************************************/
/* Predefinición de funciones locales usadas en el algoritmo de ordenación quicksort implementado   */



/* 
 * Precondición:    0 <= izq <= der <= |v|-1, med = (izq+der)/2
 * Postcondición:   reordena las dos particiones ordenadas del vector v. La primera particion va entre
 *                  los índices izq y med y la segunda entre los índices med+1 y der.
 */
void merge(vector<int>& v,int izq,int med,int der);


/* 
 * Precondición:    0 <= izq <= der <= |v|-1
 * Postcondición:   ordena el vector v entre los índices inicio y fin
                    de forma ascendente mediante el algoritmo de ordenación mergesort.
 */
void mergesortRec(vector<int>& v,int izq, int der);


/****************************************************************************************************/


/****************************************************************************************************/
/*                Implementación de las funciones de ordenación según algoritmo mergesort           */


/* 
 * Precondición:
 * Postcondición:   ordena el vector v de forma ascendente 
 *                  mediante el algoritmo de ordenación mergesort.
 */
void mergesort(vector<int>& v){
    int n = v.size();
    if(n > 1){
        mergesortRec(v,0,n-1);
    }
}


/****************************************************************************************************/


/****************************************************************************************************/
/* Implementación de funciones locales usadas en el algoritmo de ordenación mergesort implementado  */


/* 
 * Precondición:    0 <= izq <= der <= |v|-1, med = (izq+der)/2
 * Postcondición:   reordena las dos particiones ordenadas del vector v. La primera particion va entre
 *                  los índices izq y med y la segunda entre los índices med+1 y der.
 */
void merge(vector<int>& v,int izq,int med,int der){
    
    // Copiamos los elementos de v
    vector<int> aux = v;

    int i=izq,j=med+1,k=izq;

    while(i<=med && j <= der){
        // comparamos un elemento de cada partición
        if(aux[i] <= aux[j]){ // Si el elemento de la partición izquierda es menor
            v[k] = aux[i];
            k++;i++; // Incremento el indice global(k) y el de la partición izquierda(i)
        }
        else{  // Si el elemento de la partición derecha es menor
            v[k] = aux[j];
            k++;j++; // Incremento el indice global(k) y el de la partición derecha(j)
        }
    }
    
    // Si aun quedaban elementos restantes los añado al vector en orden
    
    while(i <= med){
        v[k] = aux[i];
        k++;i++;
    }
    while(j <= der){
        v[k] = aux[j];
        k++;j++;
    }


}


/* 
 * Precondición:    0 <= izq <= der <= |v|-1
 * Postcondición:   ordena el vector v entre los índices inicio y fin
                    de forma ascendente mediante el algoritmo de ordenación mergesort.
 */
void mergesortRec(vector<int>& v,int izq, int der){
    if(izq < der){
        int med = (izq+der)/2;

        // Se ordena v entre los índices izq y med
        mergesortRec(v,izq,med);

        // Se ordena v entre los índices med+1 y der
        mergesortRec(v,med+1,der);
        
        //Juntamos las dos mitades
        merge(v,izq,med,der);
    }
}


/****************************************************************************************************/