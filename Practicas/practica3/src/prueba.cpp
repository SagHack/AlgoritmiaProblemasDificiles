#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cassert>
#include "carretera.h"
#include "interseccion.h"
#include "leerMapa.h"
#include "bootstraps.h"

using namespace std;



int main(int argc, char *argv[]) {
    
    string ficheroEntrada;
    vector<Carretera> carreteras;
    vector<Interseccion> intersecciones;
    int n_simulaciones;
    int C,A,B; // C->Interseccion en al que vivo, A y B -> Interseccion de los almacenes de las dos mensajerias

    if(argc!=4) {
        cout << "Introduce el nombre del fichero de entrada <ficheroEntrada>, el número de simulaciones <n> y el límite de tiempo en minutos de una entrega <limiteTiempo>" << endl;
        cout << "Uso main <ficheroEntrada> <n> <limiteTiempo>" << endl;
        exit(1);
    }

    ficheroEntrada = argv[1];
    n_simulaciones = stoi(argv[2]);
    int limiteTiempo = stoi(argv[3]);
    
    // Comprobamos si se puede leer el ficheor correctamente
    if(!leerMapa(ficheroEntrada,carreteras,intersecciones,C,A,B)){
        cout << "Error al leer el fichero de entrada " << ficheroEntrada << endl;
        exit(1);
    }  

    float L_A,R_A; // Intervalo de confianza del 90% para el almacen A
    float L_B,R_B; // Intervalo de confianza del 90% para el almacen B
    int veces_no_entrega_paqueteA = 0,veces_no_entrega_paqueteB = 0; 
    
    cout << "Realizando simulaciones Almacen A\n";
    realizar_bootstraps(carreteras,intersecciones,C,A,n_simulaciones,L_A,R_A,veces_no_entrega_paqueteA,limiteTiempo); // Bootstraps para el almacen A
    cout << "Simulaciones Almacen A finalizadas\n\n";

    cout << "Realizando simulaciones Almacen B\n";
    realizar_bootstraps(carreteras,intersecciones,C,B,n_simulaciones,L_B,R_B,veces_no_entrega_paqueteB,limiteTiempo); // Bootstraps para el almacen B
    cout << "Simulaciones Almacen B finalizadas\n\n";

    cout << "Almacen A -> Paquetes entregados: " << n_simulaciones - veces_no_entrega_paqueteA << ". Paquetes no entregados: " << veces_no_entrega_paqueteA << endl;
    cout << "Almacen B -> Paquetes entregados: " << n_simulaciones - veces_no_entrega_paqueteB << ". Paquetes no entregados: " << veces_no_entrega_paqueteB << endl;
    cout << "Almacen A -> Intervalo del 90%: [" << L_A << ", " << R_A << "]" << endl;
    cout << "Almacen B -> Intervalo del 90%: [" << L_B << ", " << R_B << "]" << endl;

    

    return 0;
}
