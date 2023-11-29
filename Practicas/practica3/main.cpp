#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cassert>
#include "carretera.h"
#include "interseccion.h"
#include "leerMapa.cpp"

using namespace std;




// Obtiene la media de tiempo de realizar n simulaciones.
float  media_tiempo_simulaciones(const vector<Carretera>& carreteras, const vector<Interseccion>& intersecciones, int IC, int IA,int n){
    float tiempo_total = 0;
    for(int i =0;i<n;i++){
        // Almacen A
        tiempo_total += entregarPaquete(carreteras,intersecciones,IC,IA);
    }
    return tiempo_total/n;
}


bootstraps(){
    vector<float> 
}



int main(int argc, char *argv[]) {
    
    string ficheroEntrada = argv[1];
    vector<Carretera> carreteras;
    vector<Interseccion> intersecciones;

    if(argc!=2) {
        cout << "Introduce el nombre del fichero de entrada" << endl;
        cout << "Uso main <ficheroEntrada> " << endl;
        exit(1);
    }
    // Comprobamos si se puede leer el ficheor correctamente
    if(!leerMapa(ficheroEntrada,carreteras,intersecciones)){
        cout << "Error al leer el fichero de entrada " << ficheroEntrada << endl;
        exit(1);
    }  






    return 0;
}
