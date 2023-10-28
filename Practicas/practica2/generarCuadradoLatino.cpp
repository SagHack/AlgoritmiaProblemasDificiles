#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <random>
#include <algorithm>
using namespace std;




struct PosiblesValores{
    vector<int> v;
    PosiblesValores(int n) {
        for(int i = 0; i < n ; i++){
            v.push_back(i+1);
        }
    }
};


void mostrarVL(const PosiblesValores& VL) {
    cout << "\tValores: ";
    for(const auto& pv : VL.v){
        cout << pv << " ";
    }
    cout << endl;
}

void borrarPosibleValorRec(PosiblesValores& pv, int valor, int inicio, int final){
    //cout << "\t\t\tBorrar valor: " << valor << " inicio: " << inicio << " final: " << final << endl;
    if(inicio == final){
        if(pv.v[inicio] == valor){
            //cout << "\t\t\t\tBorrar número: " << *(pv.v.begin() + inicio) << endl;
            pv.v.erase(pv.v.begin() + inicio);
        }
    }
    else{
        int medio = (inicio+final)/2;
        //cout << "\t\t\t\tMedio: " << medio << " numero: " << pv.v[medio] << endl;
        if(pv.v[medio] == valor){
            //cout << "\t\t\t\tBorrar número: " << *(pv.v.begin() + medio) << endl;
            pv.v.erase(pv.v.begin() + medio);
        }
        else if(valor < pv.v[medio]){
            if(inicio < medio) borrarPosibleValorRec(pv,valor,inicio,medio-1);
        }
        else{
            borrarPosibleValorRec(pv,valor,medio+1,final); 
        }
    }
}

bool borrarPosibleValor(PosiblesValores& pv,int valor){
    int n = pv.v.size();
    if(n <= 0){
        return false;
    }
    borrarPosibleValorRec(pv,valor,0,n-1);
    return true;
}

void generarFilaAleatoria(vector<int>& aux,int n, mt19937& gen){
    shuffle(aux.begin(),aux.end(),gen);
    
}

bool filaValida(vector<string>& CL,vector<int>& fila,vector<unsigned long long>& valoresPosibles,int n, int nfila){
    vector<unsigned long long> aux = valoresPosibles;
    for(int i = 0; i < n; i++){
        int k = fila[i];
        CL[nfila*n+i] = to_string(k);
        unsigned long long mascara = (unsigned long long) (1) << (k-1);
        
        if(aux[i] & mascara){
            aux[i] &= ~mascara;
        }
        else{
           // cout << "Columna : " << i << " Valores posibles : " << aux[i] << " mascara " << mascara << endl;
            return false;
        }
    }
    valoresPosibles = aux;
    return true;
}

void mostrarCL(const vector<string>& CL, int n) {
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cout << CL[i*n+j] << " ";
        }
        cout << endl;
    }
}
bool noEsta(vector<int>& v, int s){
    int n = v.size();
    for(int i = 0; i < n; i++){
        if(v[i] == s) return false;
    }
    return true;
}

void ponerAlante(vector<int>& v, int s){
    int n = v.size(), elem;
    bool esta = false;
    for(int i = 0; i < n && !esta; i++){
        if(v[i] == s){
            elem = i;
            esta = true;
        }
    }
    if(esta){
        for(int i = 0; i < elem; i++){ 
            swap(v[i],v[elem]);
        } 
    }
    else{
        v.push_back(s);
    }
}


