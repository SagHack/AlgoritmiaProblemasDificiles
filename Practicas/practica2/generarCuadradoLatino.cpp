#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>


#include <random>
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

bool generarCuadradoLatinoCompleto(vector<string>& CL, int n){
    vector<PosiblesValores> valoresCL(n*n,PosiblesValores(n));
    srand(time(NULL));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            //cout << "Celda: (" << i+1 << "," << j+1 << ")\n";
            PosiblesValores aux = valoresCL[i*n+j];
            int maxVals = aux.v.size();
            if(maxVals == 0) return false;
            int indice_aleatorio = rand() % maxVals;
            int num = aux.v[indice_aleatorio];
            //cout << "\tIndice: " << indice_aleatorio << ", Num: " << num << endl;
            CL[i*n+j] = to_string(num);
            for(int k = i+1; k < n; k++){
                //cout << "\tBorrar valor: " << num << " en celda: (" << k+1 << "," << j+1 << ")\n";
                borrarPosibleValor(valoresCL[k*n+j],num);
            }
            
            for(int k = j; k < n; k++){
                //cout << "\tBorrar valor: " << num << " en celda: (" << i+1 << "," << k+1 << ")\n";
                borrarPosibleValor(valoresCL[i*n+k],num);
            }

        }
    }
    return true;

}


void generarCuadradoLatinoParcial(vector<string>& CL,const int n,const double porcentaje){
    
    int fila = 0, columna = 0, asteriscos = ((n * n)*porcentaje) / 100.0;
    srand(time(NULL));

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

void mostrarCL(const vector<string>& CL, int n) {
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cout << CL[i*n+j] << " ";
        }
        cout << endl;
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
    while(!generarCuadradoLatinoCompleto(CL,n));
    generarCuadradoLatinoParcial(CL,n,p);
    escribirCuadradoLatinoParcial(CL,ficheroSalida,n);
}