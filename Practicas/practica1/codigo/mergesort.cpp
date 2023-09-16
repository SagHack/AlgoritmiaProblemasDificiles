#include <iostream>
#include <vector>

using namespace std;


void merge(vector<int>& v,int izq,int med,int der){
    vector<int> v_izq,v_der;
    // Copiamos los elementos de la mitad izquierda al vector izquierda
    for(int i =izq;i<=med;i++){
        v_izq.push_back(v[i]);
    }
    // Copiamos los elementos de la mitad derecha al vector derecha
    for(int i=med+1;i<=der;i++){
        v_der.push_back(v[i]);
    }
    
    // Obtenemos el tamaño de ambos vectores
    int size_izq = v_izq.size();
    int size_der = v_der.size();


    int i=0,j=0,k=izq;
    while(i< size_izq && j < size_der){
        if(v_izq[i] <= v_der[j]){ //izq < der entonces añado el contenido de v_izq al vector
            v[k] = v_izq[i];
            k++;i++; // Incremento el indice global(k) y el del vector izquierdo(i)
        }else{  
            v[k] = v_der[j];
            k++;j++; // Incremento el indice global(k) y el del vector derecho(j)
        }
    }
    
    // Si aun quedaban elementos restantes los añado al vector en orden
    while(i < size_izq){
        v[k] = v_izq[i];
        k++;i++;
    }
    while(j < size_der){
        v[k] = v_der[j];
        k++;j++;
    }



}

void mergeSort(vector<int>& v,int izq, int der){
    if(izq < der){
        int med = izq + (der - izq)/2;
        // Ordenamos recursivamente las dos primeras mitades
        mergeSort(v,izq,med);
        mergeSort(v,med+1,der);
        //Juntamos las dos mitades
        merge(v,izq,med,der);
    }
}






int main() {
    std::vector<int> arr = {12, 11, 13, 5, 6, 7};
    int n = arr.size();

    std::cout << "Original array: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    mergeSort(arr, 0, n - 1);

    std::cout << "Sorted array: ";
    for (int num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}