bool generarCuadradoLatinoCompleto(vector<string>& CL, int n){
    
    vector<int> aux,fila;
    vector<unsigned long long> valoresPosiblesColumna(n,(1<<n)-1);
    bool valido = false;
    int repeticiones = 0;
    int filas;

    for(int i = 0; i < n; i++){
        fila.push_back(i+1);
    }
    while(1){
        retry:
        vector<unsigned long long> valoresColumnas = valoresPosiblesColumna;
        filas = 0;
        for(int i = 0; i < n/2; i++){
            vector<unsigned long long> valoresAux = valoresColumnas;
            random_device rd;
            mt19937 generador(rd());
            int nrep = 0;
            //cout << "Fila : " << i << " " << nrep << endl;
            //cout << endl;
            aux = fila;
            do{
                //cout << "Fila : " << i << " " << nrep << endl;
                //cout << "Generar fila" << endl;
                generarFilaAleatoria(aux,n,generador);

                //cout << "Fila generada" << endl;
                if(nrep++ == 100000){
                    //cout << "retry fila " << i << "\n";
                    if(repeticiones++ > 20) goto fin;
                    goto retry;
                }
            }
            while(!filaValida(CL,aux,valoresAux,n,i));
            valoresColumnas = valoresAux;
            filas++;

        }
        fin:
        valoresPosiblesColumna = valoresColumnas;
        break;
    }

    random_device rd;
    mt19937 generador(rd());
    uniform_int_distribution<int> dis(0,n-1);

    mostrarCL(CL,n);
    for(int i = 0; i < n; i++){
        cout << valoresPosiblesColumna[i] << endl;
    }
    bool fallo = false;
    for(int i = filas; i < n; i++){
        vector<int> fallidos;
        retry2:
        cout << endl;
        int j,recorridos = 0,nsize=fallidos.size();
        if(!fallo){
            j = dis(generador);
        }
        vector<unsigned long long> valoresAuxColumna = valoresPosiblesColumna;
        unsigned long long valoresAuxFila = ((unsigned long long) (1) << n)-1;

        for(;recorridos < n;){
            if(recorridos < nsize){
                j = fallidos[recorridos++];
            }
            else{
                if(++j == n){
                    j = 0;
                }
                if(noEsta(fallidos,j)){
                    recorridos++;
                }
                else continue;

            }
            unsigned long long kaux = valoresAuxColumna[j] & valoresAuxFila;
            if(kaux == 0){
                cout << "Go to Celda : (" << i+1 << "," << j+1 << "), kaux: " << kaux << endl;
                ponerAlante(fallidos,j);
                goto retry2;
            }
            int k = log2(static_cast<double>(kaux));
            cout << "Celda : (" << i+1 << "," << j+1 << "), valor : " << k+1 << ", kaux: " << kaux << endl;
            
            unsigned long long mascara = (unsigned long long) (1) << (k);
            valoresAuxColumna[j] &= ~mascara;
            valoresAuxFila &= ~mascara;
            CL[i*n+j] = to_string(k+1);
        }
        fallo = false;
        valoresPosiblesColumna = valoresAuxColumna;
        
    }
    return true;

}




void generarCuadradoLatinoParcial(vector<string>& CL,const int n,const double porcentaje){
    
    int fila = 0, columna = 0, asteriscos = ((n * n)*porcentaje) / 100.0;
    srand(time(NULL));
    cout << "cuadrado latina parcial" << endl;
    for(int i = 0; i < asteriscos; i++){
        fila = rand() % n;
        columna = rand() % n;
        CL[fila*n + columna] = "*";
    }

}

void escribirCuadradoLatinoParcial(const vector<string>& CL,const string ficheroSalida,const int n){
    ofstream salida(ficheroSalida);
    if(salida.is_open()){

        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                salida << CL[i*n+j] << " ";
            }
            salida << endl;
        }   

    }
}






int main(int argc, char* argv[]) {

    if(argc != 4){
        exit(1);
    }

    string ficheroSalida = argv[1];
    int n = stoi(argv[2]);
    double p = stod(argv[3]);
    vector<string> CL(n*n,"");
    int ncuadrados = 0;

    while(!generarCuadradoLatinoCompleto(CL,n)){
        cout << "Generar otro cuadrado " << ncuadrados++ << endl;
    }
    generarCuadradoLatinoParcial(CL,n,p);
    escribirCuadradoLatinoParcial(CL,ficheroSalida,n);
}

