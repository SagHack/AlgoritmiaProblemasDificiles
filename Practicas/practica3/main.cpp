#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cassert>
#include "carretera.h"
#include "interseccion.h"
using namespace std;

bool comprobar_numero_intersecciones(int N){
    return 3 <= N && N <= 900;
}

bool comprobar_numero_carreteras(int N,int M){
    return 2 <= M && M <= N * (N - 1) / 2;
}

bool comprobar_interseccion_vives(int C,int N){
    return 0 <= C && C < N;
}


bool comprobar_almacen_A(int A,int N){
    return 0 <= A && A < N;
}

bool comprobar_almacen_B(int B,int N){
    return 0 <= B && B < N;
}

bool comprobar_interseccion(int i,int N){
    return 3<=i && i<N;
}






int main() {
    ifstream archivo("entrada.txt");

    if (!archivo) {
        cerr << "No se pudo abrir el archivo." << endl;
        return 1;
    }

    int N, M, C, A, B;

    // Lee la primera línea del archivo
    if (archivo >> N >> M >> C >> A >> B) {
        // Realiza las validaciones según las restricciones dadas
        if(!comprobar_numero_intersecciones(N)){
           exit(1);
        }
        if(!comprobar_numero_carreteras(N,M)){
            exit(1);
        }
        
        if(!comprobar_interseccion_vives(C,N)){
            exit(1);
        }

        if(!comprobar_almacen_A(A,N)){
            exit(1);
        }

        if(comprobar_almacen_B(B,N)){
            exit(1);
        }
        
    } else {
        cerr << "Error al leer la primera línea del archivo." << endl;
        return 1;
    }
    
    // Inicializamos las carreteras e intersecciones
    vector<Carretera> v_carreteras(M,Carretera());
    vector<Interseccion> v_interseccion(N,Interseccion());

    int u,v,tuv;
    float puv,pvu;
    int numC = 0,nuI = 0;
     if (archivo >> u >> v >> tuv >> puv >> pvu) {
        if(!comprobar_interseccion(u)){
            exit(1);
        }
        if(!comprobar_interseccion(v)){
            exit(1);
        }

        // Linea correcta
        
        v_carreteras[numC].u = u;
        v_carreteras[numC].v = v;
        v_carreteras[numC].tuv = tuv;
        
        int size = v_interseccion[u].salidas.size();
        v_interseccion[u].salidas.push_back(numC);
        if(size == 0){ 
            v_interseccion[u].limitesP.push_back(puv);
        }   
        else{
            v_interseccion[u].limitesP.push_back(v_interseccion[u].limitesP[size-1] + puv);
        }    

        size = v_interseccion[v].salidas.size();
        v_interseccion[v].salidas.push_back(numC);
        if(size == 0){ 
            v_interseccion[v].limitesP.push_back(puv);
        }   
        else{
            v_interseccion[v].limitesP.push_back(v_interseccion[v].limitesP[size-1] + puv);
        }    

     }







    // Resto del código

    archivo.close();
    return 0;
}
