#include "leerMapa.h"

/* 
 * Precondición:    
 * Postcondición:   devuelve MIN_INTERSECCIONES <= N <= MAX_INTERSECCIONES
 */
bool comprobar_numero_intersecciones(int N){
    return MIN_INTERSECCIONES <= N && N <= MAX_INTERSECCIONES;
}

/* 
 * Precondición:    
 * Postcondición:   devuelve N/2 <= M <= N*(N-1)/2
 */
bool comprobar_numero_carreteras(int N,int M){
    return N/2 <= M && M <= N * (N - 1) / 2;
}

/* 
 * Precondición:    
 * Postcondición:   devuelve 0 <= I < N
 */
bool comprobar_interseccion(int I,int N){
    return 0 <= I && I < N;
}



/* 
 * Precondición:    
 * Postcondición:   Si el fichero <ficheroEntrada> tiene el formato correcto y cumple todas las condiciones devolverá True:
 *                  carreteras = Todas las carreteras
 *                  intersecciones = Todas las intersecciones 
 *                  C = Interseccion en la que vivo
 *                  A = Interseccion del primer almacen
 *                  B = Interseccion del segundo almacen
 *                  En caso de no tener el formato correcto, o no cumplir alguna de las condiciones devolverá False.
 */
bool leerMapa(const string ficheroEntrada,vector<Carretera>& carreteras, vector<Interseccion>& intersecciones,int& C,int& A,int& B){

    ifstream archivo(ficheroEntrada);
    if (!archivo) {
        cerr << "No se pudo abrir el archivo " << ficheroEntrada << "." << endl;
        return false;
    } 

    int N, M;

    // Lee la primera línea del archivo
    if (archivo >> N >> M >> C >> A >> B) {
        // Realiza las validaciones según las restricciones dadas
        if(!comprobar_numero_intersecciones(N)){
            cerr << "Número de intersecciones no válido. " << MIN_INTERSECCIONES << " <= nº intersecciones <= " << MAX_INTERSECCIONES << ".\n";
            return false;
        }
        if(!comprobar_numero_carreteras(N,M)){
            cerr << "Número de carreteras no válido. " << N/2 << " <= nº carreteras <= " << N*(N-1)/2 << ".\n";
            return false;
        }
        
        if(!comprobar_interseccion(C,N)){
            cerr << "Intersección del cliente no válida. 0 <= intersección cliente < " << N << ".\n";
            return false;
        }

        if(!comprobar_interseccion(A,N)){
            cerr << "Intersección del almacen A no válida. 0 <= intersección almacén A < " << N << ".\n";
            return false;
        }

        if(!comprobar_interseccion(B,N)){
            cerr << "Intersección del almacen B no válida. 0 <= intersección almacén B < " << N << ".\n";
            return false;
        }
        
    } else {
        cerr << "Error al leer la primera línea del archivo." << endl;
        return false;
    }

    carreteras = vector<Carretera>(M,Carretera());
    intersecciones = vector<Interseccion>(N,Interseccion());
    int u,v,tuv;
    float puv,pvu;
    int numC = 0, numI = 0;

    while(archivo >> u >> v >> tuv >> puv >> pvu){

        if(!comprobar_interseccion(u,N)){
            cerr << "Intersección u de la carretera " <<u << " " << numC << " no válida. 0 <= intersección u < " << N << ".\n";
            return false;
        }
        if(!comprobar_interseccion(v,N)){
            cerr << "Intersección v de la carretera " << v  << " " << numC << " no válida. 0 <= intersección v < " << N << ".\n";
            return false;
        }

        if(u == v){
            cerr << "Carretera  " << numC << " no válida. Para que sea válida, intersección u != intersección v. < " << N << ".\n";
            return false;
        }



        // La linea leída es válida
        
        carreteras[numC].u = u;
        carreteras[numC].v = v;
        carreteras[numC].tuv = tuv;
        
        int size = intersecciones[u].salidas.size();
        intersecciones[u].salidas.push_back(numC);
        if(size == 0){ 
            intersecciones[u].limitesP.push_back(puv);
            numI++;
        }   
        else{
            float nuevoLimite = intersecciones[u].limitesP[size-1] + puv;
            intersecciones[u].limitesP.push_back(nuevoLimite);
        } 


        size = intersecciones[v].salidas.size();
        intersecciones[v].salidas.push_back(numC);
        if(size == 0){ 
            intersecciones[v].limitesP.push_back(pvu);
            numI++;
        }   
        else{
            float nuevoLimite = intersecciones[v].limitesP[size-1] + pvu;
            intersecciones[v].limitesP.push_back(nuevoLimite);
        }
        numC++;
    }

    if(numI != N){
        cerr << "En el fichero no hay realmente " << N << " intersecciones.\n";
        return false;
    }

    if(numC != M){
        cerr << "En el fichero no hay realmente " << M << " carreteras.\n";
        return false;
    }

    for(int i = 0; i < N; i++){
        int size = intersecciones[i].limitesP.size();
        float limiteSuperiorP = intersecciones[i].limitesP[size-1];
        if(limiteSuperiorP != 1.0f){
            cerr << "La suma de las probabilidades de las posibles salidas de la intersección " << i << " no es 1.\n";
            return false;
        }
    }
    archivo.close();
    return true;
}