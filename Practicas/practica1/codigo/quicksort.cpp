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

 void imprimirVector(vector<int>& v, int inicio, int fin){
    //cout  << "Vector: ";
    for(int i = inicio; i <= fin; i++){
        //cout  << v[i] << " ";
    }
}
void quicksort(vector<int>& v)
{
    
    int n = v.size();
    //cout   << "\nEmpiezo quicksort\nTamaño vector : " << n << "\n\n";
    if(n > 1){
        imprimirVector(v,0,n-1);
        //cout  << endl;
        quicksortRec(v,0,n-1);
    }
        
}


int mediana(int primero, int segundo , int tercero){
    if(primero >= segundo){
        if(segundo >= tercero){
            return 2;
        }
        else {
            return (primero >= tercero) ? 3 : 1;
        }
    }
    else{
        if(primero >= tercero){
            return 1;
        }
        else{
            return (segundo >= tercero) ? 3 : 2;
        }
    }
}

int elegirPivote(vector<int> v, int inicio, int fin){

    int n = v.size();

    if((fin - inicio) >= 3){
        int countNums = 0;
        int nums[3] = {-1,-1,-1};
        srand(time(nullptr));

        while(countNums < 3){
            int random = rand() % (fin - inicio + 1) + inicio;
            if(nums[0] == random || nums[1] == random || nums[2] == random) continue;
            else{
                nums[countNums++] = random;
                //cout   << "\t\t\tNumero random : " << random <<  " num : " << v[random] << endl;
            }
        }

        int m = mediana(v[nums[0]],v[nums[1]],v[nums[2]]);
        //cout   << "\t\t\tElegir Pivote. Inicio : " << inicio << ". Fin : " << fin << ". Pivote : " << nums[m-1] << endl;
        return nums[m-1];
        
    }
    else{
        //cout   << "\t\t\tElegir Pivote. Inicio : " << inicio << ". Fin : " << fin << ". Pivote : " << fin << endl;
        return fin;
    }
}

int particion(vector<int>& v, int inicio, int fin){

    //cout   << "\t\tParticion. Inicio : " << inicio << ". Fin : " << fin << endl;
    int pivote = elegirPivote(v,inicio,fin);
    int nPivote = v[pivote];
    //cout  << "\t\tPivote: " << pivote << ". Npivote : " << nPivote << endl; 
    //cout  << "\t\tAntes: "; 
    imprimirVector(v,inicio,fin); 
    //cout  << endl;
    int index = inicio;
    for(int i = inicio; i <= fin; i++){
        
        if(i != pivote && v[i] < nPivote){
            if(index == pivote) pivote = i;
            //cout  << "\t\t\tAntes: "; 
            imprimirVector(v,inicio,fin); 
            //cout  << endl;
            swap(v[i],v[index++]);
            //cout  << "\t\t\tDespues: "; 
            imprimirVector(v,inicio,fin); 
            //cout  << endl;
        }
    }
    if(index != pivote) swap(v[index],v[pivote]);
    //cout  << "\t\tDespues: "; 
    imprimirVector(v,inicio,fin); 
    //cout  << endl;
    return index;

}


void quicksortRec(vector<int>& v, int inicio, int fin){
    if(fin > inicio){
        //cout   << "\tIteración quicksortRec. Inicio : " << inicio << ". Fin : " << fin << endl;
        int pPivote = particion(v,inicio,fin);
        //cout   << "\tPivote iteración: " << pPivote << "\n\n";
        
        quicksortRec(v,inicio,pPivote-1);
        quicksortRec(v,pPivote+1,fin);
    }
}
